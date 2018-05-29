const vault = require('../../vault.js').zinian;
const logger = require('../../logger');
var debug = true;
const WawajiStatus = require('../../constants').WawajiStatus;
const request = require("request");
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
    this.url = null;
    this.video_channel = vault.video_channel;
    this.video_rotation = vault.video_rotation;
    this.app_id = vault.app_id;
    this.room_id = vault.room_id;
    this.binding = vault.binding;
    this.log = (new logger('zinian', 'logs/zinian.log')).get();

    this.prepare = () => {
        let ts = new Date().getTime();
        if(this.url && ts - this.lastRefreshTs < 1000 * 60 * 60 * 24) {
            //refresh daily
            return Promise.resolve(this.url);
        }

        return new Promise((resolve, reject) => {
            console.log(`prepare url..`);
            let options = {
                uri: `https://catchu.azusasoft.com/open_api/v0.2/rooms/${this.room_id}/play`,
                method: "post",
                json: {
                    binding: this.binding,
                    room_id: this.room_id,
                    app_id: this.app_id
                }
            }
            request(options, (error, response, body) => {
                if(body.status !== "ok") {
                    reject("failed");
                } else {
                    console.log(`prepared url: ${body.user.ws_url}`);
                    this.url = body.user.ws_url;
                    this.lastRefreshTs = new Date().getTime();
                    resolve(body.user.ws_url);
                }
            });
        });
    }

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

