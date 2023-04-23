# D-Link DIR-820L 存在命令注入漏洞

**漏洞厂商**: D-Link

**厂商官网**: http://www.dlink.com.cn/

**影响产品**: DIR-820L

**影响产品版本**: 1.05 B03

**固件链接**: http://www.dlinktw.com.tw/techsupport/download.ashx?file=2663

**发现者**: [SkYe231](mailto:skye231@foxmail.com)@Hillstone

## 漏洞详情

DEVICE_NAME  可以命令注入和之前漏洞一个样在 `/lan.asp` 可以设置 DEVICE_NAME 

没找到这里触发地方，这个 ncc_rtk_lltdd.c 触发的地方没找到

![image-20220227191040808](../../../Library/Application Support/typora-user-images/image-20220227191040808.png)

## EXP



