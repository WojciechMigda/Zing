/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: nyse_lrp_unpack.h
 *
 * Description:
 *      NYSE LRP unpack interface
 *
 * Authors:
 *          Wojciech Migda (wm)
 *
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-22   wm              Initial version
 *
 ******************************************************************************/


#ifndef NYSE_LRP_UNPACK_H_
#define NYSE_LRP_UNPACK_H_

#include <stdint.h>
#include <stddef.h>

#include "compiler.h"
#include "nyse_lrp_pdp_header.h"
#include "nyse_lrp_lrp_message.h"

#ifdef __cplusplus
extern "C"
{
#endif

int nyse_lrp_unpack_pdp_header(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_lrp_pdp_header_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p);

int nyse_lrp_unpack_lrp_msg(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_lrp_lrp_msg_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p);

#ifdef __cplusplus
} // extern C
#endif

#endif /* NYSE_LRP_UNPACK_H_ */
