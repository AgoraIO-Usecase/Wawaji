
const vault = require('./vault.js')
var debug = true;
const WawajiStatus = {
    INITIAL: 0,
    INITIALIZING: 1,
    WAITING: 2,
    READY: 3,
    BUSY: 4,
    RESULT: 6
}
var dbg = function () {
    if (debug) {
        var x = [];
        for (var i in arguments) x.push(arguments[i]);
        console.log.apply(null, ['Agora ZhuaZhua profile dbg :'].concat(x));
    }
};

ZhuaZhuaProfile = function(){
    var profile = this;
    this.machine = null;
    this.appid = vault.appid;
    this.url = vault.url;
    this.video_channel = vault.video_channel;
    this.video_host = vault.video_host;
    this.video_rotation = 90;

    this.onInit = function(machine){
        profile.machine = machine;
        machine.socket.on('open', function open() {
            dbg("WebSocket opened");
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
        profile.machine.status = WawajiStatus.READY;
        profile.machine.setPlaying(account);
    }

    this.controlData = function(data){

        var control_data = {
            type: 'Control',
            data: ''
        };
        switch (data.data) {
            case 'left': control_data.data = data.pressed ? 'l' : 'A'; break;
            case 'right': control_data.data = data.pressed ? 'r' : 'D'; break;
            case 'up': control_data.data = data.pressed ? 'u' : 'W'; break;
            case 'down': control_data.data = data.pressed ? 'd' : 'S'; break;
            case 'b': control_data.data = 'b';break;
            default: break;
        }

        return control_data;
    }
}


module.exports = ZhuaZhuaProfile;