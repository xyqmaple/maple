/**
 * @file module.c
 * @author yeqiang_xu <yeqiang_xu@maxio-tech.com>
 * @brief 
 * @version 0.1
 * @date 2022-08-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include "module.h"

static int mod_vprint(const struct module *mod, u8 level, const char *fmt, va_list args)
{
	int ret;
	static char textbuf[1024];
	char *text = textbuf;

	ret = vsnprintf(text, sizeof(textbuf), fmt, args);
	printf("%s[%d][%s]%s", log_color(level), level, mod->name, text);

	return ret;
}

int mod_print(const struct module *mod, u8 level, const char *fmt, ...)
{
	int ret;
	va_list args;

	if (level > mod->loglevel)
		return 0;

	va_start(args, fmt);
	ret = mod_vprint(mod, level, fmt, args);
	va_end(args);

	return ret;
}
