const vault = require('../../vault.js').qiyiguo;
const request = require('request');
const md5 = require('md5');
const sortKeys = require('sort-keys');
const WawajiStatus = require('../../constants').WawajiStatus;

var debug = true;
var dbg = function () {
    if (debug) {
        var x = [];
        for (var i in arguments) x.push(arguments[i]);
        console.log.apply(null, ['Agora Qiyiguo profile dbg :'].concat(x));
    }
};

QiyiguoProfile = function(mode){
    var profile = this;
    this.machine = null;
    this.appid = vault.appid;
    this.appcert = vault.appcert;
    this.url = vault.url;
    this.http_url = '';
    this.video_channel = vault.video_channel;
    this.video_host = vault.video_host;
    this.video_rotation = vault.video_rotation;
    this.stream_secret = vault.stream_secret;
    this.mode = mode;
    this.actions = {};

    this.onResult = null;
    this.onError = null;

    this.sendMessage = function(msgObj, type){
        var msg = {type:type, data:msgObj};
        profile.machine.socket.send(JSON.stringify(msg));
        dbg(`sending action ${JSON.stringify(msg)}`);
    }

    this.onInit = function(machine, done){
        profile.machine = machine;

        machine.socket.on('open', function open() {
            dbg("WebSocket opened");
            done();
        });

        machine.socket.on('message', function incoming(data) {
            dbg(machine.name + " WebSocket receive: " + data);

            var json = JSON.parse(data);
            if(json.type) {
                switch (json.type) {
                    case "Ready": {
                        break;
                    }
                    case "Result": {
                        if(json.data !== undefined) {
                            if (json.data.operate_result === 1 /* TODO ------- "1"*/) {
                                profile.onResult && profile.onResult(true);
                            }
                            else {
                                profile.onResult && profile.onResult(false);
                            }
                        }
                        break;
                    }
                    default:
                        break;
                }
            }
        });
    }

    this.onPlay = function(account){
        profile.genURL(profile.onRequestUrl);
    }

    this.onRequestUrl = function(http_url) {
        request(http_url, function (err, response, body) {
            dbg(body);
            var msg = JSON.parse(body);
            if (msg) {
                if(msg.done === "true") {
                    // TODO ----------------
                    profile.url = msg.wsUrl;
                    profile.onReinitWS(function(){
                        //profile.sendMessage(null, "Insert");
                    });
                }
                else {
                    dbg("Return: " + false);
                }
            }
        });
    }

    this.onControl = function(data){
        var control_data = "";
        switch (data.data) {
            case 'left':  control_data = data.pressed ? "3" : "8"; break;
            case 'right': control_data = data.pressed ? "4" : "9"; break;
            case 'up':    control_data = data.pressed ? "1" : "6"; break;
            case 'down':  control_data = data.pressed ? "2" : "7"; break;
            default: break;
        }
        profile.sendMessage(control_data, "Control");
    }

    this.onCatch = function(){
        var control_data = "5";
        profile.sendMessage(control_data, "Control");
    }

    this.genURL = function(cb) {
        var http_url = vault.http_url_header;
        var device_id = vault.device_id;
        var time = new Date().getTime();
        var params = { 
            "device_id": `${device_id}`,
            "platform": "shengwang",
            "user_id": "1",
            "ts": `${time}`
        }
        var sort_params = sortKeys(params);
        var sign_content = '';
        for (var key in sort_params) {
            var temp = "&" +  key + "=" + sort_params[key];   
            http_url += temp;
            sign_content += key + sort_params[key];
        }

        var partner_secret = vault.partner_secret;
        var sign_ret = md5( md5(sign_content) + partner_secret);
        http_url  += "&sign=" + sign_ret;
        dbg(http_url);

        cb && cb(http_url);
    };
}

module.exports = QiyiguoProfile;

