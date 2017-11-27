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
var SocketStream = require('./modules/socketStream.js')
var vault = require('./modules/vault')

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


var manager = new WawajiManager("server");
manager.onStarted = function(){
    manager.machines.add('machine1', vault.machine);
}


request(`http://recording.agorapremium.agora.io:9001/agora/media/genDynamicKey5?uid=0&key=${vault.appid}&sign=${vault.appcert}&channelname=${"xcapture"}`, function(err, response, body){
    var stream = new SocketStream(io, "xcapture", body, "1", "2");
});

http.listen("4000");