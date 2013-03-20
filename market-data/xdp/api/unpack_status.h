/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: unpack_status.h
 *
 * Description:
 *      XDP general unpack status return codes
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


#ifndef UNPACK_STATUS_H_
#define UNPACK_STATUS_H_

#ifdef __cplusplus
extern "C"
{
#endif

enum xdp_unpack_status_values
{
    XDP_UNPACK_SUCCESS                  = 0,
    XDP_UNPACK_NULL_INPUT_PACKET_PTR    = -1,
    XDP_UNPACK_INPUT_PACKET_TOO_SHORT   = -2,
};

#ifdef __cplusplus
} // extern C
#endif

#endif /* UNPACK_STATUS_H_ */
