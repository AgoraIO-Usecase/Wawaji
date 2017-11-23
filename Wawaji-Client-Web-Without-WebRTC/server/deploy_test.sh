#!/bin/sh
#copy client static files

cd ../WawajiClient
gulp build
cd ../WawajiServer
cp -r ../WawajiClient/dist/* ./public/.

deployDir=/home/devops/web_demo/project/Wawaji_Full
ServerName=${@:$OPTIND:1}

# Rev="$(git rev-parse HEAD)"

# echo $Rev
# cd dist
rsync -v -z -r --progress -h --exclude=node_modules/* --exclude=.* --exclude=deploy_test.sh . $ServerName:$deployDir

echo service deployed on:$ServerName:$deployDir