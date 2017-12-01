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
var VideoProfile = require('./modules/profiles/video/profile');
var StreamMethod = require('./modules/constants').StreamMethod;
var api = require('./routes/api');

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

//create video only profiles
var test_profiles = [];
for (var i = 1; i <= 8; i++) {
    test_profiles.push(new VideoProfile(StreamMethod.JSMPEG, "wawaji" + i));
}

var unique = function (s) {
    return s + (process.argv[2] ? "_" + process.argv[2] : "");
}

var manager = new WawajiManager(unique("server_agora"), io);
for (var i = 0; i < test_profiles.length; i++) {
    //add machines to manager
    manager.machines.add(unique('machine_pressure_test' + i), test_profiles[i]);
}

api(manager, app);

var port = process.argv[3] || 4000;
console.log(`listening on port ${port}`)
http.listen(port);
