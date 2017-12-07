$(function () {
    var appid = Vault.appid, appcert = Vault.appcert;
    var wawaji_control_center = Vault.cc_server;
    var debug = true;
    var dbg = function () {
        if (debug) {
            var x = [];
            for (var i in arguments) x.push(arguments[i]);
            console.log.apply(null, ['Agora sig client dbg :'].concat(x));
        }
    };
    var getParameterByName = (name, url) => {
        if (!url) url = window.location.href;
        name = name.replace(/[\[\]]/g, "\\$&");
        var regex = new RegExp("[?&]" + name + "(=([^&#]*)|&|#|$)"),
            results = regex.exec(url);
        if (!results) return null;
        if (!results[2]) return '';
        return decodeURIComponent(results[2].replace(/\+/g, " "));
    }
    var randName = function (length) {
        var text = "";
        var charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
        for (var i = 0; i < parseInt(length); i++)
            text += charset.charAt(Math.floor(Math.random() * charset.length));
        return text;
    };

    var Lobby = function (account) {
        var lobby = this;
        this.account = account;
        this.uid = null;
        this.machines = [];
        this.game = null;

        this.list = function () {
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
            for(var i = 0; i < machines.length; i++){
                machines[i].room_name = "room_" + machines[i].name;
            }
            lobby.setMachines(machines);
        }

        this.setMachines = function (macs) {
            dbg("found " + macs.length + " machines");
            lobby.machines = macs;
            // for (var i = 0; i < macs.length; i++) {
            //     $('<li name=' + macs[i].name + ' class="roomBtn list-group-item list-group-item-action d-flex justify-content-between align-items-center">' + macs[i].name + '<span class="badge badge-primary badge-pill">' + macs[i].players.length + '</span></li>')
            //         .appendTo($(".machine-list"));
            // }
            $(".game-list").html("");
            for (var i = 0; i < macs.length; i++){
                var html = "";
                html += '<div class="game-room" name="' + macs[i].name + '">';
                html += '<div class="room-container">';
                html += '<div class="room-img" style="background-image: url(\'/assets/images/' + macs[i].image + '\')">';
                html += '<div class="room-label">';
                html += '<div class="name">Agora公仔</div>';
                html += '<div class="price" style="float: left">24/次</div>';
                html += '<img class="status" src="./assets/images/available.png" />';
                html += '</div></div></div>';
                html += '<img src="./assets/images/game_frame.png" style="width: 100%" />';
                html += '</div>';
                $(html).appendTo(".game-list");
            }

            localStorage.setItem("machines", JSON.stringify(macs));

            $(".game-room").off("click").on("click", function () {
                var name = $(this).attr("name");
                if (!name) {
                    alert("设备维护中！")
                } else {
                    for (var i = 0; i < lobby.machines.length; i++) {
                        if (name === lobby.machines[i].name) {
                            location.href = "play.html?account=" + lobby.account + "&machine=" + name;
                            break;
                        }
                    }
                }
            });
        };
    };

    var account = getParameterByName("account") || localStorage.getItem("account") || randName(10);
    // localStorage.setItem("account", account);
    var lobby = new Lobby(account);
    lobby.list();
});
