/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: nyse_alerts_delay_halts_msg.i
 *
 * Description:
 *      NYSE Alerts Delay Halts message definition
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
__OP_ARRAY( symbol,                 char,       NYSE_ALERTS_SYMBOL_LEN  )
__OP_FIELD( security_status,        uint8_t     )
__OP_FIELD( halt_condition,         char        )
