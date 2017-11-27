const exec = require('child_process').exec;
const path = require('path');
const fs = require('fs');
const Connection = require('./connection')

var debug = true;
var dbg = function () {
    if (debug) {
        var x = [];
        for (var i in arguments) x.push(arguments[i]);
        console.log.apply(null, ['Agora Socket stream dbg :'].concat(x));
    }
};

function SocketStream(io, appid, channel, channelKey, front_camera, back_camera) {
    var stream = this;
    this.channels = {};
    this.watchers = {};
    this.cameras = {front: front_camera, back: back_camera};

    dbg(`channel ${channel} connected ${channelKey}`);
    function schedule_cleanup() {
        setTimeout(function () {
            var script = `bash clean_files.sh`;
            dbg(`executing script ${script}`);
            exec(script, (error, stdout, stderr) => {
                dbg(`${stdout}`);
                dbg(`${stderr}`);
                if (error !== null) {
                    dbg(`exec error: ${error}`);
                }
            });
            schedule_cleanup();
        }, 30000);
    }

    schedule_cleanup();

    var script = channelKey ? `bash start_record.sh -c ${channel} -i ${appid} -k ${channelKey}` : `bash start_record.sh -c ${channel} -i ${appid}`;
    this.folderPath = path.join(__dirname, `../public/${appid}${channel}`);
    dbg(`executing script ${script}`);
    exec(script, (error, stdout, stderr) => {
        dbg(`${stdout}`);
        dbg(`${stderr}`);
        if (error !== null) {
            dbg(`exec error: ${error}`);
        }
    });

    io.sockets.on('connection', function (socket) {
        var connect_ts = new Date();
        // connect_ts = parseTs("605485335_20171102103938.jpg");
        connect_ts.setSeconds(connect_ts.getSeconds());
        connect_ts = connect_ts.getTime();

        var query = socket.request._query;
        var conn = new Connection(socket, query.channel, query.appid, stream.cameras.front);
        var channelId = conn.getChannelId();
        stream.channels[channelId] = stream.channels[channelId] || [];
        stream.channels[channelId].push(conn);
        dbg(`channel joined, this channel has ${stream.channels[channelId].length} users`);
        conn.imageFolderPath = stream.folderPath;
        dbg(`image folder ${conn.imageFolderPath}`);
        startMonitoring(conn);

        socket.on('disconnect', function (reason) {
            var sid = socket.id;
            dbg(`socket disconneted ${sid}`);
            var all_connections = stream.channels[channelId];
            var left_connections = all_connections.filter(function (connection) {
                return connection.socketid !== sid;
            });

            stream.channels[channelId] = left_connections;
        });

        socket.on('cameras', function(data, cb){
            var channel = data.channel;
            var socketid = data.socketid;
            var connections = stream.channels[channel];
            var connection = null;

            for(var i = 0; i < connections.length; i++){
                if(connections[i].socketid === socketid){
                    connection = connections[i];
                    break;
                }
            }

            if(connection){
                dbg(`using ${connection.uid}, ${connection}`)
                cb({cameras: {front: stream.cameras.front, back: stream.cameras.back}, using: connection.uid});
            } else {
                cb(null);
            }

        });

        socket.on('switch', function(data){
            var channel = data.channel;
            var camera = data.camera;
            var socketid = data.socketid;
            dbg(`switch to uid ${camera}`);
            var connections = stream.channels[channel];
            for(var i = 0; i < connections.length; i++){
                if(connections[i].socketid === socketid){
                    connections[i].uid = camera;
                }
            }
        });

        function parseTs(filename) {
            var suffix = filename.split(".")[1];
            if (suffix !== "jpg" && suffix !== "webp") {
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

        function parseUid(channelId, filename) {
            var uid = filename.split("_")[0];
            var connections = stream.channels[channelId];
            for (var i = 0; i < connections.length; i++) {
                if (!connections[i].uid) {
                    connections[i].uid = uid;
                }
            }
            // dbg(`uid status for channel ${channelId}, ${stream.uids[channelId]}`)
            return uid;
        }

        function sendSingleImage(channelId, filename) {
            var connections = stream.channels[channelId];
            if (!filename || !parseTs(filename) || connections.length === 0) {
                // dbg(`imageFolderPath ${ifolder}`);
                return;
            }
            // dbg(`sending image ${filename}`)
            fs.readFile(path.join(connections[0].imageFolderPath, `./${filename}`), (err, data) => {
                if (err || data.length === 0) {
                    // dbg("error converting image");
                    return;
                }

                var uid = parseUid(channelId, filename);

                for (var i = 0; i < connections.length; i++) {
                    // dbg(`socketid: ${connections[i].socketid}`);
                    if(uid === connections[i].uid){
                        connections[i].socket.send(data);
                    }
                }
            });
        }

        function startMonitoring(connection) {
            var cid = connection.getChannelId();
            if (stream.watchers[cid]) {
                dbg("watcher exists " + cid);
                stream.watchers[cid].close();
            }
            try {
                dbg("watcher registered " + cid + " on " + connection.imageFolderPath);
                var watcher = fs.watch(connection.imageFolderPath, function (event, filename) {
                    // images.push(filename);
                    // dbg(`${new Date()} folder changed for files: ${filename}`);
                    sendSingleImage(cid, filename);
                })
                stream.watchers[cid] = watcher;
            } catch (e) {
                dbg(`fail to watch on folder: ${e}`);
            }
        }
    });
}


module.exports = SocketStream;