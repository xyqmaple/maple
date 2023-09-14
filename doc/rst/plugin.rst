
================
Sphinx Extension
================

sphinx.ext.todo
===============

.. todo::
    :class: danger

    class value is danger

| 段落1


.. todo::
	:class: warning

	class value is warning

sphinx-tabs
===========

Basic Tabs
----------

.. tabs::

	.. tab:: Apples

		Apples are green, or sometimes red.
	
	.. tab:: Pears

		Pears are yellow.
	
	.. tab:: Oranges

		Oranges are orange.


Nested Tabs
-----------

.. tabs::

	.. tab:: Stars

		.. tabs::

			.. tab:: The Sun

				The closest star to the Earth.
			
			.. tab:: Proxima Centauri

				The second closest star to the Earth.
			
	.. tab:: Planets

		.. tabs::

			.. tab:: Mercury

				The closest planet to the Sun.
			
			.. tab:: Venus

				The second closest planet to the Sun.

Group Tabs
----------

.. tabs::

	.. group-tab:: Linux

		Linux tab content - tab set 1
	
	.. group-tab:: Mac OS

		Mac OS tab content - tab set 1
	
	.. group-tab:: Windows

		Windows tab content - tab set 1

.. tabs::

	.. group-tab:: Linux

		Linux tab content - tab set 2
	
	.. group-tab:: Mac OS

		Mac OS tab content - tab set 2
	
	.. group-tab:: Windows

		Windows tab content - tab set 2

Code Tabs
---------

.. tabs::

	.. code-tab:: c

		int main(int argc, char *argv[])
		{
			return 0;
		}
	
	.. code-tab:: c++

		int main(int argc, char *argv[])
		{
			return 0;
		}
	
	.. code-tab:: py

		def main():
			return

sphinx-design
=============

Article-info
------------

.. article-info::
	:avatar: image/key_board.jpg
	:avatar-link: https://github.com/
	:avatar-outline: info
	:author: Author
	:date: Sep 14, 2023
	:read-time: 5 min read

.. article-info::
	:avatar: image/key_board.jpg
	:avatar-link: https://github.com/
	:avatar-outline: muted
	:author: Author
	:date: Sep 14, 2023
	:read-time: 5 min read
	:class-container: sd-p-2 sd-outline-muted sd-rounded-1


Grids
-----

.. grid:: 2
	:outline:
	:reverse:

	.. grid-item::

		Apple
	
	.. grid-item::

		Banana

.. grid:: 2

	.. grid-item::

		Apple
	
	.. grid-item::

		Banana

.. grid:: 2

	.. grid-item-card:: Title 1

		Apple
	
	.. grid-item-card:: Title 2

		Banana

.. grid:: 1 1 2 2
	:gutter: 1

	.. grid-item::

		.. grid:: 1 1 1 1
			:gutter: 1

			.. grid-item-card:: Item 1.1

				Multi-line

				content
			
			.. grid-item-card:: Item 1.2

				Content
			
	.. grid-item::

		.. grid:: 1 1 1 1
			:gutter: 1

			.. grid-item-card:: Item 2.1

				Content
			
			.. grid-item-card:: Item 2.2

				Content
			
			.. grid-item-card:: Item 2.3

.. grid:: 1 1 2 2
	:gutter: 1

	.. grid-item::
		:child-direction: row

		Item 1.1
		Item 1.2
			
	.. grid-item::
		:child-align: end

		Item 2.1
		Item 2.2
		Item 2.3


Cards
-----

.. card:: Card Title
	:width: 50%
	:text-align: center

	Card Content

.. card:: Card Title
	:text-align: left

	Card Content

.. card:: Card Title
	:width: 50%
	:text-align: right

	Card Content

.. card:: Card Title
	:text-align: justify

	Card Content

.. card:: Card Title

	Header
	^^^
	Card Content
	+++
	Footer

.. card:: Github
	:link: https://github.com/

	Click it to jump to Github website.

.. card-carousel:: 3

	.. card:: Card 1

		Content 1
	
	.. card:: Card 2

		Content 2
	
	.. card:: Card 3
	
	.. card:: Card 4
	
	.. card:: Card 5
	
	.. card:: Card 6

Dropdowns
---------

.. dropdown:: Title

	Content


Tabs
----

Basic Tabs
^^^^^^^^^^

.. tab-set::

	.. tab-item:: Label1

		Content 1
	
	.. tab-item:: Label2

		Content 2

Synchronised Tabs
^^^^^^^^^^^^^^^^^

.. tab-set::

	.. tab-item:: Label1
		:sync: key1

		Content 1
	
	.. tab-item:: Label2
		:sync: key2

		Content 2

.. tab-set::

	.. tab-item:: Label1
		:sync: key1

		Content 1
	
	.. tab-item:: Label2
		:sync: key2

		Content 2

Code Tabs
^^^^^^^^^

.. tab-set-code::

	.. code-block:: c

		int main(int argc, char *argv[])
		{
			printf("Hello world!\n");
			return 0;
		}

	.. code-block:: py

		if 'str' in list:
			print("true")


Badges
------

:bdg:`badge`

:bdg-primary:`badge-primary` , :bdg-primary-line:`badge-primary-line`

Buttons
-------

.. button-link:: https://github.com

.. button-link:: https://github.com
	:color: primary
	:outline: 
	:expand: 

	Github: primary

.. button-link:: https://github.com
	:color: secondary

	Github: secondary

.. button-link:: https://github.com
	:color: success

	Github: success

.. button-link:: https://github.com
	:color: info

	Github: info

.. button-link:: https://github.com
	:color: warning

	Github: warning

.. button-link:: https://github.com
	:color: danger

	Github: danger

.. button-link:: https://github.com
	:color: light

	Github: light

.. button-link:: https://github.com
	:color: muted

	Github: muted

.. button-link:: https://github.com
	:color: dark

	Github: dark

.. button-link:: https://github.com
	:color: white

	Github: white

.. button-link:: https://github.com
	:color: black

	Github: black


sphinx-togglebutton
===================

.. .. toggle::
.. 	:show:

.. 	Content

.. .. toggle::

.. 	Content

.. .. admonition:: What could be inside this warning?
.. 	:class: warning, dropdown, toggle-shown

.. 	Nothing happened, it's a joke!


.. note:: message

.. tip:: message

.. attention:: message

.. caution:: message



.. important:: message

.. warning:: message

.. error:: message

.. danger:: message

