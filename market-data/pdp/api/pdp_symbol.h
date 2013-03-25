/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 * Filename: pdp_symbol.h
 *
 * Description:
 *      PDP Symbol field definitions
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


#ifndef PDP_SYMBOL_H_
#define PDP_SYMBOL_H_

#ifdef __cplusplus
extern "C"
{
#endif

enum pdp_symbol_field_length_values
{
    NYSE_SHORT_SYMBOL_LEN   = 11,
    NYSE_SYMBOL_LEN         = 16,
};

#ifdef __cplusplus
} // extern C
#endif

#endif /* PDP_SYMBOL_H_ */
