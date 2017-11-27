// Use the websocket-relay to serve a raw MPEG-TS over WebSockets. You can use
// ffmpeg to feed the relay. ffmpeg -> websocket-relay -> browser
// Example:
// node websocket-relay yoursecret 8081 8082
// ffmpeg -i <some input> -f mpegts http://localhost:8081/yoursecret

var fs = require('fs'),
    http = require('http'),
    WebSocket = require('ws');
const exec = require('child_process').exec;



var JsMpegStream = function (stream_port, websocket_port, secret, appid, channel, key) {
    // Websocket Server
    var stream = this;

    stream.socketServer = new WebSocket.Server({ port: websocket_port, perMessageDeflate: false });
    stream.socketServer.connectionCount = 0;
    stream.socketServer.on('connection', function (socket, upgradeReq) {
        stream.socketServer.connectionCount++;
        console.log(
            'New WebSocket Connection: ',
            (upgradeReq || socket.upgradeReq).socket.remoteAddress,
            (upgradeReq || socket.upgradeReq).headers['user-agent'],
            '(' + stream.socketServer.connectionCount + ' total)'
        );
        socket.on('close', function (code, message) {
            stream.socketServer.connectionCount--;
            console.log(
                'Disconnected WebSocket (' + stream.socketServer.connectionCount + ' total)'
            );
        });
    });
    stream.socketServer.broadcast = function (data) {
        stream.socketServer.clients.forEach(function each(client) {
            if (client.readyState === WebSocket.OPEN) {
                client.send(data);
            }
        });
    };

    // HTTP Server to accept incomming MPEG-TS Stream from ffmpeg
    var streamServer = http.createServer(function (request, response) {
        var params = request.url.substr(1).split('/');

        if (params[0] !== secret) {
            console.log(
                'Failed Stream Connection: ' + request.socket.remoteAddress + ':' +
                request.socket.remotePort + ' - wrong secret.'
            );
            response.end();
        }

        response.connection.setTimeout(60 * 60 * 1000);
        console.log(
            'Stream Connected: ' +
            request.socket.remoteAddress + ':' +
            request.socket.remotePort
        );
        request.on('data', function (data) {
            stream.socketServer.broadcast(data);
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
    }).listen(stream_port);

    // console.log('Listening for incomming MPEG-TS Stream on http://127.0.0.1:' + STREAM_PORT + '/<secret>');
    // console.log('Awaiting WebSocket connections on ws://127.0.0.1:' + WEBSOCKET_PORT + '/');
    // setTimeout(function () {
        //start record server
        var push_url = `http://localhost:${stream_port}/${secret}`
        var script = `bash start_record_jsmpeg.sh -i ${appid} -c ${channel} -k ${key} -u ${push_url}`;
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
