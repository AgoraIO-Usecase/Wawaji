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
    var cameras = null;
    var camera = null;
    var player = null;

    var playJSMpeg = function (url) {

        var canvas = document.getElementById('jsmpeg-player');
        if (!player) {
            player = new JSMpeg.Player(url, { canvas: canvas });
        } else {
            player.destroy();
            player = null;
            player = new JSMpeg.Player(url, { canvas: canvas });
        }
    }

    $.get("/v1/machines").done(function (machines) {
        for (var i = 0; i < machines.length; i++) {
            var machine = null;
            if (!machineName) {
                machine = machines[0];
                break;
            } else if (machineName === machine.name) {
                machine = machines[i];
                break;
            }
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
            playJSMpeg(camera);
        }
    });

    $(".control-camera").off("click").on("click", function(){
        if(camera === cameras.main){
            camera = cameras.sub;
        } else {
            camera = cameras.main;
        }
        playJSMpeg(camera);
    });
});