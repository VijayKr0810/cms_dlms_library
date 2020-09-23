#!/bin/sh
HOST='192.168.101.178'
USER='root'
PASSWD='softel'
FILE_TX_TYPE='bi'

DEST_PATH='/usr/cms/config'
TX_FILE_NAME='dlms_api_config.cfg'

ftp -n -v $HOST << EOT
ascii
user $USER $PASSWD
prompt
$FILE_TX_TYPE
cd $DEST_PATH
put $TX_FILE_NAME
chmod 777 $TX_FILE_NAME
quit
EOT
