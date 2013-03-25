/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: nyse_protrac_execution_report_cancellation.h
 *
 * Description:
 *      NYSE ProTrac Execution Report Cancellation message definitions
 *
 *      References:
 *      [1] NYSE PROGRAM TRADING EXECUTION REPORTS (PROTRAC) CLIENT
 *          SPECIFICATION, Version 2.3a, 2012-08-10
 *          Section 4.9
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


#ifndef NYSE_PROTRAC_EXECUTION_REPORT_CANCELLATION_H_
#define NYSE_PROTRAC_EXECUTION_REPORT_CANCELLATION_H_

#include <stdint.h>

#include "pdp_symbol.h"

#ifdef __cplusplus
extern "C"
{
#endif

enum { NYSE_PROTRAC_EXECUTION_REPORT_CANCELLATION_MSG_SIZE = 30 };

typedef struct
{
    uint32_t        exec_time;
    char            symbol[NYSE_SYMBOL_LEN];
    uint32_t        volume;
    uint32_t        link_id;
    uint16_t        execution_type;
} nyse_protrac_execution_report_cancellation_msg_t;

#ifdef __cplusplus
} // extern C
#endif

#endif /* NYSE_PROTRAC_EXECUTION_REPORT_CANCELLATION_H_ */
