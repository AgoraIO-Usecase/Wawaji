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

ZhuaZhuaProfile = function(mode){
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

    this.onInit = function(machine, done){
        profile.machine = machine;
        machine.socket.on('open', function open() {
            dbg("WebSocket opened");
            done();
        });

        machine.socket.on('message', function incoming(data) {
            dbg(machine.name + " WebSocket receive: " + data);
        });
    }

    this.onPlay = function(account){
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
        var control_data = {
            type: 'Control',
            data: 'b'
        };

        profile.machine.socket.send(JSON.stringify(control_data));

        setTimeout(function(){
            profile.onResult(false);
        }, 7000);
    }
}


module.exports = ZhuaZhuaProfile;