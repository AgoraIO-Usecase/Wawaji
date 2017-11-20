
usage() { echo "Usage: $0 [-c <channel name>] [-i <app id>]" 1>&2; exit 1; }

while getopts ":c:i:" o; do
    case "${o}" in
        c)
            CHANNEL_NAME=${OPTARG}
            ;;
        i)
            APP_ID=${OPTARG}
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
    echo {\"Recording_Dir\":\"/home/devops/web_demo/project/ImageStreaming/public/${APP_ID}${CHANNEL_NAME}\"} > ./public/${APP_ID}${CHANNEL_NAME}/cfg.json
    nohup ../../Agora_Recording_SDK_for_Linux_FULL/samples/release/bin/recorder --appId ${APP_ID} --channel ${CHANNEL_NAME} --cfgFilePath ./public/${APP_ID}${CHANNEL_NAME}/cfg.json --appliteDir `pwd`/../../Agora_Recording_SDK_for_Linux_FULL/bin/ --getVideoFrame 4 --captureInterval 0 --channelProfile 1 > /dev/null 2>&1 &
fi

