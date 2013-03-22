/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: nyse_bbo_unpack.h
 *
 * Description:
 *      NYSE BBO unpack interface
 *
 * Authors:
 *          Wojciech Migda (wm)
 *
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-21   wm              Initial version
 *
 ******************************************************************************/


#ifndef NYSE_BBO_UNPACK_H_
#define NYSE_BBO_UNPACK_H_

#include <stdint.h>
#include <stddef.h>

#include "compiler.h"
#include "nyse_bbo_pdp_header.h"
#include "nyse_bbo_quote.h"

#ifdef __cplusplus
extern "C"
{
#endif

int nyse_bbo_unpack_pdp_header(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_bbo_pdp_header_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p);

int nyse_bbo_unpack_quote_msg(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_bbo_quote_msg_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p);

#ifdef __cplusplus
} // extern C
#endif

#endif /* NYSE_BBO_UNPACK_H_ */
