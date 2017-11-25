var debug = true;

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
    this.appid = "8b0faaf944034061a5ffd263d3f3f7a4";
    this.url = "ws://116.62.228.246:60011?t=9b41c170-0580-46a5-a066-7dd9151d83a6&target=agora";
    this.video_channel = "wawajiDemo";

    this.init = function(machine){
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
}


module.exports = ZhuaZhuaProfile;