const express = require('express')
const app = express()
const http = require('http').Server(app);
const io = require('socket.io')(http);
const fs = require('fs');
const exec = require('child_process').exec;
const path = require('path');
const ps = require('ps-node');
const request = require('request');
var WawajiManager = require('./modules/wawajiManager.js')
var bodyParser = require('body-parser');
var vault = require('./modules/vault').signal
var ZhuaZhuaProfile = require('./modules/profiles/zhuazhua/profile');
var LeiDiProfile = require('./modules/profiles/leidi/profile');
var LeyaoyaoProfile = require('./modules/profiles/leyaoyao/profile');
var QiyiguoProfile = require('./modules/profiles/qiyiguo/profile');
var HuizhiProfile = require('./modules/profiles/huizhi/profile');
var KedieProfile = require('./modules/profiles/kedie/profile');
var StreamMethod = require('./modules/constants').StreamMethod;
var api  = require('./routes/api');

app.use(express.static('public'));

// parse application/json
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: false }));

// Add headers
app.use(function (req, res, next) {

    // Website you wish to allow to connect
    res.setHeader('Access-Control-Allow-Origin', '*');

    // Request methods you wish to allow
    res.setHeader('Access-Control-Allow-Methods', 'GET, POST, OPTIONS, PUT, PATCH, DELETE');

    // Request headers you wish to allow
    res.setHeader('Access-Control-Allow-Headers', 'X-Requested-With,content-type');

    // Set to true if you need the website to include cookies in the requests sent
    // to the API (e.g. in case you use sessions)
    // res.setHeader('Access-Control-Allow-Credentials', true);

    // Pass to next layer of midd leware
    next();
});

var zhuazhua_profile = new ZhuaZhuaProfile(StreamMethod.IMAGES);
var zhuazhua2_profile = new ZhuaZhuaProfile(StreamMethod.JSMPEG);
var leidi_profile = new LeiDiProfile(StreamMethod.JSMPEG);
var leyaoyao_profile = new LeyaoyaoProfile(StreamMethod.JSMPEG);
var huizhi_profile = new HuizhiProfile(StreamMethod.JSMPEG);
var kedie_profile = new KedieProfile(StreamMethod.JSMPEG);
//var qiyiguo_profile = new QiyiguoProfile(StreamMethod.JSMPEG);

var unique = function(s){
    return s + (process.argv[2] ? "_" + process.argv[2] :  "");
}

request(leyaoyao_profile.http_url, function (err, response, body) {
	console.log(body);
    var msg = JSON.parse(body);
    if (msg) {
        leyaoyao_profile.url = msg.data.wsUrl;
    }
});

//qiyiguo_profile.genURL(qiyiguo_profile.onRequestUrl);

var manager = new WawajiManager(unique("server_agora"), io);
manager.onStarted = function(){
    manager.machines.add(new Wawaji.Machine(unique('machine_leyaoyao'), leyaoyao_profile));
    manager.machines.add(new Wawaji.Machine(unique('machine_leidi'), leidi_profile));
    manager.machines.add(new Wawaji.Machine(unique('machine_zhuazhua2'), zhuazhua2_profile));
    manager.machines.add(new Wawaji.Machine(unique('machine_huizhi'), huizhi_profile));
    manager.machines.add(new Wawaji.Machine(unique('machine_kedie'), kedie_profile));
    //manager.machines.add(unique('machine_qiyiguo'), qiyiguo_profile);
    // manager.machines.add(unique('machine_test'), test_profile);
}

api(manager, app);

var port = process.argv[3] || 4000;
console.log(`listening on port ${port}`)
http.listen(port);
