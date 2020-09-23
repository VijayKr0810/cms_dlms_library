#!/bin/sh
VER="U"
killall cms_mon_proc
tar -xvf /root/cms_dcu_firmware.tar

sleep 1

CFGFOUND=0
UPGRADECFG=0
RETAINFLAG=1
CFGFILENAME=/usr/cms/config/dlms_api_config.cfg
NEWCFG=cms_dcu_firmware/usr/cms/config/dlms_api_config.cfg
RETAINFILES=0

if [ -f $CFGFILENAME ]; then
	echo "Cfg file exists"
	CFGFOUND=1
	FILESIZE=$(ls -la $CFGFILENAME | awk '{ print $5}')
	echo "Size of $CFGFILENAME = $FILESIZE bytes."
	NEWFILESIZE=$(ls -la $NEWCFG | awk '{ print $5}')
	if [ $FILESIZE = $NEWFILESIZE ]; then
		echo "File sizes are the same,retain the cfg files"
		RETAINFILES=1
		
		cp /usr/cms/config/dlms_api_config.cfg .
		cp /usr/cms/def/dlms_api_config.cfg defconfig.cfg
		cp /srv/www/htdocs/info/serial.txt .

	else
		RETAINFILES=0
		UPGRADECFG=1
		cp /usr/cms/config/dlms_api_config.cfg .
		cp /usr/cms/def/dlms_api_config.cfg defconfig.cfg
		cp /srv/www/htdocs/info/serial.txt .
	fi		
fi

echo $RETAINFILES
cp -R /root/cms_dcu_firmware/bin/* /bin/
cp -R /root/cms_dcu_firmware/sbin/* /bin/
cp -R /root/cms_dcu_firmware/lib/* /lib/

mkdir -p /libexec
rm -Rf /usr/cms/*

cp -R /root/cms_dcu_firmware/libexec/* /libexec/
cp -R /root/cms_dcu_firmware/home/* /home/
cp -R /root/cms_dcu_firmware/usr/* /usr/
rm -Rf /usr/cms/event/*
rm /usr/cms/log/*
cp -R /root/cms_dcu_firmware/usr/sbin/* /usr/sbin/
rm -Rf /srv/*
cp -R /root/cms_dcu_firmware/srv /
cp -R /root/cms_dcu_firmware/etc/* /etc/

if [ $RETAINFILES = $RETAINFLAG ]; then
	echo "Copying the cfg files back"
	cp /root/dlms_api_config.cfg /usr/cms/config/dlms_api_config.cfg
fi

chmod +x /bin/*
chmod +x /usr/sbin/*
chmod +x /usr/cms/bin/*
chmod 666 /srv/www/htdocs/*

if [ $CFGFOUND = 1 ]; then
	echo "Config file found, create new ones from old"
	rm /root/*.cfg
	rm /root/*.json
	
fi

chmod +x /etc/init.d/*
cp /root/cms_dcu_firmware/lib/libcurl* /lib/
cp /root/cms_dcu_firmware/lib/curl /lib
chmod +x /lib/curl
cp /root/cms_dcu_firmware/lib/curl /usr/cms/bin/
chmod +x /usr/cms/bin/curl

cd /lib
chmod +x libcurl.so.4.4.0
ln -s libcurl.so.4.4.0 libcurl.so
ln -s libcurl.so.4.4.0 libcurl.so.4

rm -Rf /root/cms_dcu_firmware*
mv /root/serial.txt /srv/www/htdocs/info/serial.txt
echo "Installed DCU Firmware Successfully"
date > /srv/www/htdocs/info/fwInstDate
echo -e $VER >> /srv/www/htdocs/info/fwInstDate
sleep 3
reboot
exit
