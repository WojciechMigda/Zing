/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: nyse_obultra_full_update_fixed.i
 *
 * Description:
 *      NYSE OpenBook Ultra Full Update message definition (fixed part)
 *
 * Authors:
 *          Wojciech Migda (wm)
 *
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-24   wm              Initial version
 *
 ******************************************************************************/

__OP_FIELD( msg_size,               uint16_t    )
__OP_FIELD( security_index,         uint16_t    )
__OP_FIELD( source_time,            uint32_t    )
__OP_FIELD( source_time_ms,         uint16_t    )
__OP_FIELD( symbol_seq_num,         uint32_t    )
__OP_FIELD( source_session_id,      uint8_t     )
__OP_ARRAY( symbol,                 char,       NYSE_SHORT_SYMBOL_LEN )
__OP_FIELD( price_scale_code,       uint8_t     )
__OP_FIELD( quote_condition,        char        )
__OP_FIELD( trading_status,         char        )
__OP_FIELD( filler,                 uint8_t     )
__OP_FIELD( mpv,                    uint16_t    )
