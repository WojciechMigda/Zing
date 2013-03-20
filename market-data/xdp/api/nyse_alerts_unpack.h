/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: nyse_alerts_unpack.h
 *
 * Description:
 *      NYSE Alerts unpack interface
 *
 * Authors:
 *          Wojciech Migda (wm)
 *
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-20   wm              Initial version
 *
 ******************************************************************************/


#ifndef NYSE_ALERTS_UNPACK_H_
#define NYSE_ALERTS_UNPACK_H_

#include <stdint.h>
#include <stddef.h>
#include "nyse_alerts_pdp.h"
#include "unpack_status.h"

#ifdef __cplusplus
extern "C"
{
#endif

int nyse_alerts_unpack_pdp_header(
    const uint8_t * in_data_p,
    const size_t in_size,
    nyse_alerts_pdp_header_t * const out_body_p,
    size_t * const out_offset_p)
{
    if (NULL == in_data_p)
    {
        return XDP_UNPACK_NULL_INPUT_PACKET_PTR;
    }

    if (in_size < NYSE_ALERTS_PDP_HEADER_SIZE)
    {
        return XDP_UNPACK_INPUT_PACKET_TOO_SHORT;
    }

    if (out_offset_p != NULL)
    {
        *out_offset_p = NYSE_ALERTS_PDP_HEADER_SIZE;
    }
    if (out_body_p != NULL)
    {
        *out_body_p = *((nyse_alerts_pdp_header_t *)in_data_p);

//        out_body_p->ether_type = ntohs(out_body_p->ether_type);
    }

    return XDP_UNPACK_SUCCESS;
}

#ifdef __cplusplus
} // extern C
#endif

#endif /* NYSE_ALERTS_UNPACK_H_ */
