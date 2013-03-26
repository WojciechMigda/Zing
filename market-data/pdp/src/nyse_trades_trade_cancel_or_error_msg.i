/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: nyse_trades_trade_cancel_or_error_msg.i
 *
 * Description:
 *      NYSE Trades Trade Cancel or Error message definition
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
__OP_FIELD( source_seq_num,         uint32_t    )
__OP_FIELD( original_trade_ref_num, uint32_t    )
__OP_FIELD( source_session_id,      uint8_t     )
__OP_FIELD( exchange_id,            char        )
__OP_FIELD( security_type,          char        )
__OP_ARRAY( filler,                 char,       1 )
__OP_ARRAY( symbol,                 char,       NYSE_SYMBOL_LEN )
