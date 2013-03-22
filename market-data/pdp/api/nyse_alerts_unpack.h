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

#include "nyse_alerts_pdp_header.h"
#include "nyse_alerts_security_info.h"
#include "nyse_alerts_market_imbalance.h"
#include "nyse_alerts_delay_halts.h"
#include "nyse_alerts_indication.h"
#include "nyse_alerts_t_time.h"
#include "nyse_alerts_circuit_breaker.h"
#include "nyse_alerts_short_sale_restriction.h"
#include "nyse_alerts_rpi.h"
#include "compiler.h"

#ifdef __cplusplus
extern "C"
{
#endif

int nyse_alerts_unpack_pdp_header(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_alerts_pdp_header_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p);

int nyse_alerts_unpack_security_info_msg(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_alerts_security_info_msg_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p);

int nyse_alerts_unpack_market_imbalance_msg(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_alerts_market_imbalance_msg_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p);

int nyse_alerts_unpack_delay_halts_msg(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_alerts_delay_halts_msg_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p);

int nyse_alerts_unpack_indication_msg(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_alerts_indication_msg_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p);

int nyse_alerts_unpack_t_time_msg(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_alerts_t_time_msg_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p);

int nyse_alerts_unpack_circuit_breaker_msg(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_alerts_circuit_breaker_msg_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p);

int nyse_alerts_unpack_short_sale_restriction_msg(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_alerts_short_sale_restriction_msg_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p);

int nyse_alerts_unpack_rpi_msg(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_alerts_rpi_msg_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p);

#ifdef __cplusplus
} // extern C
#endif

#endif /* NYSE_ALERTS_UNPACK_H_ */
