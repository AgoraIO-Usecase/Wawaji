$(document).ready(function(){
    var appid = Vault.appid, appcert = Vault.appcert;
    var wawaji_control_center = Vault.cc_server;

    var randName = function (length) {
        var text = "";
        var charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
        for (var i = 0; i < parseInt(length); i++)
            text += charset.charAt(Math.floor(Math.random() * charset.length));
        return text;
    };

    function updateStatus(type, vendor, content, success){
        var table = $("table." + type);
        var vendor = table.find("." + vendor);
        var status = vendor.find("." + content);
        status.removeClass("table-info").addClass(success?"table-success":"table-danger");
        status.text(success?"Success":"Fail");
    }

    var getKey = function (machine, cb) {
        if (!machine.dynamicKeyEnabled) {
            cb && cb(null);
        } else {
            $.ajax({
                url: "http://recording.agorapremium.agora.io:9001/agora/media/genDynamicKey5",
                // url: "/v1/key",
                type: "GET", //send it through get method
                data: {
                    uid: 0,
                    key: machine.appid,
                    sign: machine.appcert,
                    channelname: machine.channel
                }
            }).done(function (key) {
                cb && cb(key);
            });
        }
    }

    var prepare_meta = function (machine, cb) {
        getKey(machine, function (key) {
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
            }).done(function (domains) {
                var gateways = domains.gateway_addr || [];

                if (gateways.length === 0) {
                    console.log(machine.name + ": no gateway available");
                } else {
                    $.ajax({
                        url: "https://" + domains.gateway_addr[0] + "/v1/machine",
                        // url: "http://wawa1.agoraio.cn:4000/v1/machine",
                        // url: "http://127.0.0.1:4000/v1/machine",
                        type: "POST",
                        data: {
                            appid: machine.appid,
                            channel: machine.channel,
                            key: key
                        }
                    }).done(function (video_info) {
                        cb(video_info);
                    }).fail(function (e) {
                        alert("err");
                    });
                }
            });
        })
    }

    var checkStreams = function(){
        var machines = [{
            name: "wawaji_machine_leyaoyao",
            appid: "274acaf097b54d86acd6b21d0a753205",
            channel: "10001",
            dynamicKeyEnabled: false,
            video_rotation: 90,
            image: "IMG_5467.png",
            available: true
        }, {
            name: "wawaji_machine_leidi",
            appid: "324f0da1e2284832a44fee5fcbec44c1",
            appcert: "164aa13965394ffbb5ebeb43c4c7ed5c",
            channel: "leidi01",
            dynamicKeyEnabled: true,
            image: "IMG_5468.png",
            available: true
        }, {
            name: "wawaji_machine_zhuazhua2",
            appid: "8b0faaf944034061a5ffd263d3f3f7a4",
            channel: "wawajiDemo",
            dynamicKeyEnabled: false,
            video_rotation: 90,
            image: "IMG_5469.png",
            available: true
        }, {
            name: "wawaji_machine_kedie",
            appid: "9aa74fadb6594733a673f40fab8d933d",
            channel: "03A3",
            dynamicKeyEnabled: true,
            appcert: "18db294f9bb347c1bbeabd30ef13793d",
            image: "IMG_5470.png",
            available: true
        }, {
            name: "wawaji_machine_huizhi",
            appid: "f451ae655cfe491b907d67728f9dee8b",
            channel: "555",
            dynamicKeyEnabled: false,
            image: "IMG_5467.png",
            available: true
        }];

        var checkStream = function(machine, vendor){
            prepare_meta(machine, function(video){
                var url1 = video.cameras.main;
                var url2 = video.cameras.sub;
    
                var ws1 = new WebSocket(url1);
                var ws2 = new WebSocket(url2);
    
                var timer1 = setTimeout(function(){
                    updateStatus("websocket", vendor, "status_1", false);
                    ws1.close();
                }, 5000);
                var timer2 = setTimeout(function(){
                    updateStatus("websocket", vendor, "status_2", false);
                    ws2.close();
                }, 5000);
    
                ws1.onopen = function(){
                    console.log("opened");
                };
                ws1.onmessage = function(){
                    updateStatus("websocket", vendor, "status_1", true);
                    ws1.close();
                    clearTimeout(timer1);
                }
                ws2.onopen = function(){
                    console.log("opened");
                };
                ws2.onmessage = function(){
                    updateStatus("websocket", vendor, "status_2", true);
                    ws2.close();
                    clearTimeout(timer2);
                }
            });
        }

        checkStream(machines[0], "leyaoyao");
        checkStream(machines[1], "leidi");
        checkStream(machines[2], "zhuazhua");
        checkStream(machines[3], "kedie");
        checkStream(machines[4], "huizhi");
    }

    var account = randName(15);
    var signal = Signal(appid);
    var session = signal.login(account, SignalingToken.get(appid, appcert, account, 1));
    session.onLoginSuccess = function (uid) {
        session.invoke("io.agora.signal.user_query_user_status", {account: wawaji_control_center}, function(err, val){
            updateStatus("signal", "cc", "status", val.status === 1);
        });

        session.invoke("io.agora.signal.user_query_user_status", {account: "wawaji_machine_leidi"}, function(err, val){
            updateStatus("signal", "leidi", "status", val.status === 1);
        });

        session.invoke("io.agora.signal.user_query_user_status", {account: "wawaji_machine_leyaoyao"}, function(err, val){
            updateStatus("signal", "leyaoyao", "status", val.status === 1);
        });

        session.invoke("io.agora.signal.user_query_user_status", {account: "wawaji_machine_kedie"}, function(err, val){
            updateStatus("signal", "kedie", "status", val.status === 1);
        });

        session.invoke("io.agora.signal.user_query_user_status", {account: "wawaji_machine_zhuazhua2"}, function(err, val){
            updateStatus("signal", "zhuazhua", "status", val.status === 1);
        });

        session.invoke("io.agora.signal.user_query_user_status", {account: "wawaji_machine_huizhi"}, function(err, val){
            updateStatus("signal", "huizhi", "status", val.status === 1);
        });

        session.invoke("io.agora.signal.channel_query_user_isin", {name: "room_wawaji_machine_leidi", account: "wawaji_machine_leidi"}, function(err, val){
            updateStatus("signal", "leidi", "room_status", val.isin === 1);
        })


        session.invoke("io.agora.signal.channel_query_user_isin", {name: "room_wawaji_machine_leyaoyao", account: "wawaji_machine_leyaoyao"}, function(err, val){
            updateStatus("signal", "leyaoyao", "room_status", val.isin === 1);
        })


        session.invoke("io.agora.signal.channel_query_user_isin", {name: "room_wawaji_machine_zhuazhua2", account: "wawaji_machine_zhuazhua2"}, function(err, val){
            updateStatus("signal", "zhuazhua", "room_status", val.isin === 1);
        })


        session.invoke("io.agora.signal.channel_query_user_isin", {name: "room_wawaji_machine_kedie", account: "wawaji_machine_kedie"}, function(err, val){
            updateStatus("signal", "kedie", "room_status", val.isin === 1);
        })


        session.invoke("io.agora.signal.channel_query_user_isin", {name: "room_wawaji_machine_huizhi", account: "wawaji_machine_huizhi"}, function(err, val){
            updateStatus("signal", "huizhi", "room_status", val.isin === 1);
        })

        checkStreams();
    };
    session.onLoginFailed = function(){
        console.log("login failed");
    }

});