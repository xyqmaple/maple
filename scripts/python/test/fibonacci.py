#!/usr/bin/env python
#-*- coding: utf-8 -*-

class Fibonacci(object):
	'''返回一个 fibonacci 数列'''
	def __init__(self):
		self.list = [0, 1] # 设置初始列表
		self.main()
	
	def main(self):
		list_len = input('请输入 fibonacci 数列的长度(3-50):')
		self.check_len(list_len)
		while len(self.list) < int(list_len):
			self.list.append(self.list[-1] + self.list[-2])
		print(f'得到的 fibonaci 数列为:\n {self.list}')
	
	def check_len(self, len):
		list = map(str, range(3, 51))
		if len in list:
			print(u'输入的长度符合标准，继续运行')
		else:
			print(u'只能输入3-50')
			exit()

if __name__ == '__main__':
	Fibonacci()