const WebSocket = require('ws');
const WawajiStatus = require('./constants').WawajiStatus;
const StreamMethod = require('./constants').StreamMethod;
const JsmpegStream = require('./jsmpegStream');
const ImageStream = require('./imageStream');
const request = require('request');
const Utils = require('./utils');

var global_port = 8100;

var debug = true;

var dbg = function () {
    if (debug) {
        var x = [];
        for (var i in arguments) x.push(arguments[i]);
        console.log.apply(null, ['Agora sig client dbg :'].concat(x));
    }
};

Wawaji = {};

Wawaji.Server = function (io) {
    //utils
    var client = this;
    this.onStarted = null;

    /*------------------------------------------------
    |   Session API : initiate
    \*----------------------------------------------*/
    this.channel = null;
    this.ipaddress = Utils.getDomain().replace("\n", "") || Utils.getIp();


    /*------------------------------------------------
    |   Class : Machines
    \*----------------------------------------------*/
    Wawaji.MachineSet = function () {
        var collection = this;
        this.__machines = [];
        this.add = function (name, url, cb) {
            collection.__machines.push(new Wawaji.Machine(name, url, cb));
            dbg("machine " + name + " added");
            return collection;
        }

        this.remove = function (name) {
            collection.__machines = collection.__machines.filter(function(item){
                return item.name !== name;
            });
            return collection;
        }

        this.get = function (name) {
            for (var i = 0; i < collection.__machines.length; i++) {
                var machine = collection.__machines[i];
                if (name === machine.name) {
                    return machine;
                }
            }
            return null;
        }

        this.all = function(){
            var machines = Object.assign([], collection.__machines);
            return machines;
        }

        this.toJSON = function () {
            var results = [];
            dbg(`toJSON ${collection.__machines.length} machines`);
            for (var i = 0; i < collection.__machines.length; i++) {
                var machine = collection.__machines[i];
                if (machine.online) {
                    results.push({ name: machine.name, status: machine.status, players: [], video_channel: machine.video_channel, video_host: machine.video_host, video_appid: machine.video_appid, video_rotation: machine.video_rotation, stream_method: machine.stream_method });
                }
            }
            return results;
        }
    }



    Wawaji.User = function (uid, account) {
        this.uid = uid;
        this.account = account;
    }


    /*------------------------------------------------
    |   Class : Machine
    \*----------------------------------------------*/
    Wawaji.Machine = function (name, profile, cb) {
        var machine = this;
        this.status = WawajiStatus.INITIAL;
        this.name = "wawaji_" + name;
        machine.profile = profile;
        this.uid = null;
        this.channel = null;
        this.users = [];
        this.queue = [];
        this.socket = null;
        this.url = profile.url;
        this.playing = null;
        this.video_channel = profile.video_channel;
        this.video_host = profile.video_host;
        this.video_appid = profile.appid;
        this.video_rotation = profile.video_rotation;
        this.result = false;
        this.prepare_timer = null;
        this.game_timer = null;
        this.result_timer = null;
        this.stream_method = profile.mode;
        this.stream_port1 = global_port++;
        this.stream_port2 = global_port++;
        this.websocket_port1 = global_port++;
        this.websocket_port2 = global_port++;
        this.online = false;
        // this.attributes = { queue: [], playing: null, cameras: { front: this.websocket_port1, back: this.websocket_port2 } };


        dbg(`stream: ${machine.stream_port1}, ${machine.stream_port2} ws: ${machine.websocket_port1},${machine.websocket_port2}`);
        if (machine.stream_method === StreamMethod.JSMPEG) {
            if (profile.appcert) {
                request(`http://recording.agorapremium.agora.io:9001/agora/media/genDynamicKey5?uid=0&key=${profile.appid}&sign=${profile.appcert}&channelname=${profile.video_channel}`, function (err, response, body) {
                    machine.stream = new JsmpegStream(machine.stream_port1, machine.stream_port2, machine.websocket_port1, machine.websocket_port2, profile.stream_secret, profile.appid, profile.video_channel, body, cb);
                });
            } else {
                machine.stream = new JsmpegStream(machine.stream_port1, machine.stream_port2, machine.websocket_port1, machine.websocket_port2, profile.stream_secret, profile.appid, profile.video_channel, null, cb);
            }
        } else {
            if (!profile.video_host) {
                machine.stream = new ImageStream(io, profile.appid, profile.video_channel, null, "1", "2");
            }
        }
    }

    client.machines = new Wawaji.MachineSet();
}

module.exports = Wawaji.Server;