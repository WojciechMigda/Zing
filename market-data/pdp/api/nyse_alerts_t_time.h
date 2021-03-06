/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 * Filename: nyse_alerts_t_time.h
 *
 * Description:
 *      NYSE Alerts T-Time message definitions
 *
 *      References:
 *      [1] NYSE ALERTS CLIENT SPECIFICATION, Version 2.12, 2013-01-24
 *          Sec. 4.12
 *
 * Authors:
 *          Wojciech Migda (wm)
 *
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-19   wm              Initial version
 *
 ******************************************************************************/


#ifndef NYSE_ALERTS_T_TIME_H_
#define NYSE_ALERTS_T_TIME_H_

#include <stdint.h>
#include "pdp_symbol.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct
{
    uint32_t        source_time;
    char            symbol[NYSE_SHORT_SYMBOL_LEN];
    uint8_t         security_status;
    uint32_t        trade_dissemination_time;
} nyse_alerts_t_time_msg_t;

enum { NYSE_ALERTS_T_TIME_MSG_SIZE = 20 };

#ifdef __cplusplus
} // extern C
#endif

#endif /* NYSE_ALERTS_T_TIME_H_ */
