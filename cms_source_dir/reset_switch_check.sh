#***********************************************************************
# Copyright (c) 2020 All Right Reserved
# File Name 	: 	reset_switch_check.sh
# Description 	:	this script will monitor gpio pin if it is high more then 5 sec then 
# 					reboot status will update in redis server
# Author		:	Creative Micro Systems
# Contact		:	support@cmsgp.com
#**********************************************************************/

#!/bin/sh
source /root/pin_details.sh

#**************************************************************************************************
#Function 					: write_to_redis_server()
#Input Parameters 			: None
#Return	Value				: None
#Description 				: This function is used write reboot status on redis server
#**************************************************************************************************

write_to_redis_server()
{
result=$(/bin/redis-cli hmset reboot_msg reboot_status 1 process_name reset_switch_check.sh reason "reset_switch_pressed" )
printf "result %s.\n" $result
}

#**************************************************************************************************
#Function 					: write_hc_msg_redis_server()
#Input Parameters 			: None
#Return	Value				: None
#Description 				: This function is used write hc messages on redis server
#**************************************************************************************************

write_hc_msg_redis_server()
{
	current_time=$(date +"%s")
	#echo $current_time
	/bin/redis-cli hmset reset_switch_hc_msg updatetime $current_time
	#echo "$result"
	
}
#**************************************************************************************************
#Function 					: main
#Input Parameters 			: None
#Return	Value				: None
#Description 				: to monitor gpio pin
#**************************************************************************************************

gpio=$RESET_SWITCH
if [ ! -d /sys/class/gpio/gpio$gpio ] #To find GPIO is present or not
then
	echo "${gpio}" > /sys/class/gpio/export # To export required GPIO
	echo "in" > /sys/class/gpio/gpio$gpio/direction #To give direction for gpio (input or output)
else
	echo "${gpio} is already available no need export"
	#error msg need to send radis server
fi
#value=$(cat /sys/class/gpio/gpio$gpio/value)
while [ 1 ]
do
  value=$(cat < /sys/class/gpio/gpio$gpio/value)
  if [ 1 -eq $value ] #to check is the gpio is high or not
  then
    echo "gpio is high"
  else
    echo "gpio is low"
	sleep 2
	if [ 0 -eq "$(cat </sys/class/gpio/gpio"$gpio"/value)" ]
	then
		cp /usr/cms/def/dlms_api_config.cfg /usr/cms/config/
		cp /usr/cms/def/interfaces/interfaces /etc/network/interfaces
		write_to_redis_server 
		echo "reset switch is pressed"
	fi
  fi
  sleep 3
  write_hc_msg_redis_server
done 