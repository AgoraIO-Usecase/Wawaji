$(function () {
    var appid = Vault.signal.appid, appcert = Vault.signal.appcert;
    var wawaji_control_center = Vault.signal.cc_server;
    var debug = true;
    var dbg = function (msg) {
        if (debug) {
            console.log(msg);
        }
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
    function isMobile() {
        var check = false;
        (function (a) { if (/(android|bb\d+|meego).+mobile|avantgo|bada\/|blackberry|blazer|compal|elaine|fennec|hiptop|iemobile|ip(hone|od)|iris|kindle|lge |maemo|midp|mmp|mobile.+firefox|netfront|opera m(ob|in)i|palm( os)?|phone|p(ixi|re)\/|plucker|pocket|psp|series(4|6)0|symbian|treo|up\.(browser|link)|vodafone|wap|windows ce|xda|xiino|android|ipad|playbook|silk/i.test(a) || /1207|6310|6590|3gso|4thp|50[1-6]i|770s|802s|a wa|abac|ac(er|oo|s\-)|ai(ko|rn)|al(av|ca|co)|amoi|an(ex|ny|yw)|aptu|ar(ch|go)|as(te|us)|attw|au(di|\-m|r |s )|avan|be(ck|ll|nq)|bi(lb|rd)|bl(ac|az)|br(e|v)w|bumb|bw\-(n|u)|c55\/|capi|ccwa|cdm\-|cell|chtm|cldc|cmd\-|co(mp|nd)|craw|da(it|ll|ng)|dbte|dc\-s|devi|dica|dmob|do(c|p)o|ds(12|\-d)|el(49|ai)|em(l2|ul)|er(ic|k0)|esl8|ez([4-7]0|os|wa|ze)|fetc|fly(\-|_)|g1 u|g560|gene|gf\-5|g\-mo|go(\.w|od)|gr(ad|un)|haie|hcit|hd\-(m|p|t)|hei\-|hi(pt|ta)|hp( i|ip)|hs\-c|ht(c(\-| |_|a|g|p|s|t)|tp)|hu(aw|tc)|i\-(20|go|ma)|i230|iac( |\-|\/)|ibro|idea|ig01|ikom|im1k|inno|ipaq|iris|ja(t|v)a|jbro|jemu|jigs|kddi|keji|kgt( |\/)|klon|kpt |kwc\-|kyo(c|k)|le(no|xi)|lg( g|\/(k|l|u)|50|54|\-[a-w])|libw|lynx|m1\-w|m3ga|m50\/|ma(te|ui|xo)|mc(01|21|ca)|m\-cr|me(rc|ri)|mi(o8|oa|ts)|mmef|mo(01|02|bi|de|do|t(\-| |o|v)|zz)|mt(50|p1|v )|mwbp|mywa|n10[0-2]|n20[2-3]|n30(0|2)|n50(0|2|5)|n7(0(0|1)|10)|ne((c|m)\-|on|tf|wf|wg|wt)|nok(6|i)|nzph|o2im|op(ti|wv)|oran|owg1|p800|pan(a|d|t)|pdxg|pg(13|\-([1-8]|c))|phil|pire|pl(ay|uc)|pn\-2|po(ck|rt|se)|prox|psio|pt\-g|qa\-a|qc(07|12|21|32|60|\-[2-7]|i\-)|qtek|r380|r600|raks|rim9|ro(ve|zo)|s55\/|sa(ge|ma|mm|ms|ny|va)|sc(01|h\-|oo|p\-)|sdk\/|se(c(\-|0|1)|47|mc|nd|ri)|sgh\-|shar|sie(\-|m)|sk\-0|sl(45|id)|sm(al|ar|b3|it|t5)|so(ft|ny)|sp(01|h\-|v\-|v )|sy(01|mb)|t2(18|50)|t6(00|10|18)|ta(gt|lk)|tcl\-|tdg\-|tel(i|m)|tim\-|t\-mo|to(pl|sh)|ts(70|m\-|m3|m5)|tx\-9|up(\.b|g1|si)|utst|v400|v750|veri|vi(rg|te)|vk(40|5[0-3]|\-v)|vm40|voda|vulc|vx(52|53|60|61|70|80|81|83|85|98)|w3c(\-| )|webc|whit|wi(g |nc|nw)|wmlb|wonu|x700|yas\-|your|zeto|zte\-/i.test(a.substr(0, 4))) check = true; })(navigator.userAgent || navigator.vendor || window.opera)
        return check;
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
                id: "wawaji_machine_leidi",
                name: "wawaji_machine_leidi",
                appid: "324f0da1e2284832a44fee5fcbec44c1",
                channel: "leidi01",
                dynamicKeyEnabled: true,
                image: "IMG_5468.png",
                available: true
            }, {
                id: "wawaji_machine_zinian",
                name: "wawaji_machine_zinian",
                appid: "a3b353ea71c34ea3851f2849a6301858",
                channel: "agora_wawaji",
                dynamicKeyEnabled: false,
                video_rotation: 0,
                image: "IMG_5467.png",
                available: true
            }, {
                id: "wawaji_machine_shuangqu",
                name: "wawaji_machine_shuangqu",
                appid: "df5d561c7c094b028a3100fba535dfa9",
                channel: "bj_A131",
                dynamicKeyEnabled: true,
                video_rotation: 0,
                image: "IMG_5468.png",
                reverseControl: true,
                available: true
            }, {
                id: "wawaji_machine_zhuazhua2",
                name: "wawaji_machine_zhuazhua2",
                appid: "8b0faaf944034061a5ffd263d3f3f7a4",
                channel: "wawajiDemo",
                dynamicKeyEnabled: false,
                video_rotation: 90,
                image: "IMG_5469.png",
                available: false
            }, {
                id: "wawaji_machine_kedie",
                name: "wawaji_machine_kedie",
                appid: "9aa74fadb6594733a673f40fab8d933d",
                channel: "0338",
                dynamicKeyEnabled: true,
                image: "IMG_5470.png",
                available: false
            }, {
                id: "wawaji_machine_huizhi",
                name: "wawaji_machine_huizhi",
                appid: "f451ae655cfe491b907d67728f9dee8b",
                channel: "7008",
                dynamicKeyEnabled: false,
                image: "IMG_5467.png",
                available: false
            },{
                id: "wawaji_machine_leidi_internal",
                name: "wawaji_machine_leidi",
                appid: "324f0da1e2284832a44fee5fcbec44c1",
                channel: "leidi01",
                dynamicKeyEnabled: true,
                image: "IMG_5468.png",
                internal: true,
                available: true
            }];
            for(var i = 0; i < machines.length; i++){
                machines[i].room_name = "room_" + machines[i].name;
            }

            lobby.setMachines(machines);
        }

        this.setMachines = function (macs) {
            var internal = getParameterByName("internal") === "true";
            dbg("found " + macs.length + " machines");
            lobby.machines = macs;
            $(".game-list").html("");
            for (var i = 0; i < macs.length; i++) {
                if(macs[i].internal && !internal){
                    continue;
                }
                var html = "";
                html += '<div class="game-room" name="' + macs[i].id + '">';
                html += '<div class="room-container">';
                html += '<div class="room-img" style="background-image: url(\'/assets/images/' + macs[i].image + '\')">';
                html += '<div class="room-label">';
                html += '<div class="name">Agora公仔</div>';
                html += '<div class="price" style="float: left">24/次</div>';
                html += '<img class="status" src="./assets/images/';
                html += macs[i].available ? 'available' : 'busy';
                html += '.png" />';
                html += '</div></div></div>';
                html += '<img src="./assets/images/game_frame.png" style="width: 100%" />';
                html += '</div>';
                $(html).appendTo(".game-list");
            }

            localStorage.setItem("machines", JSON.stringify(macs));

            // var start_event = isMobile() ? "touchstart" : "mousedown";
            var end_event = isMobile() ? "touchend" : "mouseup";

            $(".game-room").off(end_event).on(end_event, function () {
                var name = $(this).attr("name");

                for (var i = 0; i < lobby.machines.length; i++) {
                    if (name === lobby.machines[i].id) {
                        if (!lobby.machines[i].available) {
                            alert("设备维护中！");
                        } else {
                            var url = "play.html?account=" + lobby.account + "&machine=" + lobby.machines[i].name;
                            var isDebug = getParameterByName("debug") === "true";
                            var isH264 = getParameterByName("h264") === "true";
                            
                            if(isH264){
                                url += "&h264=true";
                            }
                            location.href = url;
                        }
                        break;
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
