const vault = require('../../vault.js').shuangqu;
const request = require('request');
const logger = require('../../logger');

var debug = true;
const WawajiStatus = require('../../constants').WawajiStatus;
var dbg = function () {
    if (debug) {
        var x = [];
        for (var i in arguments) x.push(arguments[i]);
        console.log.apply(null, ['Agora Shuangqu profile dbg :'].concat(x));
    }
};

ShuangquProfile = function (mode) {
    var profile = this;
    this.machine = null;
    this.appid = vault.appid;
    this.appcert = vault.appcert;
    this.video_channel = vault.video_channel;
    this.video_host = vault.video_host;
    this.video_rotation = vault.video_rotation;
    this.stream_secret = vault.stream_secret;
    this.mode = mode;
    this.actions = {};
    this.log = (new logger('shuangqu', 'shuangqu.log')).get();

    this.url = vault.url;
    this.create_user_url = `${vault.shuangqu_url_prefix}/Doll/createUser/appid/${vault.shuangqu_appid}/sign/${vault.shuangqu_sign}/binding/${vault.shuangqu_user}`;
    this.http_url = `${vault.shuangqu_url_prefix}/Doll/bind/appid/${vault.shuangqu_appid}/sign/${vault.shuangqu_sign}/binding/${vault.shuangqu_user}/roomId/${vault.shuangqu_room}`;

    this.onResult = null;
    this.onError = null;

    this.prepare = () => {
        return new Promise((resolve, reject) => {
            console.log(`prepare url..`);
            request(this.create_user_url, (error, response, body) => {
                console.log(`create user: ${this.create_user_url}`);
                let result = JSON.parse(body);
                if(!result.success){
                    reject(error);
                    return;
                }
                request(this.http_url, (error, response, body) => {
                    console.log(`url request: ${this.http_url}`);
                    result = JSON.parse(body);
                    if(result.success){
                        this.url = result.data.ws_url;
                        resolve(result.data.ws_url);
                    } else {
                        reject(error);
                    }
                })
            });
        });
    }

    this.sendMessage = function (msgObj, type) {
        let data = { event: type, param: msgObj };
        if (profile.machine && profile.machine.socket) {
            profile.machine.socket.send(JSON.stringify(data));
        }
        console.log(`sending action ${JSON.stringify(data)}`);
    }

    this.onInit = (machine, done) => {
        console.log("onInit.");

        profile.machine = machine;

        machine.socket.on('open', function open() {
            console.log("WebSocket opened");
            done();
        });

        machine.socket.on('message', function incoming(data) {
            console.log(machine.name + " WebSocket receive: " + data);
            let json = JSON.parse(data);
            if (json.type) {
                switch (json.type) {
                    case "Status": {
                        if (json.status && (json.status === "Ready")) {
                            let data = { "record": "phoenix_test_record" };
                            profile.sendMessage(data, "start");
                        }
                        if (json.status && (json.status === "Play")) {
                            //done();
                        }
                        break;
                    }
                    case "Result": {
                        if (json.result !== undefined) {
                            profile.onResult && profile.onResult(json.result);
                        }
                        
                        let data = {};
                        profile.sendMessage(data, "close");
                        
                        machine.socket.close();
                        break;
                    }
                    case "Error": {
                        profile.onError && profile.onError();
                        break;
                    }
                    default:
                        break;
                }
            }
        });
    }

    this.onPlay = function (account) {

        request(profile.http_url, function (err, response, body) {
            console.log(`server response body ${body}`);
            let msg = JSON.parse(body);
            if (msg.success && (msg.success === false)) {
                return;
            }
            if (msg.data && msg.data.ws_url) {
                profile.url = msg.data.wsUrl;
                profile.onReinitWS();
            }
        });

    }

    this.onControl = function (data) {
        let control_data = {};
        switch (data.data) {
            case 'left': control_data = data.pressed ? { opeType: "turnLeft" } : { opeType: "stop" }; break;
            case 'right': control_data = data.pressed ? { opeType: "turnRight" } : { opeType: "stop" }; break;
            case 'up': control_data = data.pressed ? { opeType: "turnBack" } : { opeType: "stop" }; break;
            case 'down': control_data = data.pressed ? { opeType: "turnUp" } : { opeType: "stop" }; break;
            default: break;
        }
        profile.sendMessage(control_data, "control");
    }

    this.onCatch = function () {
        let data = { opeType: "turnDown" };
        profile.sendMessage(data, "control");
        if (profile.machine && profile.machine.socket) {
            profile.machine.socket.close();
        }
    }
}

module.exports = ShuangquProfile;