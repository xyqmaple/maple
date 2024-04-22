/**
 * @file module.h
 * @author yeqiang_xu <yeqiang_xu@maxio-tech.com>
 * @brief 
 * @version 0.1
 * @date 2022-08-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __MODULE_H
#define __MODULE_H

#include "log.h"

#define mod_emerg(mod, fmt, arg...)	mod_print(mod, LOG_LEVEL_EMERG, pr_fmt(fmt), ##arg)
#define mod_alert(mod, fmt, arg...)	mod_print(mod, LOG_LEVEL_ALERT, pr_fmt(fmt), ##arg)
#define mod_crit(mod, fmt, arg...)	mod_print(mod, LOG_LEVEL_CRIT, pr_fmt(fmt), ##arg)
#define mod_err(mod, fmt, arg...)	mod_print(mod, LOG_LEVEL_ERR, pr_fmt(fmt), ##arg)
#define mod_warn(mod, fmt, arg...)	mod_print(mod, LOG_LEVEL_WARN, pr_fmt(fmt), ##arg)
#define mod_notice(mod, fmt, arg...)	mod_print(mod, LOG_LEVEL_NOTICE, pr_fmt(fmt), ##arg)
#define mod_info(mod, fmt, arg...)	mod_print(mod, LOG_LEVEL_INFO, pr_fmt(fmt), ##arg)
#define mod_dbg(mod, fmt, arg...)	mod_print(mod, LOG_LEVEL_DEBUG, pr_fmt(fmt), ##arg)
#define mod_dbgs(mod, fmt, arg...)	mod_print(mod, LOG_LEVEL_DEBUG, pr_fmt(fmt), ##arg)
#define mod_bub(mod, fmt, arg...)	mod_print(mod, LOG_LEVEL_BUBBLING, pr_fmt(fmt), ##arg)
#define mod_bubs(mod, fmt, arg...)	mod_print(mod, LOG_LEVEL_BUBBLING, pr_fmt(fmt), ##arg)
#define mod_div(mod, fmt, arg...)	mod_print(mod, LOG_LEVEL_DIVING, pr_fmt(fmt), ##arg)
#define mod_divs(mod, fmt, arg...)	mod_print(mod, LOG_LEVEL_DIVING, pr_fmt(fmt), ##arg)

struct module {
	const char		*name;
	int				loglevel;
};

int mod_print(const struct module *mod, u8 level, const char *fmt, ...);

#endif /* !__MODULE_H */
