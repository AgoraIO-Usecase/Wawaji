const request = require('request');
const keygen = require('../modules/dynamicKey').generateMediaChannelKey;
const vault = require('../modules/vault');

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
            appcert = vault.kedie.appcert;
        } else if(appid === "324f0da1e2284832a44fee5fcbec44c1") {
            //leidi
            appcert = vault.leidi.appcert;
        } else {
            res.json({err: "unrecognized device", key: null});
            return;
        }

        // var authTs = new Date().getTime() + 60*5;
        var authTs = Math.floor(new Date() / 1000) + 60*5
        // var expiredTs = new Date().getTime() + 3600 * 24;
        var key = keygen(appid, appcert, channel, authTs, Math.floor(Math.random() * 0xFFFFFFFF), 0, 0);
        res.json({key: key});
    });
}



module.exports = Api;