/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: pdp_side.h
 *
 * Description:
 *      PDP Side element definitions
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


#ifndef PDP_SIDE_H_
#define PDP_SIDE_H_

#ifdef __cplusplus
extern "C"
{
#endif

enum side_values
{
    SIDE_BUY        = 'B',
    SIDE_SELL       = 'S',
};

#ifdef __cplusplus
} // extern C
#endif

#endif /* PDP_SIDE_H_ */
