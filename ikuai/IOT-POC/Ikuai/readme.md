# Ikuai OS unauthorized cmd injection vulnerability
An unauthorized command injection vulnerability exists in the ActionLogin function of the webman.lua file. Due to its lax filtering of the username parameter passed during login, it is directly spliced and submitted to the logger function for execution, resulting in command injection.
![image](image/13.png)
![image](image/14.png)

The shell reverse attack is as below.
![image](image/16.png)

The vendor has patched the vulnerability in version 3.7.2. 
