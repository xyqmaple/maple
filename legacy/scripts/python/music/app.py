#!/usr/bin/env python
#-*- coding: utf-8 -*-

# import os
# import shutil
# import time
# import pandas
# import numpy
# import json

from PyQt5 import QtCore, QtGui, QtWidgets
import sys
import qtawesome

class MainUi(QtWidgets.QMainWindow):
	def __init__(self):
		super().__init__()
		self.init_ui()
	
	def init_ui(self):
		self.setFixedSize(960, 700)
		# 创建窗口主部件
		self.main_widget = QtWidgets.QWidget()
		# 创建主部件的网格布局
		self.main_layout = QtWidgets.QGridLayout()
		# 设置窗口主部件布局为网格布局
		self.main_widget.setLayout(self.main_layout)

		self.left_widget = QtWidgets.QWidget()
		self.left_widget.setObjectName('left_widget')
		self.left_layout = QtWidgets.QGridLayout()
		self.left_widget.setLayout(self.left_layout)

		self.right_widget = QtWidgets.QWidget()
		self.right_widget.setObjectName('right_widget')
		self.right_layout = QtWidgets.QGridLayout()
		self.right_widget.setLayout(self.right_layout)

		# 左侧部件从第 0 行，第 0 列开始，占 13 行，2 列
		self.main_layout.addWidget(self.left_widget, 0, 0, 13, 2)
		# 右侧部件从第 0 行，第 2 列开始，占 13 行，10 列
		self.main_layout.addWidget(self.right_widget, 0, 2, 13, 10)
		self.setCentralWidget(self.main_widget)

		# 关闭按钮
		self.left_close = QtWidgets.QPushButton("")
		# 空白按钮
		self.left_visit = QtWidgets.QPushButton("")
		# 最小化按钮
		self.left_mini = QtWidgets.QPushButton("")

		# 创建按钮
		self.left_label_1 = QtWidgets.QPushButton("每日推荐")
		self.left_label_1.setObjectName('left_label')
		self.left_label_2 = QtWidgets.QPushButton("我的音乐")
		self.left_label_2.setObjectName('left_label')
		self.left_label_3 = QtWidgets.QPushButton("联系与帮助")
		self.left_label_3.setObjectName('left_label')

		self.left_button_1 = QtWidgets.QPushButton(
			qtawesome.icon('fa.music', color='white'), "华语流行")
		self.left_button_1.setObjectName('left_button')
		self.left_button_2 = QtWidgets.QPushButton(
			qtawesome.icon('fa.sellsy', color='white'), "在线 FM")
		self.left_button_2.setObjectName('left_button')
		self.left_button_3 = QtWidgets.QPushButton(
			qtawesome.icon('fa.film', color='white'), "热门 MV")
		self.left_button_3.setObjectName('left_button')
		self.left_button_4 = QtWidgets.QPushButton(
			qtawesome.icon('fa.home', color='white'), "本地音乐")
		self.left_button_4.setObjectName('left_button')
		self.left_button_5 = QtWidgets.QPushButton(
			qtawesome.icon('fa.download', color='white'), "下载管理")
		self.left_button_5.setObjectName('left_button')
		self.left_button_6 = QtWidgets.QPushButton(
			qtawesome.icon('fa.heart', color='white'), "我的收藏")
		self.left_button_6.setObjectName('left_button')
		self.left_button_7 = QtWidgets.QPushButton(
			qtawesome.icon('fa.comment', color='white'), "反馈建议")
		self.left_button_7.setObjectName('left_button')
		self.left_button_8 = QtWidgets.QPushButton(
			qtawesome.icon('fa.star', color='white'), "关注我们")
		self.left_button_8.setObjectName('left_button')
		self.left_button_9 = QtWidgets.QPushButton(
			qtawesome.icon('fa.question', color='white'), "遇到问题")
		self.left_button_9.setObjectName('left_button')

		self.right_layout.addWidget(self.left_label_1, 1, 0, 1, 3)
		# 将创建的按钮添加到左侧部件的网格布局中
		self.left_layout.addWidget(self.left_mini, 0, 0, 1, 1)
		self.left_layout.addWidget(self.left_visit, 0, 1, 1, 1)
		self.left_layout.addWidget(self.left_close, 0, 2, 1, 1)
		self.left_layout.addWidget(self.left_label_1, 1, 0, 1, 3)
		self.left_layout.addWidget(self.left_button_1, 2, 0, 1, 3)
		self.left_layout.addWidget(self.left_button_2, 3, 0, 1, 3)
		self.left_layout.addWidget(self.left_button_3, 4, 0, 1, 3)
		self.left_layout.addWidget(self.left_label_2, 5, 0, 1, 3)
		self.left_layout.addWidget(self.left_button_4, 6, 0, 1, 3)
		self.left_layout.addWidget(self.left_button_5, 7, 0, 1, 3)
		self.left_layout.addWidget(self.left_button_6, 8, 0, 1, 3)
		self.left_layout.addWidget(self.left_label_3, 9, 0, 1, 3)
		self.left_layout.addWidget(self.left_button_7, 10, 0, 1, 3)
		self.left_layout.addWidget(self.left_button_8, 11, 0, 1, 3)
		self.left_layout.addWidget(self.left_button_9, 12, 0, 1, 3)

		# 创建右侧顶部搜索框部件
		self.right_bar_widget = QtWidgets.QWidget()
		# 设置右侧顶部搜索框网格布局
		self.right_bar_layout = QtWidgets.QGridLayout()
		self.right_bar_widget.setLayout(self.right_bar_layout)
		self.search_icon = QtWidgets.QLabel(chr(0xf002) + ' ' + '搜索  ')
		self.search_icon.setFont(qtawesome.font('fa', 16))
		self.right_bar_widget_search_input = QtWidgets.QLineEdit()
		self.right_bar_widget_search_input.setPlaceholderText(
			"输入歌手、歌曲或用户，回车进行搜索")
		self.right_bar_layout.addWidget(self.search_icon, 0, 0, 1, 1)
		self.right_bar_layout.addWidget(self.right_bar_widget_search_input, 
			0, 1, 1, 8)
		self.right_layout.addWidget(self.right_bar_widget, 0, 0, 1, 9)

		# 推荐音乐模块：推荐标题 + 封面列表

		self.right_recommend_label = QtWidgets.QLabel("今日推荐")
		self.right_recommend_label.setObjectName('right_label')
		
		# 推荐封面部件
		self.right_recommend_widget = QtWidgets.QWidget()
		self.right_recommend_layout = QtWidgets.QGridLayout()
		self.right_recommend_widget.setLayout(self.right_recommend_layout)

		self.recommend_button_1 = QtWidgets.QToolButton()
		# 设置按钮文本
		self.recommend_button_1.setText("她说")
		# 设置按钮图标
		self.recommend_button_1.setIcon(QtGui.QIcon('./image/she_says.png'))
		# 设置图标大小
		self.recommend_button_1.setIconSize(QtCore.QSize(100, 100))
		# 设置按钮为上下图文
		self.recommend_button_1.setToolButtonStyle(
			QtCore.Qt.ToolButtonTextUnderIcon)
		
		self.recommend_button_2 = QtWidgets.QToolButton()
		self.recommend_button_2.setText("罄竹难书")
		self.recommend_button_2.setIcon(QtGui.QIcon('./image/book.jpg'))
		self.recommend_button_2.setIconSize(QtCore.QSize(100, 100))
		self.recommend_button_2.setToolButtonStyle(
			QtCore.Qt.ToolButtonTextUnderIcon)

		self.recommend_button_3 = QtWidgets.QToolButton()
		self.recommend_button_3.setText("重归与好")
		self.recommend_button_3.setIcon(QtGui.QIcon('./image/reconcile.jpg'))
		self.recommend_button_3.setIconSize(QtCore.QSize(100, 100))
		self.recommend_button_3.setToolButtonStyle(
			QtCore.Qt.ToolButtonTextUnderIcon)

		self.recommend_button_4 = QtWidgets.QToolButton()
		self.recommend_button_4.setText("雾")
		self.recommend_button_4.setIcon(QtGui.QIcon(
			'./image/murray_designs.jpg'))
		self.recommend_button_4.setIconSize(QtCore.QSize(100, 100))
		self.recommend_button_4.setToolButtonStyle(
			QtCore.Qt.ToolButtonTextUnderIcon)

		self.recommend_button_5 = QtWidgets.QToolButton()
		self.recommend_button_5.setText("海边")
		self.recommend_button_5.setIcon(QtGui.QIcon('./image/gummy.jpg'))
		self.recommend_button_5.setIconSize(QtCore.QSize(100, 100))
		self.recommend_button_5.setToolButtonStyle(\
			QtCore.Qt.ToolButtonTextUnderIcon)
		
		self.right_recommend_layout.addWidget(self.recommend_button_1, 0, 0)
		self.right_recommend_layout.addWidget(self.recommend_button_2, 0, 1)
		self.right_recommend_layout.addWidget(self.recommend_button_3, 0, 2)
		self.right_recommend_layout.addWidget(self.recommend_button_4, 0, 3)
		self.right_recommend_layout.addWidget(self.recommend_button_5, 0, 4)

		self.right_layout.addWidget(self.right_recommend_label, 1, 0, 1, 9)
		self.right_layout.addWidget(self.right_recommend_widget, 2, 0, 2, 9)

		# 创建音乐列表模块：标题 + 部件
		self.right_newsong_label = QtWidgets.QLabel("最新歌曲")
		self.right_newsong_label.setObjectName('right_label')

		self.right_newsong_widget = QtWidgets.QWidget()
		self.right_newsong_layout = QtWidgets.QGridLayout()
		self.right_newsong_widget.setLayout(self.right_newsong_layout)

		self.newsong_button_1 = QtWidgets.QPushButton(
			"专辑        歌手        歌曲        时长")
		self.newsong_button_2 = QtWidgets.QPushButton(
			"何必        于文文      何必        04:58")
		self.newsong_button_3 = QtWidgets.QPushButton(
			"何必        于文文      何必        04:58")
		self.newsong_button_4 = QtWidgets.QPushButton(
			"何必        于文文      何必        04:58")
		self.newsong_button_5 = QtWidgets.QPushButton(
			"何必        于文文      何必        04:58")
		self.newsong_button_6 = QtWidgets.QPushButton(
			"何必        于文文      何必        04:58")
		
		self.right_newsong_layout.addWidget(self.newsong_button_1, 0, 1)
		self.right_newsong_layout.addWidget(self.newsong_button_2, 1, 1)
		self.right_newsong_layout.addWidget(self.newsong_button_3, 2, 1)
		self.right_newsong_layout.addWidget(self.newsong_button_4, 3, 1)
		self.right_newsong_layout.addWidget(self.newsong_button_5, 4, 1)
		self.right_newsong_layout.addWidget(self.newsong_button_6, 5, 1)

		# 创建音乐歌单模块：标题 + 部件
		self.right_playlist_label = QtWidgets.QLabel("热门歌单")
		self.right_playlist_label.setObjectName('right_label')

		self.right_playlist_widget = QtWidgets.QWidget()
		self.right_playlist_layout = QtWidgets.QGridLayout()
		self.right_playlist_widget.setLayout(self.right_playlist_layout)

		self.playlist_button_1 = QtWidgets.QToolButton()
		self.playlist_button_1.setText("忆故乡")
		self.playlist_button_1.setIcon(QtGui.QIcon('./image/zhoujielun.jpg'))
		self.playlist_button_1.setIconSize(QtCore.QSize(100, 100))
		self.playlist_button_1.setToolButtonStyle(\
			QtCore.Qt.ToolButtonTextUnderIcon)

		self.playlist_button_2 = QtWidgets.QToolButton()
		self.playlist_button_2.setText("200首成语歌名")
		self.playlist_button_2.setIcon(QtGui.QIcon(\
			'./image/where_have_you_been.jpg'))
		self.playlist_button_2.setIconSize(QtCore.QSize(100, 100))
		self.playlist_button_2.setToolButtonStyle(\
			QtCore.Qt.ToolButtonTextUnderIcon)

		self.playlist_button_3 = QtWidgets.QToolButton()
		self.playlist_button_3.setText("心在旅行")
		self.playlist_button_3.setIcon(QtGui.QIcon('./image/save.jpg'))
		self.playlist_button_3.setIconSize(QtCore.QSize(100, 100))
		self.playlist_button_3.setToolButtonStyle(\
			QtCore.Qt.ToolButtonTextUnderIcon)

		self.playlist_button_4 = QtWidgets.QToolButton()
		self.playlist_button_4.setText("阳光下午茶")
		self.playlist_button_4.setIcon(QtGui.QIcon('./image/huang_jian.jpg'))
		self.playlist_button_4.setIconSize(QtCore.QSize(100, 100))
		self.playlist_button_4.setToolButtonStyle(\
			QtCore.Qt.ToolButtonTextUnderIcon)
		
		self.right_playlist_layout.addWidget(self.playlist_button_1, 0, 0)
		self.right_playlist_layout.addWidget(self.playlist_button_2, 0, 1)
		self.right_playlist_layout.addWidget(self.playlist_button_3, 1, 0)
		self.right_playlist_layout.addWidget(self.playlist_button_4, 1, 1)

		self.right_layout.addWidget(self.right_newsong_label, 4, 0, 1, 5)
		self.right_layout.addWidget(self.right_playlist_label, 4, 5, 1, 4)
		self.right_layout.addWidget(self.right_newsong_widget, 5, 0, 1, 5)
		self.right_layout.addWidget(self.right_playlist_widget, 5, 5, 1, 4)

		# 创建音乐播放进度部件
		self.right_process_bar = QtWidgets.QProgressBar()
		self.right_process_bar.setValue(25)
		# 设置进度条高度
		self.right_process_bar.setFixedHeight(3)
		# 不显示进度条文字
		self.right_process_bar.setTextVisible(False)

		# 创建音乐播放控制部件
		self.right_playconsole_widget = QtWidgets.QWidget()
		self.right_playconsole_layout = QtWidgets.QGridLayout()
		self.right_playconsole_widget.setLayout(self.right_playconsole_layout)

		self.console_button_1 = QtWidgets.QPushButton(qtawesome.icon(
			'fa.backward', color = '#F76677'), "")
		self.console_button_2 = QtWidgets.QPushButton(qtawesome.icon(
			'fa.forward', color = '#F76677'), "")
		self.console_button_3 = QtWidgets.QPushButton(qtawesome.icon(
			'fa.pause', color = '#F76677', font = 18), "")
		self.console_button_3.setIconSize(QtCore.QSize(30, 30))

		self.right_playconsole_layout.addWidget(self.console_button_1, 0, 0)
		self.right_playconsole_layout.addWidget(self.console_button_2, 0, 2)
		self.right_playconsole_layout.addWidget(self.console_button_3, 0, 1)
		# 设置布局内的部件居中显示
		self.right_playconsole_layout.setAlignment(QtCore.Qt.AlignCenter)

		self.right_layout.addWidget(self.right_process_bar, 9, 0, 1, 9)
		self.right_layout.addWidget(self.right_playconsole_widget, 
			10, 0, 1, 9)

		# 设置关闭按钮的大小
		self.left_close.setFixedSize(15, 15)
		self.left_visit.setFixedSize(15, 15)
		self.left_mini.setFixedSize(15, 15)
		# 设置按钮部件的 QSS 样式
		self.left_close.setStyleSheet('''
			QPushButton {
				background: #F76677;
				border-radius: 5px;
			}
			QPushButton:hover {
				background: red;
			}
		''')
		self.left_visit.setStyleSheet('''
			QPushButton {
				background: #F7D674;
				border-radius: 5px;
			}
			QPushButton:hover {
				background: yellow;
			}
		''')
		self.left_mini.setStyleSheet('''
			QPushButton {
				background: #6DDF6D;
				border-radius: 5px;
			}
			QPushButton:hover {
				background: green;
			}
		''')

		# 设置左侧部件的 QSS 样式: 背景为灰色，边框左上角和左下角处理为圆角...
		self.left_widget.setStyleSheet('''
			QWidget#left_widget{
				background: gray;
				border-top: 1px solid white;
				border-bottom: 1px solid white;
				border-left: 1px solid white;
				border-top-left-radius: 10px;
				border-bottom-left-radius: 10px;
			}
			QPushButton {
				border: none;
				color: white;
			}
			QPushButton#left_label {
				border: none;
				border-bottom: 1px solid white;
				font-size: 18px;
				font-weight: 700;
				font-family: "Helvetica Neue", Helvetica, Arial, sans-serif;
			}
			QPushButton#left_button:hover {
				border-left: 4px solid red;
				font-weight: 700;
			}
		''')

		# 设置右侧部件的 QSS 样式
		# 右侧搜索框显示为圆角
		self.right_bar_widget_search_input.setStyleSheet('''
			QLineEdit {
				border: 1px solid gray;
				border-radius: 10px;
				padding: 2px 4px;
			}
		''')
		# 右侧部件背景为白色，边框右上角和右下角处理为圆角，放大标题的字体
		self.right_widget.setStyleSheet('''
			QWidget#right_widget {
				background: white;
				border-top: 1px solid darkGray;
				border-bottom: 1px solid darkGray;
				border-right: 1px solid darkGray;
				border-top-right-radius: 10px;
				border-bottom-right-radius: 10px;
			}
			QLabel#right_label{
				border: none;
				font-size: 16px;
				font-weight: 700;
				font-family: "Helvetica Neue", Helvetica, Arial, sans-serif;
			}
		''')

		self.right_recommend_widget.setStyleSheet('''
			QToolButton {
				border: none;
			}
			QToolButton:hover {
				border-bottom: 2px solid #F76677;
			}
		''')
		self.right_playlist_widget.setStyleSheet('''
			QToolButton {
				border: none;
			}
			QToolButton:hover {
				border-bottom: 2px solid #F76677;
			}
		''')
		# 音乐列表需要去除边框，修改字体和颜色等
		self.right_newsong_widget.setStyleSheet('''
			QPushButton{
				border: none;
				color: gray;
				font-size: 12px;
				height: 40px;
				padding-left: 5px;
				padding-right: 10px;
				text-align: left;
			}
			QPushButton:hover {
				color: black;
				border: 1px solid #F3F3F5;
				border-radius: 10px;
				background: LightGray;
			}
		''')
		# 播放进度条和播放控制按钮组
		self.right_process_bar.setStyleSheet('''
			QProgressBar::chunk {
				background-color: #F76677;
			}
		''')
		self.right_playconsole_widget.setStyleSheet('''
			QPushButton{
				border: none;
			}
		''')

		# 设置窗口背景透明
		self.setWindowOpacity(0.9)
		self.setAttribute(QtCore.Qt.WA_TranslucentBackground)
		# 去除窗口边框
		self.setWindowFlag(QtCore.Qt.FramelessWindowHint)

		self.main_layout.setSpacing(0)



def main():
	app = QtWidgets.QApplication(sys.argv)
	gui = MainUi()
	gui.show()
	sys.exit(app.exec_())

if __name__ == '__main__':
	main()


