
const vault = require('../../vault.js').huizhi
const WawajiStatus = require('../../constants').WawajiStatus;
const request = require('request');
const logger = require('../../logger');

const ACTION = {
    LEFT:  'SXActionLeft',
    RIGHT: 'SXActionRight',
    UP:    'SXActionBack',
    DOWN:  'SXActionFront',
    CATCH: 'SXActionFetch'
};

const OPERATION = {
    CONNECT:    'webConnectWithBinDataStr',
    CHECKCONN:  'webCheckConnect',
    DISCONN:    'webDisConnect',
    SENDACTION: 'webSendAction',
    CHECKHAND:  'webCheckHand'
};

var debug = true;
var dbg = function () {
    if (debug) {
        var x = [];
        for (var i in arguments) x.push(arguments[i]);
        console.log.apply(null, ['Agora Huizhi profile dbg :'].concat(x));
    }
};

HuizhiProfile = function (mode) {
    var profile = this;
    this.machine = null;
    this.appid = vault.appid;
    this.appcert = vault.appcert;
    this.url = vault.url;
    this.http_url = vault.http_url;
    this.video_channel = vault.video_channel;
    this.video_host = vault.video_host;
    this.video_rotation = vault.video_rotation;
    this.stream_secret = vault.stream_secret;
    this.mode = mode;
    this.actions = {};
    this.dyn_key = '';
    this.binstr  = vault.binstr;
    this.password = vault.password;
    this.protocol = vault.protocol;
    this.log = (new logger('huizhi', 'huizhi.log')).get();

    this.onInit = function(machine, done){
        profile.log.info("onInit.");
        profile.machine = machine;
        done();
    }

    this.disconnect = function () {
        profile.log.info("disconnect.");
        var dst_url = profile.http_url + OPERATION.DISCONN;
        request.post({url:dst_url, form:{binStr:profile.binstr, pass:profile.password}}, function (err, response, body) {
            var msg = JSON.parse(body);
            if (msg) {
                if (msg.code > 0) {
                    profile.log.info("Response: " + msg.mess);
                }
                else {
                    profile.log.info("Response ERROR:" + msg.mess);
                }
            }
        });
    }

    this.onPlay = function(account){
        var dst_url = profile.http_url + OPERATION.CONNECT;
        request.post({url:dst_url, form:{binStr:profile.binstr, pass:profile.password}}, function (err, response, body) {
            var msg = JSON.parse(body);
            if (msg) {
                if (msg.code > 0) {
                    profile.dyn_key = msg.data;
                    profile.log.info("Response: dynKey=" + profile.dyn_key);
                }
                else {
                    profile.log.info("Response ERROR:" + msg.mess);
                }
            }
        });
    }

    this.onControl = function(data){
        profile.log.info("onControl: " + data.data);
        var action = '';
        switch (data.data) {
            case 'left':  action = ACTION.LEFT;  break;
            case 'right': action = ACTION.RIGHT; break;
            case 'up':    action = ACTION.UP;    break;
            case 'down':  action = ACTION.DOWN;  break;
            default: break;
        }
        var dst_url = profile.http_url + OPERATION.SENDACTION;
        request.post({url:dst_url, form:{binStr:profile.binstr, pass:profile.password, dynKey:profile.dyn_key, action:action}}, function (err, response, body) {
            var msg = JSON.parse(body);
            if (msg) {
                if (msg.code > 0) {
                    profile.log.info("Response: " + msg.mess);
                }
                else {
                    profile.log.info("Response ERROR: " + msg.mess);
                }
            }
        });
    }

    this.onCatch = function(){
        profile.log.info("onCatch.");
        var action = ACTION.CATCH;
        var dst_url = profile.http_url + OPERATION.SENDACTION;
        request.post({url:dst_url, form:{binStr:profile.binstr, pass:profile.password, dynKey:profile.dyn_key, action:action}}, function (err, response, body) {
            var msg = JSON.parse(body);
            if (msg) {
                if (msg.code > 0) {
                    profile.log.info("Response: " + msg.mess);

                    setTimeout(profile.check, 15000);
                }
                else {
                    profile.log.info("Response ERROR: " + msg.mess);
                }
            }
        });
    }

    this.check = function () {
        profile.log.info("check.");
        var dst_url = profile.http_url + OPERATION.CHECKHAND;
        request.post({url:dst_url, form:{binStr:profile.binstr, pass:profile.password, dynKey:profile.dyn_key}}, function (err, response, body) {
            profile.log.info(body);
            var msg = JSON.parse(body);
            if (msg) {
                if (msg.code > 0) {
                    profile.log.info("[Huizhi] Response: " + msg.mess + " code:" + msg.code );
                    profile.onResult && profile.onResult(true);
                }
                else {
                    profile.log.info("[Huizhi] Response ERROR: " + msg.mess);
                    profile.onResult && profile.onResult(false);
                }
            }

            profile.disconnect();
        });
    }  

}

module.exports = HuizhiProfile;

