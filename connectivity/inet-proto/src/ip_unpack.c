/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All Rights Reserved.
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: ip_unpack.c
 *
 * Description:
 *      ip_unitdata_unpack interface implementation
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

#include <stdint.h>
#include <stddef.h>
#include <arpa/inet.h>

#include "ip_unpack.h"
#include "inet_unpack_status.h"
#include "compiler.h"

/*******************************************************************************
 * @brief unpack IP header from the packet
 *******************************************************************************
 * Unpack IP header from the supplied packet. Error is reported when the
 * input pointer is NULL or the amount of data is not sufficient. User has to
 * make sure that the space where the header will be unpacked is large enough
 * to hold entire header data.
 * Areas where @c out_ip_header_p and @c out_offset_p point to will be modified
 * only when they are not NULL and no error occurs.
 * Unpacked header has host's endianness.
 *
 * NOTE: only mandatory (non-optional) part of the header is unpacked.
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 17-03-2013   wm              Initial version
 *
 *******************************************************************************
 * @param in_data_p pointer to the input packet data
 * @param in_size amount of octets in the input packet
 * @packet out_ip_header_p pointer to the space where the header will be
 *         unpacked. May be NULL.
 * @param out_offset_p pointer where number of unpacked octets will be stored.
 *        May be NULL.
 * @return status of unpacking - @c inet_proto_unpack_status_values
 ******************************************************************************/
int ip_unitdata_unpack(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    ip_header_t * const RESTRICT out_ip_header_p,
    size_t * const RESTRICT out_offset_p)
{
    int retval;

    if (NULL == in_data_p)
    {
        return INET_PROTO_UNPACK_NULL_PACKET_PTR;
    }

    if (in_size < sizeof (ip_header_t))
    {
        return INET_PROTO_UNPACK_PACKET_TOO_SHORT;
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

    return INET_PROTO_UNPACK_SUCCESS;
}
