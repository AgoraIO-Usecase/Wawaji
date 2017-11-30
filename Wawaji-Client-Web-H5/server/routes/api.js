function Api(manager, app){
    app.use("/v1/machine", function(req, res){
        var query = req.query;
        if(!query.appid || !query.channel){
            res.status(500);
            res.json({err: "PARAMETER_MISSING"});
        }

        var machines = manager.machines.all() || [];

        machines = machines.filter(function(item){
            return item.video_appid === query.appid && item.video_channel === query.channel;
        });

        var machine = machines.length > 0 ? machines[0] : null;

        machine = machine ? {
            name: machine.name,
            video_channel: machine.video_channel,
            stream_method: machine.profile.mode === 1 ? "jsmpeg" : "image",
            video_rotation: machine.profile.video_rotation,
            cameras: { 
                main: `ws://${manager.ipaddress}:${machine.websocket_port1}`, 
                sub: `ws://${manager.ipaddress}:${machine.websocket_port2}`
            }
        } : {};
        res.json(machine);
    });
}



module.exports = Api;