/*
 * udp_unpack.c
 *
 *  Created on: 15-03-2013
 *      Author: wojtek
 */

#include <stdint.h>
#include <stddef.h>
#include <arpa/inet.h>

#include "udp_unpack.h"

int udp_unitdata_ind_unpack(
    const uint8_t * in_data_p,
    const size_t in_size,
    udp_header_t * const out_udp_header_p,
    size_t * const out_offset_p)
{
    int retval;

    if (NULL == in_data_p)
    {
        return -1;
    }

    if (in_size < sizeof (udp_header_t))
    {
        return -2;
    }

    if (out_udp_header_p != NULL)
    {
        *out_udp_header_p = *((udp_header_t *)in_data_p);
        out_udp_header_p->source = ntohs(out_udp_header_p->source);
        out_udp_header_p->dest = ntohs(out_udp_header_p->dest);
        out_udp_header_p->len = ntohs(out_udp_header_p->len);
        out_udp_header_p->check = ntohs(out_udp_header_p->check);
    }
    if (out_offset_p != NULL)
    {
        *out_offset_p = sizeof (udp_header_t);
    }

    return 0;
}
