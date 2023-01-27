#!/usr/bin/env python
#-*- coding: utf-8 -*-

import os

def edit_file():
	print(u'创建一个名字为 test.txt 的文件，并在其中写入 Hello Python')
	print(u'先得保证 test.txt 不存在')
	os.system('rm test.txt')
	os.system('ls -l test.txt')

	print(u'现在再来创建文件并写入内容\n')
	fp = open('test.txt', 'w')
	fp.write('Hello Python')
	fp.close()

	print(u'不要忘记用 close 关闭文件哦')
	print(u'检查下 test.txt 是否存在，以及内容是否一致')
	os.system('ls -l test.txt')
	os.system('cat test.txt')
	print('\n')
	
	print(u'如何避免 open 文件失败的问题呢?')
	print(u'使用 with as 就可以了')
	with open('test.txt', 'r') as fp:
		st = fp.read()
	print(f'test.txt 的内容是: {st}')

if __name__ == '__main__':
	edit_file()