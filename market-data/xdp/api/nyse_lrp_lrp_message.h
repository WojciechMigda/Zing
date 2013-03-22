/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: nyse_lrp_lrp_message.h
 *
 * Description:
 *      NYSE LRP - Nyse Lrp message definitions
 *
 *      References:
 *      [1] NYSE LIQUIDITY REPLENISHMENT POINTS® (LRP),
 *          Version 1.2a, 2012-08-31,
 *          Sec. 4.8
 *
 * Authors:
 *          Wojciech Migda (wm)
 *
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-20   wm              Initial version
 *
 ******************************************************************************/


#ifndef NYSE_LRP_LRP_MESSAGE_H_
#define NYSE_LRP_LRP_MESSAGE_H_

#include <stdint.h>
#include "compiler.h"
#include "static_assert.h"
#include "xdp_symbol.h"

#ifdef __cplusplus
extern "C"
{
#endif

enum lrp_change_indicator_values
{
    LRP_CHANGE_IND_LOW_LRP              = 'L',
    LRP_CHANGE_IND_HIGH_LRP             = 'H',
    LRP_CHANGE_IND_LOW_AND_HIGH_LRP     = 'B',
};

typedef struct PACKED
{
    uint32_t        filler1;
    uint32_t        source_time;
    uint32_t        low_lrp_numerator;
    uint32_t        high_lrp_numerator;
    uint8_t         price_scale_code;
    char            lrp_change_indicator;
    uint16_t        filler2;
    char            symbol[NYSE_SYMBOL_LEN];
} nyse_lrp_lrp_msg_t;

enum { NYSE_LRP_LRP_MSG_SIZE = 36 };

STATIC_ASSERT(sizeof (nyse_lrp_lrp_msg_t) == NYSE_LRP_LRP_MSG_SIZE);

#ifdef __cplusplus
} // extern C
#endif

#endif /* NYSE_LRP_LRP_MESSAGE_H_ */
