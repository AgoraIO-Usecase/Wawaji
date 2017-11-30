const os = require('os');
const fs = require('fs');


var getIp = function () {
    var interfaces = os.networkInterfaces();
    var addresses = [];
    for (var k in interfaces) {
        for (var k2 in interfaces[k]) {
            var address = interfaces[k][k2];
            if (address.family === 'IPv4' && !address.internal) {
                addresses.push(address.address);
            }
        }
    }
    return addresses.length > 0 ? addresses[0] : null;
}


var getDomain = function(){
    var domain = "";
    try{
        domain = fs.readFileSync('/etc/wwj_dns', 'utf8');
    } catch(e){
        console.log("[ERROR] Fail to read domain");
    }
    return domain;
}

module.exports = {
    getIp: getIp,
    getDomain: getDomain
}