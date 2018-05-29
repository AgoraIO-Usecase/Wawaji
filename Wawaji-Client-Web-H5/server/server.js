const express = require('express')
const app = express()
const sslcerts = require("./modules/sslcerts");
const https= require("https").createServer(sslcerts, app);
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
var ZiNianProfile = require('./modules/profiles/zinian/profile');
var ShuangquProfile = require('./modules/profiles/shuangqu/profile');
var StreamMethod = require('./modules/constants').StreamMethod;
var api  = require('./routes/api');

app.use(express.static(path.join(__dirname, 'public')));

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
var zinian_profile = new ZiNianProfile(StreamMethod.JSMPEG);
var shuangqu_profile = new ShuangquProfile(StreamMethod.JSMPEG);
//var qiyiguo_profile = new QiyiguoProfile(StreamMethod.JSMPEG);


shuangqu_profile.prepare().then(() => {
    var manager = new WawajiManager("server_agora", io);
    manager.onStarted = function(){
        // manager.machines.add(new Wawaji.Machine(unique('machine_leyaoyao'), leyaoyao_profile));
        manager.machines.add(new Wawaji.Machine('machine_leidi', leidi_profile));
        // manager.machines.add(new Wawaji.Machine(unique('machine_zhuazhua2'), zhuazhua2_profile));
        // manager.machines.add(new Wawaji.Machine(unique('machine_huizhi'), huizhi_profile));
        // manager.machines.add(new Wawaji.Machine(unique('machine_kedie'), kedie_profile));
        manager.machines.add(new Wawaji.Machine('machine_zinian', zinian_profile));
        manager.machines.add(new Wawaji.Machine('machine_shuangqu', shuangqu_profile));
        //manager.machines.add(unique('machine_qiyiguo'), qiyiguo_profile);
        // manager.machines.add(unique('machine_test'), test_profile);
    }


    api(manager, app);
    let port = 4000;
    console.log(`listening on port ${port}`)
    http.listen(port);
    https.listen(4002);
}).catch(e => {
    console.log(`failed to start: shuangqu profile update failed`);
});
