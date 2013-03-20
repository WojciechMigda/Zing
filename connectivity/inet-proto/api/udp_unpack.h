/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All Rights Reserved.
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: udp_unpack.h
 *
 * Description:
 *      udp_unpack interface
 *
 * Authors:
 *          Wojciech Migda (wm)
 *
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-16   wm              Initial version
 *
 ******************************************************************************/

#ifndef UDP_UNPACK_H_
#define UDP_UNPACK_H_

#include <stdint.h>
#include <stddef.h>
#include <netinet/udp.h>
#include "compiler.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct udphdr udp_header_t;

int udp_unitdata_unpack(
    const uint8_t * in_data_p,
    const size_t in_size,
    udp_header_t * const out_udp_header_p,
    size_t * const out_offset_p);

#ifdef __cplusplus
} // extern C
#endif

#endif /* UDP_UNPACK_H_ */
