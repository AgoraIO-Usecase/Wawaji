const vault = require('./vault.js')
var debug = true;
const WawajiStatus = require('../../constants').WawajiStatus;
var dbg = function () {
    if (debug) {
        var x = [];
        for (var i in arguments) x.push(arguments[i]);
        console.log.apply(null, ['Agora ZhuaZhua profile dbg :'].concat(x));
    }
};

TestProfile = function(mode, video_channel){
    var profile = this;
    this.machine = null;
    this.appid = vault.appid;
    this.appcert = vault.appcert;
    this.url = vault.url;
    this.video_channel = video_channel || vault.video_channel;
    this.video_host = vault.video_host;
    this.video_rotation = vault.video_rotation;
    this.game_timeout = null;
    this.stream_secret = vault.stream_secret;
    this.mode = mode;

    this.onInit = function(machine){
        profile.machine = machine;
        machine.socket.on('open', function open() {
            dbg("WebSocket opened");
            profile.machine.status = WawajiStatus.READY;
        });

        machine.socket.on('message', function incoming(data) {
            dbg(machine.name + " WebSocket receive: " + data);
        });

        machine.socket.onclose = function (e) {
            dbg("WebSocket closed for " + machine.name);
            machine.socket = null;
        }
    }

    this.onPlay = function(account){
        profile.game_timeout = setTimeout(function(){
            dbg("auto catch after waiting for 30 seconds");
            profile.onCatch();
        }, 30000);
    }

    this.onControl = function(data){

        var control_data = {
            type: 'Control',
            data: ''
        };
        switch (data.data) {
            case 'left': control_data.data = data.pressed ? 'l' : 'A'; break;
            case 'right': control_data.data = data.pressed ? 'r' : 'D'; break;
            case 'up': control_data.data = data.pressed ? 'u' : 'W'; break;
            case 'down': control_data.data = data.pressed ? 'd' : 'S'; break;
            default: break;
        }
        profile.machine.socket.send(JSON.stringify(control_data));
    }

    this.onCatch = function(){
        clearTimeout(profile.game_timeout);
        var control_data = {
            type: 'Control',
            data: 'b'
        };

        profile.machine.socket.send(JSON.stringify(control_data));

        setTimeout(function(){
            profile.machine.channel.messageChannelSend(JSON.stringify({type: "RESULT", data: false, player: profile.machine.playing}));
            profile.machine.status = WawajiStatus.READY;
            profile.machine.processQueue();
        }, 5000);
    }
}


module.exports = TestProfile;