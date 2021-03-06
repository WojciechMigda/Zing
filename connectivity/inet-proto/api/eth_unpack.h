/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: eth_unpack.h
 *
 * Description:
 *      eth_unitdata_unpack interface
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

#ifndef ETH_UNPACK_H_
#define ETH_UNPACK_H_

#include <stdint.h>
#include <stddef.h>
#include <net/ethernet.h>
#include "compiler.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct ether_header eth_header_t;

int eth_unitdata_unpack(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    eth_header_t * const RESTRICT out_eth_header_p,
    size_t * const RESTRICT out_offset_p);

#ifdef __cplusplus
} // extern C
#endif

#endif /* ETH_UNPACK_H_ */
