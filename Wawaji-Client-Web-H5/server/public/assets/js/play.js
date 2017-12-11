function preload(items) {
    for (i = 0; i < items.length; i++) {
        var img = new Image()
        img.src = items[i]
    }
}
preload(
    "/assets/images/up.png",
    "/assets/images/up_down.png",
    "/assets/images/left.png",
    "/assets/images/left_down.png",
    "/assets/images/down.png",
    "/assets/images/down_down.png",
    "/assets/images/right.png",
    "/assets/images/right_down.png",
    "/assets/images/catcher.png",
    "/assets/images/catcher_down.png"
)

$(function () {
    window.oncontextmenu = function (event) {
        event.preventDefault();
        event.stopPropagation();
        return false;
    };
    var getParameterByName = function(name, url) {
        if (!url) url = window.location.href;
        name = name.replace(/[\[\]]/g, "\\$&");
        var regex = new RegExp("[?&]" + name + "(=([^&#]*)|&|#|$)"),
            results = regex.exec(url);
        if (!results) return null;
        if (!results[2]) return '';
        return decodeURIComponent(results[2].replace(/\+/g, " "));
    }
    var namespace = getParameterByName("namespace") || "";
    var appid = Vault.appid, appcert = Vault.appcert;
    var wawaji_control_center = namespace + Vault.cc_server;
    var debug = getParameterByName("debug") === "true";
    var loading = true;
    var startTime = new Date().getTime();
    var dbg = function () {
        if (debug) {
            var x = [];
            for (var i in arguments) x.push(arguments[i]);
            var msg = [(new Date().getTime() - startTime) + "ms: "].concat(x);
            console.log(msg.join(":"));
            $(".logs").show();
            $("<li>" + msg + "</li>").appendTo(".logs");
        }
    };
    var randName = function (length) {
        var text = "";
        var charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
        for (var i = 0; i < parseInt(length); i++)
            text += charset.charAt(Math.floor(Math.random() * charset.length));
        return text;
    };

    var machine_name = getParameterByName("machine");
    var machine_list = JSON.parse(localStorage.getItem("machines"));

    if (!machine_name || !machine_list) {
        location.href = "index.html";
    }

    dbg("document loaded");

    var getKey = function (machine) {
        var deferred = $.Deferred();
        if (!machine.dynamicKeyEnabled) {
            return deferred.resolve(null).promise();
        } else {
            $.ajax({
                url: "/v1/key",
                // url: "/v1/key",
                type: "GET", //send it through get method
                data: {
                    appid: machine.appid,
                    channel: machine.channel
                }
            }).done(function (key) {
                dbg("get key success")
                deferred.resolve(key.key);
            });
        }
        return deferred.promise();
    }

    var getGateways = function (machine) {
        var deferred = $.Deferred();
        $.ajax({
            url: "https://h5cs-1.agoraio.cn:7668/geth5gw/jsonp",
            type: "POST",
            headers: {
                "Content-type": "application/json; charset=utf-8"
            },
            data: JSON.stringify({
                key: machine.appid,
                cname: machine.channel
            })
        }).done(function(domains){
            dbg("get gateway success")
            deferred.resolve(domains);
        }).fail(function(){
            deferred.reject();  
        });

        return deferred.promise();
    }

    var prepare_meta = function (machine, cb) {
        $.when(getKey(machine), getGateways(machine)).done(function (key, domains) {
            var gateways = domains.gateway_addr || [];

            if (gateways.length === 0) {
                alert("同时观看此机器的人数太多，请稍后再来")
            } else {
                $.ajax({
                    url: "https://" + domains.gateway_addr[0] + "/v1/machine",
                    // url: "http://wawa1.agoraio.cn:4000/v1/machine",
                    // url: "http://127.0.0.1:4000/v1/machine",
                    type: "POST",
                    data: {
                        appid: machine.appid,
                        channel: machine.channel,
                        key: key,
                        uid1: 1,
                        uid2: 2
                    }
                }).done(function (video_info) {
                    dbg("get video info success")
                    cb(video_info);
                }).fail(function (e) {
                    console.log("err: failed to get machine info");
                });
            }
        })
    }


    var Lobby = function (account, cb) {
        var lobby = this;
        this.account = account;
        this.signal = Signal(appid);
        this.uid = null;
        this.machines = [];
        this.game = null;
        this.session = this.signal.login(account, SignalingToken.get(appid, appcert, account, 1));
        this.session.onLoginSuccess = function (uid) {
            dbg("signal login successful account:" + lobby.account + " uid: " + uid);
            lobby.uid = uid;

            cb && cb();
        };

        //if fail
        this.session.onLoginFailed = function () {
            // dbg("login failed ");
        };

        this.session.onMessageInstantReceive = function (account, uid, msg) {
            console.log("message received: " + msg);
            var data = JSON.parse(msg);
            if (data.type !== undefined) {
                switch (data.type) {
                    case "INFO":
                        console.log(msg);
                        break;
                    case "ERROR":
                        alert("错误");
                        break;
                    case "PREPARE":
                        console.log("receive prepare, sending start to " + lobby.game.machine.name);
                        lobby.session.messageInstantSend(lobby.game.machine.name, JSON.stringify({ type: "START" }));
                        break;
                }
            }
        }

        Lobby.Game = function (machine, account, info) {
            var game = this;

            this.machine = machine;
            this.account = account;
            this.video_info = info;
            this.users = 0;
            game.queue = [];
            game.playing = null;

            this.channel = lobby.session.channelJoin(namespace + this.machine.room_name);
            this.channel.onChannelJoined = function () {
                dbg("Enter room " + game.machine.name + "");
            };

            this.channel.onChannelJoinFailed = function (ecode) {
                dbg("machine connect failed");
            };

            this.channel.onChannelAttrUpdated = function (type, k, v) {
                dbg(`type: ${type}, k: ${k}, v: ${v}`);
                var attrs = {}
                if (k === "attrs" && (type === "update" || type === "set")) {
                    attrs = JSON.parse(v) || {};
                }
                if ((v === "update" || v === "set") && type === "attrs") {
                    attrs = JSON.parse(k) || {};
                }
                game.queue = attrs.queue || [];
                game.playing = attrs.playing;
                updateViews();
                dbg('machine attributes updated ' + type + ' ' + k + ' ' + v);
            };

            this.channel.onChannelUserList = function (users) {
                game.users = users.length;
                $(".banner-container .user-number").text(game.users + "人在房间");
            }

            this.channel.onChannelUserJoined = function (users) {
                game.users = game.users + 1;
                $(".banner-container .user-number").text(game.users + "人在房间");
            }

            this.channel.onChannelUserLeave = function (users) {
                game.users = game.users - 1;
                $(".banner-container .user-number").text(game.users + "人在房间");
            }

            this.channel.onMessageChannelReceive = function (account, uid, msg) {
                var result;
                console.log("channel message received: " + msg);
                var data = JSON.parse(msg);
                if (data.type !== undefined) {
                    switch (data.type) {
                        case "RESULT":
                            result = data.data;
                            if (data.player === lobby.account) {
                                if (result) {
                                    showMessage("抓到啦！", "再来一次")
                                } else {
                                    showMessage("好遗憾..！", "我不服")
                                }
                            }
                            break;
                        case "PLAY_COUNTING":
                            result = data.data;
                            $(".control-catch").text("(" + result + "s)")
                            break;
                    }
                }
            };

            this.play = function () {
                lobby.session.messageInstantSend(wawaji_control_center, JSON.stringify({ "type": "PLAY", "machine": machine_name }));
            }
            this.control = function (data, pressed) {
                var action = data;
                if (!game.player.isUsingFrontCamera()) {
                    //if is using side camera, update control
                    switch (data) {
                        case 'left':
                            action = 'down';
                            break;
                        case 'right':
                            action = 'up';
                            break;
                        case 'up':
                            action = 'left';
                            break;
                        case 'down':
                            action = 'right';
                            break;
                    }
                }
                game.channel.messageChannelSend(JSON.stringify({ "type": "CONTROL", "data": action, "pressed": pressed }));
            }
            this.catch = function () {
                game.channel.messageChannelSend(JSON.stringify({ "type": "CATCH" }));
            }


            Lobby.VideoPlayer = function (info) {
                var player = this;
                player.cameras = info.cameras || {};
                player.camera = info.cameras.main;
                player.player1 = null;
                player.player2 = null;
                player.slow_switch = parseInt(getParameterByName("slow_switch")) === 1;

                if (game.machine.video_rotation === 90) {
                    $("#jsmpeg-player").addClass("rotation-90");
                    $("#jsmpeg-player2").addClass("rotation-90");
                }


                player.isUsingFrontCamera = function () {
                    return player.cameras && player.camera === player.cameras.main;
                }

                player.play = function (url, position) {
                    var canvas = document.getElementById('jsmpeg-player');
                    var canvas2 = document.getElementById('jsmpeg-player2');
                    if (position === 0) {
                        //front
                        // player.player2.stop();
                        $(canvas2).hide();
                        // player.player1.seek(player.player1.currentTime);
                        // player.player1.play();
                        $(canvas).show();
                    } else {
                        //side
                        // player.player1.stop();
                        $(canvas).hide();
                        // player.player2.seek(player.player1.currentTime);
                        // player.player2.play();
                        $(canvas2).show();
                    }
                }
                player.switchCamera = function () {
                    if (player.camera === player.cameras.main) {
                        player.camera = player.cameras.sub;
                        player.play(player.camera, 1);
                    } else {
                        player.camera = player.cameras.main;
                        player.play(player.camera, 0);
                    }
                }

                var canvas = document.getElementById('jsmpeg-player');
                var canvas2 = document.getElementById('jsmpeg-player2');
                dbg("setup jsmpeg player..")
                player.player1 = new JSMpeg.Player(player.cameras.main, {
                    canvas: canvas,
                    audio: false,
                    autoplay: false,
                    decodeFirstFrame: true,
                    agora_id: 1,
                    onStartDecoding: function(){
                        dbg("play start.")
                        loading = false;
                        updateViews();
                    }
                 });
                player.player2 = new JSMpeg.Player(player.cameras.sub, { canvas: canvas2, audio: false, autoplay: false, decodeFirstFrame: true, agora_id: 2 });
                player.play(player.camera, 0);
            }

            game.player = new Lobby.VideoPlayer(game.video_info);
        }

    };

    var account = getParameterByName("account") || localStorage.getItem("account") || randName(10);
    // localStorage.setItem("account", account);

    var lobby_prepare = $.Deferred();
    var meta_prepare = $.Deferred();
    var lobby = new Lobby(account, function () {
        lobby_prepare.resolve();
    });
    for (var i = 0; i < machine_list.length; i++) {
        if (machine_list[i].name === machine_name) {
            prepare_meta(machine_list[i], function (video_info) {
                meta_prepare.resolve(video_info);
            });
            break;
        }
    }
    $.when(lobby_prepare, meta_prepare).done(function(result, video_info){
        lobby.game = new Lobby.Game(machine_list[i], lobby.account, video_info);
    });


    (function layoutItems() {
        var width = $(document).innerWidth(), height = $(document).innerHeight();
        // $('#video').width(width > 468 ? 468 : width);
        $('#video').height(height - 200);
        // // $('#game').width(width > 468 ? 468 : width);
        // $('#game').height(height * 2 / 5);

        var baseH = 55;
        var baseV = height - 200 + 40;
        $('.control-left').css("left", baseH - 40 + "px");
        $('.control-left').css("top", (baseV + 30) + "px");
        $('.control-up').css("left", baseH + 20 + "px");
        $('.control-up').css("top", baseV - 20 + "px");
        $('.control-down').css("left", baseH + 20 + "px");
        $('.control-down').css("top", baseV + 75 + "px");
        $('.control-right').css("left", baseH + 80 + "px");
        $('.control-right').css("top", baseV + 30 + "px");


        $('.control-catch').css("top", baseV + 10 + "px");
        $('.control-catch').css("right", baseH - 30 + "px");
    })();


    function isMobile() {
        var check = false;
        (function (a) { if (/(android|bb\d+|meego).+mobile|avantgo|bada\/|blackberry|blazer|compal|elaine|fennec|hiptop|iemobile|ip(hone|od)|iris|kindle|lge |maemo|midp|mmp|mobile.+firefox|netfront|opera m(ob|in)i|palm( os)?|phone|p(ixi|re)\/|plucker|pocket|psp|series(4|6)0|symbian|treo|up\.(browser|link)|vodafone|wap|windows ce|xda|xiino|android|ipad|playbook|silk/i.test(a) || /1207|6310|6590|3gso|4thp|50[1-6]i|770s|802s|a wa|abac|ac(er|oo|s\-)|ai(ko|rn)|al(av|ca|co)|amoi|an(ex|ny|yw)|aptu|ar(ch|go)|as(te|us)|attw|au(di|\-m|r |s )|avan|be(ck|ll|nq)|bi(lb|rd)|bl(ac|az)|br(e|v)w|bumb|bw\-(n|u)|c55\/|capi|ccwa|cdm\-|cell|chtm|cldc|cmd\-|co(mp|nd)|craw|da(it|ll|ng)|dbte|dc\-s|devi|dica|dmob|do(c|p)o|ds(12|\-d)|el(49|ai)|em(l2|ul)|er(ic|k0)|esl8|ez([4-7]0|os|wa|ze)|fetc|fly(\-|_)|g1 u|g560|gene|gf\-5|g\-mo|go(\.w|od)|gr(ad|un)|haie|hcit|hd\-(m|p|t)|hei\-|hi(pt|ta)|hp( i|ip)|hs\-c|ht(c(\-| |_|a|g|p|s|t)|tp)|hu(aw|tc)|i\-(20|go|ma)|i230|iac( |\-|\/)|ibro|idea|ig01|ikom|im1k|inno|ipaq|iris|ja(t|v)a|jbro|jemu|jigs|kddi|keji|kgt( |\/)|klon|kpt |kwc\-|kyo(c|k)|le(no|xi)|lg( g|\/(k|l|u)|50|54|\-[a-w])|libw|lynx|m1\-w|m3ga|m50\/|ma(te|ui|xo)|mc(01|21|ca)|m\-cr|me(rc|ri)|mi(o8|oa|ts)|mmef|mo(01|02|bi|de|do|t(\-| |o|v)|zz)|mt(50|p1|v )|mwbp|mywa|n10[0-2]|n20[2-3]|n30(0|2)|n50(0|2|5)|n7(0(0|1)|10)|ne((c|m)\-|on|tf|wf|wg|wt)|nok(6|i)|nzph|o2im|op(ti|wv)|oran|owg1|p800|pan(a|d|t)|pdxg|pg(13|\-([1-8]|c))|phil|pire|pl(ay|uc)|pn\-2|po(ck|rt|se)|prox|psio|pt\-g|qa\-a|qc(07|12|21|32|60|\-[2-7]|i\-)|qtek|r380|r600|raks|rim9|ro(ve|zo)|s55\/|sa(ge|ma|mm|ms|ny|va)|sc(01|h\-|oo|p\-)|sdk\/|se(c(\-|0|1)|47|mc|nd|ri)|sgh\-|shar|sie(\-|m)|sk\-0|sl(45|id)|sm(al|ar|b3|it|t5)|so(ft|ny)|sp(01|h\-|v\-|v )|sy(01|mb)|t2(18|50)|t6(00|10|18)|ta(gt|lk)|tcl\-|tdg\-|tel(i|m)|tim\-|t\-mo|to(pl|sh)|ts(70|m\-|m3|m5)|tx\-9|up(\.b|g1|si)|utst|v400|v750|veri|vi(rg|te)|vk(40|5[0-3]|\-v)|vm40|voda|vulc|vx(52|53|60|61|70|80|81|83|85|98)|w3c(\-| )|webc|whit|wi(g |nc|nw)|wmlb|wonu|x700|yas\-|your|zeto|zte\-/i.test(a.substr(0, 4))) check = true; })(navigator.userAgent || navigator.vendor || window.opera)
        return check;
    }

    var start_event = isMobile() ? "touchstart" : "mousedown";
    var end_event = isMobile() ? "touchend" : "mouseup";

    $(".controls .main").off("click").on("click", function () {
        var text = $(this).text();
        if (text === "开始游戏") {
            lobby.game.play();
        } else if (text === "预约排队") {
            lobby.game.play();
        }
        //todo disable btn
    });

    $(".control-camera").off("click").on("click", function () {
        lobby.game.player.switchCamera();
    });

    $("body").on(start_event, ".control-left", function () {
        lobby.game.control('left', true)
    });
    $("body").on(start_event, ".control-right", function () {
        lobby.game.control('right', true)
    });
    $("body").on(start_event, ".control-up", function () {
        lobby.game.control('up', true)
    });
    $("body").on(start_event, ".control-down", function () {
        lobby.game.control('down', true)
    });

    $("body").on(end_event, ".control-left", function () {
        lobby.game.control('left', false)
    });
    $("body").on(end_event, ".control-right", function () {
        lobby.game.control('right', false)
    });
    $("body").on(end_event, ".control-up", function () {
        lobby.game.control('up', false)
    });
    $("body").on(end_event, ".control-down", function () {
        lobby.game.control('down', false)
    });
    $("body").on(end_event, ".control-catch", function () {
        lobby.game.catch()
    });

    function showMessage(mainText, subText, cb) {
        $(".top-layer").show();
        $(".top-layer .message-box").html(mainText);
        $(".top-layer .confirm").html(subText);

        $(".top-layer .confirm").off("click").on("click", function () {
            cb && cb();
            $(".top-layer").hide();
        })
    }

    function updateViews() {
        if( loading ){
            $(".loading").show();
        } else {
            $(".loading").hide();
            $("#video").show();
            if (lobby.game) {
                //control logic
                var idx = lobby.game.queue.indexOf(lobby.game.account);
                if (lobby.game.playing !== account) {
                    //not yet in play
                    $(".controls-game").hide();
                    $(".controls").show();
    
                    if (lobby.game.queue.length === 0 && !lobby.game.playing) {
                        //no people in queue, starts directly
                        $(".controls .main .content").text("开始游戏");
                        $(".controls .info").text("");
                    } else {
                        //people in queue
                        var queuelength = lobby.game.playing ? 1 : 0;
                        if (idx !== -1) {
                            queuelength += idx;
                            //i am already in queue
                            $(".controls .main .content").text("已预约");
                            //todo disable button
                        } else {
                            queuelength += lobby.game.queue.length;
                            $(".controls .main .content").text("预约排队");
                        }
                        $(".controls .info").text(queuelength === 0 ? "" : "前面还有" + queuelength + "人排队");
                    }
    
                } else {
                    //playing
                    $(".controls-game").show();
                    $(".controls").hide();
                }
    
                $(".banner-container .users").remove();
    
                if (lobby.game.playing) {
                    $('<div class="users active"><img src="/assets/images/avatar.png" /></div>').appendTo($(".banner-container"))
                }
                if (lobby.game.queue.length > 0) {
                    for (var i = 0; i < lobby.game.queue.length; i++) {
                        $('<div class="users"><img src="/assets/images/avatar.png" /></div>').appendTo($(".banner-container"))
                    }
                }
            }
        }

        
    }
});