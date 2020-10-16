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

write_into_file1()
{
	size=`wc -c /usr/cms/log/rbtinfo | awk '{print $1}'`
	echo "$size"
	if [ $size -ge 1024*1024 ]
	then
		current_time=$(date +"%d/%b/%Y:%H:%M:%S")
		echo "updatetime $current_time msg $1 process_name : $1 reason : $2" >> /usr/cms/log/rbtinfo
	else
		current_time=$(date +"%d/%b/%Y:%H:%M:%S")
		echo "updatetime $current_time msg $1 process_name : $1 reason : $2" >> /usr/cms/log/rbtinfo
	fi
}

write_into_file()
{
	size=`wc -c /usr/cms/log/cms_reboot_wdt.log | awk '{print $1}'`
	#echo "$size"
	if [ $size -ge 1024000 ]
	then
		echo "Reached Max size file : $size"
		cp -v /usr/cms/log/cms_reboot_wdt.log /usr/cms/log/cms_reboot_wdt_bkp.log
		rm -f /usr/cms/log/cms_reboot_wdt.log
		current_time=$(date +"%d/%b/%Y:%H:%M:%S")
		echo "$current_time : RebootWdtProc() : Message : $1" >> /usr/cms/log/cms_reboot_wdt.log
	else
		current_time=$(date +"%d/%b/%Y:%H:%M:%S")
		echo "$current_time : RebootWdtProc() : Message : $1" >> /usr/cms/log/cms_reboot_wdt.log
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
	write_into_file "write_to_redis_server result : $result"
	echo "write_to_redis_server result " $result
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
	#printf " %s \n" $result
	#restrict list size
	if [ $result -gt 100 ]
	then
		printf "more than max elements : %s \n" $list_name
		result=$(/bin/redis-cli ltrim reboot_log 0 100)
		printf "  %s.\n" $result
	fi
	current_time=$(date +"%d/%b/%Y:%H:%M:%S")
	
	result=$(/bin/redis-cli lpush reboot_log "Update TIme : $current_time process_name : $1 reason : $2" )
	#printf "  %s.\n" $result
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
	echo "Current Reboot status from Redis Server : " "$result"
	if [ ! -z $result ]
	then
	if [ $result -eq 1 ]
	then 
		echo "Reboot is enabled"
		write_into_file "Reboot is enabled"
		proc_name=$(/bin/redis-cli hmget reboot_msg process_name)
		reason=$(/bin/redis-cli hmget reboot_msg reason)
		write_msg_to_redis_server $proc_name $reason
		write_into_file "process name : $proc_name, Reason : $reason"
		echo "process name $proc_name"
		sleep 2
		write_to_redis_server $proc_name 
		sleep 5
		if [ ! -z $proc_name ]
		then
			if [ $proc_name == "save_reset_ip" ]
			then 
				write_into_file "reboot initiated from webpageprocess save and reset ip"
				echo "reboot initiated from webpageprocess save and reset ip "
				sleep 5
				killall cms_mon_proc
				sleep 1
				killall cms_mon_proc
				sleep 2
				ip addr flush dev eth0
				sleep 2
				ip addr flush dev eth1
				sleep 2
				/etc/init.d/S40network stop
				sleep 3
				/etc/init.d/S40network start
				sleep 5
				/usr/cms/bin/cms_mon_proc > /dev/null &
			elif [ $proc_name == "save_reset" -o $proc_name == "uploadconfig" ] 
			then
				write_into_file "reboot initiated from webpageprocess save and reset"
				echo "reboot initiated from webpageprocess save and reset"
				killall cms_mon_proc
				sleep 2
				killall cms_mon_proc
				sleep 10
				
				/usr/cms/bin/cms_mon_proc > /dev/null &
			
			else
				reboot_value=1
			# if [ $proc_name == "save_reset" ]
			# then 
				# write_into_file "reboot initiated from webpageprocess save and reset"
				# echo "reboot initiated from webpageprocess save and reset"
			# else
				# reboot_value=1
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
	write_into_file "GPIO $gpio already exported"
	echo "GPIO $gpio already exported"
else
	echo $gpio > /sys/class/gpio/export
	echo out > /sys/class/gpio/gpio$gpio/direction
	write_into_file "GPIO $gpio exported"
	echo "GPIO $gpio exported"
fi

write_into_file "Entry into Ideal Loop to Monitor reboot status and provide wdt Pulse"

while [ 1 ]
do
	sleep 10
	echo "Writing Low on WDT Gpio Pin"
	#write_into_file "Writing Low on WDT Gpio Pin"
	#write_into_file("Writing Low on WDT Gpio Pin")
	echo 0 > /sys/class/gpio/gpio$gpio/value 
	sleep 1
	echo "Writing High on WDT Gpio Pin"
	#write_into_file "Writing High on WDT Gpio Pin"
	echo 1 > /sys/class/gpio/gpio$gpio/value
	sleep 1
	res=$(/bin/redis-cli ping)
	if [ -z $res ]
	then
		reboot_value=1
		echo "redis is failed to ping" 
		write_into_file "redis is failed to ping, going to reboot unit"
	fi
	 	
	echo "$reboot_value"
	reboot_msgcheck 	
	echo "Current Reboot Status Value " "$reboot_value"
	write_into_file "Current Reboot Status Value $reboot_value"
	if [ $reboot_value -eq 1 ]
	then
		echo "Reboot status become high, Need to reboot systems"
		write_into_file "Reboot status become high, Need to reboot systems"
		write_to_redis_server $proc_name 
		sync
		write_into_file "Killing Cms MonProc Process"
		echo "Killing Cms MonProc Process"
		killall cms_mon_proc
		sleep 5
		write_into_file "Issueing PowerOff Command"
		echo "Issueing PowerOff Command"
		/sbin/poweroff
		exit
	fi
done
