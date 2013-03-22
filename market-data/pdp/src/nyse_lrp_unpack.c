/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: nyse_lrp_unpack.c
 *
 * Description:
 *      NYSE LRP feed unpacking routines implementation
 *
 * Authors:
 *          Wojciech Migda (wm)
 *
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-22   wm              Initial version
 *
 ******************************************************************************/

#include <stdint.h>
#include <stddef.h>
#include <endian.h>

#include "nyse_lrp_pdp_header.h"
#include "nyse_lrp_lrp_message.h"
#include "unpack_status.h"

/*******************************************************************************
 * @brief Unpack general PDP header of the NYSE LRP feed
 *******************************************************************************
 * Endianness of the unpacked data is that of the host.
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-22   wm              Initial version
 *
 *******************************************************************************
 * @param in_data_p pointer to the input packet
 * @param in_size number of octets in the input packet
 * @param out_body_p pointer to the header where the packet will be unpacked
 * @param out_offset_p pointer to the output variable where the amount of
 *        unpacked octets will be stored
 * @return PDP unpack return code
 ******************************************************************************/
int nyse_lrp_unpack_pdp_header(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_lrp_pdp_header_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p)
{
    if (NULL == in_data_p)
    {
        return PDP_UNPACK_NULL_INPUT_PACKET_PTR;
    }

    if (in_size < NYSE_LRP_PDP_HEADER_SIZE)
    {
        return PDP_UNPACK_INPUT_PACKET_TOO_SHORT;
    }

    if (out_offset_p != NULL)
    {
        *out_offset_p = NYSE_LRP_PDP_HEADER_SIZE;
    }
    if (out_body_p != NULL)
    {
        *out_body_p = *((nyse_lrp_pdp_header_t *)in_data_p);

        out_body_p->msg_size =      be16toh(out_body_p->msg_size);
        out_body_p->msg_type =      be16toh(out_body_p->msg_type);
        out_body_p->msg_seq_num =   be32toh(out_body_p->msg_seq_num);
        out_body_p->send_time =     be32toh(out_body_p->send_time);
    }

    return PDP_UNPACK_SUCCESS;
}

/*******************************************************************************
 * @brief Unpack LRP message of the NYSE BBO feed
 *******************************************************************************
 * Endianness of the unpacked data is that of the host.
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-22   wm              Initial version
 *
 *******************************************************************************
 * @param in_data_p pointer to the input packet
 * @param in_size number of octets in the input packet
 * @param out_body_p pointer to the variable where the packet will be unpacked
 * @param out_offset_p pointer to the output variable where the amount of
 *        unpacked octets will be stored
 * @return PDP unpack return code
 ******************************************************************************/
int nyse_lrp_unpack_lrp_msg(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_lrp_lrp_msg_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p)
{
    if (NULL == in_data_p)
    {
        return PDP_UNPACK_NULL_INPUT_PACKET_PTR;
    }

    if (in_size < NYSE_LRP_LRP_MSG_SIZE)
    {
        return PDP_UNPACK_INPUT_PACKET_TOO_SHORT;
    }

    if (out_offset_p != NULL)
    {
        *out_offset_p = NYSE_LRP_LRP_MSG_SIZE;
    }
    if (out_body_p != NULL)
    {
        *out_body_p = *((nyse_lrp_lrp_msg_t *)in_data_p);

        out_body_p->source_time =           be32toh(out_body_p->source_time);
        out_body_p->low_lrp_numerator =     be32toh(out_body_p->low_lrp_numerator);
        out_body_p->high_lrp_numerator =    be32toh(out_body_p->high_lrp_numerator);
    }

    return PDP_UNPACK_SUCCESS;
}
