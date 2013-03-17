/*
 * ip_unpack.h
 *
 *  Created on: 15-03-2013
 *      Author: wojtek
 */

#ifndef IP_UNPACK_H_
#define IP_UNPACK_H_

#include <stdint.h>
#include <stddef.h>
#include <netinet/ip.h>

typedef struct iphdr ip_header_t;

int ip_unitdata_unpack(
    const uint8_t * in_data_p,
    const size_t in_size,
    ip_header_t * const out_ip_header_p,
    size_t * const out_offset_p);

#endif /* IP_UNPACK_H_ */
