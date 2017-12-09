JSMpeg.Decoder.MP2Audio = (function(){ "use strict";

// Based on kjmp2 by Martin J. Fiedler
// http://keyj.emphy.de/kjmp2/

var MP2 = function(options) {
	JSMpeg.Decoder.Base.call(this, options);

	var bufferSize = options.audioBufferSize || 128*1024;
	var bufferMode = options.streaming
		? JSMpeg.BitBuffer.MODE.EVICT
		: JSMpeg.BitBuffer.MODE.EXPAND;

	this.bits = new JSMpeg.BitBuffer(bufferSize, bufferMode);

	this.left = new Float32Array(1152);
	this.right = new Float32Array(1152);
	this.sampleRate = 44100;
	
	this.D = new Float32Array(1024);
	this.D.set(MP2.SYNTHESIS_WINDOW, 0);
	this.D.set(MP2.SYNTHESIS_WINDOW, 512);
	this.V = new Float32Array(1024);
	this.U = new Int32Array(32);
	this.VPos = 0;

	this.allocation = [new Array(32), new Array(32)];
	this.scaleFactorInfo = [new Uint8Array(32), new Uint8Array(32)];
	this.scaleFactor = [new Array(32), new Array(32)];
	this.sample = [new Array(32), new Array(32)];
	
	for (var j = 0; j < 2; j++) {
		for (var i = 0; i < 32; i++) {
			this.scaleFactor[j][i] = [0, 0, 0];
			this.sample[j][i] = [0, 0, 0];
		}
	}
};

MP2.prototype = Object.create(JSMpeg.Decoder.Base.prototype);
MP2.prototype.constructor = MP2;

MP2.prototype.decode = function() {
	var pos = this.bits.index >> 3;
	if (pos >= this.bits.byteLength) {
		return false;
	}

	var decoded = this.decodeFrame(this.left, this.right);
	this.bits.index = (pos + decoded) << 3;

	if (!decoded) {
		return false;
	}

	if (this.destination) {
		this.destination.play(this.sampleRate, this.left, this.right);
	}

	this.advanceDecodedTime(this.left.length / this.sampleRate);
	return true;
};

MP2.prototype.getCurrentTime = function() {
	var enqueuedTime = this.destination ? this.destination.enqueuedTime : 0;
	return this.decodedTime - enqueuedTime;
};

MP2.prototype.decodeFrame = function(left, right) {
	// Check for valid header: syncword OK, MPEG-Audio Layer 2
	var sync = this.bits.read(11),
		version = this.bits.read(2),
		layer = this.bits.read(2),
		hasCRC = !this.bits.read(1);

	if (
		sync !== MP2.FRAME_SYNC ||
		version !== MP2.VERSION.MPEG_1 ||
		layer !== MP2.LAYER.II
	) {
		return 0; // Invalid header or unsupported version
	}

	var bitrateIndex = this.bits.read(4) - 1;
	if (bitrateIndex > 13) {
		return 0;  // Invalid bit rate or 'free format'
	}

	var sampleRateIndex = this.bits.read(2);
	var sampleRate = MP2.SAMPLE_RATE[sampleRateIndex];
	if (sampleRateIndex === 3) {
		return 0; // Invalid sample rate
	}
	if (version === MP2.VERSION.MPEG_2) {
		sampleRateIndex += 4;
		bitrateIndex += 14;
	}
	var padding = this.bits.read(1),
		privat = this.bits.read(1),
		mode = this.bits.read(2);

	// Parse the mode_extension, set up the stereo bound
	var bound = 0;
	if (mode === MP2.MODE.JOINT_STEREO) {
		bound = (this.bits.read(2) + 1) << 2;
	}
	else {
		this.bits.skip(2);
		bound = (mode === MP2.MODE.MONO) ? 0 : 32;
	}

	// Discard the last 4 bits of the header and the CRC value, if present
	this.bits.skip(4);
	if (hasCRC) {
		this.bits.skip(16);
	}

	// Compute the frame size
	var bitrate = MP2.BIT_RATE[bitrateIndex],
		sampleRate = MP2.SAMPLE_RATE[sampleRateIndex],
		frameSize = ((144000 * bitrate / sampleRate) + padding)|0;
	

	// Prepare the quantizer table lookups
	var tab3 = 0;
	var sblimit = 0;
	if (version === MP2.VERSION.MPEG_2) {
		// MPEG-2 (LSR)
		tab3 = 2;
		sblimit = 30;
	}
	else {
		// MPEG-1
		var tab1 = (mode === MP2.MODE.MONO) ? 0 : 1;
		var tab2 = MP2.QUANT_LUT_STEP_1[tab1][bitrateIndex];
		tab3 = MP2.QUANT_LUT_STEP_2[tab2][sampleRateIndex];
		sblimit = tab3 & 63;
		tab3 >>= 6;
	}

	if (bound > sblimit) {
		bound = sblimit;
	}

	// Read the allocation information
	for (var sb = 0; sb < bound; sb++) {
		this.allocation[0][sb] = this.readAllocation(sb, tab3);
		this.allocation[1][sb] = this.readAllocation(sb, tab3);
	}

	for (var sb = bound; sb < sblimit; sb++) {
		this.allocation[0][sb] = 
			this.allocation[1][sb] =
			this.readAllocation(sb, tab3);
	}

	// Read scale factor selector information
	var channels = (mode === MP2.MODE.MONO) ? 1 : 2;
	for (var sb = 0;  sb < sblimit; sb++) {
		for (ch = 0;  ch < channels; ch++) {
			if (this.allocation[ch][sb]) {
				this.scaleFactorInfo[ch][sb] = this.bits.read(2);
			}
		}
		if (mode === MP2.MODE.MONO) {
			this.scaleFactorInfo[1][sb] = this.scaleFactorInfo[0][sb];
		}
	}

	// Read scale factors
	for (var sb = 0;  sb < sblimit; sb++) {
		for (var ch = 0;  ch < channels; ch++) {
			if (this.allocation[ch][sb]) {
				var sf = this.scaleFactor[ch][sb];
				switch (this.scaleFactorInfo[ch][sb]) {
					case 0:
						sf[0] = this.bits.read(6);
						sf[1] = this.bits.read(6);
						sf[2] = this.bits.read(6);
						break;
					case 1:
						sf[0] =
						sf[1] = this.bits.read(6);
						sf[2] = this.bits.read(6);
						break;
					case 2:
						sf[0] =
						sf[1] =
						sf[2] = this.bits.read(6);
						break;
					case 3:
						sf[0] = this.bits.read(6);
						sf[1] =
						sf[2] = this.bits.read(6);
						break;
				}
			}
		}
		if (mode === MP2.MODE.MONO) {
			this.scaleFactor[1][sb][0] = this.scaleFactor[0][sb][0];
			this.scaleFactor[1][sb][1] = this.scaleFactor[0][sb][1];
			this.scaleFactor[1][sb][2] = this.scaleFactor[0][sb][2];
		}
	}

	// Coefficient input and reconstruction
	var outPos = 0;
	for (var part = 0; part < 3; part++) {
		for (var granule = 0; granule < 4; granule++) {

			// Read the samples
			for (var sb = 0; sb < bound; sb++) {
				this.readSamples(0, sb, part);
				this.readSamples(1, sb, part);
			}
			for (var sb = bound; sb < sblimit; sb++) {
				this.readSamples(0, sb, part);
				this.sample[1][sb][0] = this.sample[0][sb][0];
				this.sample[1][sb][1] = this.sample[0][sb][1];
				this.sample[1][sb][2] = this.sample[0][sb][2];
			}
			for (var sb = sblimit; sb < 32; sb++) {
				this.sample[0][sb][0] = 0;
				this.sample[0][sb][1] = 0;
				this.sample[0][sb][2] = 0;
				this.sample[1][sb][0] = 0;
				this.sample[1][sb][1] = 0;
				this.sample[1][sb][2] = 0;
			}

			// Synthesis loop
			for (var p = 0; p < 3; p++) {
				// Shifting step
				this.VPos = (this.VPos - 64) & 1023;

				for (var ch = 0;  ch < 2; ch++) {
					MP2.MatrixTransform(this.sample[ch], p, this.V, this.VPos);

					// Build U, windowing, calculate output
					JSMpeg.Fill(this.U, 0);

					var dIndex = 512 - (this.VPos >> 1);
					var vIndex = (this.VPos % 128) >> 1;
					while (vIndex < 1024) {
						for (var i = 0; i < 32; ++i) {
							this.U[i] += this.D[dIndex++] * this.V[vIndex++];
						}

						vIndex += 128-32;
						dIndex += 64-32;
					}

					vIndex = (128-32 + 1024) - vIndex;
					dIndex -= (512 - 32);
					while (vIndex < 1024) {
						for (var i = 0; i < 32; ++i) {
							this.U[i] += this.D[dIndex++] * this.V[vIndex++];
						}

						vIndex += 128-32;
						dIndex += 64-32;
					}

					// Output samples
					var outChannel = ch === 0 ? left : right;
					for (var j = 0; j < 32; j++) {
						outChannel[outPos + j] = this.U[j] / 2147418112;
					}
				} // End of synthesis channel loop
				outPos += 32;
			} // End of synthesis sub-block loop

		} // Decoding of the granule finished
	}

	this.sampleRate = sampleRate;
	return frameSize;
};

MP2.prototype.readAllocation = function(sb, tab3) {
	var tab4 = MP2.QUANT_LUT_STEP_3[tab3][sb];
	var qtab = MP2.QUANT_LUT_STEP4[tab4 & 15][this.bits.read(tab4 >> 4)];
	return qtab ? (MP2.QUANT_TAB[qtab - 1]) : 0;
};

MP2.prototype.readSamples = function(ch, sb, part) {
	var q = this.allocation[ch][sb],
		sf = this.scaleFactor[ch][sb][part],
		sample = this.sample[ch][sb],
		val = 0;

	if (!q) {
		// No bits allocated for this subband
		sample[0] = sample[1] = sample[2] = 0;
		return;
	}

	// Resolve scalefactor
	if (sf === 63) {
		sf = 0;
	}
	else {
		var shift = (sf / 3)|0;
		sf = (MP2.SCALEFACTOR_BASE[sf % 3] + ((1 << shift) >> 1)) >> shift;
	}

	// Decode samples
	var adj = q.levels;
	if (q.group) {
		// Decode grouped samples
		val = this.bits.read(q.bits);
		sample[0] = val % adj;
		val = (val / adj)|0;
		sample[1] = val % adj;
		sample[2] = (val / adj)|0;
	}
	else {
		// Decode direct samples
		sample[0] = this.bits.read(q.bits);
		sample[1] = this.bits.read(q.bits);
		sample[2] = this.bits.read(q.bits);
	}

	// Postmultiply samples
	var scale = (65536 / (adj + 1))|0;
	adj = ((adj + 1) >> 1) - 1;

	val = (adj - sample[0]) * scale;
	sample[0] = (val * (sf >> 12) + ((val * (sf & 4095) + 2048) >> 12)) >> 12;

	val = (adj - sample[1]) * scale;
	sample[1] = (val * (sf >> 12) + ((val * (sf & 4095) + 2048) >> 12)) >> 12;

	val = (adj - sample[2]) * scale;
	sample[2] = (val * (sf >> 12) + ((val * (sf & 4095) + 2048) >> 12)) >> 12;
};

MP2.MatrixTransform = function(s, ss, d, dp) {
	var t01, t02, t03, t04, t05, t06, t07, t08, t09, t10, t11, t12,
		t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24,
		t25, t26, t27, t28, t29, t30, t31, t32, t33;

	t01 = s[ 0][ss] + s[31][ss]; t02 = (s[ 0][ss] - s[31][ss]) * 0.500602998235;
	t03 = s[ 1][ss] + s[30][ss]; t04 = (s[ 1][ss] - s[30][ss]) * 0.505470959898;
	t05 = s[ 2][ss] + s[29][ss]; t06 = (s[ 2][ss] - s[29][ss]) * 0.515447309923;
	t07 = s[ 3][ss] + s[28][ss]; t08 = (s[ 3][ss] - s[28][ss]) * 0.53104259109;
	t09 = s[ 4][ss] + s[27][ss]; t10 = (s[ 4][ss] - s[27][ss]) * 0.553103896034;
	t11 = s[ 5][ss] + s[26][ss]; t12 = (s[ 5][ss] - s[26][ss]) * 0.582934968206;
	t13 = s[ 6][ss] + s[25][ss]; t14 = (s[ 6][ss] - s[25][ss]) * 0.622504123036;
	t15 = s[ 7][ss] + s[24][ss]; t16 = (s[ 7][ss] - s[24][ss]) * 0.674808341455;
	t17 = s[ 8][ss] + s[23][ss]; t18 = (s[ 8][ss] - s[23][ss]) * 0.744536271002;
	t19 = s[ 9][ss] + s[22][ss]; t20 = (s[ 9][ss] - s[22][ss]) * 0.839349645416;
	t21 = s[10][ss] + s[21][ss]; t22 = (s[10][ss] - s[21][ss]) * 0.972568237862;
	t23 = s[11][ss] + s[20][ss]; t24 = (s[11][ss] - s[20][ss]) * 1.16943993343;
	t25 = s[12][ss] + s[19][ss]; t26 = (s[12][ss] - s[19][ss]) * 1.48416461631;
	t27 = s[13][ss] + s[18][ss]; t28 = (s[13][ss] - s[18][ss]) * 2.05778100995;
	t29 = s[14][ss] + s[17][ss]; t30 = (s[14][ss] - s[17][ss]) * 3.40760841847;
	t31 = s[15][ss] + s[16][ss]; t32 = (s[15][ss] - s[16][ss]) * 10.1900081235;

	t33 = t01 + t31; t31 = (t01 - t31) * 0.502419286188;
	t01 = t03 + t29; t29 = (t03 - t29) * 0.52249861494;
	t03 = t05 + t27; t27 = (t05 - t27) * 0.566944034816;
	t05 = t07 + t25; t25 = (t07 - t25) * 0.64682178336;
	t07 = t09 + t23; t23 = (t09 - t23) * 0.788154623451;
	t09 = t11 + t21; t21 = (t11 - t21) * 1.06067768599;
	t11 = t13 + t19; t19 = (t13 - t19) * 1.72244709824;
	t13 = t15 + t17; t17 = (t15 - t17) * 5.10114861869;
	t15 = t33 + t13; t13 = (t33 - t13) * 0.509795579104;
	t33 = t01 + t11; t01 = (t01 - t11) * 0.601344886935;
	t11 = t03 + t09; t09 = (t03 - t09) * 0.899976223136;
	t03 = t05 + t07; t07 = (t05 - t07) * 2.56291544774;
	t05 = t15 + t03; t15 = (t15 - t03) * 0.541196100146;
	t03 = t33 + t11; t11 = (t33 - t11) * 1.30656296488;
	t33 = t05 + t03; t05 = (t05 - t03) * 0.707106781187;
	t03 = t15 + t11; t15 = (t15 - t11) * 0.707106781187;
	t03 += t15;
	t11 = t13 + t07; t13 = (t13 - t07) * 0.541196100146;
	t07 = t01 + t09; t09 = (t01 - t09) * 1.30656296488;
	t01 = t11 + t07; t07 = (t11 - t07) * 0.707106781187;
	t11 = t13 + t09; t13 = (t13 - t09) * 0.707106781187;
	t11 += t13; t01 += t11; 
	t11 += t07; t07 += t13;
	t09 = t31 + t17; t31 = (t31 - t17) * 0.509795579104;
	t17 = t29 + t19; t29 = (t29 - t19) * 0.601344886935;
	t19 = t27 + t21; t21 = (t27 - t21) * 0.899976223136;
	t27 = t25 + t23; t23 = (t25 - t23) * 2.56291544774;
	t25 = t09 + t27; t09 = (t09 - t27) * 0.541196100146;
	t27 = t17 + t19; t19 = (t17 - t19) * 1.30656296488;
	t17 = t25 + t27; t27 = (t25 - t27) * 0.707106781187;
	t25 = t09 + t19; t19 = (t09 - t19) * 0.707106781187;
	t25 += t19;
	t09 = t31 + t23; t31 = (t31 - t23) * 0.541196100146;
	t23 = t29 + t21; t21 = (t29 - t21) * 1.30656296488;
	t29 = t09 + t23; t23 = (t09 - t23) * 0.707106781187;
	t09 = t31 + t21; t31 = (t31 - t21) * 0.707106781187;
	t09 += t31;	t29 += t09;	t09 += t23;	t23 += t31;
	t17 += t29;	t29 += t25;	t25 += t09;	t09 += t27;
	t27 += t23;	t23 += t19; t19 += t31;	
	t21 = t02 + t32; t02 = (t02 - t32) * 0.502419286188;
	t32 = t04 + t30; t04 = (t04 - t30) * 0.52249861494;
	t30 = t06 + t28; t28 = (t06 - t28) * 0.566944034816;
	t06 = t08 + t26; t08 = (t08 - t26) * 0.64682178336;
	t26 = t10 + t24; t10 = (t10 - t24) * 0.788154623451;
	t24 = t12 + t22; t22 = (t12 - t22) * 1.06067768599;
	t12 = t14 + t20; t20 = (t14 - t20) * 1.72244709824;
	t14 = t16 + t18; t16 = (t16 - t18) * 5.10114861869;
	t18 = t21 + t14; t14 = (t21 - t14) * 0.509795579104;
	t21 = t32 + t12; t32 = (t32 - t12) * 0.601344886935;
	t12 = t30 + t24; t24 = (t30 - t24) * 0.899976223136;
	t30 = t06 + t26; t26 = (t06 - t26) * 2.56291544774;
	t06 = t18 + t30; t18 = (t18 - t30) * 0.541196100146;
	t30 = t21 + t12; t12 = (t21 - t12) * 1.30656296488;
	t21 = t06 + t30; t30 = (t06 - t30) * 0.707106781187;
	t06 = t18 + t12; t12 = (t18 - t12) * 0.707106781187;
	t06 += t12;
	t18 = t14 + t26; t26 = (t14 - t26) * 0.541196100146;
	t14 = t32 + t24; t24 = (t32 - t24) * 1.30656296488;
	t32 = t18 + t14; t14 = (t18 - t14) * 0.707106781187;
	t18 = t26 + t24; t24 = (t26 - t24) * 0.707106781187;
	t18 += t24; t32 += t18; 
	t18 += t14; t26 = t14 + t24;
	t14 = t02 + t16; t02 = (t02 - t16) * 0.509795579104;
	t16 = t04 + t20; t04 = (t04 - t20) * 0.601344886935;
	t20 = t28 + t22; t22 = (t28 - t22) * 0.899976223136;
	t28 = t08 + t10; t10 = (t08 - t10) * 2.56291544774;
	t08 = t14 + t28; t14 = (t14 - t28) * 0.541196100146;
	t28 = t16 + t20; t20 = (t16 - t20) * 1.30656296488;
	t16 = t08 + t28; t28 = (t08 - t28) * 0.707106781187;
	t08 = t14 + t20; t20 = (t14 - t20) * 0.707106781187;
	t08 += t20;
	t14 = t02 + t10; t02 = (t02 - t10) * 0.541196100146;
	t10 = t04 + t22; t22 = (t04 - t22) * 1.30656296488;
	t04 = t14 + t10; t10 = (t14 - t10) * 0.707106781187;
	t14 = t02 + t22; t02 = (t02 - t22) * 0.707106781187;
	t14 += t02;	t04 += t14;	t14 += t10;	t10 += t02;
	t16 += t04;	t04 += t08;	t08 += t14;	t14 += t28;
	t28 += t10;	t10 += t20;	t20 += t02;	t21 += t16;
	t16 += t32;	t32 += t04;	t04 += t06;	t06 += t08;
	t08 += t18;	t18 += t14;	t14 += t30;	t30 += t28;
	t28 += t26;	t26 += t10;	t10 += t12;	t12 += t20;
	t20 += t24;	t24 += t02;

	d[dp + 48] = -t33;
	d[dp + 49] = d[dp + 47] = -t21;
	d[dp + 50] = d[dp + 46] = -t17;
	d[dp + 51] = d[dp + 45] = -t16;
	d[dp + 52] = d[dp + 44] = -t01;
	d[dp + 53] = d[dp + 43] = -t32;
	d[dp + 54] = d[dp + 42] = -t29;
	d[dp + 55] = d[dp + 41] = -t04;
	d[dp + 56] = d[dp + 40] = -t03;
	d[dp + 57] = d[dp + 39] = -t06;
	d[dp + 58] = d[dp + 38] = -t25;
	d[dp + 59] = d[dp + 37] = -t08;
	d[dp + 60] = d[dp + 36] = -t11;
	d[dp + 61] = d[dp + 35] = -t18;
	d[dp + 62] = d[dp + 34] = -t09;
	d[dp + 63] = d[dp + 33] = -t14;
	d[dp + 32] = -t05;
	d[dp +  0] = t05; d[dp + 31] = -t30;
	d[dp +  1] = t30; d[dp + 30] = -t27;
	d[dp +  2] = t27; d[dp + 29] = -t28;
	d[dp +  3] = t28; d[dp + 28] = -t07;
	d[dp +  4] = t07; d[dp + 27] = -t26;
	d[dp +  5] = t26; d[dp + 26] = -t23;
	d[dp +  6] = t23; d[dp + 25] = -t10;
	d[dp +  7] = t10; d[dp + 24] = -t15;
	d[dp +  8] = t15; d[dp + 23] = -t12;
	d[dp +  9] = t12; d[dp + 22] = -t19;
	d[dp + 10] = t19; d[dp + 21] = -t20;
	d[dp + 11] = t20; d[dp + 20] = -t13;
	d[dp + 12] = t13; d[dp + 19] = -t24;
	d[dp + 13] = t24; d[dp + 18] = -t31;
	d[dp + 14] = t31; d[dp + 17] = -t02;
	d[dp + 15] = t02; d[dp + 16] =  0.0;
};

MP2.FRAME_SYNC = 0x7ff;

MP2.VERSION = {
	MPEG_2_5: 0x0,
	MPEG_2: 0x2,
	MPEG_1: 0x3
};

MP2.LAYER = {
	III: 0x1,
	II: 0x2,
	I: 0x3
};

MP2.MODE = {
	STEREO: 0x0,
	JOINT_STEREO: 0x1,
	DUAL_CHANNEL: 0x2,
	MONO: 0x3
};

MP2.SAMPLE_RATE = new Uint16Array([
	44100, 48000, 32000, 0, // MPEG-1
	22050, 24000, 16000, 0  // MPEG-2
]);

MP2.BIT_RATE = new Uint16Array([
	32, 48, 56, 64, 80, 96, 112, 128, 160, 192, 224, 256, 320, 384, // MPEG-1
	 8, 16, 24, 32, 40, 48,  56,  64,  80,  96, 112, 128, 144, 160  // MPEG-2
]);

MP2.SCALEFACTOR_BASE = new Uint32Array([
	0x02000000, 0x01965FEA, 0x01428A30
]);

MP2.SYNTHESIS_WINDOW = new Float32Array([
	     0.0,     -0.5,     -0.5,     -0.5,     -0.5,     -0.5,
	    -0.5,     -1.0,     -1.0,     -1.0,     -1.0,     -1.5,
	    -1.5,     -2.0,     -2.0,     -2.5,     -2.5,     -3.0,
	    -3.5,     -3.5,     -4.0,     -4.5,     -5.0,     -5.5,
	    -6.5,     -7.0,     -8.0,     -8.5,     -9.5,    -10.5,
	   -12.0,    -13.0,    -14.5,    -15.5,    -17.5,    -19.0,
	   -20.5,    -22.5,    -24.5,    -26.5,    -29.0,    -31.5,
	   -34.0,    -36.5,    -39.5,    -42.5,    -45.5,    -48.5,
	   -52.0,    -55.5,    -58.5,    -62.5,    -66.0,    -69.5,
	   -73.5,    -77.0,    -80.5,    -84.5,    -88.0,    -91.5,
	   -95.0,    -98.0,   -101.0,   -104.0,    106.5,    109.0,
	   111.0,    112.5,    113.5,    114.0,    114.0,    113.5,
	   112.0,    110.5,    107.5,    104.0,    100.0,     94.5,
	    88.5,     81.5,     73.0,     63.5,     53.0,     41.5,
	    28.5,     14.5,     -1.0,    -18.0,    -36.0,    -55.5,
	   -76.5,    -98.5,   -122.0,   -147.0,   -173.5,   -200.5,
	  -229.5,   -259.5,   -290.5,   -322.5,   -355.5,   -389.5,
	  -424.0,   -459.5,   -495.5,   -532.0,   -568.5,   -605.0,
	  -641.5,   -678.0,   -714.0,   -749.0,   -783.5,   -817.0,
	  -849.0,   -879.5,   -908.5,   -935.0,   -959.5,   -981.0,
	 -1000.5,  -1016.0,  -1028.5,  -1037.5,  -1042.5,  -1043.5,
	 -1040.0,  -1031.5,   1018.5,   1000.0,    976.0,    946.5,
	   911.0,    869.5,    822.0,    767.5,    707.0,    640.0,
	   565.5,    485.0,    397.0,    302.5,    201.0,     92.5,
	   -22.5,   -144.0,   -272.5,   -407.0,   -547.5,   -694.0,
	  -846.0,  -1003.0,  -1165.0,  -1331.5,  -1502.0,  -1675.5,
	 -1852.5,  -2031.5,  -2212.5,  -2394.0,  -2576.5,  -2758.5,
	 -2939.5,  -3118.5,  -3294.5,  -3467.5,  -3635.5,  -3798.5,
	 -3955.0,  -4104.5,  -4245.5,  -4377.5,  -4499.0,  -4609.5,
	 -4708.0,  -4792.5,  -4863.5,  -4919.0,  -4958.0,  -4979.5,
	 -4983.0,  -4967.5,  -4931.5,  -4875.0,  -4796.0,  -4694.5,
	 -4569.5,  -4420.0,  -4246.0,  -4046.0,  -3820.0,  -3567.0,
	  3287.0,   2979.5,   2644.0,   2280.5,   1888.0,   1467.5,
	  1018.5,    541.0,     35.0,   -499.0,  -1061.0,  -1650.0,
	 -2266.5,  -2909.0,  -3577.0,  -4270.0,  -4987.5,  -5727.5,
	 -6490.0,  -7274.0,  -8077.5,  -8899.5,  -9739.0, -10594.5,
	-11464.5, -12347.0, -13241.0, -14144.5, -15056.0, -15973.5,
	-16895.5, -17820.0, -18744.5, -19668.0, -20588.0, -21503.0,
	-22410.5, -23308.5, -24195.0, -25068.5, -25926.5, -26767.0,
	-27589.0, -28389.0, -29166.5, -29919.0, -30644.5, -31342.0,
	-32009.5, -32645.0, -33247.0, -33814.5, -34346.0, -34839.5,
	-35295.0, -35710.0, -36084.5, -36417.5, -36707.5, -36954.0,
	-37156.5, -37315.0, -37428.0, -37496.0,  37519.0,  37496.0,
	 37428.0,  37315.0,  37156.5,  36954.0,  36707.5,  36417.5,
	 36084.5,  35710.0,  35295.0,  34839.5,  34346.0,  33814.5,
	 33247.0,  32645.0,  32009.5,  31342.0,  30644.5,  29919.0,
	 29166.5,  28389.0,  27589.0,  26767.0,  25926.5,  25068.5,
	 24195.0,  23308.5,  22410.5,  21503.0,  20588.0,  19668.0,
	 18744.5,  17820.0,  16895.5,  15973.5,  15056.0,  14144.5,
	 13241.0,  12347.0,  11464.5,  10594.5,   9739.0,   8899.5,
	  8077.5,   7274.0,   6490.0,   5727.5,   4987.5,   4270.0,
	  3577.0,   2909.0,   2266.5,   1650.0,   1061.0,    499.0,
	   -35.0,   -541.0,  -1018.5,  -1467.5,  -1888.0,  -2280.5,
	 -2644.0,  -2979.5,   3287.0,   3567.0,   3820.0,   4046.0,
	  4246.0,   4420.0,   4569.5,   4694.5,   4796.0,   4875.0,
	  4931.5,   4967.5,   4983.0,   4979.5,   4958.0,   4919.0,
	  4863.5,   4792.5,   4708.0,   4609.5,   4499.0,   4377.5,
	  4245.5,   4104.5,   3955.0,   3798.5,   3635.5,   3467.5,
	  3294.5,   3118.5,   2939.5,   2758.5,   2576.5,   2394.0,
	  2212.5,   2031.5,   1852.5,   1675.5,   1502.0,   1331.5,
	  1165.0,   1003.0,    846.0,    694.0,    547.5,    407.0,
	   272.5,    144.0,     22.5,    -92.5,   -201.0,   -302.5,
	  -397.0,   -485.0,   -565.5,   -640.0,   -707.0,   -767.5,
	  -822.0,   -869.5,   -911.0,   -946.5,   -976.0,  -1000.0,
	  1018.5,   1031.5,   1040.0,   1043.5,   1042.5,   1037.5,
	  1028.5,   1016.0,   1000.5,    981.0,    959.5,    935.0,
	   908.5,    879.5,    849.0,    817.0,    783.5,    749.0,
	   714.0,    678.0,    641.5,    605.0,    568.5,    532.0,
	   495.5,    459.5,    424.0,    389.5,    355.5,    322.5,
	   290.5,    259.5,    229.5,    200.5,    173.5,    147.0,
	   122.0,     98.5,     76.5,     55.5,     36.0,     18.0,
		1.0,    -14.5,    -28.5,    -41.5,    -53.0,    -63.5,
	   -73.0,    -81.5,    -88.5,    -94.5,   -100.0,   -104.0,
	  -107.5,   -110.5,   -112.0,   -113.5,   -114.0,   -114.0,
	  -113.5,   -112.5,   -111.0,   -109.0,    106.5,    104.0,
	   101.0,     98.0,     95.0,     91.5,     88.0,     84.5,
	    80.5,     77.0,     73.5,     69.5,     66.0,     62.5,
	    58.5,     55.5,     52.0,     48.5,     45.5,     42.5,
	    39.5,     36.5,     34.0,     31.5,     29.0,     26.5,
	    24.5,     22.5,     20.5,     19.0,     17.5,     15.5,
	    14.5,     13.0,     12.0,     10.5,      9.5,      8.5,
	     8.0,      7.0,      6.5,      5.5,      5.0,      4.5,
	     4.0,      3.5,      3.5,      3.0,      2.5,      2.5,
	     2.0,      2.0,      1.5,      1.5,      1.0,      1.0,
	     1.0,      1.0,      0.5,      0.5,      0.5,      0.5,
	     0.5,      0.5
]);

// Quantizer lookup, step 1: bitrate classes
MP2.QUANT_LUT_STEP_1 = [
 	// 32, 48, 56, 64, 80, 96,112,128,160,192,224,256,320,384 <- bitrate
	[   0,  0,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2], // mono
	// 16, 24, 28, 32, 40, 48, 56, 64, 80, 96,112,128,160,192 <- bitrate / chan
	[   0,  0,  0,  0,  0,  0,  1,  1,  1,  2,  2,  2,  2,  2] // stereo
];

// Quantizer lookup, step 2: bitrate class, sample rate -> B2 table idx, sblimit
MP2.QUANT_TAB = {
	A: (27 | 64), // Table 3-B.2a: high-rate, sblimit = 27
	B: (30 | 64), // Table 3-B.2b: high-rate, sblimit = 30
	C:   8,       // Table 3-B.2c:  low-rate, sblimit =  8
	D:  12        // Table 3-B.2d:  low-rate, sblimit = 12
};

MP2.QUANT_LUT_STEP_2 = [
	//   44.1 kHz,        48 kHz,          32 kHz
	[MP2.QUANT_TAB.C, MP2.QUANT_TAB.C, MP2.QUANT_TAB.D], // 32 - 48 kbit/sec/ch
	[MP2.QUANT_TAB.A, MP2.QUANT_TAB.A, MP2.QUANT_TAB.A], // 56 - 80 kbit/sec/ch
	[MP2.QUANT_TAB.B, MP2.QUANT_TAB.A, MP2.QUANT_TAB.B]  // 96+	 kbit/sec/ch
];

// Quantizer lookup, step 3: B2 table, subband -> nbal, row index
// (upper 4 bits: nbal, lower 4 bits: row index)
MP2.QUANT_LUT_STEP_3 = [
	// Low-rate table (3-B.2c and 3-B.2d)
	[
		0x44,0x44,
	  	0x34,0x34,0x34,0x34,0x34,0x34,0x34,0x34,0x34,0x34
	],
	// High-rate table (3-B.2a and 3-B.2b)
	[
		0x43,0x43,0x43,
		0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,
		0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x31,
		0x20,0x20,0x20,0x20,0x20,0x20,0x20
	],
	// MPEG-2 LSR table (B.2 in ISO 13818-3)
	[
		0x45,0x45,0x45,0x45,
		0x34,0x34,0x34,0x34,0x34,0x34,0x34,
		0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24,
					   0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24,0x24	
	]
];

// Quantizer lookup, step 4: table row, allocation[] value -> quant table index
MP2.QUANT_LUT_STEP4 = [
	[0, 1, 2, 17],
	[0, 1, 2, 3, 4, 5, 6, 17],
	[0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 17],
	[0, 1, 3, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17],
	[0, 1, 2, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 17],
	[0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
];

MP2.QUANT_TAB = [
	{levels:     3, group: 1, bits:  5},  //  1
	{levels:     5, group: 1, bits:  7},  //  2
	{levels:     7, group: 0, bits:  3},  //  3
	{levels:     9, group: 1, bits: 10},  //  4
	{levels:    15, group: 0, bits:  4},  //  5
	{levels:    31, group: 0, bits:  5},  //  6
	{levels:    63, group: 0, bits:  6},  //  7
	{levels:   127, group: 0, bits:  7},  //  8
	{levels:   255, group: 0, bits:  8},  //  9
	{levels:   511, group: 0, bits:  9},  // 10
	{levels:  1023, group: 0, bits: 10},  // 11
	{levels:  2047, group: 0, bits: 11},  // 12
	{levels:  4095, group: 0, bits: 12},  // 13
	{levels:  8191, group: 0, bits: 13},  // 14
	{levels: 16383, group: 0, bits: 14},  // 15
	{levels: 32767, group: 0, bits: 15},  // 16
	{levels: 65535, group: 0, bits: 16}   // 17
];

return MP2;

})();

