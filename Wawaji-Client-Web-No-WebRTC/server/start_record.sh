
usage() { echo "Usage: $0 [-c <channel name>] [-i <app id>] [-k <channel key>]" 1>&2; exit 1; }

while getopts ":c:i:k:" o; do
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
        *)
            usage
            ;;
    esac
done
shift $((OPTIND-1))

if [ -z "${CHANNEL_NAME}" ] || [ -z "${APP_ID}" ]; then
    usage
else
    #ok to go
    ps aux | grep -ie  recorder\ --appid\ ${APP_ID}\ --channel\ ${CHANNEL_NAME} | awk '{print $2}' | xargs kill -9
    # rm -rf ./public/${CHANNEL_NAME}
    [ -d ./public/${APP_ID}${CHANNEL_NAME} ] || mkdir ./public/${APP_ID}${CHANNEL_NAME}
    echo {\"Recording_Dir\":\"`pwd`/public/${APP_ID}${CHANNEL_NAME}\"} > ./public/${APP_ID}${CHANNEL_NAME}/cfg.json

    if [ -z "${CHANNEL_KEY}" ]; then
        echo "nohup ./Agora_Recording_SDK_for_Linux_FULL/samples/release/bin/recorder --appId ${APP_ID} --channel ${CHANNEL_NAME} --cfgFilePath ./public/${APP_ID}${CHANNEL_NAME}/cfg.json --appliteDir `pwd`/Agora_Recording_SDK_for_Linux_FULL/bin/ --getVideoFrame 4 --captureInterval 0 --channelProfile 1 > ./recorder.log 2>&1 &"
        nohup ./Agora_Recording_SDK_for_Linux_FULL/samples/release/bin/recorder --appId ${APP_ID} --channel ${CHANNEL_NAME} --cfgFilePath ./public/${APP_ID}${CHANNEL_NAME}/cfg.json --appliteDir `pwd`/Agora_Recording_SDK_for_Linux_FULL/bin/ --getVideoFrame 4 --captureInterval 0 --channelProfile 1 > ./recorder.log 2>&1 &
    else
        echo "nohup ./Agora_Recording_SDK_for_Linux_FULL/samples/release/bin/recorder --appId ${APP_ID} --channel ${CHANNEL_NAME} --channelKey ${CHANNEL_KEY} --cfgFilePath ./public/${APP_ID}${CHANNEL_NAME}/cfg.json --appliteDir `pwd`/Agora_Recording_SDK_for_Linux_FULL/bin/ --getVideoFrame 4 --captureInterval 0 --channelProfile 1 > ./recorder.log 2>&1 &"
        nohup ./Agora_Recording_SDK_for_Linux_FULL/samples/release/bin/recorder --appId ${APP_ID} --channel ${CHANNEL_NAME} --channelKey ${CHANNEL_KEY} --cfgFilePath ./public/${APP_ID}${CHANNEL_NAME}/cfg.json --appliteDir `pwd`/Agora_Recording_SDK_for_Linux_FULL/bin/ --getVideoFrame 4 --captureInterval 0 --channelProfile 1 > ./recorder.log 2>&1 &
    fi
fi

