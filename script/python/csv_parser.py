#!/usr/bin/env python
#-*- coding: utf-8 -*-

import csv, os, sys

sys.path.append('./packages')
import log
from wrap import check

logger = log.UserLogger(os.getlogin())



class PCIeTraceParser(object):
	Second = 1000000000000

	def __init__(self, csvfile: str):
		logger.notice('Start to parse \'%s\' ...$' %csvfile)
		self.__readFile(csvfile)
		self.__parse()

	def __readFile(self, csvfile: str) -> None:
		with open(csvfile, 'r', newline='') as fd:
			_data = csv.reader(fd)

			self.rdata = dict()
			self.rdata['table'] = [row for row in _data]
			self.rdata['total'] = len(self.rdata['table'])
			self.rdata['pos'] = 1
			logger.dbg('csv file total lines: %d' %self.rdata['total'])

	def __writeFile(self, csvfile: str) -> None:
		pass

	def __parse(self) -> None:
		self.__parseHeader()
		self.__parseXferLength()

	def __parseHeader(self) -> None:
		self.head = dict()
		self.head['line'] = self.rdata['table'][0]
		self.head['len'] = len(self.head['line'])

		self.index = dict()
		self.index['Time'] = self.head['line'].index('Time')
		self.index['Type'] = self.head['line'].index('Type')
		self.index['Length'] = self.head['line'].index('Length')
		logger.vdbg('Index >> Time:%d, Type:%d, Length:%d'
			%(self.index['Time'], self.index['Type'], self.index['Length']))

	def __parseXferLength(self) -> None:
		self.result = list()

		_table = self.rdata['table']
		_pos = self.rdata['pos']
		_idx_time = self.index['Time']
		_idx_type = self.index['Type']
		_idx_length = self.index['Length']

		_boundary = self.Second * (len(self.result) + 1)
		_xfer_length = 0
		while _pos < self.rdata['total']:
			if int(_table[_pos][_idx_time]) > _boundary:
				logger.vdbg("Position: %d" %_pos)
				self.result.append(_xfer_length)
				_boundary = self.Second * (len(self.result) + 1)
				_xfer_length = 0

			if _table[_pos][_idx_type] == 'MRd':
				pass
			else:
				# Convert DWord to Byte
				_xfer_length += 4 * int('0x' + _table[_pos][_idx_length], 16)

			_pos += 1

		_xfer_total = _xfer_length
		for _item in self.result:
			_xfer_total += _item

		logger.info('Total transfer length: %d' %_xfer_total)
		logger.dbg('%s' %self.result)



@check
def csvDisplay(filepath: str):
	logger.info('The content of \'%s\' is as follows:' %filepath)
	with open(filepath, 'r') as fd:
		lines = csv.reader(fd)
		for line in lines:
			print(line)

def main():
	logger.setFileEnable(False)
	logger.setConsoleLevel(log.DEBUG)
	if len(sys.argv) == 2:
		parser = PCIeTraceParser(sys.argv[1])
	else:
		logger.warn("Select a csv file to parse!")
	# csvDisplay('test.csv')
	# parser = PCIeTraceParser('test.csv')

if __name__ == '__main__':
	main()
