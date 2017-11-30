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
        this.player = null;


        this.play = function (url) {
            var canvas = document.getElementById('jsmpeg-player');
            if (!player.player) {
                player.player = new JSMpeg.Player(url, { canvas: canvas });
            } else {
                player.player.destroy();
                player.player = null;
                player.player = new JSMpeg.Player(url, { canvas: canvas });
            }
        }
        this.switchCamera = function () {
            if (camera === cameras.main) {
                camera = cameras.sub;
            } else {
                camera = cameras.main;
            }
            player.play(camera);
        }
    }

    var video_player = new Player();

    $(".btn[data-type='connect']").off("click").on("click", function () {
        var appid = $("input[name='appid']").val();
        var channel = $("input[name='channelName']").val();

        if (!appid || !channel) {
            alert("appid or channel empty");
            return;
        }
        $.ajax({
            url: "/v1/machine",
            type: "GET",
            data: {
                appid: appid,
                channel: channel
            }
        }).done(function (machine) {
            if (!machine || machine === {}) {
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
                video_player.play(camera);
            }
        }).fail(function (e) {
            alert("err");
        });
    });

    $(".btn[data-type='switch']").off("click").on("click", function () {
        video_player.switchCamera();
    });
});