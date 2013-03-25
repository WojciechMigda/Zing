/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: nyse_ordimb_closing_imbalance.h
 *
 * Description:
 *      NYSE Order Imbalances Closing Imbalance message definitions
 *
 *      References:
 *      [1] NYSE ORDER IMBALANCES CLIENT SPECIFICATION, Version 1.12, 2012-11-09
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


#ifndef NYSE_ORDIMB_CLOSING_IMBALANCE_H_
#define NYSE_ORDIMB_CLOSING_IMBALANCE_H_

#include <stdint.h>
#include "pdp_symbol.h"

#ifdef __cplusplus
extern "C"
{
#endif

enum { NYSE_ORDIMB_CLOSING_IMBALANCE_MSG_SIZE = 38 };

typedef struct
{
    char                symbol[NYSE_SHORT_SYMBOL_LEN];
    uint8_t             regulatory_imbalance_indicator;
    char                imbalance_side;
    uint8_t             price_scale_code;
    uint32_t            reference_price_numerator;
    uint32_t            imbalance_quantity;
    uint32_t            paired_quantity;
    uint32_t            continuous_book_clearing_price_numerator;
    uint32_t            closing_only_clearing_price_numerator;
    uint32_t            source_time;
} nyse_ordimb_closing_imb_msg_t;

#ifdef __cplusplus
} // extern C
#endif

#endif /* NYSE_ORDIMB_CLOSING_IMBALANCE_H_ */
