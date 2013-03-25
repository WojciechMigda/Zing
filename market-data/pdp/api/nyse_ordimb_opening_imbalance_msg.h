/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: nyse_ordimb_opening_imbalance_msg.h
 *
 * Description:
 *      NYSE Order Imbalances Opening Imbalance message definitions
 *
 *      References:
 *      [1] NYSE ORDER IMBALANCES CLIENT SPECIFICATION, Version 1.12, 2012-11-09
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


#ifndef NYSE_ORDIMB_OPENING_IMBALANCE_MSG_H_
#define NYSE_ORDIMB_OPENING_IMBALANCE_MSG_H_

#include <stdint.h>
#include "pdp_symbol.h"

#ifdef __cplusplus
extern "C"
{
#endif

enum { NYSE_ORDIMB_OPENING_IMBALANCE_MSG_SIZE = 38 };

enum stock_open_indicator_values
{
    STOCK_OPEN_IND_NOT_OPEN     = 0,
    STOCK_OPEN_IND_OPEN         = 1,
};

typedef struct
{
    char                symbol[NYSE_SHORT_SYMBOL_LEN];
    uint32_t            stock_open_indicator;
    char                imbalance_side;
    uint8_t             price_scale_code;
    uint32_t            reference_price_numerator;
    uint32_t            imbalance_quantity;
    uint32_t            paired_quantity;
    uint32_t            clearing_price_numerator;
    uint32_t            source_time;
    uint32_t            ssr_filing_price_numerator;
} nyse_ordimb_opening_imb_msg_t;

#ifdef __cplusplus
} // extern C
#endif

#endif /* NYSE_ORDIMB_OPENING_IMBALANCE_MSG_H_ */
