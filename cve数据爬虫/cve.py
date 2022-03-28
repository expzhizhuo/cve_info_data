import time
import requests
import re
import datetime
import pymysql
from time import gmtime, strftime
import random


# 获取cve编号和描述信息
def info(count, name):
    print('爬取厂商：'+name)
    base_url = 'https://cve.mitre.org/cgi-bin/cvekey.cgi?keyword='+name
    headers = {
        'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9',
        'Accept-Encoding': 'gzip, deflate, br',
        'Accept-Language': 'zh-CN,zh;q=0.9',
        'Cache-Control': 'max-age=0',
        # 'Connection': 'keep-alive',
        'Host': 'cve.mitre.org',
        'Referer': 'https://cve.mitre.org/cve/search_cve_list.html',
        'sec-ch-ua': '" Not A;Brand";v="99", "Chromium";v="96", "Google Chrome";v="96"',
        'sec-ch-ua-mobile': '?0',
        'sec-ch-ua-platform': '"Windows"',
        'Sec-Fetch-Dest': 'document',
        'Sec-Fetch-Mode': 'navigate',
        'Sec-Fetch-Site': 'same-origin',
        'Sec-Fetch-User': '?1',
        'Upgrade-Insecure-Requests': '1',
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/96.0.4664.110 Safari/537.36'
    }
    resp = requests.get(base_url, headers=headers, timeout=120)
    if resp.status_code == 200:
        cvenum = re.findall('<a href=".*?">(.*?)</a></td>', resp.text, re.M)
        print(len(cvenum))
        print('================================')
        Description = re.compile(
            '<td valign="top">(.*?)</td>', re.S).findall(resp.text)
        print(len(Description))
        print('================================')
        if len(cvenum) > 20:
            for i in range(0, 20):
                cvenumbe = cvenum[i]
                # cvenumbe='CVE-2021-31385'
                Descriptiontxt = Description[i].replace('\n', '')
                cveinfo(cvenumbe, Descriptiontxt, name)
                count = count+1
        else:
            for i in range(0, len(cvenum)):
                cvenumbe = cvenum[i]
                # cvenumbe='CVE-2021-31385'
                Descriptiontxt = Description[i].replace('\n', '')
                cveinfo(cvenumbe, Descriptiontxt, name)
                count = count+1
        print('================================')
        print('共爬取：'+str(count)+'次')
        print(name)
        sleep1 = random.randint(10, 20)  # 反爬，每次访问随机间隔5-10s
        print('程序休息：'+str(sleep1)+'秒')
        time.sleep(sleep1)
    else:
        pass


# 获取评分信息
def cveinfo(cvenumbe, Descriptiontxt, name):
    base_url = 'https://nvd.nist.gov/vuln/detail/'+cvenumbe
    header = {
        'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9',
        'Accept-Encoding': 'gzip, deflate, br',
        'Accept-Language': 'zh-CN,zh;q=0.9',
        'Cache-Control': 'max-age=0',
        # 'Connection': 'keep-alive',
        'Cookie': '__utma=141729133.1858053219.1638156451.1641789700.1642036679.25; __utmc=141729133; __utmz=141729133.1642036679.25.12.utmcsr=cve.mitre.org|utmccn=(referral)|utmcmd=referral|utmcct=/; __utmt_GSA_CP1=1; __utmt_GSA_CP2=1; __utmb=141729133.4.10.1642036679',
        'Host': 'nvd.nist.gov',
        'Referer': 'https://cve.mitre.org/',
        'sec-ch-ua': '" Not A;Brand";v="99", "Chromium";v="96", "Google Chrome";v="96"',
        'sec-ch-ua-mobile': '?0',
        'sec-ch-ua-platform': '"Windows"',
        'Sec-Fetch-Dest': 'document',
        'Sec-Fetch-Mode': 'navigate',
        'Sec-Fetch-Site': 'cross-site',
        'Sec-Fetch-User': '?1',
        'Upgrade-Insecure-Requests': 'Upgrade-Insecure-Requests',
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/96.0.4664.110 Safari/537.36'
    }
    resp = requests.get(url=base_url, headers=header, timeout=120)
    if resp.status_code == 200:
        print(cvenumbe)  # cve编号
        print('==============开始获取数据=============')
        print(Descriptiontxt)  # 描述
        NIST = re.findall(
            'data-testid="vuln-cvss3-source-nvd">(.*?)</span>', resp.text)  # 正则匹配NIST3名字
        NIST2 = re.findall(
            'data-testid="vuln-cvss2-source-nvd">(.*?)</span>', resp.text)  # 正则匹配NIST2名字
        Score = re.findall(
            'class="label label-.*?">(.*?)</a>', resp.text)  # 正则匹配所有评分
        # 正则匹配cvssv3评分用于判断v3评分是否存在
        NVDv3score = re.findall(
            'data-testid="vuln-cvss3-panel-score-na">(.*?)</a>', resp.text)
        CNA = re.findall(
            'data-testid="vuln-cvss3-source-cna">(.*?)</span>', resp.text)  # 正则匹配CNA名字
        NVD_Published_Date = re.findall(
            'vuln-published-on">(.*?)</span>', resp.text)  # 正则匹配NVD发布日期
        NVD_Last_Modified = re.findall(
            'vuln-last-modified-on">(.*?)</span>', resp.text)  # 正则匹配NVS最后修改日期
        Source = re.findall(
            'vuln-current-description-source">(.*?)</span>', resp.text)  # 正则匹配来源（发布者）
        Hyperlinkold = re.findall(
            'target="_blank">(.*?)</a></td>', resp.text)  # 正则匹配参考链接
        if len(Hyperlinkold) == 0:
            Hyperlink = None
        else:
            Hyperlink = ''.join(str(i+';') for i in Hyperlinkold)  # 将参考链接转成字符串
        # 判断NIST的名字是否存在
        if len(Hyperlinkold) == 0:
            Hyperlink = None
        else:
            Hyperlink = ''.join(str(i+';') for i in Hyperlinkold)  # 将参考链接转成字符串
        # 判断NIST的名字是否存在
        if len(NIST) < 1:
            NISTname = None
        else:
            NISTname = NIST[0]
        # 判断CNA是否出现
        if len(CNA) < 1:
            CNAname = None  # CNA名字
            if len(Score) == 0:
                Scorev3 = 0  # NVDv3分数
                Scorev2 = 0  # NVDv2分数
                ScoreCNAnum = 0  # CNA分数
            elif len(Score) == 1:
                # 判断NISTV3的评分是否存在
                if len(NIST2) > 1:
                    Scorev3 = 0  # NVDv3分数
                    Scorev2 = Score[0].split(' ')[0]  # NVDv2分数
                    ScoreCNAnum = 0  # CNA分数
                else:
                    Scorev3 = 0  # NVDv3分数
                    Scorev2 = 0  # NVDv2分数
                    ScoreCNAnum = Score[0].split(' ')[0]  # CNA分数
            elif len(Score) == 2:
                Scorev3 = Score[0].split(' ')[0]  # NVDv3分数
                Scorev2 = Score[1].split(' ')[0]  # NVDv2分数
                ScoreCNAnum = 0  # CNA分数
            else:
                pass
        else:
            CNAname = CNA[0]  # CNA名字
            if len(Score) == 0:
                Scorev3 = 0  # NVDv3分数
                Scorev2 = 0  # NVDv2分数
                ScoreCNAnum = 0  # CNA分数
            elif len(Score) == 1:
                ScoreCNAnum = Score[0].split(' ')[0]  # CNA分数
                Scorev3 = 0  # NVDv3分数
                Scorev2 = 0  # NVDv2分数
            elif len(Score) == 2:
                # 判断NISTV3的评分是否存在
                if len(NVDv3score) > 1:
                    Scorev3 = 0  # NVDv3分数
                    Scorev2 = Score[1].split(' ')[0]  # NVDv2分数
                    ScoreCNAnum = Score[0].split(' ')[0]  # CNA分数
                else:
                    if len(NVDv3score) > 0 and len(NIST2) > 0:
                        Scorev3 = 0  # NVDv3分数
                        Scorev2 = Score[1].split(' ')[0]  # NVDv2分数
                        ScoreCNAnum = Score[0].split(' ')[0]  # CNA分数
                    else:
                        Scorev3 = Score[0].split(' ')[0]  # NVDv3分数
                        Scorev2 = 0  # NVDv2分数
                        ScoreCNAnum = Score[1].split(' ')[0]  # CNA分数
            else:
                Scorev3 = Score[0].split(' ')[0]  # NVDv3分数
                Scorev2 = Score[2].split(' ')[0]  # NVDv2分数
                ScoreCNAnum = Score[1].split(' ')[0]  # CNA分数
        # 判断首次提交时间
        if len(NVD_Published_Date) == 0:
            NVD_Published_Date_time = None
        else:
            Published_yesr = int(NVD_Published_Date[0].split('/')[2])
            Published_month = int(NVD_Published_Date[0].split('/')[0])
            Published_day = int(NVD_Published_Date[0].split('/')[1])
            NVD_Published_Date_time = datetime.date(
                Published_yesr, Published_month, Published_day)
        # 判断最后修改时间
        if len(NVD_Last_Modified) == 0:
            NVD_Last_Modified1 = None
        else:
            Last_year = int(NVD_Last_Modified[0].split('/')[2])
            Last_month = int(NVD_Last_Modified[0].split('/')[0])
            Last_day = int(NVD_Last_Modified[0].split('/')[1])
            NVD_Last_Modified1 = datetime.date(Last_year, Last_month, Last_day)
        # 判断来源
        if len(Source) == 0:
            Sourcewho = None
        else:
            Sourcewho = Source[0]
        # 定义初始id，数据库id默认自增
        id = None
        # 获取当前时间
        timenow = datetime.datetime.now()
        # 调用数据库储存数据
        print('============爬取数据结果===============')
        print(id,cvenumbe,'\n', Descriptiontxt,'\n',NISTname,'\n',Scorev3,'\n',CNAname,'\n',ScoreCNAnum,'\n',
              Scorev2,'\n',NVD_Published_Date_time,'\n',NVD_Last_Modified1,'\n',Sourcewho,'\n',name,'\n',Hyperlink,'\n',timenow)
        print('=======================================')
        mysqlin(id, cvenumbe, Descriptiontxt, NISTname, Scorev3, CNAname, ScoreCNAnum,
                Scorev2, NVD_Published_Date_time, NVD_Last_Modified1, Sourcewho, name, Hyperlink, timenow)
    else:
        pass
        print("请求出错！404")


# 数据库链接
def mysqlin(id, cvenumbe, Descriptiontxt, NISTname, Scorev3, CNAname, ScoreCNAnum, Scorev2, NVD_Published_Date_time, NVD_Last_Modified1, Sourcewho, name, Hyperlink, timenow):
    print('连接到mysql服务器...')
    db = pymysql.connect(
        host="127.0.0.1",
        user="root",
        passwd="root",
        port=3306,
        db="cvedata",
        charset='utf8',
        cursorclass=pymysql.cursors.DictCursor)
    print('连接成功!')
    cursor = db.cursor()
    insert_color = ("SELECT id FROM `cvedata` where cvenumber=%s")
    dese = (cvenumbe)
    cursor.execute(insert_color, dese)
    db.commit()
    result = cursor.fetchall()
    print(result)
    if len(result) == 0:
        insert_data = ("INSERT INTO `cvedata` (`id`, `cvenumber`, `description`,`nist`,`score3`,`cna`,`scorecnanum`,`score2`,`nvd_published_date`,`nvd_last_modified`,`sorce`,`name`,`hyperlink`,`time`) VALUES(%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s);")
        dese = (id, cvenumbe, Descriptiontxt, NISTname, Scorev3, CNAname, ScoreCNAnum,
                Scorev2, NVD_Published_Date_time, NVD_Last_Modified1, Sourcewho, name, Hyperlink, timenow)
        cursor.execute(insert_data, dese)
        db.commit()
        result = cursor.fetchall()
        print(len(result))
        print('爬取数据成功')
    else:
        updata_data = ("UPDATE `cvedata` SET `description`=%s,`nist`=%s,`score3`=%s,`cna`=%s,`scorecnanum`=%s,`score2`=%s,`nvd_published_date`=%s,`nvd_last_modified`=%s,`sorce`=%s,`hyperlink`=%s,`time`=%s WHERE `cvenumber`=%s")
        dese = (Descriptiontxt, NISTname, Scorev3, CNAname, ScoreCNAnum,
                Scorev2, NVD_Published_Date_time, NVD_Last_Modified1, Sourcewho, Hyperlink, timenow, cvenumbe)
        cursor.execute(updata_data, dese)
        db.commit()
        result = cursor.fetchall()
        print(len(result))
        print('更新数据成功')
    sleep1 = random.randint(0, 1)  # 反爬，每次访问随机间隔5-10s
    print('程序休息：'+str(sleep1)+'秒')
    time.sleep(sleep1)


if __name__ == '__main__':
    print('Start!')
    while(True):
        count = 0
        # name=input('请输入要爬取的厂商或者设备名称：')
        namecve = [ 'Juniper', 'Netgear', 'F5 BIG-IP', 'Belkin', 'Billion', 'DrayTek', 'Honeywell', 'ASUS', 'HUAWEI', 'Cisco', 'Xiaomi',
                   'OpenWrt', 'Tenda','MERCUSYS', 'MERCURY', 'MikroTik', 'DD-WRT', 'Vxworks', 'ZTE', 'Tomato', 'FreeRTOS', 'Hikvision', 'Dahua', '360', 'H3C', 'Ruijie','D-Link', 'TP-Link',]
        for name in namecve:
            # print('爬取厂商：'+name)
            info(count, name)
            count = count+1
        print('爬取结束!')
        print('共爬取厂商'+str(count)+'个')
