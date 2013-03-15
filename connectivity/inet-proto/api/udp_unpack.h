/*
 * udp_unpack.h
 *
 *  Created on: 15-03-2013
 *      Author: wojtek
 */

#ifndef UDP_UNPACK_H_
#define UDP_UNPACK_H_

#include <stdint.h>
#include <stddef.h>
#include <netinet/udp.h>

typedef struct udphdr udp_header_t;

int udp_unitdata_ind_unpack(
    const uint8_t * in_data_p,
    const size_t in_size,
    udp_header_t * const out_udp_header_p,
    size_t * const out_offset_p);

#endif /* UDP_UNPACK_H_ */
