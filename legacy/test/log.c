/**
 * @file log.c
 * @author yeqiang_xu <yeqiang_xu@maxio-tech.com>
 * @brief 
 * @version 0.1
 * @date 2022-08-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "log.h"

int main(int argc, char *argv[])
{
	pr_emerg("emergency\n");
	pr_alert("alert\n");
	pr_crit("critical\n");
	pr_err("error\n");
	pr_warn("warning\n");
	pr_notice("notice\n");
	pr_info("information\n");
	pr_debug("debug\n");
	return 0;
}
