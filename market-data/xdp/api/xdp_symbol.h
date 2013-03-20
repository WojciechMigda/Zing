/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 * Filename: xdp_symbol.h
 *
 * Description:
 *      Symbol field definitions
 *
 * Authors:
 *          Wojciech Migda (wm)
 *
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-18   wm              Initial version
 *
 ******************************************************************************/


#ifndef XDP_SYMBOL_H_
#define XDP_SYMBOL_H_

#ifdef __cplusplus
extern "C"
{
#endif

enum xdp_symbol_field_length_values
{
    NYSE_ALERTS_SYMBOL_LEN  = 11,
    NYSE_BBO_SYMBOL_LEN     = 16,
    NYSE_LRP_SYMBOL_LEN     = 16,
};

#ifdef __cplusplus
} // extern C
#endif

#endif /* XDP_SYMBOL_H_ */
