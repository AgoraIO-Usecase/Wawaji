
const vault = require('../../vault.js').kedie
const WawajiStatus = require('../../constants').WawajiStatus;
const request = require('request');
const md5 = require('md5');

const ACTION = {
    RELEASE: '00',
    LEFT:    '01',
    RIGHT:   '02',
    UP:      '03',
    DOWN:    '04',
    CATCH:   '05',
    PLAY:    '10'
};

const OPERATION = {
    CMD:     'api/extra/online/command.do',
    CHECK:   'api/extra/online/check.do'
};

var debug = true;
var dbg = function () {
    if (debug) {
        var x = [];
        for (var i in arguments) x.push(arguments[i]);
        console.log.apply(null, ['Agora Kedie profile dbg :'].concat(x));
    }
};


KedieProfile = function (mode) {
    var profile = this;
    this.machine = null;
    this.appid = vault.appid;
    this.appcert = vault.appcert;
    this.url = vault.url;
    this.http_url = vault.http_url;
    this.video_channel = vault.video_channel;
    this.video_host = vault.video_host;
    this.video_rotation = vault.video_rotation;
    this.stream_secret = vault.stream_secret;
    this.mode = mode;
    this.actions = {};
    this.protocol = vault.protocol;

    this.vendor_device = vault.vendor_device;
    this.vendor_sn = vault.vendor_sn;
    this.vendor_key = vault.vendor_key;

    this.onInit = function (machine, done) {
        dbg("onInit.");
        profile.machine = machine;
        done();
    }

    this.onPlay = function (account) {
        dbg("onPlay.");

        var action = {
            "order": ACTION.PLAY,
            "sn": `${profile.vendor_sn}`,
            "device": `${profile.vendor_device}`
        };
        action.sign = md5(`device=${action.device}&order=${action.order}&sn=${action.sn}&${profile.vendor_key}`);
        dbg(JSON.stringify(action));

        var dst_url = profile.http_url + OPERATION.CMD;
        request.post({ url: dst_url, json: action }, function (err, response, body) {
            dbg(body);
        });
    }

    this.onControl = function (data) {
        dbg("onControl: " + data.data);

        var action = {
            "sn": `${profile.vendor_sn}`,
            "device": `${profile.vendor_device}`
        };
        switch (data.data) {
            case 'left':  action.order = data.pressed ? ACTION.LEFT  : ACTION.RELEASE; break;
            case 'right': action.order = data.pressed ? ACTION.RIGHT : ACTION.RELEASE; break;
            case 'up':    action.order = data.pressed ? ACTION.UP    : ACTION.RELEASE; break;
            case 'down':  action.order = data.pressed ? ACTION.DOWN  : ACTION.RELEASE; break;
            default: break;
        }
        action.sign = md5(`device=${action.device}&order=${action.order}&sn=${action.sn}&${profile.vendor_key}`);
        dbg(JSON.stringify(action));

        var dst_url = profile.http_url + OPERATION.CMD;
        request.post({ url: dst_url, json: action }, function (err, response, body) {
            dbg(body);
        });
    }

    this.onCatch = function () {
        dbg("onCatch.");

        var action = {
            "order": ACTION.CATCH,
            "sn": `${profile.vendor_sn}`,
            "device": `${profile.vendor_device}`
        };
        action.sign = md5(`device=${action.device}&order=${action.order}&sn=${action.sn}&${profile.vendor_key}`);
        dbg(JSON.stringify(action));

        var dst_url = profile.http_url + OPERATION.CMD;
        request.post({ url: dst_url, json: action }, function (err, response, body) {
            dbg(body);
        });
    }

    this.check = function () {
        dbg("check.");

        var action = {
			"sn": `${profile.vendor_sn}`,
			"device": `${profile.vendor_device}`
        }
        action.sign = md5(`device=${action.device}&sn=${action.sn}&${profile.vendor_key}`);
        dbg(JSON.stringify(action));

        var dst_url = profile.http_url + OPERATION.CHECK;
        request.post({ url: dst_url, json: action }, function (err, response, body) {
            var msg = JSON.parse(body);
            if (msg) {
                if(msg.isget !== undefined) {
                    profile.onResult && profile.onResult(msg.isget);
                }
            }
        });
    }

}

module.exports = KedieProfile;

