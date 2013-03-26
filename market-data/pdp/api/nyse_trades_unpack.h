/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: nyse_trades_unpack.h
 *
 * Description:
 *      NYSE Trades feed unpacking interface
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


#ifndef NYSE_TRADES_UNPACK_H_
#define NYSE_TRADES_UNPACK_H_

#include <stdint.h>
#include <stddef.h>

#include "compiler.h"
#include "nyse_trades_pdp_header.h"
#include "nyse_trades_trade.h"
#include "nyse_trades_trade_cancel_or_error.h"
#include "nyse_trades_trade_correction.h"

#ifdef __cplusplus
extern "C"
{
#endif

int nyse_trades_unpack_pdp_header(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_trades_pdp_header_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p);

int nyse_trades_unpack_trade_msg(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_trades_trade_msg_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p);

int nyse_trades_unpack_trade_cancel_or_error_msg(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_trades_trade_cancel_or_error_msg_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p);

int nyse_trades_unpack_trade_correction_msg(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_trades_trade_correction_msg_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p);

#ifdef __cplusplus
} // extern C
#endif

#endif /* NYSE_TRADES_UNPACK_H_ */
