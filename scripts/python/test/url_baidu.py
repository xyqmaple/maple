#!/usr/bin/env python
#-*- coding: utf-8 -*-

import urllib.request

def link_baidu():
	url = 'http://www.baidu.com'
	try:
		resp = urllib.request.urlopen(url, timeout=3)
	except urllib.URLError:
		print(u"网络地址错误")
		exit()
	with open('./baidu.html', 'w') as fp:
		string = resp.read().decode('utf-8')
		fp.write(string)
	print(u"获取url信息: %s" %resp.geturl())
	print(u"获取返回代码: %s" %resp.getcode())
	print(u"获取返回信息: %s" %resp.info())
	print(u"获取的网页内容已存入当前目录的 baidu.txt 中，请自行查看")

if __name__ == '__main__':
	link_baidu()