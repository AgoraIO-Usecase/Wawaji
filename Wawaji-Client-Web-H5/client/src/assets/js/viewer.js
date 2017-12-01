$(function () {
    var getParameterByName = (name, url) => {
        if (!url) url = window.location.href;
        name = name.replace(/[\[\]]/g, "\\$&");
        var regex = new RegExp("[?&]" + name + "(=([^&#]*)|&|#|$)"),
            results = regex.exec(url);
        if (!results) return null;
        if (!results[2]) return '';
        return decodeURIComponent(results[2].replace(/\+/g, " "));
    }

    var machineName = getParameterByName("name");


    function Player() {
        var player = this;
        this.cameras = null;
        this.camera = null;
        this.player1 = null;
        this.player2 = null;
        this.switching = false;


        this.play = function (url, position) {
            if(player.switching){
                console.log("switching...");
                return;
            }

            var canvas = document.getElementById('jsmpeg-player');
            var canvas2 = document.getElementById('jsmpeg-player2');
            player.switching = true;
            var switching_time = 1000;

            if(position === 0){
                //front
                if(!player.player1){
                    player.player1 = new JSMpeg.Player(url, { canvas: canvas });
                    setTimeout(function(){
                        $(canvas2).hide();
                        $(canvas).show();
                        player.player2 && player.player2.destroy();
                        player.player2 = null;
                        player.switching = false;
                    }, switching_time);
                } else {
                }
            } else {
                //side
                if(!player.player2){
                    player.player2 = new JSMpeg.Player(url, { canvas: canvas2 });
                    setTimeout(function(){
                        $(canvas).hide();
                        $(canvas2).show();
                        player.player1 && player.player1.destroy();
                        player.player1 = null;
                        player.switching = false;
                    }, switching_time);
                } else {
                }
            }
        }
        this.switchCamera = function () {
            if (camera === cameras.main) {
                camera = cameras.sub;
                player.play(camera, 1);
            } else {
                camera = cameras.main;
                player.play(camera, 0);
            }
        }
    }

    var video_player = new Player();

    $(".btn[data-type='connect']").off("click").on("click", function () {
        var appid = $("input[name='appid']").val();
        var channel = $("input[name='channelName']").val();
        var appcert = $("input[name='appcert']").val()

        if (!appid || !channel) {
            alert("appid or channel empty");
            return;
        }
        $.ajax({
            // url: "/v1/machine",
            url: "http://wawa1.agoraio.cn:4000/v1/machine",
            type: "GET",
            data: {
                appid: appid,
                channel: channel,
                appcert: appcert
            }
        }).done(function (machine) {
            if (!machine || !machine.name) {
                alert("no machine found");
                return;
            }

            if (machine.video_rotation === 90) {
                $("#jsmpeg-player").addClass("rotation-90");
                $("#jsmpeg-player2").addClass("rotation-90");
            }

            if (machine.stream_method === 0) {
                alert("image streaming is not yet supported");
            } else {
                cameras = machine.cameras;
                camera = machine.cameras.main;
                video_player.play(camera, 0);
            }
        }).fail(function (e) {
            alert("err");
        });
    });

    $(".btn[data-type='switch']").off("click").on("click", function () {
        video_player.switchCamera();
    });
    $(".btn[data-type='start']").off("click").on("click", function () {
        var appid = $("input[name='appid']").val();
        var channel = $("input[name='channelName']").val();
        var appcert = $("input[name='appcert']").val()

        if (!appid || !channel) {
            alert("appid or channel empty");
            return;
        }
        $.ajax({
            url: "/v1/machine/start",
            type: "POST",
            data: {
                appid: appid,
                channel: channel,
                appcert: appcert
            }
        }).done(function (response) {
            console.log(JSON.stringify(response));
        }).fail(function (e) {
            alert("err");
        });
    });
});