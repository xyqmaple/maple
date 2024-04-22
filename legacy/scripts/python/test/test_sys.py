#!/usr/bin/env python
#-*- coding: utf-8 -*-

import sys

class ShowSysModule(object):
	def __init__(self):
		print(u'sys 模块最常用的功能就是获取程序的参数')
		self.get_arg()
		print(u'其次就是获取当前的系统平台')
		self.get_os()
	
	def get_arg(self):
		print(u'开始获取参数的个数')
		print(f'当前参数有 {len(sys.argv)}')
		print(f'这些参数分别是 {sys.argv}')

	def get_os(self):
		print(f'当前的系统是 {sys.platform}')
	
if __name__ == '__main__':
	ssm = ShowSysModule()
