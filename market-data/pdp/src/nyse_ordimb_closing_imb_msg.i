/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: nyse_ordimb_closing_imb_msg.i
 *
 * Description:
 *      NYSE Order Imbalances Closing Imbalance message definition
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

__OP_ARRAY( symbol,                 char,       NYSE_SHORT_SYMBOL_LEN )
__OP_FIELD( regulatory_imbalance_indicator, uint8_t     )
__OP_FIELD( imbalance_side,         char        )
__OP_FIELD( price_scale_code,       uint8_t     )
__OP_FIELD( reference_price_numerator, uint32_t    )
__OP_FIELD( imbalance_quantity,     uint32_t    )
__OP_FIELD( paired_quantity,        uint32_t    )
__OP_FIELD( continuous_book_clearing_price_numerator, uint32_t    )
__OP_FIELD( closing_only_clearing_price_numerator, uint32_t    )
__OP_FIELD( source_time,            uint32_t    )
