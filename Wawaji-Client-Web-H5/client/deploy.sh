#!/bin/sh
deployDir=/home/devops/web_test/project/wawaji_demo
ServerName=${@:$OPTIND:1}

# Rev="$(git rev-parse HEAD)"

echo $Rev
rsync -v -z -r --delete --progress -h --exclude=*.sh . $ServerName:$deployDir

echo service deployed on:$ServerName:$deployDir
