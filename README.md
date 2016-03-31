# wifiPrinter_mt7688Duo
mt7688Duo demo, a wifi printer using Ada printer.

## Usage
### Goto mt7688 Terminal by ssh or serial
Now you can set 7688duo's WiFi to **AP mode** or **station mode**. <br>
If you have an ethernet cable I suggest you to set AP mode, then 7688Duo can also be a router.<br>
To set station mode your mobile phone or PC must be in the same network with 7688duo.<br>

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

* Modify configure file to change mt7688Duo to station mode **vi /etc/config/wireless**
<pre>
config wifi-iface 'sta'
        option device 'radio0'
        option mode 'sta'
        option network 'wan'
        option ifname 'apcli0'
        option led 'mediatek:orange:wifi'
        option ssid 'UplinkAp'  # router ssid
        option key 'SecretKey'  # pass world
        option encryption 'psk'
        option disabled '1'     # 0 to enable
</pre>
* Type cmdline **wifi** to let wifi work.
<pre>
> wifi
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
