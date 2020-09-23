#!/bin/sh
./create_install_script.sh PROD
echo " Creating upgrade version...... "
sleep 10
./create_install_script.sh UPGRADE

