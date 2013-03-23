/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 * Filename: nyse_alerts_delay_halts.h
 *
 * Description:
 *      NYSE Alerts Delay Halts message definitions
 *
 *      References:
 *      [1] NYSE ALERTS CLIENT SPECIFICATION, Version 2.12, 2013-01-24
 *          Sec. 4.10
 *
 * Authors:
 *          Wojciech Migda (wm)
 *
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-18   wm              Initial version
 *
 ******************************************************************************/


#ifndef NYSE_ALERTS_DELAY_HALTS_H_
#define NYSE_ALERTS_DELAY_HALTS_H_

#include <stdint.h>
#include "pdp_symbol.h"
#include "pdp_security_status.h"
#include "compiler.h"

#ifdef __cplusplus
extern "C"
{
#endif

enum halt_condition_values
{
    HALT_COND_NOT_DELAYED_HALTED                            = '~',
    HALT_COND_AS_OF_UPDATE                                  = 'A',
    HALT_COND_NEWS_DISSEMINATION                            = 'D',
    HALT_COND_ORDER_IMBALANCE                               = 'I',
    HALT_COND_NEWS_PENDING                                  = 'P',
    HALT_COND_DUE_TO_RELATED_SECURITY_NEWS_DISSEMINATION    = 'J',
    HALT_COND_DUE_TO_RELATED_SECURITY_NEWS_PENDING          = 'K',
    HALT_COND_VOLATILITY_TRADING_PAUSE                      = 'M',
    HALT_COND_DUE_TO_RELATED_SECURITY                       = 'Q',
    HALT_COND_RELATED_SECURITY_NOT_USED                     = 'S',
    HALT_COND_IN_VIEW_OF_COMMON                             = 'V',
    HALT_COND_EQUIPMENT_CHANGEOVER                          = 'X',
    HALT_COND_SUB_PENNY_TRADING                             = 'Y',
    HALT_COND_NO_OPEN_NO_RESUME                             = 'Z',
    HALT_COND_MARKETWIDE_CIRCUIT_BREAKER_LVL_1_BREACHED     = '1',
    HALT_COND_MARKETWIDE_CIRCUIT_BREAKER_LVL_2_BREACHED     = '2',
    HALT_COND_MARKETWIDE_CIRCUIT_BREAKER_LVL_3_BREACHED     = '3',
    // NO LONGER EXPECTED
    HALT_COND_ORDER_INFLUX                                  = 'E',
    HALT_COND_RESUME                                        = 'T',
};

typedef struct
{
    uint32_t        source_time;
    char            symbol[NYSE_ALERTS_SYMBOL_LEN];
    uint8_t         security_status;
    char            halt_condition;
} nyse_alerts_delay_halts_msg_t;

enum { NYSE_ALERTS_DELAY_HALTS_MSG_SIZE = 17 };

#ifdef __cplusplus
} // extern C
#endif

#endif /* NYSE_ALERTS_DELAY_HALTS_H_ */
