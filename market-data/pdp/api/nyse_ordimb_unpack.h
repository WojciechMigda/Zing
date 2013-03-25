/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: nyse_ordimb_unpack.h
 *
 * Description:
 *      NYSE Order Imbalances feed unpacking interface
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


#ifndef NYSE_ORDIMB_UNPACK_H_
#define NYSE_ORDIMB_UNPACK_H_

#include <stdint.h>
#include <stddef.h>

#include "compiler.h"
#include "nyse_ordimb_pdp_header.h"
#include "nyse_ordimb_opening_imbalance.h"
#include "nyse_ordimb_closing_imbalance.h"

#ifdef __cplusplus
extern "C"
{
#endif

int nyse_ordimb_unpack_pdp_header(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_ordimb_pdp_header_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p);

int nyse_ordimb_unpack_opening_imbalance_msg(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_ordimb_opening_imb_msg_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p);

int nyse_ordimb_unpack_closing_imbalance_msg(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_ordimb_closing_imb_msg_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p);

#ifdef __cplusplus
} // extern C
#endif

#endif /* NYSE_ORDIMB_UNPACK_H_ */
