function preload(items) {
    for (i = 0; i < items.length; i++) {
        var img = new Image()
        img.src = items[i]
    }
}
preload([
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
])

$(function () {
    window.oncontextmenu = function (event) {
        event.preventDefault();
        event.stopPropagation();
        return false;
    };
    var getParameterByName = function (name, url) {
        if (!url) url = window.location.href;
        name = name.replace(/[\[\]]/g, "\\$&");
        var regex = new RegExp("[?&]" + name + "(=([^&#]*)|&|#|$)"),
            results = regex.exec(url);
        if (!results) return null;
        if (!results[2]) return '';
        return decodeURIComponent(results[2].replace(/\+/g, " "));
    }
    var namespace = getParameterByName("namespace") || "";
    var appid = Vault.signal.appid, appcert = Vault.signal.appcert;
    var wawaji_control_center = namespace + Vault.signal.cc_server;
    var debug = getParameterByName("debug") === "true";
    var loading = true;
    var control_ready = false;
    var startTime = new Date().getTime();
    var dbg = function (msg) {
        if (debug) {
            var x = [];
            var tsmsg = [(new Date().getTime() - startTime) + "ms: ", msg];
            console.log(tsmsg.join(":"));
            $(".logs").show();
            $("<li>" + tsmsg + "</li>").appendTo(".logs");
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



    var Lobby = function (account, cb) {
        var lobby = this;
        this.account = account;
        this.signal = Signal(appid);
        this.uid = null;
        this.machines = [];
        this.game = null;
        this.player = null;
        this.machine = null;
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
                        console.log("receive prepare, sending start to " + lobby.machine.name);
                        lobby.session.messageInstantSend(lobby.machine.name, JSON.stringify({ type: "START" }));
                        break;
                }
            }
        }

        Lobby.Game = function (account) {
            var game = this;
            this.account = account;
            this.users = 0;
            game.queue = [];
            game.playing = null;

            this.channel = lobby.session.channelJoin(namespace + lobby.machine.room_name);
            this.channel.onChannelJoined = function () {
                dbg("Enter room " + lobby.machine.name + "");
                control_ready = true;
                updateViews();
            };

            this.channel.onChannelJoinFailed = function (ecode) {
                dbg("machine connect failed");
            };

            this.channel.onChannelAttrUpdated = function (type, k, v) {
                dbg(`type: ${type}, k: ${k}, v: ${v}`);
                var attrs = null;
                if (k === "attrs" && (type === "update" || type === "set")) {
                    attrs = JSON.parse(v) || {};
                }
                if ((v === "update" || v === "set") && type === "attrs") {
                    attrs = JSON.parse(k) || {};
                }

                if(attrs !== null){
                    game.queue = attrs.queue || [];
                    game.playing = attrs.playing;
                    updateViews();
                    dbg('machine attributes updated ' + type + ' ' + k + ' ' + v);
                }
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
                if (!video_client.isUsingFrontCamera()) {
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
        }
        // Lobby.VideoPlayer = function (info) {
        //     var player = this;
        //     var canvas = document.getElementById('jsmpeg-player');
        //     var canvas2 = document.getElementById('jsmpeg-player2');
        //     var doubleStream = getParameterByName("double-stream") === "true";
        //     player.cameras = info.cameras || {};
        //     player.camera = info.cameras.main;
        //     player.player1 = null;
        //     player.player2 = null;
        //     player.switching = false;

        //     var onConnectionEstablished = function () { dbg("socket open") };
        //     var onFirstPacketReceived = function () { dbg("first packet received") };
        //     var onWillDecodeFirstFrame = function () { dbg("will decode first frame") };

        //     if (lobby.machine.video_rotation === 90) {
        //         $("#jsmpeg-player").addClass("rotation-90");
        //         $("#jsmpeg-player2").addClass("rotation-90");
        //     }

        //     player.isUsingFrontCamera = function () {
        //         return player.cameras && player.camera === player.cameras.main;
        //     }

        //     player.fitScreen = function () {
        //         if (lobby.machine.video_rotation === 90) {
        //             //do nothing
        //             var width = $(".wrapper").width();
        //             var video_width = parseFloat($("#jsmpeg-player").attr("width"));
        //             var video_height = parseFloat($("#jsmpeg-player").attr("height"));

        //             var scale = width / video_height;
        //             scale = scale > 1 ? 1 : scale;
        //             $("#jsmpeg-player").css("transform", "translateX(-50%) rotate(90deg) scale(" + scale + "," + scale + ")");
        //             $("#jsmpeg-player2").css("transform", "translateX(-50%) rotate(90deg) scale(" + scale + "," + scale + ")");
        //         } else {
        //             var width = $(".wrapper").width();
        //             var video_width = parseFloat($("#jsmpeg-player").attr("width"));
        //             var video_height = parseFloat($("#jsmpeg-player").attr("height"));

        //             var scale = width / video_width;
        //             scale = scale > 1 ? 1 : scale;
        //             $("#jsmpeg-player").css("transform", "scale(" + scale + "," + scale + ")");
        //             $("#jsmpeg-player2").css("transform", "scale(" + scale + "," + scale + ")");
        //         }
        //     }


        //     player.play = function (url, position) {
        //         player.switching = true;
        //         if (position === 0) {
        //             //front
        //             player.player1 = new JSMpeg.Player(player.cameras.main, {
        //                 canvas: canvas,
        //                 audio: false,
        //                 agora_id: 1,
        //                 onDidDecodeFirstFrame: function () {
        //                     dbg("play start.")
        //                     player.fitScreen();
        //                     $(canvas2).hide();
        //                     $(canvas).show();

        //                     player.player2.destroy();
        //                     player.player2 = null;
        //                     player.switching = false;
        //                 },
        //                 onConnectionEstablished: onConnectionEstablished,
        //                 onFirstPacketReceived: onFirstPacketReceived,
        //                 onWillDecodeFirstFrame: onWillDecodeFirstFrame
        //             });
        //         } else {
        //             //side
        //             player.player2 = new JSMpeg.Player(player.cameras.sub, {
        //                 canvas: canvas2,
        //                 audio: false,
        //                 agora_id: 2,
        //                 onDidDecodeFirstFrame: function () {
        //                     dbg("play start.")
        //                     player.fitScreen();
        //                     $(canvas).hide();
        //                     $(canvas2).show();

        //                     player.player1.destroy();
        //                     player.player1 = null;
        //                     player.switching = false;
        //                 },
        //                 onConnectionEstablished: onConnectionEstablished,
        //                 onFirstPacketReceived: onFirstPacketReceived,
        //                 onWillDecodeFirstFrame: onWillDecodeFirstFrame
        //             });
        //         }
        //     }
        //     player.switchCamera = function () {
        //         if (player.switching) {
        //             console.log("switching..pls wait");
        //             return;
        //         }
        //         if (player.camera === player.cameras.main) {
        //             player.camera = player.cameras.sub;
        //             player.play(player.camera, 1);
        //         } else {
        //             player.camera = player.cameras.main;
        //             player.play(player.camera, 0);
        //         }
        //     }

        //     dbg("setup jsmpeg player..")
        //     player.player1 = new JSMpeg.Player(player.cameras.main, {
        //         canvas: canvas,
        //         audio: false,
        //         autoplay: false,
        //         decodeFirstFrame: true,
        //         agora_id: 1,
        //         onDidDecodeFirstFrame: function () {
        //             dbg("play start.")
        //             player.fitScreen();
        //             loading = false;
        //             updateViews();
        //         },
        //         onConnectionEstablished: onConnectionEstablished,
        //         onFirstPacketReceived: onFirstPacketReceived,
        //         onWillDecodeFirstFrame: onWillDecodeFirstFrame
        //     });

        // }

    };

    var account = getParameterByName("account") || localStorage.getItem("account") || randName(10);
    // localStorage.setItem("account", account);

    var meta_prepare = $.Deferred();
    var lobby = new Lobby(account, function () {
        lobby.game = new Lobby.Game(machine_list[i], lobby.account);
    });
    for (var i = 0; i < machine_list.length; i++) {
        if (machine_list[i].name === machine_name) {
            lobby.machine = machine_list[i];
            break;
        }
    }


    function fitScreen(){
        if (lobby.machine.video_rotation === 90) {
            //do nothing
            var width = $(".wrapper").width();
            var video_width = parseFloat($("#jsmpeg-player").attr("width"));
            var video_height = parseFloat($("#jsmpeg-player").attr("height"));

            var scale = width / video_height;
            scale = scale > 1 ? 1 : scale;
            $("#jsmpeg-player").css("transform", "rotate(90deg) scale(" + scale + "," + scale + ")");
            $("#jsmpeg-player2").css("transform", "rotate(90deg) scale(" + scale + "," + scale + ")");
        } else {
            var width = $(".wrapper").width();
            var video_width = parseFloat($("#jsmpeg-player").attr("width"));
            var video_height = parseFloat($("#jsmpeg-player").attr("height"));

            var scale = width / video_width;
            scale = scale > 1 ? 1 : scale;
            $("#jsmpeg-player").css("transform", "scale(" + scale + "," + scale + ")");
            $("#jsmpeg-player2").css("transform", "scale(" + scale + "," + scale + ")");
        }
    }

    var video_client = AgoraCMH5SDK.createClient();

    video_client.on("camera_switched", function (params) {
        dbg("camera_switched");
    });

    video_client.on("get_gateways", function (params) {
        dbg("get gateways");
    });

    video_client.on("get_video_info", function (params) {
        dbg("get video info: " + params.gw);
    });

    video_client.on("connection_established", function (params) {
        dbg("connection established");
    });

    video_client.on("first_packet_received", function (params) {
        dbg("first packet received");
    });

    video_client.on("will_decode_first_frame", function (params) {
        dbg("will decode first frame");
    });

    video_client.on("ready", function (params) {
        fitScreen();
    });

    getKey(lobby.machine).done(function (key) {
        video_client.init(lobby.machine.appid, lobby.machine.channel, {
            key: key,
            uid1: 1,
            uid2: 2
        }, function () {
            video_client.play({
                canvas1: "jsmpeg-player",
                canvas2: "jsmpeg-player2"
            }, function () {
                dbg("play start.")
                fitScreen();
                loading = false;
                updateViews();
            });
        });
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
        video_client.switchCamera();
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
        if (loading) {
            $(".loading").show();
        } else {
            if (control_ready) {
                $(".disabled").removeClass("disabled");
            }
            $(".loading").hide();
            $("#video").show();
            if (lobby.game) {
                //control logic
                var idx = lobby.game.queue.indexOf(lobby.account);
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