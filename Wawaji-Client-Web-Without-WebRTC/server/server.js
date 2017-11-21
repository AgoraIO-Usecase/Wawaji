const express = require('express')
const app = express()
const http = require('http').Server(app);
const io = require('socket.io')(http);
const fs = require('fs');
const exec = require('child_process').exec;
const path = require('path');
const ps = require('ps-node');
var bodyParser = require('body-parser');
const Connection = require('./src/connection.js');

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

    // Pass to next layer of middleware
    next();
});

var channels = {};
var watchers = {};

function schedule_cleanup(){
    setTimeout(function(){
        var script = `bash clean_files.sh`;
        console.log(`executing script ${script}`);
        exec(script, (error, stdout, stderr) => {
            console.log(`${stdout}`);
            console.log(`${stderr}`);
            if (error !== null) {
                console.log(`exec error: ${error}`);
            }
        });
        schedule_cleanup();
    }, 30000);
}

schedule_cleanup();

io.sockets.on('connection', function (socket) {
    var connect_ts = new Date();
    // connect_ts = parseTs("605485335_20171102103938.jpg");
    connect_ts.setSeconds(connect_ts.getSeconds());
    connect_ts = connect_ts.getTime();

    var query = socket.request._query;
    var conn = new Connection(socket, query.channel, query.appid, query.uid);
    var channelId = conn.getChannelId();
    var conns = channels[channelId] || [];
    conns.push(conn);
    channels[channelId] = conns;
    console.log(`channel joined, this channel has ${conns.length} users`);
    conn.imageFolderPath = path.join(__dirname, `./public/${channelId}`);
    console.log(`image folder ${conn.imageFolderPath}`);
    startMonitoring(conn);

    socket.on('disconnect', function (reason) {
        var existing_connection = conn;
        var all_connections = conns;
        var left_connections = all_connections.filter(function (connection) {
            return connection !== existing_connection;
        });
        
        channels[existing_connection.getChannelId()] = left_connections;
        // console.log(`${existing_connection.socketid} disconnected, channel has ${JSON.stringify(socketIds)}`);
    });

    function parseTs(channelId, filename) {
        var connections = channels[channelId];
        var suffix = filename.split(".")[1];
        if (suffix !== "jpg" && suffix !== "webp") {
            return null;
        }
        var uid = filename.split("_")[0];
        if(connections[0] && connections[0].uid && connections[0].uid !== uid){
            console.log(`${uid} not matching given uid ${connections[0].uid}`)
            return null;
        }
        var ts = filename.split("_")[1].split(".")[0];
        var year = ts.substr(0, 4);
        var month = ts.substr(4, 2);
        var day = ts.substr(6, 2);
        var hour = ts.substr(8, 2);
        var minute = ts.substr(10, 2);
        var second = ts.substr(12, 2);
        var milliseconds = filename.split("_")[2].split(".")[0];
        var date = Date.UTC(year, month - 1, day, hour, minute, second, milliseconds);
        return date;
    }


    function sendSingleImage(channelId, filename) {
        var connections = channels[channelId];
        if (!filename || !parseTs(channelId, filename) || connections.length === 0) {
            // console.log(`imageFolderPath ${ifolder}`);
            return;
        }
        console.log(`sending image ${filename}`)
        fs.readFile(path.join(connections[0].imageFolderPath, `./${filename}`), (err, data) => {
            if (err || data.length === 0) {
                // console.log("error converting image");
                return;
            }

            for (var i = 0; i < connections.length; i++) {
                connections[i].socket.send(data);
            }
        });
        // sharp(path.join(imagesFolderPath, `./${filename}`)).webp({quality: 10, alphaQuality:1}).toBuffer((err, data, info) => {
        //     if(err){
        //         console.log("error converting image");
        //         return;
        //     }
        //     console.log(`converted ${filename} to webp`)
        //     var socketIds = channels[channel] || [];
        //     for(var i = 0; i < socketIds.length; i++){
        //         sockets[socketIds[i]].send(data);
        //     }
        // });
        // sharp(path.join(imagesFolderPath, `./${filename}`)).webp({quality: 40}).toFile(path.join(imagesFolderPath, `./${filename}.webp`));
    }

    function startMonitoring(connection) {
        var cid = connection.getChannelId();
        if (watchers[cid]) {
            console.log("watcher exists " + cid);
            watchers[cid].close();
        }
        try {
            console.log("watcher registered " + cid + " on " + connection.imageFolderPath);
            var watcher = fs.watch(connection.imageFolderPath, function (event, filename) {
                // images.push(filename);
                // console.log(`${new Date()} folder changed for files: ${filename}`);
                sendSingleImage(cid, filename);
            })
            watchers[cid] = watcher;
        } catch (e) {
            console.log(`fail to watch on folder: ${e}`);
        }
    }

});

app.post("/record", function (req, res) {
    console.log("executing record script");
    var enable = req.body.enable === 'true';
    var channel = req.body.channel || "";
    var appid = req.body.appid || "";
    var sid = req.body.socketid || "";
    var script = `bash start_record.sh -c ${channel} -i ${appid}`;


    var folderPath = path.join(__dirname, `./public/${appid}${channel}`);

    if (enable) {
        console.log(`executing script ${script}`);
        exec(script, (error, stdout, stderr) => {
            console.log(`${stdout}`);
            console.log(`${stderr}`);
            if (error !== null) {
                console.log(`exec error: ${error}`);
            }
            res.json({ msg: "recording started" });
        });
    }

});

http.listen("3000");