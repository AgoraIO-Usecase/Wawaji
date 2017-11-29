#delete files earlier than 1 mins
find `pwd`/public/**/-*.jpg -type f -mmin +1 -delete
find `pwd`/public/**/*.jpg -type f -mmin +1 -delete

now=$(date +"%T")
echo "Current time : $now" > `pwd`/clean.log