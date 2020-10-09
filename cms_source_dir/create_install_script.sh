#!/bin/sh
VERSION_CODE="$(echo "Hello Hai Hi hhh" | awk '{print $2}')"
#VERSION_CODE={ls} 
#VERSION_CODE="$(echo | awk -v home=$HOME '{print "My home is " home}')"
echo $VERSION_CODE

#exit 0
echo $1
if [ "$1" = "" ]
then
	echo "Enter the version : PROD/UPGRADE"
	exit
elif [ "$1" = "PROD" ]
then
	echo "Production version"
elif [ "$1" = "UPGRADE" ]
then
	echo "Upgrade version"
else
	echo "Enter the version : PROD/UPGRADE"
	exit
fi

VER="$1"
echo $VER
echo ""
echo "DCU"

echo "Creating DCU Config file"
cd ./cms_gen_def_cfg_proc
make clean;make
./cms_gen_def_cfg

cp dlms_api_config.cfg ../cms_dcu_firmware/usr/cms/config/
cp dlms_api_config.cfg ../cms_dcu_firmware/usr/cms/def/

#cp ../cms_dcu_firmware/srv/www/htdocs/auth.json ../cms_dcu_firmware/usr/cms/def/
cp version.txt ../cms_dcu_firmware/srv/www/htdocs/info/
cp cms_dcu_feature.json ../cms_dcu_firmware/srv/www/htdocs/

# cp dcuConfig.json ../cms_dcu_firmware/srv/www/htdocs/dcuConfig.json
# cp dcuConfig.json ../cms_dcu_firmware/srv/www/htdocs/temp_dcuConfig.json

eth=0
filename="cms_dcu_feature.json"
substring1=Ethernet
substring2=2

hw_type_str=HwType

ATSAM91G_FOUND=0
True=1

while read -r line
do
    name="$line"
	echo "Line read from file - $name"
	if printf %s\\n "${name}" | grep -qF "${hw_type_str}"; then
		echo "Line contains HW Details"
		if printf %s\\n "${name}" | grep -qF "ATSAM91G"; then
			ATSAM91G_FOUND=1
		fi
	fi

	if printf %s\\n "${name}" | grep -qF "${substring1}"; then
		echo "Line contains Ethernet"
		if printf %s\\n "${name}" | grep -qF "${substring2}"; then
			echo "Line contains Ethernet:2"
			eth=2
		fi
	fi
done < "$filename"

cd ..

if [ $ATSAM91G_FOUND -eq $True ];
	then
	echo "Hw type is ATSAM91G"
	cp atsam91g_pin_details.sh pin_details.sh
else
	echo "Hw type is ATSAM91X"
	cp atsam91x_pin_details.sh pin_details.sh
fi

cp pin_details.sh ./cms_dcu_firmware/

echo -n "Firmware Version : "
VERSION=`cat cms_common_inc/version.h | awk -F\" '{print $2}'`
echo $VERSION

echo ""
echo "building cms_mon_proc ..."
cd ./cms_mon_proc
make clean;make
cd ..
cp ./cms_mon_proc/cms_mon_proc bin/.
echo ""

echo "building FtpProc ..."
cd ./cms_ftp_push_proc
make clean;make
cd ..
cp ./cms_ftp_push_proc/cms_ftp_push_proc bin/.
echo ""

echo "building cms_dlms_api_library..."
cd ./cms_dlms_api_library
make clean;make
cd ..
cp ./cms_dlms_api_library/lib/dlms_api_lib.so lib/.
cp ./cms_dlms_api_library/lib/dlms_api_lib.so cms_dcu_firmware/usr/cms/lib/.
cp ./cms_dlms_api_library/lib/dlms_api_lib.so cms_dcu_firmware/lib/.
cp ./cms_dlms_api_library/lib/dlms_api_lib.so cms_dcu_firmware/usr/lib/.
echo ""

echo "building cms_dlms_met_poll_proc..."
cd ./cms_dlms_met_poll_proc
make clean;make
cd ..
cp ./cms_dlms_met_poll_proc/cms_dlms_met_poll_proc bin/.
echo ""

echo "building cms_web_back_end_proc..."
cd ./cms_web_back_end_proc
make clean;make
cd ..
cp ./cms_web_back_end_proc/cms_web_back_end_proc bin/.
echo ""

echo "building cms_ntpclient_proc..."
cd ./cms_ntpclient_proc
make clean;make
cd ..
cp ./cms_ntpclient_proc/cms_ntpclient_proc bin/.
echo ""

echo "building cms_bin_to_redis_proc..."
cd ./cms_bin_to_redis_proc
make clean;make
cd ..
cp ./cms_bin_to_redis_proc/cms_bin_to_redis_proc bin/.
echo ""

echo "building cms_gen_csv_file_proc..."
cd ./cms_gen_csv_file_proc
make clean;make
cd ..
cp ./cms_gen_csv_file_proc/cms_gen_csv_proc bin/.
echo ""

# echo ""
# echo "building modTcpSlaveProc ..."
# cd ./ModTcpSlave
# make clean;make
# cd ..
# cp ./ModTcpSlave/dcuModTcpSProc bin/.
# echo ""

echo ""
echo "building cms_create_nw_inf ..."
cd ./cms_create_nw_inf
make clean;make
cd ..
cp ./cms_create_nw_inf/cms_create_nw_inf bin/.
echo ""

echo "building resetSwitchProc ..."
cp ./reset_switch_check.sh bin/.
echo ""

echo "building reboot_wdt ..."
cp ./reboot_wdt.sh bin/.

echo ""

cp bin/* cms_dcu_firmware/usr/cms/bin/
echo ""

# echo ""
# echo "building WebRel"
# cd ./WebRel
# make clean;make
# cd ..
# cp WebRel/cgi-bin/* cms_dcu_firmware/srv/www/htdocs/cgi-bin/


echo "Creating FIRMWARE ..."
if [ $VER = "PROD" ]
then
	echo "Production version"
	if [ $eth = 2 ]; 
	then
		echo "Two ethernet ports"
		cp -Rf network cms_dcu_firmware/etc/
		mv cms_dcu_firmware/etc/network/interfaces2 cms_dcu_firmware/etc/network/interfaces
		rm -Rf cms_dcu_firmware/usr/cms/def/interfaces/*
		cp cms_dcu_firmware/etc/network/interfaces cms_dcu_firmware/usr/cms/def/interfaces/interfaces
	else
		echo "One ethernet port"
		cp -Rf network cms_dcu_firmware/etc/
		rm -Rf cms_dcu_firmware/usr/cms/def/interfaces/*
		cp cms_dcu_firmware/etc/network/interfaces cms_dcu_firmware/usr/cms/def/interfaces/interfaces
		rm cms_dcu_firmware/etc/network/interfaces2
	fi	
	cp newInstall.sh ../cms_install_dir/newInstall.sh
else
	echo "Upgrade version"
	if [ $eth = 2 ]; 
	then 
		rm -Rf cms_dcu_firmware/usr/cms/def/interfaces/*
		cp network/interfaces2 cms_dcu_firmware/usr/cms/def/interfaces/interfaces
	else
		rm -Rf cms_dcu_firmware/usr/cms/def/interfaces/*
		cp network/interfaces cms_dcu_firmware/usr/cms/def/interfaces/interfaces
	fi
	
	rm -Rf cms_dcu_firmware/etc/network
	cp newInstall.sh.Upgrade ../cms_install_dir/newInstall.sh
fi

cp -Rf cms_master_user_det_json/* cms_dcu_firmware/srv/www/htdocs/

tar -cvf cms_dcu_firmware.tar cms_dcu_firmware 
mv cms_dcu_firmware.tar ../cms_install_dir/

echo "building cms_fw_md5_check_sum"
cd ./cms_fw_md5_check_sum
make clean;make
./cms_fw_md5_check_sum 0
cd ..

VERSION_CODE="$(echo $VERSION | awk '{print $1}')"
echo $VERSION_CODE

VERSION_CODE_DATE="$(echo $VERSION | awk '{print $2 "_" $3}')"
echo $VERSION_CODE_DATE

WEBFWDIR="cms"

mkdir -p ../cms_install_dir/$VERSION_CODE/$VERSION_CODE_DATE/$VER  
cp ../cms_install_dir/newInstall.sh ../cms_install_dir/$VERSION_CODE/$VERSION_CODE_DATE/$VER/
cp ../cms_install_dir/cms_dcu_firmware.tar ../cms_install_dir/$VERSION_CODE/$VERSION_CODE_DATE/$VER/
cp ReleaseNotes.txt ../cms_install_dir/$VERSION_CODE/$VERSION_CODE_DATE/$VER/
cp cms_fw_md5_check_sum/checksum ../cms_install_dir/$VERSION_CODE/$VERSION_CODE_DATE/$VER/
cp cms_fw_md5_check_sum/checksum ../cms_install_dir/checksum

echo "Creating firmware for web upload"
rm -Rf ../cms_install_dir/$WEBFWDIR  
mkdir -p ../cms_install_dir/$WEBFWDIR 

cp ../cms_install_dir/newInstall.sh ../cms_install_dir/$WEBFWDIR
cp ../cms_install_dir/cms_dcu_firmware.tar ../cms_install_dir/$WEBFWDIR
cp ../cms_install_dir/checksum ../cms_install_dir/$WEBFWDIR

echo "Copying Web FW bin"
cd ../cms_install_dir
rm -Rf $WEBFWDIR.zip  
zip -r $WEBFWDIR.zip $WEBFWDIR
cp $WEBFWDIR.zip $VERSION_CODE/$VERSION_CODE_DATE/$VER/$WEBFWDIR.bin
cd -

echo "Firmware Created Successfully !!"

echo ""
echo -n "Firmware Version:  "
echo $VERSION

echo "Copied release for backup..."