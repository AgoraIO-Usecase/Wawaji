
const winston = require('winston');
const log_format = winston.format;
const log_trans  = winston.transports;
const path = require('path');

const myFormat = log_format.printf(info => {
  return `${info.timestamp} [${info.label}] ${info.level}: ${info.message}`;
});


var logger = function (tag, file) {
	var fullpath = path.join(__dirname, `../logs/${file}`);
	this.path = null;
	const logger = winston.createLogger({
		level: 'debug',
	  format: log_format.combine(
	    log_format.label({ label: `${tag}` }),
	    log_format.timestamp(),
	    myFormat
	  ),
	  transports: [new log_trans.Console(),new log_trans.File({ filename: fullpath })]
	});

	this.get = function () {
        return logger;
		}
};

module.exports = logger;


