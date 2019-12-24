#!/usr/bin/python
#coding:utf8
#exp #python smsbao.py "发送一个测试监控信息"

import requests,sys,time
import sys
import time


def sendTextMessage():

    #get localtime 2014-7-11 10:01:01
    ltime = time.strftime('%Y-%m-%d %H:%M:%S',time.localtime(time.time()))

    #u:username p:password c:content m:Phone
    Content = "【RaspiSmartHome】Intruder Alert"
    payload = {
        'u':'busaileh',
        'p':'69458a76ff6f568404da46e0edbfa74c',
        'm':'15655139302',
        'c':Content
    }

    #send msmbao message to phone
    r = requests.get('http://www.smsbao.com/sms',params=payload)
    date = ltime + "\t" + Content + "\t" + r.text + "\n"

    f = open('smsbao.log','a')
    #write log to smsbao.log
    try:
        f.write(date)
        f.close()
    except IOError,e:
        sys.exit()
