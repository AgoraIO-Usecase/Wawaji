// Use the websocket-relay to serve a raw MPEG-TS over WebSockets. You can use
// ffmpeg to feed the relay. ffmpeg -> websocket-relay -> browser
// Example:
// node websocket-relay yoursecret 8081 8082
// ffmpeg -i <some input> -f mpegts http://localhost:8081/yoursecret

var fs = require('fs'),
    http = require('http'),
    WebSocket = require('ws');
const exec = require('child_process').exec;



var JsMpegStream = function (stream_port1, stream_port2, websocket_port1, websocket_port2, secret, appid, channel, key, rand_uid) {
    // Websocket Server
    var stream = this;


    function createSocketServer(port){
        var socketServer = new WebSocket.Server({ port: port, perMessageDeflate: false });
        socketServer.connectionCount = 0;
        socketServer.on('connection', function (socket, upgradeReq) {
            socketServer.connectionCount++;
            // console.log(
            //     'New WebSocket Connection: ',
            //     (upgradeReq || socket.upgradeReq).socket.remoteAddress,
            //     (upgradeReq || socket.upgradeReq).headers['user-agent'],
            //     '(' + socketServer.connectionCount + ' total)'
            // );
            socket.on('close', function (code, message) {
                socketServer.connectionCount--;
                console.log(
                    'Disconnected WebSocket (' + socketServer.connectionCount + ' total)'
                );
            });
        });
        socketServer.broadcast = function (data) {
            socketServer.clients.forEach(function each(client) {
                if (client.readyState === WebSocket.OPEN) {
                    client.send(data);
                }
            });
        };
        return socketServer;
    }
    stream.socketServer1 = createSocketServer(websocket_port1);
    stream.socketServer2 = createSocketServer(websocket_port2);

    // HTTP Server to accept incomming MPEG-TS Stream from ffmpeg
    function createStreamServer(port, se, ws_server){
        var streamServer = http.createServer(function (request, response) {
            console.log("stream server created " + port)
            var params = request.url.substr(1).split('/');
    
            if (params[0] !== se) {
                console.log(
                    'Failed Stream Connection: ' + request.socket.remoteAddress + ':' +
                    request.socket.remotePort + ' - wrong secret.'
                );
                response.end();
            }
    
            response.connection.setTimeout(60 * 60 * 1000);
            // console.log(
            //     'Stream Connected: ' +
            //     request.socket.remoteAddress + ':' +
            //     request.socket.remotePort
            // );
            request.on('data', function (data) {
                ws_server.broadcast(data);
                // console.log("pushing stream..");
                if (request.socket.recording) {
                    request.socket.recording.write(data);
                }
            });
            request.on('end', function () {
                console.log('close');
                if (request.socket.recording) {
                    request.socket.recording.close();
                }
            });
    
            // Record the stream to a local file?
            // if (RECORD_STREAM) {
            //     var path = 'recordings/' + Date.now() + '.ts';
            //     request.socket.recording = fs.createWriteStream(path);
            // }
        }).listen(port);
    };

    createStreamServer(stream_port1, secret, stream.socketServer1);
    createStreamServer(stream_port2, secret, stream.socketServer2);

    // console.log('Listening for incomming MPEG-TS Stream on http://127.0.0.1:' + STREAM_PORT + '/<secret>');
    // console.log('Awaiting WebSocket connections on ws://127.0.0.1:' + WEBSOCKET_PORT + '/');
    // setTimeout(function () {
        //start record server
        
        var push_url1 = `http://localhost:${stream_port1}/${secret}`
        var push_url2 = `http://localhost:${stream_port2}/${secret}`
        var script = key ? `bash start_record_jsmpeg.sh -i ${appid} -c ${channel} -k ${key} -m ${push_url1} -s ${push_url2} -a ${"1"} -b ${"2"} -r ${rand_uid}` : `bash start_record_jsmpeg.sh -i ${appid} -c ${channel} -m ${push_url1} -s ${push_url2} -a ${"1"} -b ${"2"} -r ${rand_uid}`;
        console.log(script);
        exec(script, (error, stdout, stderr) => {
            console.log(`${stdout}`);
            console.log(`${stderr}`);
            if (error !== null) {
                console.log(`exec error: ${error}`);
            }
        });
    // }, 3000);
}


module.exports = JsMpegStream;
