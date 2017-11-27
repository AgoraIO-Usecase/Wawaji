$(function () {
    var appid = Vault.appid, appcert = Vault.appcert;
    var wawaji_control_center = "wawaji_cc_server_agora";
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


    var Lobby = function (account, cb) {
        var lobby = this;
        this.account = account;
        this.signal = Signal(appid);
        this.uid = null;
        this.machines = [];
        this.game = null;
        this.session = this.signal.login(account, SignalingToken.get(appid, appcert, account, 1));
        this.session.onLoginSuccess = function (uid) {
            dbg("login successful account:" + lobby.account + " uid: " + uid);
            lobby.uid = uid;

            cb && cb();
        };

        //if fail
        this.session.onLoginFailed = function () {
            dbg("login failed ");
        };

        this.session.onMessageInstantReceive = function (account, uid, msg) {
            console.log("message received: " + msg);
            var data = JSON.parse(msg);
            if (data.type !== undefined) {
                switch (data.type) {
                    case "LIST":
                        lobby.setMachines(data.machines || [])
                        break;
                    case "INFO":
                        console.log(msg);
                        break;
                }
            }
        }

        this.list = function () {
            lobby.session.messageInstantSend(wawaji_control_center, JSON.stringify({ "type": "LIST" }));
        }

        this.setMachines = function (macs) {
            dbg("found " + macs.length + " machines");
            lobby.machines = macs;
            for (var i = 0; i < macs.length; i++) {
                $('<li name=' + macs[i].name + ' class="roomBtn list-group-item list-group-item-action d-flex justify-content-between align-items-center">' + macs[i].name + '<span class="badge badge-primary badge-pill">' + macs[i].players.length + '</span></li>')
                    .appendTo($(".machine-list"));
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

    var account = getParameterByName("account") /*|| localStorage.getItem("account")*/ || randName(10);
    // localStorage.setItem("account", account);
    var lobby = new Lobby(account, function () {
        lobby.list();
    });
});
