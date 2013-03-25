/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: nyse_retrac_unpack.h
 *
 * Description:
 *      NYSE ReTrac feed unpacking interface
 *
 * Authors:
 *          Wojciech Migda (wm)
 *
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-25   wm              Initial version
 *
 ******************************************************************************/


#ifndef NYSE_RETRAC_UNPACK_H_
#define NYSE_RETRAC_UNPACK_H_

#include <stdint.h>
#include <stddef.h>

#include "compiler.h"
#include "nyse_retrac_pdp_header.h"
#include "nyse_retrac_execution_report.h"
#include "nyse_retrac_execution_report_cancellation.h"
#include "nyse_retrac_summary.h"

#ifdef __cplusplus
extern "C"
{
#endif

int nyse_retrac_unpack_pdp_header(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_retrac_pdp_header_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p);

int nyse_retrac_unpack_execution_report_msg(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_retrac_execution_report_msg_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p);

int nyse_retrac_unpack_execution_report_cancellation_msg(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_retrac_execution_report_cancellation_msg_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p);

int nyse_retrac_unpack_summary_msg(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_retrac_summary_msg_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p);

#ifdef __cplusplus
} // extern C
#endif

#endif /* NYSE_RETRAC_UNPACK_H_ */
