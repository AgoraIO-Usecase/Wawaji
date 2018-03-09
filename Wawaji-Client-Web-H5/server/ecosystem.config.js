module.exports = {
    /**
     * Application configuration section
     * http://pm2.keymetrics.io/docs/usage/application-declaration/
     */
    apps : [
  
      // First application
      {
        name      : 'Wawaji-Control',
        script    : 'server.js',
        env: {
          COMMON_VARIABLE: 'true'
        },
        env_production : {
          NODE_ENV: 'production'
        },
        args: "enable-control"
      },
      {
        name      : 'Wawaji-Web',
        script    : 'server.js',
        env: {
          COMMON_VARIABLE: 'true'
        },
        env_production : {
          NODE_ENV: 'production'
        }
      }
    ]
  };
  