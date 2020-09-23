#!/bin/sh
VER="P"
#/bin/gpioRegOutputTest 3 31 &
killall dcuMonProc
tar -xvf /root/dcuFirmware.tar
sleep 1
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
chmod +x /bin/*
chmod +x /usr/sbin/*
chmod +x /usr/cms/bin/*
chmod +x /srv/www/htdocs/cgi-bin/*
chmod 666 /srv/www/htdocs/js/*
chmod 666 /srv/www/htdocs/*
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
