/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 *******************************************************************************
 *
 * Filename: ip_unpack.h
 *
 * Description:
 *      ip_unitdata_unpack interface
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

#ifndef IP_UNPACK_H_
#define IP_UNPACK_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stddef.h>
#include <netinet/ip.h>

typedef struct iphdr ip_header_t;

int ip_unitdata_unpack(
    const uint8_t * in_data_p,
    const size_t in_size,
    ip_header_t * const out_ip_header_p,
    size_t * const out_offset_p);

#ifdef __cplusplus
} // extern C
#endif

#endif /* IP_UNPACK_H_ */
