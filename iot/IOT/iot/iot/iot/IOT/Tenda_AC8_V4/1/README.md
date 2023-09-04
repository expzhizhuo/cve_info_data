# Tenda_AC8V4 stack overflow vulnerability

## Affected version:

```
US_AC8V4.0si_V16.03.34.06
```

To download the firmware: https://www.tenda.com.cn/download/detail-3518.html

## Description

In the firmware of Tenda AC8V4 V16.03.34.06, the route /goform/SetVirtualServerCfg can cause a stack overflow, thereby achieving a denial of service attack


The "list" parameter is passed to Var through websGetVar, and then entered into the `save_virtualser_data` function as the second parameter

![image](https://github.com/Xunflash/IOT/assets/71567536/ba9a1e7f-de40-4edc-8a08-88af3d6f99b5)

a2 is assigned to v5

![image](https://github.com/Xunflash/IOT/assets/71567536/68bf1726-a944-4b78-8607-2b52393439ad)

Then the program uses the dangerous function sscanf to format v5 and pass it into v12, v13, v14, v15

![image](https://github.com/Xunflash/IOT/assets/71567536/82b71b65-fdce-404a-bbfe-66c0ff74e389)

![image](https://github.com/Xunflash/IOT/assets/71567536/dd4dc87a-6be4-47b7-995c-e7d6f66dabc8)

## Poc&&Exp

The content of this part is placed in the additional information



![image](https://github.com/Xunflash/IOT/assets/71567536/0cfe1747-fcc1-46b3-becc-04343465f8c0)
