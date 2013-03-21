/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: nyse_alerts_unpack.c
 *
 * Description:
 *      description
 *
 * Authors:
 *          Wojciech Migda (wm)
 *
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 20-03-2013   wm              Initial version
 *
 ******************************************************************************/

#include <stdint.h>
#include <stddef.h>
#include <endian.h>

#include "nyse_alerts_pdp.h"
#include "unpack_status.h"
#include "nyse_alerts_unpack.h"
#include "compiler.h"
#include "nyse_alerts_market_imbalance.h"

/*******************************************************************************
 * @brief Unpack general PDP header of the NYSE Alerts feed
 *******************************************************************************
 * Endianness of the unpacked data is that of the host.
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-20   wm              Initial version
 *
 *******************************************************************************
 * @param in_data_p pointer to the input packet
 * @param in_size number of octets in the input packet
 * @param out_body_p pointer to the header where the packet will be unpacked
 * @param out_offset_p pointer to the output variable where the amount of
 *        unpacked octets will be stored
 * @return XDP unpack return code
 ******************************************************************************/
int nyse_alerts_unpack_pdp_header(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_alerts_pdp_header_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p)
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

        out_body_p->msg_size =      be16toh(out_body_p->msg_size);
        out_body_p->msg_type =      be16toh(out_body_p->msg_type);
        out_body_p->msg_seq_num =   be32toh(out_body_p->msg_seq_num);
        out_body_p->send_time =     be32toh(out_body_p->send_time);
    }

    return XDP_UNPACK_SUCCESS;
}

/*******************************************************************************
 * @brief Unpack Security Info message of the NYSE Alerts feed
 *******************************************************************************
 * Endianness of the unpacked data is that of the host.
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-20   wm              Initial version
 *
 *******************************************************************************
 * @param in_data_p pointer to the input packet
 * @param in_size number of octets in the input packet
 * @param out_body_p pointer to the variable where the packet will be unpacked
 * @param out_offset_p pointer to the output variable where the amount of
 *        unpacked octets will be stored
 * @return XDP unpack return code
 ******************************************************************************/
int nyse_alerts_unpack_security_info_msg(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_alerts_security_info_msg_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p)
{
    if (NULL == in_data_p)
    {
        return XDP_UNPACK_NULL_INPUT_PACKET_PTR;
    }

    if (in_size < NYSE_ALERTS_SECURITY_INFO_MSG_SIZE)
    {
        return XDP_UNPACK_INPUT_PACKET_TOO_SHORT;
    }

    if (out_offset_p != NULL)
    {
        *out_offset_p = NYSE_ALERTS_SECURITY_INFO_MSG_SIZE;
    }
    if (out_body_p != NULL)
    {
        *out_body_p = *((nyse_alerts_security_info_msg_t *)in_data_p);

        out_body_p->source_time =   be32toh(out_body_p->source_time);
        out_body_p->filler =        be16toh(out_body_p->filler);
        out_body_p->mpv =           be16toh(out_body_p->mpv);
        out_body_p->uot =           be16toh(out_body_p->uot);
        out_body_p->lrp =           be16toh(out_body_p->lrp);
        out_body_p->ex_div_amount = be32toh(out_body_p->ex_div_amount);
    }

    return XDP_UNPACK_SUCCESS;
}

/*******************************************************************************
 * @brief Unpack Market Imbalance message of the NYSE Alerts feed
 *******************************************************************************
 * Endianness of the unpacked data is that of the host.
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-21   wm              Initial version
 *
 *******************************************************************************
 * @param in_data_p pointer to the input packet
 * @param in_size number of octets in the input packet
 * @param out_body_p pointer to the variable where the packet will be unpacked
 * @param out_offset_p pointer to the output variable where the amount of
 *        unpacked octets will be stored
 * @return XDP unpack return code
 ******************************************************************************/
int nyse_alerts_unpack_market_imbalance_msg(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_alerts_market_imbalance_msg_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p)
{
    if (NULL == in_data_p)
    {
        return XDP_UNPACK_NULL_INPUT_PACKET_PTR;
    }

    if (in_size < NYSE_ALERTS_MARKET_IMBALANCE_MSG_SIZE)
    {
        return XDP_UNPACK_INPUT_PACKET_TOO_SHORT;
    }

    if (out_offset_p != NULL)
    {
        *out_offset_p = NYSE_ALERTS_MARKET_IMBALANCE_MSG_SIZE;
    }
    if (out_body_p != NULL)
    {
        *out_body_p = *((nyse_alerts_market_imbalance_msg_t *)in_data_p);

        out_body_p->source_time =           be32toh(out_body_p->source_time);
        out_body_p->imbalance_quantity =    be32toh(out_body_p->imbalance_quantity);
    }

    return XDP_UNPACK_SUCCESS;
}

/*******************************************************************************
 * @brief Unpack Delay Halts message of the NYSE Alerts feed
 *******************************************************************************
 * Endianness of the unpacked data is that of the host.
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-21   wm              Initial version
 *
 *******************************************************************************
 * @param in_data_p pointer to the input packet
 * @param in_size number of octets in the input packet
 * @param out_body_p pointer to the variable where the packet will be unpacked
 * @param out_offset_p pointer to the output variable where the amount of
 *        unpacked octets will be stored
 * @return XDP unpack return code
 ******************************************************************************/
int nyse_alerts_unpack_delay_halt_msg(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_alerts_delay_halts_msg_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p)
{
    if (NULL == in_data_p)
    {
        return XDP_UNPACK_NULL_INPUT_PACKET_PTR;
    }

    if (in_size < NYSE_ALERTS_DELAY_HALTS_MSG_SIZE)
    {
        return XDP_UNPACK_INPUT_PACKET_TOO_SHORT;
    }

    if (out_offset_p != NULL)
    {
        *out_offset_p = NYSE_ALERTS_DELAY_HALTS_MSG_SIZE;
    }
    if (out_body_p != NULL)
    {
        *out_body_p = *((nyse_alerts_delay_halts_msg_t *)in_data_p);

        out_body_p->source_time =           be32toh(out_body_p->source_time);
    }

    return XDP_UNPACK_SUCCESS;
}
