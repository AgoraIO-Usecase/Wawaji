(function ($) {
    $(() => {
        let socket = null;
        let images = [];
        let currentIdx = 0;
        let record_service_started = false;
        const frame_rate = 50;

        function playImage() {
            if (images.length > 0) {
                let img = document.querySelector("#image");
                let imageUrl = null;
                if (currentIdx >= images.length) {
                    imageUrl = images[images.length - 1];
                } else {
                    imageUrl = images[currentIdx++];
                }

                if (images.length - currentIdx > 100) {
                    //if falling behind too much, jump frame
                    currentIdx = images.length - 1;
                    console.log("jumping frame");
                }

                console.log(`playing image ${currentIdx}/${images.length}`);
                img.src = imageUrl;
            }
            if (socket !== null) {
                setTimeout(playImage, 1000 / frame_rate);
            } else {
                let img = document.querySelector("#image");
                img.src = null;
            }
        }


        function subscribeEvents() {
            $('.connect_btn').off("click").on("click", function (e) {
                //connect io
                if (!socket) {
                    // socket = io();
                    let channel = $('.channelField').val()
                    let appid = $('.idField').val();
                    let uid = $('.uidField').val();
                    // let socket = io(`http://localhost:3000/?channel=${channel}&appid=${appid}`)
                    socket = io({
                        query: {
                            channel: channel,
                            appid: appid,
                            uid: uid
                        }
                    })
                    subscribeSocketEvents(socket);
                } else {
                    socket.close();
                    socket = null;
                    record_service_started = false;
                    $('.connect_btn').prop("disabled", true);
                    $('.record_btn').text(record_service_started ? "Stop" : "Record");
                    $('.record_btn').prop("disabled", false);
                }

                $('.connect_btn').text(socket === null ? "Connect" : "Disconnect");
            });

            $('.record_btn').off("click").on("click", function (e) {
                let channel = $('.channelField').val();
                let appid = $('.idField').val();
                let force = $('.forceCheck').prop("checked");
                if (!channel) {
                    $('.channelField').removeClass("is-invalid").addClass("is-invalid");
                }

                if (!appid) {
                    $('.idField').removeClass("is-invalid").addClass("is-invalid");
                }
                if (channel && appid) {

                    //run scripts to start/stop the recording service
                    record_service_started = !record_service_started;
                    $('.record_btn').text(record_service_started ? "Starting..." : "Stopping...");
                    $('.record_btn').prop("disabled", true);

                    $.post("/record", {
                        // $.post("http://localhost:3000/record", { 
                        enable: record_service_started,
                        channel: channel,
                        appid: appid,
                        force: force
                    }).done(function () {
                        $('.record_btn').text(record_service_started ? "Stop" : "Record");
                        $('.record_btn').prop("disabled", false);
                        $('.connect_btn').prop("disabled", !record_service_started);
                    }).catch(function (error) {
                        let err = error.responseJSON;
                        if (err.msg === "folder_exists") {
                            Snackbar.show({ text: 'Record服务启动失败，服务器端文件已存在，可以尝试勾选覆盖目录或者换一个channel名.' });
                        }
                        record_service_started = false;
                        $('.record_btn').text(record_service_started ? "Stop" : "Record");
                        $('.record_btn').prop("disabled", false);
                        $('.connect_btn').prop("disabled", !record_service_started);
                    });
                }
            });
        }

        function subscribeSocketEvents(s) {
            s.on('connect', function () {
                let channel = $('.channelField').val()
                let appid = $('.idField').val();
                s.on('message', function (data) {
                    console.log("message received");
                    let arrayBufferView = new Uint8Array(data);
                    let blob = new Blob([arrayBufferView], { type: "image/jpeg" });
                    let urlCreator = window.URL || window.webkitURL;
                    let imageUrl = urlCreator.createObjectURL(blob);
                    images.push(imageUrl);
                });

                playImage();
            });
        }


        subscribeEvents();
    });
}(jQuery));