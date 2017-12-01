var VideoProfile = require('../modules/profiles/video/profile');
var StreamMethod = require('../modules/constants').StreamMethod;

function Api(manager, app) {
    app.post("/v1/machine", function (req, res) {
        var query = req.body;
        if (!query.appid || !query.channel) {
            res.status(500);
            res.json({ err: "PARAMETER_MISSING" });
        }

        var machines = manager.machines.all() || [];
        console.log(`${machines.length} machines`);

        machines = machines.filter(function (item) {
            return item.video_appid === query.appid && item.video_channel === query.channel;
        });

        var machine = machines.length > 0 ? machines[0] : null;
        var mac_json = null;

        if(machine){
            console.log("existing machine found...");
            mac_json = {
                name: machine.name,
                video_channel: machine.video_channel,
                stream_method: machine.profile.mode === 1 ? "jsmpeg" : "image",
                video_rotation: machine.profile.video_rotation,
                cameras: {
                    main: `ws://${manager.ipaddress}:${machine.websocket_port1}`,
                    sub: `ws://${manager.ipaddress}:${machine.websocket_port2}`
                }
            };
            res.json(mac_json);
        } else {
            console.log("machine not found, try to start one...");
            machine = manager.machines.add(query.appid+query.channel, new VideoProfile(StreamMethod.JSMPEG, query.channel, query.appid, query.appcert));
            machine.init(function(output){
                console.log("start finished...");
                console.log(output);
                mac_json = {
                    name: machine.name,
                    video_channel: machine.video_channel,
                    stream_method: machine.profile.mode === 1 ? "jsmpeg" : "image",
                    video_rotation: machine.profile.video_rotation,
                    cameras: {
                        main: `ws://${manager.ipaddress}:${machine.websocket_port1}`,
                        sub: `ws://${manager.ipaddress}:${machine.websocket_port2}`
                    }
                }
                res.json(mac_json);
            });
        }
    });
}



module.exports = Api;