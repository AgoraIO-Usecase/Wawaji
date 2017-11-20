#!/bin/sh
#copy client static files
cp -r ../client/dist/* ./public/.

deployDir=/home/devops/web_demo/project/ImageStreaming
ServerName=${@:$OPTIND:1}

# Rev="$(git rev-parse HEAD)"

# echo $Rev
# cd dist
rsync -v -z -r --delete --progress -h --exclude=node_modules/* --exclude=.* --exclude=deploy_test.sh --exclude=deploy_test2.sh . $ServerName:$deployDir

echo service deployed on:$ServerName:$deployDir