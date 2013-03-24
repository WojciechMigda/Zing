/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: nyse_alerts_market_imbalance_msg.i
 *
 * Description:
 *      NYSE Alerts Market Imbalance message definition
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
__OP_ARRAY( symbol,                 char,       NYSE_SHORT_SYMBOL_LEN  )
__OP_FIELD( security_status,        uint8_t     )
__OP_FIELD( imbalance_quantity,     uint32_t    )
__OP_FIELD( imbalance_side,         char        )
