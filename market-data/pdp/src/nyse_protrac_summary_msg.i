/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: nyse_protrac_summary_msg.i
 *
 * Description:
 *      NYSE ProTrac Summary message definition
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

__OP_ARRAY( symbol,                 char,       NYSE_SYMBOL_LEN )
__OP_FIELD( total_volume,           uint32_t    )
__OP_FIELD( execution_type,         uint16_t    )
