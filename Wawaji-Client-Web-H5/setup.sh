usage() { echo "Usage: $0 [-i <appid>]" 1>&2; exit 1; }

while getopts ":i:" o; do
    case "${o}" in
        i)
            APP_ID=${OPTARG}
            ;;
        *)
            usage
            ;;
    esac
done
shift $((OPTIND-1))

if [ -z "${APP_ID}" ]; then
    usage
else
    echo "Preparing client node..."
    cd ./client
    npm install
    gulp build
    cd ..

    echo "Copying client code.."
    cp -r ./client/dist/. ./server/public/

    echo "Preparing server node..."
    cd ./server
    npm install
    cd ..

    echo "Initializing vault..."
    echo "module.exports={appid: \"${APP_ID}\",video_channel: \"xcapture\",stream_secret: \"supersecret\",video_rotation: 0}" > ./server/modules/profiles/video/vault.js


    echo "Done init! Remember to put your SDK in server folder and you are ready to go."
fi

