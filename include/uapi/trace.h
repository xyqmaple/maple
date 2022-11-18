/**
 * @file trace.h
 * @author yeqiang_xu <yeqiang_xu@maxio-tech.com>
 * @brief 
 * @version 0.1
 * @date 2022-08-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __TRACE_H
#define __TRACE_H

#define TRACE_FUNC_ANCHOR				trace_func_record(__func__)
#define TRACE_FUNC_DUMP					trace_func_dump(__func__)

void trace_func_record(const char *func);
void trace_func_dump(const char *func);

#endif /* !__TRACE_H */
