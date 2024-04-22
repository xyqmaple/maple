===========
一级标题
===========

二级标题
===========

三级标题
-----------

四级标题
^^^^^^^^^^^

五级标题
"""""""""""

六级标题
***********

| 段落一

	段落二

段落三

文字样式

- *这是斜体*
- :emphasis:`这也是斜体`
- **这是粗体**
- :strong:`这也是粗体`
- ``这是等宽文本``
- :literal:`这也是等宽文本`
- 上标： E = mc\ :sup:`2`
- 下标： H\ :sub:`2`\ O
- 转义： \*BSD
- 提示信息： :abbr:`LBA (Logical Block Address)`
- 文件地址： :file:`/usr/lib/python2.{x}/site-packages`

.. centered:: 居中小标题
.. rubric:: 小标题

下面是行块内容：
 | 这是行块内容
 | 这同样是行块内容

下面是文字块内容
::

	这是文字块内容
	这同样是文字块内容

段落四

定义1
  这里是定义1的内容

定义2
	这里是定义2的内容

:标题: 这里是标题内容

:时间: 2023/8/28

:内容:
	第一行内容
	第二行内容

====
列表
====

- 无序列表项1
	+ 二级无序列表项1
	+ 二级无序列表项2
		* 三级无序列表项1
		* 三级无序列表项2
	+ 二级无序列表项3
- 无序列表项2
- 无序列表项3

1. 有序列表项1
	A. 二级有序列表项1
	#. 二级有序列表项2
	#. 二级有序列表项3
#. 有序列表项2
	a. 二级有序列表项1
	#. 二级有序列表项2
	#. 二级有序列表项3
#. 有序列表项3

水平列表

.. hlist::
	:columns: 4

	* 第1项
	* 第2项
	* 第3项
	* 第4项
	* 第5项

选项列表

-a			command line option "a"
-f <file>		specify file name
-h			display help information

简单表

=====  =====  =======
input         output
------------  -------
A      B      A | B
=====  =====  =======
False  False  False
False  True   True
True   False  True
True   True   True
=====  =====  =======

网格表

+-------------------------+-----------+-----------+-----------+
| Header row, column 1    | Header 2  | Header 3  | Header 4  |
| (header rows optional)  |           |           |           |
+=========================+===========+===========+===========+
| body row 1, column 1    | column 2  | column 3  | column 4  |
+-------------------------+-----------+-----------+-----------+
| body row 2              | Cells may span columns.           |
+-------------------------+-----------+-----------------------+
| body row 3              | 1. item1  | - Table cells         |
+-------------------------+ #. item2  | - contain             |
| body row 4              | #. item3  | - body elements.      |
+-------------------------+-----------+-----------------------+

CSV 表

.. csv-table:: Here is table name!
	:header: "Fruit", "Price", "Description"
	:widths: 15, 10, 30
	:stub-columns: 1

	"Apple", 7.99, "Ripe apples are red in color"
	"Banana", 6.53, "Ripe bananas are yellow in color"
	"Watermelon", 3.11, "The color of a watermelon is always green,
	whether it is ripe or not"

LIST 表

.. list-table:: Here is table name!
	:widths: 15 10 30
	:header-rows: 1

	* - Fruit
	  - Price
	  - Description
	* - Apple
	  - 7.99
	  - Ripe apples are red in color
	* - Banana
	  - 6.53
	  - Ripe bananas are yellow in color
	* - Watermelon
	  - 3.11
	  - The color of a watermelon is always green,
	    whether it is ripe or not


代码

行内代码 ``echo "Hello World!"``

多行代码（简易）::

	int main(int argc, char *argv)
	{
		printf("Hello World!\n");
		return 0;
	}

多行代码（复杂）

.. code-block:: c
	:linenos:
	:emphasize-lines: 1,3

	int main(int argc, char *argv)
	{
		printf("Hello World!\n");
		return 0;
	}

.. code-block:: html
	:linenos:

	<b>粗体</b>

超链接

外部链接

直接使用超链接：https://www.baidu.com

链接文字+链接地址（同行）：`Github <https://github.com>`_

链接文字+链接地址（分开）：`Read the Docs`_

链接文字+链接地址（前后行）：`The Linux Kernel Archives`__

.. __: https://kernel.org

.. _Read the Docs: https://about.readthedocs.com

内部链接

`一级标题`_ 点击后跳转到当前页面“一级标题”的位置

下载链接

:download:`下载文档源码 <example.rst>`

锚点

更多信息参考 自定义锚点1_

这里是其它内容

.. _自定义锚点1:

这是锚点1的内容

引用

It is mentioned by [Spec]_ that the namespace ID is unique.

.. [Spec] NVMe Base Specification R2.0b

脚注

第一个脚注 [#脚注1]_ ，第二个脚注 [#脚注2]_ ，简书的脚注 [#简书]_

.. [#脚注1] Text of the first footnode.
.. [#脚注2] Text of the seconde footnode.
.. [#简书] http://www.jianshu.com/

替换

I like eat |apple| very much.

.. |apple| replace:: watermelon 

注释

.. 我是注释内容

..
	我也是注释内容
	你们看不见我哈

.. seealso::

	List Item1
		list item1 description
	
	List item2
		list item2 description



