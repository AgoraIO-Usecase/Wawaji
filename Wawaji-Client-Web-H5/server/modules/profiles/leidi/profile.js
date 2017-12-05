const vault = require('./vault.js')
var debug = true;
const WawajiStatus = require('../../constants').WawajiStatus;
var dbg = function () {
    if (debug) {
        var x = [];
        for (var i in arguments) x.push(arguments[i]);
        console.log.apply(null, ['Agora Leidi profile dbg :'].concat(x));
    }
};

LeiDiProfile = function(mode){
    var profile = this;
    this.machine = null;
    this.appid = vault.appid;
    this.appcert = vault.appcert;
    this.url = vault.url;
    this.video_channel = vault.video_channel;
    this.video_host = vault.video_host;
    this.video_rotation = vault.video_rotation;
    this.stream_secret = vault.stream_secret;
    this.mode = mode;
    this.actions = {};

    dbg(`${this.appid}, ${vault.appid}, ${vault.appcert}`);

    this.onResult = null;
    this.onError = null;

    this.sendMessage = function(msgObj, type){
        var id = new Date().getTime();
        var data = Object.assign({id: id}, msgObj);
        profile.actions[id] = {type:type, data: msgObj};
        profile.machine.socket.send(JSON.stringify(data));
        dbg(`sending action ${JSON.stringify(data)} ${type}`);
    }

    this.onInit = function(machine, done){
        profile.machine = machine;
        machine.socket.on('open', function open() {
            dbg("WebSocket opened");
            profile.sendMessage({"uri":"/rooms/3/enter","type":"post","data":{"token":"no_token"}}, "ENTER");
        });

        machine.socket.on('message', function incoming(data) {
            dbg(machine.name + " WebSocket receive: " + data);
            var json = JSON.parse(data);
            if(json.id){
                //action related
                var action = profile.actions[json.id] || {};
                if(json.data.ret === 1){
                    dbg(`${action.type} action ${json.id} success`);
                    if(action.type === "ENTER"){
                        done();
                    } else if(action.type === "PLAY"){
                    }
                } else {
                    dbg(`${action.type} action ${json.id} failed`);
                    profile.onError && profile.onError();
                }
    
                delete profile[json.id];
            } else {
                if(json.type === "message"){
                    if(json.data.result !== undefined){
                        if(json.data.result === 1) {
                            profile.onResult && profile.onResult(true);
                        } else {
                            profile.onResult && profile.onResult(false);
                        }
                    }
                }
            }
        });
    }

    this.onPlay = function(account){
        profile.sendMessage({"uri":"/rooms/3/start","type":"post"}, "PLAY");
    }

    this.onControl = function(data){
        var control_data = {
            "type":"post"
        };
        switch (data.data) {
            case 'left': control_data.uri = data.pressed ? "/rooms/3/move/left" : "/rooms/3/stop"; break;
            case 'right': control_data.uri = data.pressed ? "/rooms/3/move/right" : "/rooms/3/stop"; break;
            case 'up': control_data.uri = data.pressed ? "/rooms/3/move/back" : "/rooms/3/stop"; break;
            case 'down': control_data.uri = data.pressed  ? "/rooms/3/move/front" : "/rooms/3/stop"; break;
            default: break;
        }

        if(data.pressed){
            control_data.data = {time: 2000}
        }

        profile.sendMessage(control_data, "CONTROL");
    }

    this.onCatch = function(){
        var data = {
            "uri":"/rooms/3/catch","type":"post",
            "type": "post"
        }

        profile.sendMessage(data, "CATCH");

        // setTimeout(function(){
        // }, 5000);
    }
}


module.exports = LeiDiProfile;