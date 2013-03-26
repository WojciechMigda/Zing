/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: nyse_trades_trade_msg.i
 *
 * Description:
 *      NYSE Trades Trade message definition
 *
 * Authors:
 *          Wojciech Migda (wm)
 *
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-26   wm              Initial version
 *
 ******************************************************************************/

__OP_FIELD( source_time,            uint32_t    )
__OP_FIELD( link_id,                uint32_t    )
__OP_FIELD( filler,                 uint32_t    )
__OP_FIELD( price_numerator,        uint32_t    )
__OP_FIELD( volume,                 uint32_t    )
__OP_FIELD( source_seq_num,         uint32_t    )
__OP_FIELD( source_session_id,      uint8_t     )
__OP_FIELD( price_scale_code,       uint8_t     )
__OP_FIELD( exchange_id,            char        )
__OP_FIELD( security_type,          char        )
__OP_FIELD( trade_cond_1,           char        )
__OP_FIELD( trade_cond_2,           char        )
__OP_FIELD( trade_cond_3,           char        )
__OP_FIELD( trade_cond_4,           char        )
__OP_ARRAY( symbol,                 char,       NYSE_SYMBOL_LEN )
