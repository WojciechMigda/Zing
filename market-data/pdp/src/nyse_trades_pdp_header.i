/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: nyse_trades_pdp_header.i
 *
 * Description:
 *      NYSE Trades PDP header definition
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

__OP_FIELD( msg_size,               uint16_t    )
__OP_FIELD( msg_type,               uint16_t    )
__OP_FIELD( msg_seq_num,            uint32_t    )
__OP_FIELD( send_time,              uint32_t    )
__OP_FIELD( product_id,             uint8_t     )
__OP_FIELD( retrans_flag,           uint8_t     )
__OP_FIELD( num_body_entries,       uint8_t     )
__OP_ARRAY( FILLER,                 char,       1 )
