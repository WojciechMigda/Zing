/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: nyse_alerts_unpack.c
 *
 * Description:
 *      NYSE Alerts feed unpacking routines implementation
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
#include <string.h>

#include "nyse_alerts_pdp_header.h"
#include "unpack_status.h"
#include "nyse_alerts_unpack.h"
#include "compiler.h"
#include "nyse_alerts_market_imbalance.h"
#include "static_assert.h"
#include "pdp_symbol.h"

typedef struct PACKED
{
    uint32_t        source_time;
    char            symbol[NYSE_ALERTS_SYMBOL_LEN];
    uint8_t         security_status;
    uint32_t        imbalance_quantity;
    char            imbalance_side;
} market_imbalance_msg_packed_t;
STATIC_ASSERT(sizeof (market_imbalance_msg_packed_t) == NYSE_ALERTS_MARKET_IMBALANCE_MSG_SIZE);

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
 * @return PDP unpack return code
 ******************************************************************************/
int nyse_alerts_unpack_pdp_header(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_alerts_pdp_header_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p)
{
#define __STRUCT_FILE "nyse_alerts_pdp_header.i"
#define __STRUCT_SIZE NYSE_ALERTS_PDP_HEADER_SIZE

#include "unpack_generic.i"
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
 * @return PDP unpack return code
 ******************************************************************************/
int nyse_alerts_unpack_security_info_msg(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_alerts_security_info_msg_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p)
{
#define __STRUCT_FILE "nyse_alerts_security_info_msg.i"
#define __STRUCT_SIZE NYSE_ALERTS_SECURITY_INFO_MSG_SIZE

#include "unpack_generic.i"
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
 * @return PDP unpack return code
 ******************************************************************************/
int nyse_alerts_unpack_market_imbalance_msg(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_alerts_market_imbalance_msg_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p)
{
#define __STRUCT_FILE "nyse_alerts_market_imbalance_msg.i"
#define __STRUCT_SIZE NYSE_ALERTS_MARKET_IMBALANCE_MSG_SIZE

#include "unpack_generic.i"
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
 * @return PDP unpack return code
 ******************************************************************************/
int nyse_alerts_unpack_delay_halts_msg(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_alerts_delay_halts_msg_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p)
{
    if (NULL == in_data_p)
    {
        return PDP_UNPACK_NULL_INPUT_PACKET_PTR;
    }

    if (in_size < NYSE_ALERTS_DELAY_HALTS_MSG_SIZE)
    {
        return PDP_UNPACK_INPUT_PACKET_TOO_SHORT;
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

    return PDP_UNPACK_SUCCESS;
}

/*******************************************************************************
 * @brief Unpack Indication message of the NYSE Alerts feed
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
 * @return PDP unpack return code
 ******************************************************************************/
int nyse_alerts_unpack_indication_msg(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_alerts_indication_msg_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p)
{
    if (NULL == in_data_p)
    {
        return PDP_UNPACK_NULL_INPUT_PACKET_PTR;
    }

    if (in_size < NYSE_ALERTS_INDICATION_MSG_SIZE)
    {
        return PDP_UNPACK_INPUT_PACKET_TOO_SHORT;
    }

    if (out_offset_p != NULL)
    {
        *out_offset_p = NYSE_ALERTS_INDICATION_MSG_SIZE;
    }
    if (out_body_p != NULL)
    {
        *out_body_p = *((nyse_alerts_indication_msg_t *)in_data_p);

        out_body_p->source_time =           be32toh(out_body_p->source_time);
        out_body_p->bid_price =             be32toh(out_body_p->bid_price);
        out_body_p->ask_price =             be32toh(out_body_p->ask_price);
    }

    return PDP_UNPACK_SUCCESS;
}

/*******************************************************************************
 * @brief Unpack T-Time message of the NYSE Alerts feed
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
 * @return PDP unpack return code
 ******************************************************************************/
int nyse_alerts_unpack_t_time_msg(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_alerts_t_time_msg_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p)
{
    if (NULL == in_data_p)
    {
        return PDP_UNPACK_NULL_INPUT_PACKET_PTR;
    }

    if (in_size < NYSE_ALERTS_T_TIME_MSG_SIZE)
    {
        return PDP_UNPACK_INPUT_PACKET_TOO_SHORT;
    }

    if (out_offset_p != NULL)
    {
        *out_offset_p = NYSE_ALERTS_T_TIME_MSG_SIZE;
    }
    if (out_body_p != NULL)
    {
        *out_body_p = *((nyse_alerts_t_time_msg_t *)in_data_p);

        out_body_p->source_time =               be32toh(out_body_p->source_time);
        out_body_p->trade_dissemination_time =  be32toh(out_body_p->trade_dissemination_time);
    }

    return PDP_UNPACK_SUCCESS;
}

/*******************************************************************************
 * @brief Unpack Circuit Breaker message of the NYSE Alerts feed
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
 * @return PDP unpack return code
 ******************************************************************************/
int nyse_alerts_unpack_circuit_breaker_msg(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_alerts_circuit_breaker_msg_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p)
{
    if (NULL == in_data_p)
    {
        return PDP_UNPACK_NULL_INPUT_PACKET_PTR;
    }

    if (in_size < NYSE_ALERTS_CIRCUIT_BREAKER_MSG_SIZE)
    {
        return PDP_UNPACK_INPUT_PACKET_TOO_SHORT;
    }

    if (out_offset_p != NULL)
    {
        *out_offset_p = NYSE_ALERTS_CIRCUIT_BREAKER_MSG_SIZE;
    }
    if (out_body_p != NULL)
    {
        *out_body_p = *((nyse_alerts_circuit_breaker_msg_t *)in_data_p);

        out_body_p->event_time = be32toh(out_body_p->event_time);
    }

    return PDP_UNPACK_SUCCESS;
}

/*******************************************************************************
 * @brief Unpack Short Sale Restriction message of the NYSE Alerts feed
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
 * @return PDP unpack return code
 ******************************************************************************/
int nyse_alerts_unpack_short_sale_restriction_msg(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_alerts_short_sale_restriction_msg_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p)
{
    if (NULL == in_data_p)
    {
        return PDP_UNPACK_NULL_INPUT_PACKET_PTR;
    }

    if (in_size < NYSE_ALERTS_SHORT_SALE_RESTRICTION_MSG_SIZE)
    {
        return PDP_UNPACK_INPUT_PACKET_TOO_SHORT;
    }

    if (out_offset_p != NULL)
    {
        *out_offset_p = NYSE_ALERTS_SHORT_SALE_RESTRICTION_MSG_SIZE;
    }
    if (out_body_p != NULL)
    {
        *out_body_p = *((nyse_alerts_short_sale_restriction_msg_t *)in_data_p);

        out_body_p->source_time =               be32toh(out_body_p->source_time);
        out_body_p->short_sale_trigger_time =   be32toh(out_body_p->short_sale_trigger_time);
        out_body_p->trade_price =               be32toh(out_body_p->trade_price);
        out_body_p->trade_volume =              be32toh(out_body_p->trade_volume);
    }

    return PDP_UNPACK_SUCCESS;
}

/*******************************************************************************
 * @brief Unpack RPI message of the NYSE Alerts feed
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
 * @return PDP unpack return code
 ******************************************************************************/
int nyse_alerts_unpack_rpi_msg(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_alerts_rpi_msg_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p)
{
    if (NULL == in_data_p)
    {
        return PDP_UNPACK_NULL_INPUT_PACKET_PTR;
    }

    if (in_size < NYSE_ALERTS_RPI_MSG_SIZE)
    {
        return PDP_UNPACK_INPUT_PACKET_TOO_SHORT;
    }

    if (out_offset_p != NULL)
    {
        *out_offset_p = NYSE_ALERTS_RPI_MSG_SIZE;
    }
    if (out_body_p != NULL)
    {
        *out_body_p = *((nyse_alerts_rpi_msg_t *)in_data_p);

        out_body_p->source_time =               be32toh(out_body_p->source_time);
    }

    return PDP_UNPACK_SUCCESS;
}
