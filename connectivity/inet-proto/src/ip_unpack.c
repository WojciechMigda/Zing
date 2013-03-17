/*
 * ip_unpack.c
 *
 *  Created on: 15-03-2013
 *      Author: wojtek
 */

#include <stdint.h>
#include <stddef.h>
#include <arpa/inet.h>

#include "ip_unpack.h"

int ip_unitdata_unpack(
    const uint8_t * in_data_p,
    const size_t in_size,
    ip_header_t * const out_ip_header_p,
    size_t * const out_offset_p)
{
    int retval;

    if (NULL == in_data_p)
    {
        return -1;
    }

    if (in_size < sizeof (ip_header_t))
    {
        return -2;
    }

    if (out_ip_header_p != NULL)
    {
        *out_ip_header_p = *((ip_header_t *)in_data_p);
        out_ip_header_p->tot_len = ntohs(out_ip_header_p->tot_len);
        out_ip_header_p->id = ntohs(out_ip_header_p->id);
        out_ip_header_p->frag_off = ntohs(out_ip_header_p->frag_off);
        out_ip_header_p->check = ntohs(out_ip_header_p->check);
        out_ip_header_p->saddr = ntohl(out_ip_header_p->saddr);
        out_ip_header_p->daddr = ntohl(out_ip_header_p->daddr);
    }
    if (out_offset_p != NULL)
    {
        *out_offset_p = sizeof (ip_header_t);
    }

    return 0;
}
