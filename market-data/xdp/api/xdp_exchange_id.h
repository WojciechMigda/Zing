/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: xdp_exchange_id.h
 *
 * Description:
 *      Exchange Id field definitions
 *
 * Authors:
 *          Wojciech Migda (wm)
 *
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-20   wm              Initial version
 *
 ******************************************************************************/


#ifndef XDP_EXCHANGE_ID_H_
#define XDP_EXCHANGE_ID_H_

#ifdef __cplusplus
extern "C"
{
#endif

enum exchange_id_values
{
    EXCHANGE_ID_NYSE        = 'N',
};

#ifdef __cplusplus
} // extern C
#endif

#endif /* XDP_EXCHANGE_ID_H_ */
