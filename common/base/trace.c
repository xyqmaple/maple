/**
 * @file trace.c
 * @author yeqiang_xu <yeqiang_xu@maxio-tech.com>
 * @brief 
 * @version 0.1
 * @date 2022-08-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "log.h"
#include "module.h"
#include "trace.h"

#define TRACE_FUNCTION_DEPATH			4

struct trace_function {
	const char *name[TRACE_FUNCTION_DEPATH];
	unsigned long addr[TRACE_FUNCTION_DEPATH];
	unsigned int idx;
};

static struct trace_function g_trace_func;

static struct module cur_mod = {
	.name		= "trace",
	.loglevel	= LOG_LEVEL_DEFAULT,
};

/**
 * @brief Find the appropriate location to save the function caller
 *  information based on the stack address.
 * 
 * @param tf Manage function caller information, like snapshots.
 * @param addr Stack address.
 * @return The location to save the function caller information. 
 */
static int trace_func_find_position(struct trace_function *tf, 
		unsigned long addr)
{
	int i;

	if (tf->idx <= 0)
		return 0;
	
	for (i = tf->idx-1; i >= 0; i--)
	{
		if (addr < tf->addr[i])
			return i + 1;
		else if (addr == tf->addr[i])
			return i;
	}
	return 0;
}

/**
 * @brief Records the name of the current function caller
 * 
 * @param func The name of the current function caller
 */
void trace_func_record(const char *func)
{
	int pos;
	struct trace_function *tf = &g_trace_func;

	pos = trace_func_find_position(tf, (unsigned long)&pos);
	if (pos >= TRACE_FUNCTION_DEPATH)
	{
		mod_warn(&cur_mod, "Overflow! Failed to snapshoot @%s\n", func);
		return;
	}

	tf->idx = pos + 1;
	tf->name[pos] = func;
	tf->addr[pos] = (unsigned long)&pos;
}

/**
 * @brief Trace the path of the program, starting with the current function
 *  caller
 * 
 * @param func The name of the current function caller
 */
void trace_func_dump(const char *func)
{
	int i;
	struct trace_function *tf = &g_trace_func;

	mod_notice(&cur_mod, "dump stack from @%s...\n", func);
	for (i = tf->idx - 1; i >= 0; i--)
	{
		if (tf->addr[i] >= (unsigned long)&i)
			mod_dbgs(&cur_mod, "0x%lx: %s\n", tf->addr[i], tf->name[i]);
	}
}
