/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: nyse_obultra_full_update_price_point.i
 *
 * Description:
 *      NYSE OpenBook Ultra Full Update Price Point element definition
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

__OP_FIELD( price_numerator,        uint32_t    )
__OP_FIELD( volume,                 uint32_t    )
__OP_FIELD( num_orders,             uint16_t    )
__OP_FIELD( side,                   char        )
__OP_FIELD( filler,                 uint8_t     )
