
function Connection(socket, channel, appid, uid){
    this.socketid = socket.id;
    this.socket = socket;
    this.channel = channel || "";
    this.appid = appid || "";
    this.uid = uid || "";
    this.imageFolderPath = "";
}


Connection.prototype.getChannelId = function(){
    return this.appid + this.channel;
}

module.exports = Connection;