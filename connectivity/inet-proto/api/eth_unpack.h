/*
 * eth_unpack.h
 *
 *  Created on: 15-03-2013
 *      Author: wojtek
 */

#ifndef ETH_UNPACK_H_
#define ETH_UNPACK_H_

#include <stdint.h>
#include <stddef.h>
#include <net/ethernet.h>

typedef struct ether_header eth_header_t;

int eth_unitdata_ind_unpack(
    const uint8_t * in_data_p,
    const size_t in_size,
    eth_header_t * const out_eth_header_p,
    size_t * const out_offset_p);

#endif /* ETH_UNPACK_H_ */
