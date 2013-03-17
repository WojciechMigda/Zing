/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 *******************************************************************************
 *
 * Filename: inet_unpack_status.h
 *
 * Description:
 *      Internet protocol unpacking routines return status values
 *
 * Authors:
 *          Wojciech Migda (wm)
 *
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-17   wm              Initial version
 *
 ******************************************************************************/

#ifndef INET_UNPACK_STATUS_H_
#define INET_UNPACK_STATUS_H_

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * internet protocol unpacking routines return status values
 */
enum inet_proto_unpack_status_values
{
    INET_PROTO_UNPACK_SUCCESS           = 0,
    INET_PROTO_UNPACK_NULL_PACKET_PTR   = -1,
    INET_PROTO_UNPACK_PACKET_TOO_SHORT  = -2,
};

#ifdef __cplusplus
} // extern C
#endif

#endif /* INET_UNPACK_STATUS_H_ */
