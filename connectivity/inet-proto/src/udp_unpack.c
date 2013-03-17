/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All Rights Reserved.
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: udp_unpack.c
 *
 * Description:
 *      udp_unitdata_unpack interface implementation
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

#include "udp_unpack.h"
#include "inet_unpack_status.h"

/*******************************************************************************
 * @brief unpack UDP header from the packet
 *******************************************************************************
 * Unpack UDP header from the supplied packet. Error is reported when the
 * input pointer is NULL or the amount of data is not sufficient. User has to
 * make sure that the space where the header will be unpacked is large enough
 * to hold entire header data.
 * Areas where @c out_udp_header_p and @c out_offset_p point to will be modified
 * only when they are not NULL and no error occurs.
 * Unpacked header has host's endianness.
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
 * @packet out_udp_header_p pointer to the space where the header will be
 *         unpacked. May be NULL.
 * @param out_offset_p pointer where number of unpacked octets will be stored.
 *        May be NULL.
 * @return status of unpacking - @c inet_proto_unpack_status_values
 ******************************************************************************/
int udp_unitdata_unpack(
    const uint8_t * in_data_p,
    const size_t in_size,
    udp_header_t * const out_udp_header_p,
    size_t * const out_offset_p)
{
    int retval;

    if (NULL == in_data_p)
    {
        return INET_PROTO_UNPACK_NULL_PACKET_PTR;
    }

    if (in_size < sizeof (udp_header_t))
    {
        return INET_PROTO_UNPACK_PACKET_TOO_SHORT;
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

    return INET_PROTO_UNPACK_SUCCESS;
}
