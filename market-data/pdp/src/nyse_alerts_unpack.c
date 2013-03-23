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
#include "nyse_alerts_security_info.h"
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
#include "nyse_alerts_delay_halts.h"
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
#define __STRUCT_FILE "nyse_alerts_delay_halts_msg.i"
#define __STRUCT_SIZE NYSE_ALERTS_DELAY_HALTS_MSG_SIZE

#include "unpack_generic.i"
#include "nyse_alerts_indication.h"
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
#define __STRUCT_FILE "nyse_alerts_indication_msg.i"
#define __STRUCT_SIZE NYSE_ALERTS_INDICATION_MSG_SIZE

#include "unpack_generic.i"
#include "nyse_alerts_t_time.h"
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
#define __STRUCT_FILE "nyse_alerts_t_time_msg.i"
#define __STRUCT_SIZE NYSE_ALERTS_T_TIME_MSG_SIZE

#include "unpack_generic.i"
#include "nyse_alerts_circuit_breaker.h"
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
#define __STRUCT_FILE "nyse_alerts_circuit_breaker_msg.i"
#define __STRUCT_SIZE NYSE_ALERTS_CIRCUIT_BREAKER_MSG_SIZE

#include "unpack_generic.i"
#include "nyse_alerts_short_sale_restriction.h"
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
#define __STRUCT_FILE "nyse_alerts_short_sale_restriction_msg.i"
#define __STRUCT_SIZE NYSE_ALERTS_SHORT_SALE_RESTRICTION_MSG_SIZE

#include "unpack_generic.i"
#include "nyse_alerts_rpi.h"
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
#define __STRUCT_FILE "nyse_alerts_rpi_msg.i"
#define __STRUCT_SIZE NYSE_ALERTS_RPI_MSG_SIZE

#include "unpack_generic.i"
}
