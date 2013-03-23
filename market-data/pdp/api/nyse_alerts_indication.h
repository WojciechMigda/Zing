/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 * Filename: nyse_alerts_indication.h
 *
 * Description:
 *      NYSE Alerts Indication message definitions
 *
 *      References:
 *      [1] NYSE ALERTS CLIENT SPECIFICATION, Version 2.12, 2013-01-24
 *          Sec. 4.11
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


#ifndef NYSE_ALERTS_INDICATION_H_
#define NYSE_ALERTS_INDICATION_H_

#include <stdint.h>
#include "pdp_symbol.h"
#include "pdp_security_status.h"
#include "compiler.h"

#ifdef __cplusplus
extern "C"
{
#endif

enum adjustment_values
{
    ADJUSTMENT_NONE         = 0,
    ADJUSTMENT_CANCEL       = 1,
    ADJUSTMENT_CORRECTION   = 2,
};

typedef struct
{
    uint32_t        source_time;
    char            symbol[NYSE_ALERTS_SYMBOL_LEN];
    uint8_t         security_status;
    uint32_t        bid_price;
    uint32_t        ask_price;
    uint8_t         price_scale_code;
    uint8_t         adjustment;
} nyse_alerts_indication_msg_t;

enum { NYSE_ALERTS_INDICATION_MSG_SIZE = 26 };

#ifdef __cplusplus
} // extern C
#endif

#endif /* NYSE_ALERTS_INDICATION_H_ */
