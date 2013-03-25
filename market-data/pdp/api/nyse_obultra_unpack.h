/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: nyse_obultra_unpack.h
 *
 * Description:
 *      NYSE OpenBook Ultra feed unpacking interface
 *
 * Authors:
 *          Wojciech Migda (wm)
 *
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-24   wm              Initial version
 *
 ******************************************************************************/


#ifndef NYSE_OBULTRA_UNPACK_H_
#define NYSE_OBULTRA_UNPACK_H_

#include <stdint.h>
#include <stddef.h>

#include "compiler.h"
#include "nyse_obultra_pdp_header.h"
#include "nyse_obultra_full_update.h"
#include "nyse_obultra_delta_update.h"

#ifdef __cplusplus
extern "C"
{
#endif

int nyse_obultra_unpack_pdp_header(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_obultra_pdp_header_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p);

int nyse_obultra_unpack_full_update_msg(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_obultra_full_update_msg_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p);

int nyse_obultra_unpack_delta_update_msg(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_obultra_delta_update_msg_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p);

#ifdef __cplusplus
} // extern C
#endif

#endif /* NYSE_OBULTRA_UNPACK_H_ */
