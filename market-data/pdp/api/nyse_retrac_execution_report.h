/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: nyse_retrac_execution_report.h
 *
 * Description:
 *      NYSE ReTrac Execution Report message definitions
 *
 *      References:
 *      [1] NYSE RETAIL EXECUTION REPORT (RETRAC) CLIENT SPECIFICATION,
 *          Version 2.2a, 2012-08-10
 *          Section 4.8
 *
 * Authors:
 *          Wojciech Migda (wm)
 *
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-25   wm              Initial version
 *
 ******************************************************************************/


#ifndef NYSE_RETRAC_EXECUTION_REPORT_H_
#define NYSE_RETRAC_EXECUTION_REPORT_H_

#include <stdint.h>

#include "pdp_symbol.h"

#ifdef __cplusplus
extern "C"
{
#endif

enum { NYSE_RETRAC_EXECUTION_REPORT_MSG_SIZE = 30 };

typedef struct
{
    uint32_t        exec_time;
    char            symbol[NYSE_SYMBOL_LEN];
    uint32_t        volume;
    uint32_t        link_id;
    uint16_t        execution_type;
} nyse_retrac_execution_report_msg_t;

#ifdef __cplusplus
} // extern C
#endif

#endif /* NYSE_RETRAC_EXECUTION_REPORT_H_ */
