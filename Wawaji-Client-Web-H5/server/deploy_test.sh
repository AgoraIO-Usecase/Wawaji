#!/bin/sh
#copy client static files

cd ../client
gulp build
cd ../server
cp -r ../client/dist/* ./public/.

deployDir=/home/devops/web_demo/project/Wawaji_Full_Profile
ServerName=${@:$OPTIND:1}

# Rev="$(git rev-parse HEAD)"

# echo $Rev
# cd dist
rsync -v -z -r --progress -h --exclude=node_modules/* --exclude=.* --exclude=deploy_test.sh . $ServerName:$deployDir

echo service deployed on:$ServerName:$deployDir
