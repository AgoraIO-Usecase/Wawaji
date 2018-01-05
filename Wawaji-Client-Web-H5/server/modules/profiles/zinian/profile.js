const vault = require('../../vault.js').zinian;
const logger = require('../../logger');
var debug = true;
const WawajiStatus = require('../../constants').WawajiStatus;
var dbg = function () {
    if (debug) {
        var x = [];
        for (var i in arguments) x.push(arguments[i]);
        console.log.apply(null, ['Agora ZiZian profile dbg :'].concat(x));
    }
};

ZiNianProfile = function (mode) {
    var profile = this;
    this.machine = null;
    this.appid = vault.appid;
    this.appcert = vault.appcert;
    this.url = vault.url;
    this.video_channel = vault.video_channel;
    this.video_rotation = vault.video_rotation;
    this.log = (new logger('zinian', 'logs/zinian.log')).get();

    this.onInit = function (machine, done) {
        profile.log.info("onInit.");
        profile.machine = machine;
        machine.socket.on('open', function open() {
            profile.log.info("WebSocket opened");
            done();
        });

        machine.socket.on('message', function incoming(data) {
            profile.log.info(machine.name + " WebSocket receive: " + data);
            var json = JSON.parse(data);
            switch (json.type) {
                case "Wait":
                    // machine.status : WawajiStatus.WAITING;
                    break;
                case "Ready":
                    // machine.status : WawajiStatus.READY;
                    break;
                case "State":
                    switch (json.data) {
                        case "PLAY":
                        case "WAITRESULT":
                        case "RET":
                            // machine.status : WawajiStatus.BUSY;
                            break;
                        case "WAIT":
                            // machine.status : WawajiStatus.READY;
                            break;
                    }
                    break;
                case "Result":
                    if (json.data !== undefined) {
                        profile.onResult && profile.onResult(json.data);
                    }
                    break;
            }
        });
    }

    this.onPlay = function (account) {
        profile.log.info("onPlay.");
        var control_data = {
            type: 'Insert',
            data: '',
            extra: null
        };
        if (profile.machine && profile.machine.socket) {
            profile.machine.socket.send(JSON.stringify(control_data));
        }
    }

    this.onControl = function (data) {
        profile.log.info("onControl.");
        var control_data = {
            type: 'Control',
            data: ''
        };
        switch (data.data) {
            case 'left':  control_data.data = data.pressed ? 'l' : 'A'; break;
            case 'right': control_data.data = data.pressed ? 'r' : 'D'; break;
            case 'up':    control_data.data = data.pressed ? 'u' : 'W'; break;
            case 'down':  control_data.data = data.pressed ? 'd' : 'S'; break;
            default: break;
        }
        if (profile.machine && profile.machine.socket) {
            profile.machine.socket.send(JSON.stringify(control_data));
        }
    }

    this.onCatch = function () {
        profile.log.info("onCatch.");
        var control_data = {
            type: 'Control',
            data: 'b'
        };
        if (profile.machine && profile.machine.socket) {
            profile.machine.socket.send(JSON.stringify(control_data));
        }
    }
}


module.exports = ZiNianProfile;

