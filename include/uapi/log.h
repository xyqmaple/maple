/**
 * @file log.h
 * @author yeqiang_xu <yeqiang_xu@maxio-tech.com>
 * @brief 
 * @version 0.1
 * @date 2022-08-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __LOG_H
#define __LOG_H

#include <stdarg.h>
#include "types.h"

#define LOG_COLOR_NONE			"\033[0m"
#define LOG_COLOR_BLACK			"\033[1;30m"
#define LOG_COLOR_DBLACK		"\033[0;30m"
#define LOG_COLOR_RED			"\033[1;31m"
#define LOG_COLOR_DRED			"\033[0;31m"
#define LOG_COLOR_GREEN			"\033[1;32m"
#define LOG_COLOR_DGREEN		"\033[0;32m"
#define LOG_COLOR_YELLOW		"\033[1;33m"
#define LOG_COLOR_DYELLOW		"\033[0;33m"
#define LOG_COLOR_BLUE			"\033[1;34m"
#define LOG_COLOR_DBLUE			"\033[0;34m"
#define LOG_COLOR_PURPLE		"\033[1;35m"
#define LOG_COLOR_DPURPLE		"\033[0;35m"
#define LOG_COLOR_CYAN			"\033[1;36m"
#define LOG_COLOR_DCYAN			"\033[0;36m"
#define LOG_COLOR_WHITE			"\033[1;37m"

#define LOG_LEVEL_EMERG			0
#define LOG_LEVEL_ALERT			1
#define LOG_LEVEL_CRIT			2
#define LOG_LEVEL_ERR			3
#define LOG_LEVEL_WARN			4
#define LOG_LEVEL_NOTICE		5
#define LOG_LEVEL_INFO			6
#define LOG_LEVEL_DEBUG			7
#define LOG_LEVEL_BUBBLING		8
#define LOG_LEVEL_DIVING		9
#define LOG_LEVEL_DEFAULT		CONFIG_LOG_LEVEL_DEFAULT

#ifndef pr_fmt
#define pr_fmt(fmt)			fmt
#endif

#define pr_emerg(fmt, ...)		log_print(LOG_LEVEL_EMERG, pr_fmt(fmt), ##__VA_ARGS__)
#define pr_alert(fmt, ...)		log_print(LOG_LEVEL_ALERT, pr_fmt(fmt), ##__VA_ARGS__)
#define pr_crit(fmt, ...)		log_print(LOG_LEVEL_CRIT, pr_fmt(fmt), ##__VA_ARGS__)
#define pr_err(fmt, ...)		log_print(LOG_LEVEL_ERR, pr_fmt(fmt), ##__VA_ARGS__)
#define pr_warn(fmt, ...)		log_print(LOG_LEVEL_WARN, pr_fmt(fmt), ##__VA_ARGS__)
#define pr_notice(fmt, ...)		log_print(LOG_LEVEL_NOTICE, pr_fmt(fmt), ##__VA_ARGS__)
#define pr_info(fmt, ...)		log_print(LOG_LEVEL_INFO, pr_fmt(fmt), ##__VA_ARGS__)
#define pr_debug(fmt, ...)		log_print(LOG_LEVEL_DEBUG, pr_fmt(fmt), ##__VA_ARGS__)
#define pr_bub(fmt, ...)		log_print(LOG_LEVEL_BUBBLING, pr_fmt(fmt), ##__VA_ARGS__)
#define pr_div(fmt, ...)		log_print(LOG_LEVEL_DIVING, pr_fmt(fmt), ##__VA_ARGS__)


const char *log_color(u8 level);

int log_print(u8 level, const char *fmt, ...);

#endif /* !__LOG_H */
