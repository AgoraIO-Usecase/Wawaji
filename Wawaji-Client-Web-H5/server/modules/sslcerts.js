const fs = require('fs');
var privateKey  = "";
var certificate = "";
var sslcerts = null;
try{
    privateKey = fs.readFileSync('/etc/agora/agoraio.cn.key', 'utf8');
    certificate = fs.readFileSync('/etc/agora/agoraio.cn.crt', 'utf8');
    sslcerts = {key: privateKey, cert: certificate};
} catch(e){
    sslcerts = {key: privateKey, cert: certificate};
}

module.exports = sslcerts;