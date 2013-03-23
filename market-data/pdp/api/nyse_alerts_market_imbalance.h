/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 * Filename: nyse_alerts_market_imbalance.h
 *
 * Description:
 *      NYSE Alerts Market Imbalance message definitions
 *
 *      References:
 *      [1] NYSE ALERTS CLIENT SPECIFICATION, Version 2.12, 2013-01-24
 *          Sec. 4.9
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


#ifndef NYSE_ALERTS_MARKET_IMBALANCE_H_
#define NYSE_ALERTS_MARKET_IMBALANCE_H_

#include <stdint.h>
#include "pdp_symbol.h"
#include "pdp_security_status.h"

#ifdef __cplusplus
extern "C"
{
#endif

enum imbalance_side_values
{
    IMB_SIDE_BUY        = 'B',
    IMB_SIDE_SELL       = 'S',
    IMB_SIDE_NA         = ' ',
};

typedef struct
{
    uint32_t        source_time;
    char            symbol[NYSE_ALERTS_SYMBOL_LEN];
    uint8_t         security_status;
    uint32_t        imbalance_quantity;
    char            imbalance_side;
} nyse_alerts_market_imbalance_msg_t;

enum { NYSE_ALERTS_MARKET_IMBALANCE_MSG_SIZE = 21 };

#ifdef __cplusplus
} // extern C
#endif

#endif /* NYSE_ALERTS_MARKET_IMBALANCE_H_ */
