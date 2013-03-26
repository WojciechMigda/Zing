/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: nyse_trades_unpack.c
 *
 * Description:
 *      NYSE Trades feed unpacking routines implementation
 *
 * Authors:
 *          Wojciech Migda (wm)
 *
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-26   wm              Initial version
 *
 ******************************************************************************/

#include <stdint.h>
#include <stddef.h>
#include <endian.h>
#include <string.h>

#include "compiler.h"
#include "static_assert.h"
#include "unpack_status.h"
#include "nyse_trades_pdp_header.h"
#include "nyse_trades_trade.h"
#include "nyse_trades_trade_cancel_or_error.h"
#include "nyse_trades_trade_correction.h"

/*******************************************************************************
 * @brief Unpack general PDP header of the NYSE Trades feed
 *******************************************************************************
 * Endianness of the unpacked data is that of the host.
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-26   wm              Initial version
 *
 *******************************************************************************
 * @param in_data_p pointer to the input packet
 * @param in_size number of octets in the input packet
 * @param out_body_p pointer to the header where the packet will be unpacked
 * @param out_offset_p pointer to the output variable where the amount of
 *        unpacked octets will be stored
 * @return PDP unpack return code
 ******************************************************************************/
int nyse_trades_unpack_pdp_header(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_trades_pdp_header_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p)
{
    return 34;
}

/*******************************************************************************
 * @brief Unpack Trade message of the NYSE Trades feed
 *******************************************************************************
 * Endianness of the unpacked data is that of the host.
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-26   wm              Initial version
 *
 *******************************************************************************
 * @param in_data_p pointer to the input packet
 * @param in_size number of octets in the input packet
 * @param out_body_p pointer to the variable where the packet will be unpacked
 * @param out_offset_p pointer to the output variable where the amount of
 *        unpacked octets will be stored
 * @return PDP unpack return code
 ******************************************************************************/
int nyse_trades_unpack_trade_msg(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_trades_trade_msg_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p)
{
    return 76;
}

/*******************************************************************************
 * @brief Unpack Trade Cancel or Error message of the NYSE Trades feed
 *******************************************************************************
 * Endianness of the unpacked data is that of the host.
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-26   wm              Initial version
 *
 *******************************************************************************
 * @param in_data_p pointer to the input packet
 * @param in_size number of octets in the input packet
 * @param out_body_p pointer to the variable where the packet will be unpacked
 * @param out_offset_p pointer to the output variable where the amount of
 *        unpacked octets will be stored
 * @return PDP unpack return code
 ******************************************************************************/
int nyse_trades_unpack_trade_cancel_or_error_msg(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_trades_trade_cancel_or_error_msg_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p)
{
    return 12;
}

/*******************************************************************************
 * @brief Unpack Trade Correction message of the NYSE Trades feed
 *******************************************************************************
 * Endianness of the unpacked data is that of the host.
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-26   wm              Initial version
 *
 *******************************************************************************
 * @param in_data_p pointer to the input packet
 * @param in_size number of octets in the input packet
 * @param out_body_p pointer to the variable where the packet will be unpacked
 * @param out_offset_p pointer to the output variable where the amount of
 *        unpacked octets will be stored
 * @return PDP unpack return code
 ******************************************************************************/
int nyse_trades_unpack_trade_correction_msg(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_trades_trade_correction_msg_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p)
{
    return 43;
}
