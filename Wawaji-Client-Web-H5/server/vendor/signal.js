/*
 * Smoking tests
 * 1. login / logout
 * 2. logout instantly after invoking login
 * 3. join / leave channel
 * 4. join channel without logged in
 * 5. location balance service failure
 * 6. access point failure
 * 7. callback error handlers
 */


const WebSocket = require('ws');
const XMLHttpRequest = require("xmlhttprequest").XMLHttpRequest;

Signal_ = function (vid) {

    var
        SUCCESS = 0,

        LOGOUT_E_OTHER = 100,  //
        LOGOUT_E_USER = 101,  // logout by user
        LOGOUT_E_NET = 102,  // network failure
        LOGOUT_E_KICKED = 103,  // login in other device
        LOGOUT_E_PACKET = 104,  //
        LOGOUT_E_TOKENEXPIRED = 105,  // token expired
        LOGOUT_E_OLDVERSION = 106,  // 
        LOGOUT_E_TOKENWRONG = 107,
        LOGOUT_E_ALREADY_LOGOUT = 108,

        LOGIN_E_OTHER = 200,
        LOGIN_E_NET = 201,
        LOGIN_E_FAILED = 202,
        LOGIN_E_CANCEL = 203,
        LOGIN_E_TOKENEXPIRED = 204,
        LOGIN_E_OLDVERSION = 205,
        LOGIN_E_TOKENWRONG = 206,
        LOGIN_E_TOKEN_KICKED = 207,
        LOGIN_E_ALREADY_LOGIN = 208,

        JOINCHANNEL_E_OTHER = 300,

        SENDMESSAGE_E_OTHER = 400,
        SENDMESSAGE_E_TIMEOUT = 401,

        QUERYUSERNUM_E_OTHER = 500,
        QUERYUSERNUM_E_TIMEOUT = 501,
        QUERYUSERNUM_E_BYUSER = 502,

        LEAVECHANNEL_E_OTHER = 600,
        LEAVECHANNEL_E_KICKED = 601,
        LEAVECHANNEL_E_BYUSER = 602,
        LEAVECHANNEL_E_LOGOUT = 603,
        LEAVECHANNEL_E_DISCONN = 604,

        INVITE_E_OTHER = 700,
        INVITE_E_REINVITE = 701,
        INVITE_E_NET = 702,
        INVITE_E_PEEROFFLINE = 703,
        INVITE_E_TIMEOUT = 704,
        INVITE_E_CANTRECV = 705,

        GENERAL_E = 1000,
        GENERAL_E_FAILED = 1001,
        GENERAL_E_UNKNOWN = 1002,
        GENERAL_E_NOT_LOGIN = 1003,
        GENERAL_E_WRONG_PARAM = 1004,
        GENERAL_E_LARGE_PARAM = 1005

        ;

    function shuffle(arr) {
        var j, x, i;
        for (i = arr.length; i; i--) {
            j = Math.floor(Math.random() * i);
            x = arr[i - 1];
            arr[i - 1] = arr[j];
            arr[j] = x;
        }
    }

    this.lbs_url1 = ['https://lbs-1-sig.agora.io', 'https://lbs-2-sig.agora.io'];
    this.lbs_url2 = ['https://lbs-3-sig.agora.io', 'https://lbs-4-sig.agora.io'];

    function timedGetText(url, time, callback) {
        var request = new XMLHttpRequest();
        var timeout = false;
        var timer = setTimeout(function () {
            timeout = true;
            request.abort();
            callback('timeout', '');
        }, time);
        request.open("GET", url);
        request.onreadystatechange = function () {
            if (request.readyState !== 4) return;
            if (timeout) return;
            clearTimeout(timer);
            if (request.status === 200) {
                callback('', request.responseText);
            }
        }
        request.send(null);
    }

    function timedConnectWebsockt(url, milliseconds) {
        var timeout = false
        var timer = setTimeout(function () {
            timeout = true;
        }, milliseconds);
    }



    this.vid = vid;
    this.appid = vid;
    var signal = this;

    function split_python(a, s, n) {
        var x = a.split(s, n);
        var offset = 0;
        for (var i in x) {
            offset += s.length + x[i].length;
        }
        x.push(a.substr(offset));
        return x;
    }

    // Session Object
    var Session = function (account, token) {
        /*------------------------------------------------
        |   API : session level
        \*----------------------------------------------*/
        this.onLoginSuccess = '';
        this.onLoginFailed = '';
        this.onLogout = '';

        this.onInviteReceived = '';
        this.onMessageInstantReceive = '';

        /*------------------------------------------------
        |
        \*----------------------------------------------*/
        this.account = account;
        this.state = 'session_state_logining';
        this.line = '';
        this.uid = 0;
        this.dbg = false;
        var session = this;
        session.lbs_state = 'requesting';
        var server_urls = [];
        shuffle(server_urls);
        session.idx = 0
        // todo lbs

        // todo set login time out

        // login
        //var socket = io('http://web.sig.agora.io/');
        session.socket = null;
        var dbg = function () {
            if (session.dbg) {
                var x = [];
                for (var i in arguments) x.push(arguments[i]);
                console.log.apply(null, ['Agora sig dbg :'].concat(x));
            }
        };

        // var choose_server = function() {
        //   // var x = server_urls[Math.floor(Math.random() * server_urls.length)];
        //   // var host = x[0].replace(/\./g, '-') + '-sig-web.agora.io';
        //   // var port = x[1] + 1;
        //   // return 'wss://' + host + ':' + port + '/';
        //   return 'ws://125.88.159.176:3000/';
        // }

        var format_ws_url = function (x) {
            var host = x[0].replace(/\./g, '-') + '-sig-web.agora.io';
            var port = x[1] + 1;
            return 'wss://' + host + ':' + port + '/';
        }

        /*------------------------------------------------
        |   Session API : Logout
        \*----------------------------------------------*/
        session.logout = function () {
            if (session.state == 'session_state_logined' && session.onLogout) {
                session.call2('user_logout', {
                    line: session.line
                }, function (err, data) {
                    session.fire_logout(LOGOUT_E_USER);
                    session.socket.close();
                });
            } else if (session.state == 'session_state_logining') {
                session.state == 'session_state_logout';
                session.fire_logout(LOGOUT_E_USER);
            }
        };

        session.fire_logout = function (reason) {
            if (!reason) {
                reason = 0;
            }
            try {
                if (session.state == 'session_state_logined' && session.onLogout) {
                    session.onLogout(reason);
                }
            } catch (e) {
                console.error(e)
            } finally {
                session.state = 'session_state_logout';
            }
        };

        var do_lbs = function (retry, urls, idx) {
            if (session.lbs_state != 'requesting') {
                return;
            }
            var url = urls[idx];
            timedGetText(url + '/getaddr?vid=' + vid, 5000, function (err, data) {
                if (err) {
                    if (retry - 1 > 0) {
                        do_lbs(retry - 1, urls, (idx + 1) % urls.length)
                    } else {
                        session.fire_login_failed(LOGIN_E_NET);//'lbs timeout');
                    }
                } else {
                    if (session.lbs_state != 'requesting') {
                        return;
                    }
                    session.lbs_state = 'completed';
                    server_urls = JSON.parse(data).web;
                    do_connect();
                    do_connect();
                }
            });
        };


        var do_connect = function () {
            if (0) {
                session.socket = io.connect('http://125.88.159.176:3000/');
            } else {
                if (session.state == 'session_state_logining') {
                    var socket = new function () {
                        var url = format_ws_url(server_urls[session.idx]);

                        // url = 'ws://125.88.159.176:8001/';

                        session.idx += 1;
                        var websocket = new WebSocket(url);
                        websocket.state = 'CONNECTING'

                        // Close the connection request afster 5 seconds.
                        setTimeout(function () {
                            if (websocket.readyState == websocket.CONNECTING) {
                                websocket.close();
                                return;
                            }
                        }, 6000);

                        websocket.onopen = function (evt) {
                            if (session.state == 'session_state_logout') {
                                websocket.close();
                            } else if (session.state == 'session_state_logining' && session.socket == null) {
                                session.socket = socket
                                websocket.state = 'OPEN'

                                dbg('on conn open')
                                session.go_login();

                                for (var i in bufs) {
                                    websocket.send(JSON.stringify(bufs[i]));
                                }
                            } else {
                                websocket.close();
                            }
                        };
                        websocket.onclose = function (evt) {
                            if (websocket.state == 'OPEN') {
                                fire('_close', '');
                                dbg('on conn close');
                            }

                            if (websocket.state == 'CONNECTING') {
                                do_connect()
                            }

                        };
                        websocket.onmessage = function (evt) {
                            var msg = evt.data;
                            var x = JSON.parse(msg);
                            var name = x[0];
                            fire(x[0], x[1]);
                        };
                        websocket.onerror = function (evt) {
                            websocket.state = 'CLOSED'
                            if (session.idx < server_urls.length && evt.target.readyState == evt.target.CLOSED) {
                                do_connect();
                                return;
                            }
                            dbg('on conn error');
                            if (session.state == 'session_state_logined') {
                                session.fire_logout('conn error');
                            } else if (session.state == 'session_state_logining') {
                                session.fire_login_failed(LOGIN_E_NET); //'conn err'
                            }
                        };

                        var evts = {};
                        var fire = function (evt, args) {
                            if (evt in evts) {
                                evts[evt](args);
                            }
                        };
                        var bufs = [];

                        // api

                        this.on = function (evt, f) {
                            evts[evt] = f;
                        }

                        this.emit = function (evt, args) {
                            if (websocket.readyState == 0) {
                                bufs.push([evt, args]);
                                return
                            }
                            websocket.send(JSON.stringify([evt, args]));
                        }

                        this.close = function () {
                            websocket.close();
                        }
                    }();
                }
            }

            /*------------------------------------------------
            | ping
            \*----------------------------------------------*/
            var ping_i = 0;
            var start_ping = function () {
                setTimeout(function () {
                    if (session.state != 'session_state_logined') {
                        return;
                    }
                    ping_i++;
                    dbg('send ping', ping_i);
                    session.socket.emit('ping', ping_i);
                    start_ping();
                }, 1000 * 10);
            };

            session.go_login = function () {
                if (session.line == '') {
                    session.socket.emit('login', {
                        vid: vid,
                        account: account,
                        uid: 0,
                        token: token,
                        device: 'websdk',
                        ip: '',
                    });
                    session.socket.on('login_ret', function (x) {
                        var err = x[0];
                        var ret = JSON.parse(x[1]);
                        dbg('login ret', err, ret);
                        if (!err && ret['result'] == 'ok') {
                            session.uid = ret['uid'];
                            session.line = ret['line'];
                            session.state = 'session_state_logined';
                            start_ping();
                            start_tick();
                            try {
                                if (session.onLoginSuccess) {
                                    session.onLoginSuccess(session.uid);
                                };
                            } catch (e) {
                                console.error(e)
                            } finally {
                                schedule_poll();
                            }
                        } else {
                            if (err == "") {
                                err = ret['reason'];
                            }
                            try {
                                if (session.onLoginFailed) {
                                    var e = err == "kick" ? LOGIN_E_TOKEN_KICKED :
                                        err == "TokenErrorExpired" ? LOGIN_E_TOKENEXPIRED :
                                            err.startsWith("TokenError") ? LOGIN_E_TOKENWRONG :
                                                LOGIN_E_NET;

                                    session.fire_login_failed(e);
                                }
                            } catch (e) {
                                console.error(e)
                            }
                        }
                    });
                } else {
                    session.socket.emit('line_login', {
                        line: session.line
                    });
                }



                /*------------------------------------------------
                |   Call2
                \*----------------------------------------------*/

                var callid = 0;
                var calltable = {};
                var call_obj_table = {};

                session.call2 = function (func, args, cb) {
                    callid++;
                    calltable[callid] = [func, args, cb];
                    dbg('call ', [func, callid, args]);
                    session.socket.emit('call2', [func, callid, args]);
                }

                session.socket.on('call2-ret', function (msg) {
                    var callid = msg[0];
                    var err = msg[1];
                    var data = msg[2];
                    if (callid in calltable) {
                        var cb = calltable[callid][2];
                        if (err == '') {
                            try {
                                data = JSON.parse(data);
                                if (data.result != "ok") {
                                    err = data.data.result;
                                }
                            } catch (e) {
                                err = "wrong resp:" + data;
                            }
                        }
                        if (cb) cb(err, data);
                    }
                });

                var is_ok = function (err, msg) {
                    return err == '';
                }

                var channel;

                var proc_msg1 = function (src, t, content) {
                    if (t == 'channel_msg') {

                    }
                };

                var decode_msg = function (msg) {
                    if (msg.startsWith("msg-v2 ")) {
                        var r = split_python(msg, ' ', 6);
                        if (r.length == 7) {
                            var src = r[1];
                            var t = r[4];
                            var content = r[6];
                            return [src, t, content];
                        }
                    }
                    return null;
                }

                session.socket.on('pong', function (msg) {
                    dbg('recv pong');
                });

                session.socket.on('close', function (msg) {
                    session.fire_logout(0);
                    session.socket.close();
                });

                session.socket.on('_close', function (msg) {
                    session.fire_logout(0);
                });

                session.fire_login_failed = function (reason) {
                    try {
                        if (session.state == 'session_state_logining' && session.onLoginFailed) {
                            session.onLoginFailed(reason);
                        }
                    } catch (e) {
                        console.error(e)
                    } finally {
                        session.state = 'session_state_logout'
                    }
                };

                /*------------------------------------------------
                |   process_msg
                \*----------------------------------------------*/

                var process_msg = function (msg) {
                    var tmp = msg;
                    var src = tmp[0];
                    var t = tmp[1];
                    var content = tmp[2];

                    if (t == 'instant') {
                        try {
                            if (session.onMessageInstantReceive) session.onMessageInstantReceive(src, 0, content);
                        } catch (e) { console.error(e) }
                    };

                    if (t.startsWith('voip_')) {
                        var root = JSON.parse(content);

                        var channel = root.channel;
                        var peer = root.peer;
                        var extra = root.extra;
                        var peeruid = root.peeruid;

                        var call;
                        if (t == 'voip_invite') {
                            call = new Call(channel, peer, peeruid, extra);
                            session.call2('voip_invite_ack', {
                                line: session.line,
                                channelName: channel,
                                peer: peer,
                                extra: ''
                            });
                        } else {
                            call = call_obj_table[channel + peer];
                            if (!call) {
                                return;
                            }
                        }

                        if (t == 'voip_invite') {
                            try {
                                if (session.onInviteReceived) session.onInviteReceived(call);
                            } catch (e) { console.error(e) }
                        }
                        if (t == 'voip_invite_ack') {
                            try {
                                if (call.onInviteReceivedByPeer) call.onInviteReceivedByPeer(extra);
                            } catch (e) { console.error(e) }
                        }
                        if (t == 'voip_invite_accept') {
                            try {
                                if (call.onInviteAcceptedByPeer) call.onInviteAcceptedByPeer(extra);
                            } catch (e) { console.error(e) }
                        }
                        if (t == 'voip_invite_refuse') {
                            try {
                                if (call.onInviteRefusedByPeer) call.onInviteRefusedByPeer(extra);
                            } catch (e) { console.error(e) }
                        }
                        if (t == 'voip_invite_failed') {
                            try {
                                if (call.onInviteFailed) call.onInviteFailed(extra);
                            } catch (e) { console.error(e) }
                        }
                        if (t == 'voip_invite_bye') {
                            try {
                                if (call.onInviteEndByPeer) call.onInviteEndByPeer(extra);
                            } catch (e) { console.error(e) }
                        }
                        if (t == 'voip_invite_msg') {
                            try {
                                if (call.onInviteMsg) call.onInviteMsg(extra);
                            } catch (e) { console.error(e) }
                        }
                    }
                };


                var get_time_in_ms = function () {
                    return Date.now();
                }

                /*------------------------------------------------
                |   poll
                \*----------------------------------------------*/
                var m_ver_clear = 0;
                var m_ver_notify = 0;
                var m_ver_ack = 0;
                var m_last_active_time = 0;
                var m_time_poll_last = 0;
                var m_is_polling = false;

                var schedule_poll = function () {
                    if (m_is_polling) return;

                    m_is_polling = true;

                    session.call2('user_getmsg', {
                        line: session.line,
                        ver_clear: m_ver_clear,
                        max: 30
                    }, function (err, data) {
                        // todo ecode
                        if (err == '') {
                            var resp = data;

                            var ver_clear_old = m_ver_clear;
                            m_ver_clear = resp["ver_clear"];
                            m_ver_ack = m_ver_clear;

                            for (var i in resp["msgs"]) {
                                var v = resp["msgs"][i][0];
                                var line = resp["msgs"][i][1];

                                process_msg(decode_msg(line));

                                m_ver_clear = v;
                            }

                            if (resp["msgs"].length == 30 || m_ver_clear < m_ver_notify) {
                                schedule_poll();
                            }

                            m_last_active_time = get_time_in_ms();
                        }

                        m_is_polling = false;
                        m_time_poll_last = get_time_in_ms();
                    });
                };

                var schedule_poll_tail = function () {
                    m_time_poll_last = get_time_in_ms();
                };

                var start_tick = function () {
                    setTimeout(function () {
                        if (session.state == 'session_state_logout') {
                            return;
                        }

                        if (session.state == 'session_state_logined') {
                            var t = get_time_in_ms();

                            // poll tail
                            if (m_ver_ack < m_ver_clear && t - m_time_poll_last > 1000) {
                                schedule_poll();
                            } else if (t - m_time_poll_last >= 1000 * 60) {
                                schedule_poll();
                            }
                        }

                        start_tick();
                    }, 100);
                };

                /*------------------------------------------------
                |   notify
                \*----------------------------------------------*/

                session.socket.on('notify', function (msg) {
                    dbg('recv notify ', msg);
                    if (typeof (msg) == 'string') {
                        msg = split_python(msg, ' ', 2);
                        msg = msg.slice(1);
                    }

                    var e = msg[0];
                    if (e == 'channel2') {
                        var cid = msg[1];
                        var msgid = msg[2];
                        if (channel.m_channel_msgid != 0 && channel.m_channel_msgid + 1 > msgid) {
                            dbg('ignore channel msg', cid, msgid, channel.m_channel_msgid)
                            return;
                        }

                        // todo : handle m_channel_msgid + 1 < msgid
                        channel.m_channel_msgid = msgid;

                        var tmp = decode_msg(msg[3]);
                        if (tmp) {
                            var src = tmp[0];
                            var t = tmp[1];
                            var content = tmp[2];

                            var jj = JSON.parse(content);
                            if (t == 'channel_msg') {
                                try {
                                    if (channel.onMessageChannelReceive) {
                                        channel.onMessageChannelReceive(jj.account, jj.uid, jj.msg);
                                    }
                                } catch (e) { console.error(e) }
                            }

                            if (t == 'channel_user_join') {
                                try {
                                    if (channel.onChannelUserJoined) {
                                        channel.onChannelUserJoined(jj.account, jj.uid);
                                    }
                                } catch (e) { console.error(e) }
                            }

                            if (t == 'channel_user_leave') {
                                try {
                                    if (channel.onChannelUserLeaved) {
                                        channel.onChannelUserLeaved(jj.account, jj.uid);
                                    }
                                } catch (e) { console.error(e) }
                            }

                            if (t == 'channel_attr_update') {
                                try {
                                    if (channel.onChannelAttrUpdated) {
                                        channel.onChannelAttrUpdated(jj.name, jj.value, jj.type);
                                    }
                                } catch (e) { console.error(e) }
                            }
                        }
                    }

                    if (e == 'msg') {
                        m_ver_notify = msg[1];
                        schedule_poll();
                    }

                    if (e == 'recvmsg') {
                        var r = JSON.parse(msg[1]);
                        var v = r[0];
                        var line = r[1];
                        if (v == m_ver_clear + 1) {
                            process_msg(decode_msg(line));
                            m_ver_clear = v;
                            schedule_poll_tail();
                        } else {
                            m_ver_notify = v;
                            schedule_poll();
                        }
                    }
                });

                /*------------------------------------------------
                |   Session API : Inst msg
                \*----------------------------------------------*/
                session.messageInstantSend = function (peer, msg, cb) {
                    session.call2('user_sendmsg', {
                        line: session.line,
                        peer: peer,
                        flag: 'v1:E:3600',
                        t: 'instant',
                        content: msg
                    }, function (err, data) {
                        if (cb) cb(!is_ok(err, data));
                    });
                };


                /*------------------------------------------------
                |   Session API : General Call
                \*----------------------------------------------*/

                session.invoke = function (func, args, cb) {
                    if (func.startsWith('io.agora.signal.')) {
                        var f = func.split('.')[3];
                        args.line = session.line;
                        session.call2(f, args, function (err, ret) {
                            if (cb) {
                                cb(err, ret);
                            }
                        });
                    }
                };

                /*------------------------------------------------
                |   Session API : Attributes
                \*----------------------------------------------*/

                // // cb(err)
                // session.setAttr = function(attr, value, cb) {
                //   session.call2('user_set_attr', {
                //     line: session.line,
                //     name: attr,
                //     value: value
                //   }, function(err, data) {
                //     if (cb) {
                //         cb(err);
                //     }
                //   });
                // };

                // // cb(err, value)
                // session.getAttr = function(attr, cb) {
                //   session.call2('user_get_attr', {
                //     line: session.line,
                //     account : session.account,
                //     name: attr,
                //   }, function(err, data) {
                //     if (cb) {
                //         cb(err, data.value);
                //     }
                //   });
                // };

                // // cb(err, value)
                // session.getAttrAll = function(cb) {
                //   session.call2('user_get_attr_all', {
                //     line: session.line,
                //     account : session.account,
                //   }, function(err, data) {
                //     if (cb) {
                //         cb(err, data.json);
                //     }
                //   });
                // };

                // // cb(err, value)
                // session.getAttrAll = function(cb) {
                //   session.call2('user_get_attr_all', {
                //     line: session.line,
                //     account : session.account,
                //   }, function(err, data) {
                //     if (cb) {
                //         cb(err, data.json);
                //     }
                //   });
                // };


                /*------------------------------------------------
                |   Session API : Invite
                \*----------------------------------------------*/
                var Call = function (channelID, peer, extra) {
                    // Events
                    this.onInviteReceivedByPeer = '';
                    this.onInviteAcceptedByPeer = '';
                    this.onInviteRefusedByPeer = '';
                    this.onInviteFailed = '';
                    this.onInviteEndByPeer = '';
                    this.onInviteEndByMyself = '';
                    this.onInviteMsg = '';
                    var call = this;
                    this.channelName = channelID;
                    this.peer = peer;
                    this.extra = extra;

                    call_obj_table[channelID + peer] = call;

                    // Actions
                    this.channelInviteUser2 = function () {
                        extra = extra || '';
                        session.call2('voip_invite', {
                            line: session.line,
                            channelName: channelID,
                            peer: peer,
                            extra: extra
                        }, function (err, msg) {
                            if (is_ok(err, msg)) {

                            } else {
                                try {
                                    call.onInviteFailed(err);
                                } catch (e) { console.error(e) }
                            }
                        });
                    };

                    this.channelInviteAccept = function (extra) {
                        extra = extra || '';
                        session.call2('voip_invite_accept', {
                            line: session.line,
                            channelName: channelID,
                            peer: peer,
                            extra: extra
                        });
                    };

                    this.channelInviteRefuse = function (extra) {
                        extra = extra || '';
                        session.call2('voip_invite_refuse', {
                            line: session.line,
                            channelName: channelID,
                            peer: peer,
                            extra: extra
                        });
                    };

                    this.channelInviteDTMF = function (dtmf) {
                        session.call2('voip_invite_msg', {
                            line: session.line,
                            channelName: channelID,
                            peer: peer,
                            extra: JSON.stringify({
                                msgtype: 'dtmf',
                                msgdata: dtmf
                            })
                        });
                    };

                    this.channelInviteEnd = function (extra) {
                        extra = extra || '';
                        session.call2('voip_invite_bye', {
                            line: session.line,
                            channelName: channelID,
                            peer: peer,
                            extra: extra
                        });

                        try {
                            if (call.onInviteEndByMyself) call.onInviteEndByMyself('');
                        } catch (e) { console.error(e) }
                    };
                };

                session.channelInviteUser2 = function (channelID, peer, extra) {
                    var call = new Call(channelID, peer, extra);
                    call.channelInviteUser2();
                    return call;
                };

                /*------------------------------------------------
                |   API : Channel
                \*----------------------------------------------*/

                session.channelJoin = function (name) {
                    if (session.state != 'session_state_logined') {
                        dbg('You should log in first.')
                        return;
                    }
                    // Channel Object
                    //var channel = new function(){
                    channel = new function () {
                        //
                        // Events
                        //
                        this.onChannelJoined = '';
                        this.onChannelJoinFailed = '';
                        this.onChannelLeaved = '';
                        this.onChannelUserList = '';
                        this.onChannelUserJoined = '';
                        this.onChannelUserLeaved = '';
                        this.onChannelUserList = '';
                        this.onChannelAttrUpdated = '';
                        this.onMessageChannelReceive = '';

                        this.name = name;
                        this.state = 'joining';
                        this.m_channel_msgid = 0;

                        //
                        // Actions
                        //
                        this.messageChannelSend = function (msg, f) {
                            session.call2('channel_sendmsg', {
                                line: session.line,
                                name: name,
                                msg: msg
                            }, function (err, msg) {
                                if (f) {
                                    f();
                                }
                            });
                        };

                        this.channelLeave = function (f) {
                            session.call2('channel_leave', {
                                line: session.line,
                                name: name
                            }, function (err, msg) {
                                channel.state = 'leaved';
                                if (f) {
                                    f();
                                } else {
                                    try {
                                        if (channel.onChannelLeaved) {
                                            channel.onChannelLeaved(0);
                                        }
                                    } catch (e) { console.error(e) }
                                }
                            });
                        }

                        this.channelSetAttr = function (k, v, f) {
                            session.call2('channel_set_attr', {
                                line: session.line,
                                channel: name,
                                name: k,
                                value: v
                            }, function (err, msg) {
                                if (f) {
                                    f();
                                }
                            });
                        }

                        this.channelDelAttr = function (k, f) {
                            session.call2('channel_del_attr', {
                                line: session.line,
                                channel: name,
                                name: k
                            }, function (err, msg) {
                                if (f) {
                                    f();
                                }
                            });
                        }

                        this.channelClearAttr = function (f) {
                            session.call2('channel_clear_attr', {
                                line: session.line,
                                channel: name
                            }, function (err, msg) {
                                if (f) {
                                    f();
                                }
                            });
                        }
                    }();
                    session.call2('channel_join', {
                        line: session.line,
                        name: name
                    }, function (err, msg) {
                        if (err == '') {
                            channel.state = 'joined';
                            try {
                                if (channel.onChannelJoined) {
                                    channel.onChannelJoined();
                                }
                            } catch (e) { console.error(e) }
                            // var r = JSON.parse(msg);
                            var r = msg;
                            try {
                                if (channel.onChannelUserList) {
                                    channel.onChannelUserList(r.list);
                                }
                            } catch (e) { console.error(e) }
                            try {
                                if (channel.onChannelAttrUpdated) {
                                    for (var k in r.attrs) {
                                        channel.onChannelAttrUpdated('update', k, r.attrs[k]);
                                    }
                                }
                            } catch (e) { console.error(e) }

                        } else {
                            try {
                                if (channel.onChannelJoinFailed) {
                                    channel.onChannelJoinFailed(err);
                                }
                            } catch (e) { console.error(e) }
                        }
                    });

                    return channel;
                    // call2 ('....')
                };

            };
        }

        session.socket = null;
        shuffle(signal.lbs_url1);
        shuffle(signal.lbs_url2);
        do_lbs(2, signal.lbs_url1, 0);
        do_lbs(2, signal.lbs_url2, 0);

    };

    this.login = function (account, token) {
        return new Session(account, token);
    }
};

Signal = function (vid) {
    return new Signal_(vid);
}

module.exports = Signal;