#!/bin/sh
VER="U"
#/bin/gpioRegOutputTest 3 31 &
killall dcuMonProc
tar -xvf /root/dcuFirmware.tar
sleep 1
CFGFOUND=0
UPGRADECFG=0
RETAINFLAG=1
CFGFILENAME=/usr/cms/config/config.cfg
NEWCFG=dcuFirmware/usr/cms/config/config.cfg
RETAINFILES=0
if [ -f $CFGFILENAME ]; then
	echo "Cfg file exists"
	CFGFOUND=1
#	FILESIZE=$(stat -c%s "$CFGFILENAME")
	FILESIZE=$(ls -la $CFGFILENAME | awk '{ print $5}')
	echo "Size of $CFGFILENAME = $FILESIZE bytes."
	NEWFILESIZE=$(ls -la $NEWCFG | awk '{ print $5}')
	if [ $FILESIZE = $NEWFILESIZE ]; then
		echo "File sizes are the same,retain the cfg files"
		RETAINFILES=1
		cp /usr/cms/config/config.cfg .
		cp /usr/cms/def/config.cfg defconfig.cfg
		cp /srv/www/htdocs/dcuConfig.json .
		cp /srv/www/htdocs/temp_dcuConfig.json .
		cp /srv/www/htdocs/info/serial.txt .

	else
		RETAINFILES=0
		UPGRADECFG=1
		cp /usr/cms/config/config.cfg .
		cp /usr/cms/def/config.cfg defconfig.cfg
		cp /srv/www/htdocs/dcuConfig.json .
		cp /srv/www/htdocs/temp_dcuConfig.json .
		cp /srv/www/htdocs/info/serial.txt .
		
	fi		
fi
echo $RETAINFILES
cp -R /root/dcuFirmware/bin/* /bin/
cp -R /root/dcuFirmware/sbin/* /bin/
cp -R /root/dcuFirmware/lib/* /lib/
mkdir -p /libexec
rm -Rf /usr/cms/*
cp -R /root/dcuFirmware/libexec/* /libexec/
cp -R /root/dcuFirmware/home/* /home/
cp -R /root/dcuFirmware/usr/* /usr/
rm -Rf /usr/cms/event/*
rm /usr/cms/log/*
cp -R /root/dcuFirmware/usr/sbin/* /usr/sbin/
rm -Rf /srv/*
cp -R /root/dcuFirmware/srv /
cp -R /root/dcuFirmware/etc/* /etc/
if [ $RETAINFILES = $RETAINFLAG ]; then
	echo "Copying the cfg files back"
	cp /root/config.cfg /usr/cms/config/config.cfg
#        mv /root/deftrtu.cfg /usr/cms/def/trtu.cfg
	mv /root/config.cfg /srv/www/htdocs/config.cfg
	mv /root/dcuConfig.json /srv/www/htdocs/dcuConfig.json
	mv /root/temp_dcuConfig.json /srv/www/htdocs/temp_dcuConfig.json
fi
chmod +x /bin/*
chmod +x /usr/sbin/*
chmod +x /usr/cms/bin/*
chmod +x /srv/www/htdocs/cgi-bin/*
chmod 666 /srv/www/htdocs/js/*
chmod 666 /srv/www/htdocs/*
if [ $CFGFOUND = 1 ]; then
	echo "Config file found, create new ones from old"
	echo "Copy old json file"
	cp /root/temp_dcuConfig.json /srv/www/htdocs/
	echo "Run json to config"
	/srv/www/htdocs/cgi-bin/json2config
	echo "Running config2Json"
	/srv/www/htdocs/cgi-bin/config2json
	echo "Copy config json to temp config json"
	cp /srv/www/htdocs/dcuConfig.json /srv/www/htdocs/temp_dcuConfig.json
	echo "Copying the config to running dir"
	cp /srv/www/htdocs/config.cfg /usr/cms/config/config.cfg
	rm /root/*.cfg
	rm /root/*.json
	
fi
chmod +x /etc/init.d/*
cp /root/dcuFirmware/lib/libcurl* /lib/
cp /root/dcuFirmware/lib/curl /lib
chmod +x /lib/curl
cp /root/dcuFirmware/lib/curl /usr/cms/bin/
chmod +x /usr/cms/bin/curl

cd /lib
chmod +x libcurl.so.4.4.0
ln -s libcurl.so.4.4.0 libcurl.so
ln -s libcurl.so.4.4.0 libcurl.so.4

rm -Rf /root/dcuFirmware*
mv /root/serial.txt /srv/www/htdocs/info/serial.txt
echo "Installed DCU Firmware Successfully"
date > /srv/www/htdocs/info/fwInstDate
echo -e $VER >> /srv/www/htdocs/info/fwInstDate
sleep 3
reboot
exit
