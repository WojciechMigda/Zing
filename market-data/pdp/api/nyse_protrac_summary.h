/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: nyse_protrac_summary.h
 *
 * Description:
 *      NYSE ProTrac Summary message definitions
 *
 *      References:
 *      [1] NYSE PROGRAM TRADING EXECUTION REPORTS (PROTRAC) CLIENT
 *          SPECIFICATION, Version 2.3a, 2012-08-10
 *          Section 4.10
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


#ifndef NYSE_PROTRAC_SUMMARY_H_
#define NYSE_PROTRAC_SUMMARY_H_

#ifdef __cplusplus
extern "C"
{
#endif

enum { NYSE_PROTRAC_SUMMARY_MSG_SIZE = 22 };

typedef struct
{
    char            symbol[NYSE_SYMBOL_LEN];
    uint32_t        total_volume;
    uint16_t        execution_type;
} nyse_protrac_summary_msg_t;

#ifdef __cplusplus
} // extern C
#endif

#endif /* NYSE_PROTRAC_SUMMARY_H_ */
