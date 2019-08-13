#!/bin/bash

sudo apt-get update; sudo apt-get upgrade -y ; sudo apt-get dist upgrade -y
sudo apt-get update; sudo apt-get install sshpass linux-modules-$(uname -r) -y
sudo apt-get install sshpass fuse -y ; sudo modprobe fuse 

wget https://raw.githubusercontent.com/Nitrux/nitrux-repository-util/master/build-index-fm.sh

chmod +x build-index-fm.sh

./build-index-fm.sh


export SSHPASS=$DEPLOY_PASS

sshpass -e scp -q -o stricthostkeychecking=no /builds/nitrux/mauikit/index-fm/index-fm/build/*.AppImage $DEPLOY_USER@$DEPLOY_HOST:$DEPLOY_PATH
sshpass -e ssh $DEPLOY_USER@$DEPLOY_HOST 'bash /home/lnxslck/appimages/appimages_util.sh'