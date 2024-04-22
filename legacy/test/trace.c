/**
 * @file trace.c
 * @author yeqiang_xu <yeqiang_xu@maxio-tech.com>
 * @brief 
 * @version 0.1
 * @date 2022-08-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include "log.h"
#include "trace.h"

static void test_func_0_1_0_0(void)
{
	TRACE_FUNC_ANCHOR;
}

static void test_func_0_1_0(void)
{
	TRACE_FUNC_ANCHOR;
	test_func_0_1_0_0();

	TRACE_FUNC_DUMP;
}

static void test_func_0_1_1(void)
{
	TRACE_FUNC_ANCHOR;
}

static void test_func_0_0(void)
{
	TRACE_FUNC_ANCHOR;
}

static void test_func_0_1(void)
{
	TRACE_FUNC_ANCHOR;

	test_func_0_1_0();
	test_func_0_1_1();
}

static void test_func_0_2(void)
{
	TRACE_FUNC_ANCHOR;
}

static void test_func_0(void)
{
	TRACE_FUNC_ANCHOR;

	test_func_0_0();
	test_func_0_1();
	test_func_0_2();
}

static void test_func_1(void)
{
	TRACE_FUNC_ANCHOR;
}

static void test_func_2(void)
{
	TRACE_FUNC_ANCHOR;
	TRACE_FUNC_DUMP;
}

int main(int argc, char *argv[])
{
	TRACE_FUNC_ANCHOR;

	test_func_0();
	test_func_1();
	test_func_2();
	TRACE_FUNC_DUMP;

	return 0;
}
