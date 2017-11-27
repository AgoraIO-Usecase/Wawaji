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
    this.video_rotation = 90;
    this.game_timeout = null;
    this.stream_secret = vault.stream_secret;
    this.mode = mode;
    this.actions = {};

    this.sendMessage = function(msgObj, type){
        var id = new Date().getTime();
        var data = Object.assign({id: id}, msgObj);
        profile.actions[id] = {type:type, data: msgObj};
        profile.machine.socket.send(JSON.stringify(data));
        dbg(`sending action ${JSON.stringify(data)} ${type}`);
    }

    this.onInit = function(machine, cb){
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
                        profile.machine.status = WawajiStatus.READY;
                        cb && cb();
                    } else if(action.type === "PLAY"){
                        profile.machine.status = WawajiStatus.BUSY;
                    }
                } else {
                    dbg(`${action.type} action ${json.id} failed`);
                }
    
                delete profile[json.id];
            } else {
                if(json.type === "message"){
                    if(json.data.result !== undefined){
                        profile.machine.channel.messageChannelSend(JSON.stringify({type: "RESULT", data: json.data.result, player: profile.machine.playing}));
                        profile.machine.status = WawajiStatus.READY;
                        profile.machine.processQueue();
                    }
                }
            }
        });

        machine.socket.onclose = function (e) {
            dbg("WebSocket closed for " + machine.name);
            machine.socket = null;
        }
    }

    this.onPlay = function(account){
        dbg("auto catch after waiting for 30 seconds");
        profile.sendMessage({"uri":"/rooms/3/start","type":"post"}, "PLAY");
        profile.game_timeout = setTimeout(function(){
            profile.onCatch();
        }, 30000);
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
        clearTimeout(profile.game_timeout);
        profile.game_timeout = null;
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