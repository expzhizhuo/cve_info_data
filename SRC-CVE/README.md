Stack Overflow Vulnerability in Tenda AX12 Router

write in front

Tenda official website: https://www.tenda.com.cn/default.html

About Tenda: https://www.tenda.com.cn/profile/contact.html

Firmware download: https://www.tenda.com.cn/download/

Affect version

![image](https://user-images.githubusercontent.com/102948391/161495172-905f61f5-ea0b-4012-bef9-55c041df46ca.png)

The picture shows the latest version

Vulnerability Details 

![image](https://user-images.githubusercontent.com/102948391/161495459-ec830546-9db9-4e20-ab2e-6426b355192c.png)

The program passes the content of the lanip parameter to v4, and then uses the sscanf function to format the matched content into the stack of v20, v21, v22, and v23 through regular expressions, without checking the size. There is a stack overflow vulnerability

Vulnerability reproduction and POC

In order to reproduce the vulnerability, the following steps can be followed:

1. Use fat to simulate firmware V15.03.2.21_cn

2. Attack using the following POC attack

![image](https://user-images.githubusercontent.com/102948391/161495855-6604423b-9fd0-4abe-a8f1-c603d0ac6038.png)

![image](https://user-images.githubusercontent.com/102948391/161495894-09dd1887-152b-4c2d-8cf9-4b210d12b99d.png)

The picture shows the effect of POC attack
