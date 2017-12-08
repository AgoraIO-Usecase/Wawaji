const vault = require('../../vault.js').leyaoyao;
const request = require('request');
var debug = true;
const WawajiStatus = require('../../constants').WawajiStatus;
var dbg = function () {
    if (debug) {
        var x = [];
        for (var i in arguments) x.push(arguments[i]);
        console.log.apply(null, ['Agora Leyaoyao profile dbg :'].concat(x));
    }
};

LeyaoyaoProfile = function(mode){
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

    this.onResult = null;
    this.onError = null;

    this.sendMessage = function(msgObj, type){
        var id = new Date().getTime();
        var data = {type:type, data: msgObj, extra: id};
        profile.actions[id] = data;
        profile.machine.socket.send(JSON.stringify(data));
        dbg(`sending action ${JSON.stringify(data)}`);
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
                var action = profile.actions[json.extra] || {};

                switch (json.type) {
                    case "Ready": {
                        break;
                    }
                    case "Result": {
                        if(json.data !== undefined) {
                            profile.onResult && profile.onResult(json.data);
                        }
                        break;
                    }
                    case "Error": {
                        profile.onError && profile.onError();
                        break;
                    }
                    default:
                        break;
                }
    
                delete profile[json.extra];
            }
        });
    }

    this.onPlay = function(account){

        request(profile.http_url, function (err, response, body) {
            console.log(body);
            var msg = JSON.parse(body);
            if (msg) {
                profile.url = msg.data.wsUrl;
                profile.onReinitWS(function(){
                    profile.sendMessage(null, "Insert");
                })
            }
        });

    }

    this.onControl = function(data){
        var control_data = {};
        switch (data.data) {
            case 'left':  control_data = data.pressed ? {"direction":"l"} : {"direction":"A"}; break;
            case 'right': control_data = data.pressed ? {"direction":"r"} : {"direction":"D"}; break;
            case 'up':    control_data = data.pressed ? {"direction":"u"} : {"direction":"W"}; break;
            case 'down':  control_data = data.pressed ? {"direction":"d"} : {"direction":"S"}; break;
            default: break;
        }
        profile.sendMessage(control_data, "Control");
    }

    this.onCatch = function(){
        var data = {"direction":"b"};
        profile.sendMessage(data, "Control");
    }
}


module.exports = LeyaoyaoProfile;