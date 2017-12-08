const request = require('request');

function Api(manager, app){
    app.get("/v1/key", function(req, res){
        var query = req.query;
        var appid = query.appid;
        var channel = query.channel;
        var appcert = null;
        
        if(!appid || !channel){
            res.json({err: "appid or channel is required", key: null});
            return;
        }

        if(appid === "9aa74fadb6594733a673f40fab8d933d"){
            //kedie
            appcert = "18db294f9bb347c1bbeabd30ef13793d";
        } else if(appid === "324f0da1e2284832a44fee5fcbec44c1") {
            //leidi
            appcert = "164aa13965394ffbb5ebeb43c4c7ed5c";
        } else {
            res.json({err: "unrecognized device", key: null});
            return;
        }


        request(`http://recording.agorapremium.agora.io:9001/agora/media/genDynamicKey5?uid=0&key=${appid}&sign=${appcert}&channelname=${channel}`, function (err, response, body) {
            res.json({key: body})
        });
    });

    app.get("/v1/list", function(req, res){
        var machines = [{
            name: "wawaji_machine_leidi",
            appid: "324f0da1e2284832a44fee5fcbec44c1",
            channel: "leidi01",
            dynamicKeyEnabled: true,
            image: "IMG_5468.png",
            available: true
        }, {
            name: "wawaji_machine_leyaoyao",
            appid: "274acaf097b54d86acd6b21d0a753205",
            channel: "10001",
            dynamicKeyEnabled: false,
            video_rotation: 90,
            image: "IMG_5467.png",
            available: false
        }, {
            name: "wawaji_machine_zhuazhua2",
            appid: "8b0faaf944034061a5ffd263d3f3f7a4",
            channel: "wawajiDemo",
            dynamicKeyEnabled: false,
            video_rotation: 90,
            image: "IMG_5469.png",
            available: false
        }, {
            name: "wawaji_machine_kedie",
            appid: "9aa74fadb6594733a673f40fab8d933d",
            channel: "03A3",
            dynamicKeyEnabled: true,
            image: "IMG_5470.png",
            available: false
        }, {
            name: "wawaji_machine_huizhi",
            appid: "f451ae655cfe491b907d67728f9dee8b",
            channel: "555",
            dynamicKeyEnabled: false,
            image: "IMG_5467.png",
            available: false
        }];
        for(var i = 0; i < machines.length; i++){
            machines[i].room_name = "room_" + machines[i].name;
        }

        res.json(machines);
    });
}



module.exports = Api;