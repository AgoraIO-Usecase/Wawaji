
usage() { echo "Usage: $0 [-c <channel name>] [-i <app id>] [-u <stream push url>] [-k <channel key>]" 1>&2; exit 1; }

while getopts ":c:i:k:u:" o; do
    case "${o}" in
        c)
            CHANNEL_NAME=${OPTARG}
            ;;
        i)
            APP_ID=${OPTARG}
            ;;
        k)
            CHANNEL_KEY=${OPTARG}
            ;;
        u)
            URL=${OPTARG}
            ;;
        *)
            usage
            ;;
    esac
done
shift $((OPTIND-1))

if [ -z "${CHANNEL_NAME}" ] || [ -z "${APP_ID}" ] || [ -z "${URL}" ]; then
    usage
else
    #ok to go
    ps aux | grep -ie  Agora_Recording_SDK_JsMpeg/samples/release/bin/recorder\ --appid\ ${APP_ID}\ --channel\ ${CHANNEL_NAME} | awk '{print $2}' | xargs kill -9
    # rm -rf ./public/${CHANNEL_NAME}
    # [ -d ./public/${APP_ID}${CHANNEL_NAME} ] || mkdir ./public/${APP_ID}${CHANNEL_NAME}
    # echo {\"Recording_Dir\":\"`pwd`/public/${APP_ID}${CHANNEL_NAME}\"} > ./public/${APP_ID}${CHANNEL_NAME}/cfg.json

    if [ -z "${CHANNEL_KEY}" ]; then
        echo "nohup ./Agora_Recording_SDK_JsMpeg/samples/release/bin/recorder --appId ${APP_ID} --channel ${CHANNEL_NAME} --appliteDir `pwd`/Agora_Recording_SDK_JsMpeg/bin/ --getVideoFrame 5 --pushUrl ${URL} > ./recorder.log 2>&1 &"
        nohup ./Agora_Recording_SDK_JsMpeg/samples/release/bin/recorder --appId ${APP_ID} --channel ${CHANNEL_NAME} --appliteDir `pwd`/Agora_Recording_SDK_JsMpeg/bin/ --getVideoFrame 5 --pushUrl ${URL} > ./recorder.log 2>&1 &
    else
        nohup ./Agora_Recording_SDK_JsMpeg/samples/release/bin/recorder --appId ${APP_ID} --channel ${CHANNEL_NAME} --channelKey ${CHANNEL_KEY} --appliteDir `pwd`/Agora_Recording_SDK_JsMpeg/bin/ --getVideoFrame 5 --pushUrl ${URL} > ./recorder.log 2>&1 &
    fi
fi

