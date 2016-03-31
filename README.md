# wifiPrinter_mt7688Duo
mt7688Duo demo, a wifi printer using Ada printer.

## Usage
### Goto mt7688 Terminal by ssh or serial 
* Modify configure file to change mt7688Duo to router mode **vi /etc/config/network**
<pre>
config interface 'lan'
      option proto 'static'
	  option netmask '255.255.255.0'
	  option ipaddr '192.168.100.1'
<br>
config interface 'wan'
	  option ifname 'eth0'
	  option proto 'dhcp'
</pre>
* First you need to enable yunbridge 
<pre>
> uci set yunbridge.config.disabled='0'
> uci commit
</pre>
* Then setting startup script 
<pre>
> chmod +x wifiPrinter_js/wifi_printer/script/wifiPrinter
> cp wifiPrinter_js/wifi_printer/script/wifiPrinter /etc/init.d/
> /etc/init.d/wifiPrinter enable
> /etc/init.d/wifiPrinter start &
> reboot
</pre>


## Using Arduino IDE to upload Arduino sketch
* Download this repository to your computer and copy the Arduino library to your IDE's library path, open routerBox_Arduino.ino with Arduino IDE compile and upload sketch.
