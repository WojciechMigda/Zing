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
    uint16_t        msg_size;
    uint16_t        msg_type;
    uint32_t        msg_seq_num;
    uint32_t        send_time;
    uint8_t         product_id;
    uint8_t         retrans_flag;
    uint8_t         num_body_entries;
    uint8_t         filler;
} header_packed_t;
STATIC_ASSERT(sizeof (header_packed_t) == NYSE_ALERTS_PDP_HEADER_SIZE);

typedef struct PACKED
{
    uint32_t        source_time;
    char            symbol[NYSE_ALERTS_SYMBOL_LEN];
    uint8_t         security_type;
    uint16_t        filler;
    uint16_t        mpv;
    uint8_t         post;
    char            panel[PANEL_LEN];
    char            ticker_designation;
    char            ipo_flag;
    char            country_code[COUNTRY_CODE_LEN];
    uint16_t        uot;
    uint8_t         price_scale_code;
    uint8_t         lrp_price_scale_code;
    uint16_t        lrp;
    char            bankruptcy_flag;
    uint8_t         financial_status;
    char            ex_distribution_flag;
    char            ex_rights_flag;
    char            ex_dividend_flag;
    uint8_t         ex_div_amount_price_scale_code;
    uint32_t        ex_div_amount;
    char            ex_div_date[EX_DIVIDEND_DATE_LEN];
    char            special_div_flag;
    char            stock_splt;
    char            rule_19C3;
    char            its_eligible;
} security_info_msg_packed_t;
STATIC_ASSERT(sizeof (security_info_msg_packed_t) == NYSE_ALERTS_SECURITY_INFO_MSG_SIZE);

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
    if (NULL == in_data_p)
    {
        return PDP_UNPACK_NULL_INPUT_PACKET_PTR;
    }

    if (in_size < NYSE_ALERTS_PDP_HEADER_SIZE)
    {
        return PDP_UNPACK_INPUT_PACKET_TOO_SHORT;
    }

    if (out_offset_p != NULL)
    {
        *out_offset_p = NYSE_ALERTS_PDP_HEADER_SIZE;
    }
    if (out_body_p != NULL)
    {
        header_packed_t const * const in_hdr_p = (header_packed_t const * const)in_data_p;

        out_body_p->msg_size            = be16toh(in_hdr_p->msg_size);
        out_body_p->msg_type            = be16toh(in_hdr_p->msg_type);
        out_body_p->msg_seq_num         = be32toh(in_hdr_p->msg_seq_num);
        out_body_p->send_time           = be32toh(in_hdr_p->send_time);
        out_body_p->product_id          = in_hdr_p->product_id;
        out_body_p->retrans_flag        = in_hdr_p->retrans_flag;
        out_body_p->num_body_entries    = in_hdr_p->num_body_entries;
    }

    return PDP_UNPACK_SUCCESS;
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
    if (NULL == in_data_p)
    {
        return PDP_UNPACK_NULL_INPUT_PACKET_PTR;
    }

    if (in_size < NYSE_ALERTS_SECURITY_INFO_MSG_SIZE)
    {
        return PDP_UNPACK_INPUT_PACKET_TOO_SHORT;
    }

    if (out_offset_p != NULL)
    {
        *out_offset_p = NYSE_ALERTS_SECURITY_INFO_MSG_SIZE;
    }
    if (out_body_p != NULL)
    {
        security_info_msg_packed_t const * const in_hdr_p = (security_info_msg_packed_t const * const)in_data_p;

        out_body_p->source_time                     = be32toh(in_hdr_p->source_time);
        memcpy(out_body_p->symbol, in_hdr_p->symbol, sizeof (out_body_p->symbol));
        out_body_p->security_type                   = in_hdr_p->security_type;
        out_body_p->mpv                             = be16toh(in_hdr_p->mpv);
        out_body_p->post                            = in_hdr_p->post;
        memcpy(out_body_p->panel, in_hdr_p->panel, sizeof (out_body_p->panel));
        out_body_p->ticker_designation              = in_hdr_p->ticker_designation;
        out_body_p->ipo_flag                        = in_hdr_p->ipo_flag;
        memcpy(out_body_p->country_code, in_hdr_p->country_code, sizeof (out_body_p->country_code));
        out_body_p->uot                             = be16toh(in_hdr_p->uot);
        out_body_p->price_scale_code                = in_hdr_p->price_scale_code;
        out_body_p->lrp_price_scale_code            = in_hdr_p->lrp_price_scale_code;
        out_body_p->lrp                             = be16toh(in_hdr_p->lrp);
        out_body_p->bankruptcy_flag                 = in_hdr_p->bankruptcy_flag;
        out_body_p->financial_status                = in_hdr_p->financial_status;
        out_body_p->ex_distribution_flag            = in_hdr_p->ex_distribution_flag;
        out_body_p->ex_rights_flag                  = in_hdr_p->ex_rights_flag;
        out_body_p->ex_dividend_flag                = in_hdr_p->ex_dividend_flag;
        out_body_p->ex_div_amount_price_scale_code  = in_hdr_p->ex_div_amount_price_scale_code;
        out_body_p->ex_div_amount                   = be32toh(in_hdr_p->ex_div_amount);
        memcpy(out_body_p->ex_div_date, in_hdr_p->ex_div_date, sizeof (out_body_p->ex_div_date));
        out_body_p->special_div_flag                = in_hdr_p->special_div_flag;
        out_body_p->stock_splt                      = in_hdr_p->stock_splt;
        out_body_p->rule_19C3                       = in_hdr_p->rule_19C3;
        out_body_p->its_eligible                    = in_hdr_p->its_eligible;
    }

    return PDP_UNPACK_SUCCESS;
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
    if (NULL == in_data_p)
    {
        return PDP_UNPACK_NULL_INPUT_PACKET_PTR;
    }

    if (in_size < NYSE_ALERTS_MARKET_IMBALANCE_MSG_SIZE)
    {
        return PDP_UNPACK_INPUT_PACKET_TOO_SHORT;
    }

    if (out_offset_p != NULL)
    {
        *out_offset_p = NYSE_ALERTS_MARKET_IMBALANCE_MSG_SIZE;
    }
    if (out_body_p != NULL)
    {
        market_imbalance_msg_packed_t const * const in_hdr_p = (market_imbalance_msg_packed_t const * const)in_data_p;

        out_body_p->source_time             = be32toh(in_hdr_p->source_time);
        memcpy(out_body_p->symbol, in_hdr_p->symbol, sizeof (out_body_p->symbol));
        out_body_p->security_status         = in_hdr_p->security_status;
        out_body_p->imbalance_quantity      = be32toh(in_hdr_p->imbalance_quantity);
        out_body_p->imbalance_side          = in_hdr_p->imbalance_side;
    }

    return PDP_UNPACK_SUCCESS;
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
