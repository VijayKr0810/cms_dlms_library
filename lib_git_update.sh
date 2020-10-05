#git init Only One time required
current_time=$(date +"%d/%b/%Y:%H:%M:%S")
git add *
git commit -m "$current_time :: daily update"
#git remote add origin  https://github.com/VijayKr0810/cms_dlms_library.git 
#// Only One time required
git push --force origin master

read -rsp $'Repository updated.Press to exit...\n'