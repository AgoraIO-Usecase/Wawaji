function Api(manager, app){
    app.use("/v1/machines", function(req, res){
        var machines = manager.machines.all() || [];
        machines = machines.map(function(item){
            return {
                name: item.name,
                video_channel: item.video_channel,
                stream_method: item.profile.mode,
                video_rotation: item.profile.video_rotation,
                cameras: { 
                    main: `ws://${manager.ipaddress}:${item.websocket_port1}`, 
                    sub: `ws://${manager.ipaddress}:${item.websocket_port2}`
                }
            }
        })
        res.json(machines);
    });
}



module.exports = Api;