#!/usr/bin/env python
#-*- coding: utf-8 -*-
'''Used to manage log information'''
__author__ = 'yeqiang_xu <yeqiang_xu163@163.com>'
__version__ = '1.0.0'
__date__ = '2023-01-26'

import logging
import getpass

class Log(object):
	def __init__(self):
		user = getpass.getuser()
		self.logger = logging.getLogger(user)
		self.logger.setLevel(logging.DEBUG)
		file = './' + __name__ + '.log' # log file name
		fmt = logging.Formatter('%(asctime)s %(levelname)-8s %(name)-8s %(message)s')

		'''The log is displayed on the screen and output to the log file'''
		f_hand = logging.FileHandler(file)
		f_hand.setFormatter(fmt)
		f_hand.setLevel(logging.DEBUG)

		s_hand = logging.StreamHandler()
		s_hand.setFormatter(fmt)
		s_hand.setLevel(logging.WARN)

		self.logger.addHandler(f_hand)
		self.logger.addHandler(s_hand)

	def debug(self,msg):
		'''Delegate a debug call to the underlying logger'''
		self.logger.debug(msg)
	
	def info(self,msg):
		'''Delegate a info call to the underlying logger'''
		self.logger.info(msg)
	
	def warn(self,msg):
		'''Delegate a warning call to the underlying logger'''
		self.logger.warning(msg)
	
	def err(self,msg):
		'''Delegate a error call to the underlying logger'''
		self.logger.error(msg)

	def crit(self,msg):
		'''Delegate a critical call to the underlying logger'''
		self.logger.critical(msg)

if __name__ == '__main__':
	log = Log()
	log.debug("I'm debug message")
	log.info("I'm info message")
	log.warn("I'm warn message")
	log.err("I'm error message")
	log.crit("I'm critical message")
