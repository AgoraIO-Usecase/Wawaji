
usage() { echo "Usage: $0 [-c <channel name>] [-i <app id>] [-r <recorder uid>] [-m <stream push url1>] [-s <stream push url2>] [-a <uid1>] [-b <uid2>] [-k <channel key>]" 1>&2; exit 1; }

while getopts ":c:i:k:m:s:a:b:r:" o; do
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
        m)
            push_url_1=${OPTARG}
            ;;
        s)
            push_url_2=${OPTARG}
            ;;
        a)
            uid1=${OPTARG}
            ;;
        b)
            uid2=${OPTARG}
            ;;
        r)
            recorder=${OPTARG}
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
    ps aux | grep -ie  Agora_Recording_SDK_for_Linux_FULL/samples/release/bin/recorder\ --appid\ ${APP_ID}\ --channel\ ${CHANNEL_NAME} | awk '{print $2}' | xargs kill -9
    rm -rf ./public/${CHANNEL_NAME}_jsmpeg
    [ -d ./public/${APP_ID}${CHANNEL_NAME}_jsmpeg ] || mkdir ./public/${APP_ID}${CHANNEL_NAME}_jsmpeg
    echo {\"Recording_Dir\":\"`pwd`/public/${APP_ID}${CHANNEL_NAME}_jsmpeg\", \"BitrateKbps\":\"500\",\"${uid1}\":\"${push_url_1}\", \"${uid2}\":\"${push_url_2}\"} > ./public/${APP_ID}${CHANNEL_NAME}_jsmpeg/cfg.json

    if [ -z "${CHANNEL_KEY}" ]; then
        echo "nohup ./Agora_Recording_SDK_for_Linux_FULL/samples/release/bin/recorder --appId ${APP_ID} --channel ${CHANNEL_NAME} --uid ${recorder} --cfgFilePath ./public/${APP_ID}${CHANNEL_NAME}_jsmpeg/cfg.json --appliteDir `pwd`/Agora_Recording_SDK_for_Linux_FULL/bin/ --getVideoFrame 6 > ./recorder.log 2>&1 &"
        nohup ./Agora_Recording_SDK_for_Linux_FULL/samples/release/bin/recorder --appId ${APP_ID} --channel ${CHANNEL_NAME} --uid ${recorder} --cfgFilePath ./public/${APP_ID}${CHANNEL_NAME}_jsmpeg/cfg.json --appliteDir `pwd`/Agora_Recording_SDK_for_Linux_FULL/bin/ --getVideoFrame 6 > ./recorder_jsmpeg.log 2>&1 &
    else
        echo "nohup ./Agora_Recording_SDK_for_Linux_FULL/samples/release/bin/recorder --appId ${APP_ID} --channel ${CHANNEL_NAME} --uid ${recorder} --cfgFilePath ./public/${APP_ID}${CHANNEL_NAME}_jsmpeg/cfg.json --channelKey ${CHANNEL_KEY} --appliteDir `pwd`/Agora_Recording_SDK_for_Linux_FULL/bin/ --getVideoFrame 6 > ./recorder.log 2>&1 &"
        nohup ./Agora_Recording_SDK_for_Linux_FULL/samples/release/bin/recorder --appId ${APP_ID} --channel ${CHANNEL_NAME} --uid ${recorder} --cfgFilePath ./public/${APP_ID}${CHANNEL_NAME}_jsmpeg/cfg.json --channelKey ${CHANNEL_KEY} --appliteDir `pwd`/Agora_Recording_SDK_for_Linux_FULL/bin/ --getVideoFrame 6 > ./recorder_jsmpeg.log 2>&1 &
    fi
fi

