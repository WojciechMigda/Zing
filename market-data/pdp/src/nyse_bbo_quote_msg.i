/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: nyse_bbo_quote_msg.i
 *
 * Description:
 *      NYSE BBO Quote message definition
 *
 * Authors:
 *          Wojciech Migda (wm)
 *
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-23   wm              Initial version
 *
 ******************************************************************************/

__OP_FIELD( source_time,            uint32_t    )
__OP_ARRAY( filler,                 uint8_t,    3  )
__OP_FIELD( rpi_interest,           char        )
__OP_FIELD( ask_price_nominator,    uint32_t    )
__OP_FIELD( ask_size,               uint32_t    )
__OP_FIELD( bid_price_numerator,    uint32_t    )
__OP_FIELD( bid_size,               uint32_t    )
__OP_FIELD( price_scale_code,       uint8_t     )
__OP_FIELD( exchange_id,            char        )
__OP_FIELD( security_type,          char        )
__OP_FIELD( quote_condition,        char        )
__OP_ARRAY( symbol,                 char,       NYSE_SYMBOL_LEN  )
