const request = require('request');

function Api(manager, app){
    app.use("/v1/key", function(req, res){
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
}



module.exports = Api;