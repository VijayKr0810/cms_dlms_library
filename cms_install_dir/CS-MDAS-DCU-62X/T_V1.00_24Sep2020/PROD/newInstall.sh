#!/bin/sh
VER="P"
killall cms_mon_proc
tar -xvf /root/cms_dcu_firmware.tar
sleep 1

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

chmod +x /bin/*
chmod +x /usr/sbin/*
chmod +x /usr/cms/bin/*
chmod +x /srv/www/htdocs/cgi-bin/*
chmod 666 /srv/www/htdocs/js/*
chmod 666 /srv/www/htdocs/*
chmod +x /etc/init.d/*

cp /root/cms_dcu_firmware/pin_details.sh /root/

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
