#***********************************************************************
# Copyright (c) 2020 All Right Reserved
# File Name 	: 	reboot_wdt.sh
# Description 	:	This script is used reboot setup  
# Author		:	Creative Micro Systems
# Contact		:	support@cmsgp.com
#**********************************************************************/

#!/bin/sh
#import pin_details.sh script

source /root/pin_details.sh

#**************************************************************************************************
#Function 					: write_into_file()
#Input Parameters 			: process name , reason.
#Return	Value				: None
#Description 				: This function is used write reboot messages on file
#**************************************************************************************************

write_into_file()
{
	size=`wc -c /usr/cms/log/rbtinfo | awk '{print $1}'`
	echo "$size"
	if [ $size -ge 2048 ]
	then
		current_time=$(date +"%d/%b/%Y:%H:%M:%S")
		echo "updatetime $current_time process_name : $1 reason : $2" >> /usr/cms/log/rbtinfo
	else
		current_time=$(date +"%d/%b/%Y:%H:%M:%S")
		echo "updatetime $current_time process_name : $1 reason : $2" >> /usr/cms/log/rbtinfo
	fi
}

#**************************************************************************************************
#Function 					: write_to_redis_server()
#Input Parameters 			: process_name , reboot_status 
#Return	Value				: None
#Description 				: This function is used write reboot message  status on redis server
#**************************************************************************************************

write_to_redis_server()
{
	#echo "statistics #@"
	current_time=$(date +"%d/%b/%Y:%H:%M:%S")
	result=$(/bin/redis-cli hmset reboot_msg updatetime $current_time process_name $1 reboot_status 0 reason " " )
	echo "result " $result
}

#**************************************************************************************************
#Function 					: write_msg_to_redis_server()
#Input Parameters 			: process_name , reason 
#Return	Value				: None
#Description 				: This function is used write reboot messages on redis server
#**************************************************************************************************

write_msg_to_redis_server()
{
	result=$(/bin/redis-cli llen reboot_log)
	printf "  %s.\n" $result
	#restrict list size
	if [ $result -gt 100 ]
	then
		printf "more than max elements : %s \n" $list_name
		result=$(/bin/redis-cli ltrim reboot_log 0 100)
		printf "  %s.\n" $result
	fi
	current_time=$(date +"%d/%b/%Y:%H:%M:%S")
	
	result=$(/bin/redis-cli lpush reboot_log "Update TIme : $current_time process_name : $1 reason : $2" )
	printf "  %s.\n" $result
}

#**************************************************************************************************
#Function 					: reboot_msgcheck()
#Input Parameters 			: None
#Return	Value				: None
#Description 				: This function is read reboot message status
#**************************************************************************************************


reboot_msgcheck()
{
	result=$(/bin/redis-cli hmget reboot_msg reboot_status)
	if [ ! -z $result ]
	then
	if [ $result -eq 1 ]
	then 
		echo "reboot is enabled"
		proc_name=$(/bin/redis-cli hmget reboot_msg process_name)
		reason=$(/bin/redis-cli hmget reboot_msg reason)
		write_msg_to_redis_server $proc_name $reason
		echo "process name $proc_name"
		sleep 2
		write_to_redis_server $proc_name 
		sleep 5
		if [ ! -z $proc_name ]
		then
			if [ $proc_name == "save_reset" ]
			then 
				echo "reboot initiated from webpageprocess save and reset"
			else
				reboot_value=1
			fi
		
		else
			proc_name="NA"
			reboot_value=1
		fi
		
	else
		reboot_value=0
	fi
	else
		reboot_value=0
	fi
}

#**************************************************************************************************
#Function 					: main
#Input Parameters 			: None
#Return	Value				: None
#Description 				: This function is monitor reboot status if it is high device will reboot 
#**************************************************************************************************

gpio=$WDT
touch /usr/cms/log/rbtinfo

if [ -d /sys/class/gpio/gpio$gpio ]; then
	echo "GPIO $gpio already exported"
else
	echo $gpio > /sys/class/gpio/export
	echo out > /sys/class/gpio/gpio$gpio/direction
	echo "GPIO $gpio exported"
fi
while [ 1 ]
do
	echo 0 > /sys/class/gpio/gpio$gpio/value 
	sleep 1
	echo 1 > /sys/class/gpio/gpio$gpio/value
	sleep 1
	#call function reboot_msgcheck()
	reboot_msgcheck 	
	echo "$reboot_value"	
	if [ $reboot_value -eq 1 ]
	then
		write_to_redis_server $proc_name 
		sync
		killall monProc
		sleep 5
		/sbin/poweroff
		exit
	fi
done
