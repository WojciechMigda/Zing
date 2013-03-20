/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 * Filename: nyse_alerts_short_sale_restriction.h
 *
 * Description:
 *      NYSE Alerts Short Sale Restriction message definitions
 *
 *      References:
 *      [1] NYSE ALERTS CLIENT SPECIFICATION, Version 2.12, 2013-01-24
 *          Sec. 4.14
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


#ifndef NYSE_ALERTS_SHORT_SALE_RESTRICTION_H_
#define NYSE_ALERTS_SHORT_SALE_RESTRICTION_H_

#include <stdint.h>
#include "xdp_symbol.h"
#include "static_assert.h"
#include "compiler.h"

#ifdef __cplusplus
extern "C"
{
#endif

enum short_sale_restriction_indicator_values
{
    SHORT_SALE_RESTR_IND_ACTIVATED      = 'A',
    SHORT_SALE_RESTR_IND_CONTINUED      = 'C',
    SHORT_SALE_RESTR_IND_DEACTIVATED    = 'D',
    SHORT_SALE_RESTR_IND_NO_RESTR       = '~',
    SHORT_SALE_RESTR_IND_IN_EFFECT      = 'E',
};

typedef struct PACKED
{
    uint32_t        source_time;
    char            symbol[NYSE_ALERTS_SYMBOL_LEN];
    uint8_t         security_status;
    char            short_sale_restriction_indicator;
    char            triggering_exchange_id;
    uint32_t        short_sale_trigger_time;
    uint32_t        trade_price;
    uint8_t         price_scale_code;
    uint32_t        trade_volume;
} nyse_alerts_short_sale_restriction_msg_t;

STATIC_ASSERT(sizeof (nyse_alerts_short_sale_restriction_msg_t) == 31);

#ifdef __cplusplus
} // extern C
#endif

#endif /* NYSE_ALERTS_SHORT_SALE_RESTRICTION_H_ */
