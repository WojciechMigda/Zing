/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: nyse_lrp_lrp_msg.i
 *
 * Description:
 *      NYSE LRP feed LRP message definition
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

__OP_FIELD( filler1,                uint32_t    )
__OP_FIELD( source_time,            uint32_t    )
__OP_FIELD( low_lrp_numerator,      uint32_t    )
__OP_FIELD( high_lrp_numerator,     uint32_t    )
__OP_FIELD( price_scale_code,       uint8_t     )
__OP_FIELD( lrp_change_indicator,   char        )
__OP_FIELD( filler2,                uint16_t    )
__OP_ARRAY( symbol,                 char,       NYSE_SYMBOL_LEN  )
