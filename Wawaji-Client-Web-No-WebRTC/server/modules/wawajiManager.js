var Signal = require('../vendor/signal.js');
var vault = require('./vault');
var SignalingToken = require('./token');
const WebSocket = require('ws');

const WawajiStatus = {
    INITIAL: 0,
    INITIALIZING: 1,
    WAITING: 2,
    READY: 3,
    BUSY: 4,
    RESULT: 6
}

var debug = false;

var dbg = function () {
    if (debug) {
        var x = [];
        for (var i in arguments) x.push(arguments[i]);
        console.log.apply(null, ['Agora sig client dbg :'].concat(x));
    }
};

Wawaji = {};

Wawaji.Server = function (serverid) {
    //utils
    var client = this;

    /*------------------------------------------------
    |   Session API : events
    \*----------------------------------------------*/
    this.onStarted = null;
    this.onStartFailed = null;

    /*------------------------------------------------
    |   Session API : initiate
    \*----------------------------------------------*/
    //begin creating singal
    var signal = Signal(vault.appid);
    var session = signal.login("wawaji_cc_" + serverid, SignalingToken.get(vault.appid, vault.appcert, "wawaji_cc_" + serverid, 1));
    this.uid = null;
    this.channel = null;

    session.onLoginSuccess = function (uid) {
        dbg("login successful " + uid);
        client.uid = uid;
        client.machines = new Wawaji.MachineSet();
        client.onStarted && client.onStarted();
    };

    //if fail
    session.onLoginFailed = function () {
        dbg("login failed ");
        client.onStartFailed && client.onStartFailed();
    };

    session.onMessageInstantReceive = function (account, uid, msg) {
        dbg("msg received from " + account + ": " + msg);
        var data = JSON.parse(msg);
        var machine = null;
        var response = null;

        if (data.type !== undefined) {
            switch (data.type) {
                case "LIST":
                    response = { type: "LIST", machines: client.machines }
                    session.messageInstantSend(account, JSON.stringify(response));
                    break;
                case "PLAY":
                    machine = client.machines.get(data.machine);
                    machine && machine.play(account);
                    break;
            }
        }
    }

    /*------------------------------------------------
    |   Class : Machines
    \*----------------------------------------------*/
    Wawaji.MachineSet = function () {
        var collection = this;
        this.__machines = [];
        this.add = function (name, url) {
            collection.__machines.push(new Wawaji.Machine(name, url));
            dbg("machine " + name + " added");
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

        this.toJSON = function () {
            var results = [];
            for (var i = 0; i < collection.__machines.length; i++) {
                var machine = collection.__machines[i];
                results.push({ name: machine.name, status: machine.status, players: machine.users });
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
    Wawaji.Machine = function (name, url) {
        var machine = this;
        this.status = WawajiStatus.INITIAL;
        this.name = "wawaji_" + name;

        var signal = Signal(vault.appid);
        var session = signal.login(this.name, SignalingToken.get(vault.appid, vault.appcert, this.name, 1));
        this.session = session;
        this.uid = null;
        this.channel = null;
        this.users = [];
        this.queue = [];
        this.socket = null;
        this.url = url;
        this.playing = null;
        this.result = false;

        initWS();

        function initWS(cb) {
            if(machine.socket){
                cb && cb();
                return;
            }
            if (machine.url) {
                var socket = new WebSocket(machine.url);
                machine.socket = socket;
                machine.status = WawajiStatus.INITIALIZING;
                socket.on('open', function open() {
                    dbg("WebSocket opened for " + machine.name);
                });

                socket.on('message', function incoming(data) {
                    dbg(machine.name + " WebSocket receive: " + data);
                    var json = JSON.parse(data);
                    switch (json.type) {
                        case "Wait":
                            machine.status = WawajiStatus.WAITING;
                            break;
                        case "Ready":
                            machine.status = WawajiStatus.READY;
                            cb && cb();
                            break;
                        case "State":
                            onStateChange(json.data);
                            break;
                        case "Result":
                            machine.result = json.data;
                            break;
                    }
                });

                function onStateChange(data) {
                    var player = null;
                    switch (data) {
                        case "PLAY":
                        case "WAITRESULT":
                        case "RET":
                            machine.status = WawajiStatus.BUSY;
                            break;
                        case "WAIT":
                            machine.setPlaying(null);
                            machine.status = WawajiStatus.READY;
                            machine.playNext();
                            break;
                    }
                }

                socket.onclose = function (e) {
                    dbg("WebSocket closed for " + machine.name);
                    machine.socket = null;
                }
            }
        }

        session.onLoginSuccess = function (uid) {
            dbg("login successful " + uid);
            machine.uid = uid;
            machine.channel = session.channelJoin("room_" + machine.name);
            machine.channel.onChannelJoined = function () {
                dbg(machine.name + " connected successfully");
                machine.emptyQueue();
                machine.setPlaying(null);
            };

            machine.channel.onChannelJoinFailed = function (ecode) {
                dbg("machine connect failed");
            };

            machine.channel.onChannelUserJoined = function (account, uid) {
                machine.users.push(new Wawaji.User(uid, account));
                dbg(account + " joined, " + machine.users.length + " players in " + machine.name);
            };

            machine.channel.onChannelUserLeaved = function (account, uid) {
                machine.dequeuePlayer(account);
                machine.users = machine.users.filter(function (item) {
                    return item.uid !== uid;
                });
                dbg(account + " leaved, " + machine.users.length + " players in " + machine.name);
            };

            machine.channel.onChannelUserList = function (users) {
                var results = [];
                for (var i = 0; i < users.length; i++) {
                    if (users[i][0] === machine.name) {
                        continue;
                    }
                    results.push(new Wawaji.User(users[i][1], users[i][0]));
                }
                machine.users = results;
                dbg(machine.users.length + " players in " + machine.name);
            };
        };

        //if fail
        session.onLoginFailed = function () {
            dbg("machine login failed");
        };

        session.onMessageInstantReceive = function (account, uid, msg) {
            if(account !== machine.playing){
                return;
            }
            dbg("msg received from " + account + ": " + msg);
            var data = JSON.parse(msg);

            if (data && data.type) {
                if(data.type === "CONTROL"){
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
                    initWS(function () { machine.socket.send(JSON.stringify(control_data)) });
                } else if(data.type === "CATCH"){
                    initWS(function () { machine.socket.send(JSON.stringify({type: 'Control', data: 'b'})) });
                }
            }
        }

        this.play = function (account) {
            dbg("machine status: " + machine.status);
            if (machine.playing === account) {
                dbg("you are already playing");
                return false;
            }
            if (machine.canPlay()) {
                machine.setPlaying(account);
                initWS(function () { machine.socket.send(JSON.stringify({ type: "Insert", data: "", "extra": null })) });
                return true;
            } else {
                machine.queuePlayer(account);
            }
            return false;
        };

        this.playNext = function(){
            var player = machine.nextPlayer();
            dbg("try to start next play: " + player);
            if(player && machine.status === WawajiStatus.READY){
                machine.setPlaying(player);
                initWS(function () { 
                    dbg("insert coin")
                    machine.socket.send(JSON.stringify({ type: "Insert", data: "", "extra": null }))
                })
            }
        }

        this.canPlay = function (account) {
            return machine.status === WawajiStatus.READY && machine.queue.length === 0;
        };

        this.setPlaying = function (account) {
            dbg("now playing set to " + account);
            machine.playing = account;
            machine.setAttr("playing", account);
        }

        this.emptyQueue = function(){
            dbg("empty queue");
            machine.queue = [];
            machine.setAttr("queue", JSON.stringify(machine.queue));
        }

        this.queuePlayer = function (account) {
            dbg("put " + account + " in queue");
            if(machine.queue.indexOf(account) !== -1){
                dbg(account + " already in queue");
                return
            }
            machine.queue.push(account);
            machine.setAttr("queue", JSON.stringify(machine.queue));
        }

        this.dequeuePlayer = function (account) {
            dbg("remove " + account + " from queue");
            machine.queue = machine.queue.filter(function (item) {
                return item.account !== account;
            });
            machine.setAttr("queue", JSON.stringify(machine.queue));
        }

        this.nextPlayer = function () {
            dbg("queue before" + JSON.stringify(machine.queue));
            var player = machine.queue.shift();
            dbg("queue after" + JSON.stringify(machine.queue));
            player && dbg("queue next player " + player);
            machine.setAttr("queue", JSON.stringify(machine.queue));
            return player;
        }

        this.setAttr = function (key, val) {
            machine.channel && machine.channel.channelSetAttr(key, val);
        }
    }
}

module.exports = Wawaji.Server;