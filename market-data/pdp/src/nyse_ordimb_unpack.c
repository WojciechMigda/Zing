/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: nyse_ordimb_unpack.c
 *
 * Description:
 *      NYSE Order Imbalances feed unpacking implementations
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

#include <stdint.h>
#include <stddef.h>
#include <endian.h>
#include <string.h>

#include "compiler.h"
#include "static_assert.h"
#include "unpack_status.h"
#include "nyse_ordimb_pdp_header.h"
#include "nyse_ordimb_opening_imbalance_msg.h"
#include "nyse_ordimb_closing_imbalance_msg.h"

/*******************************************************************************
 * @brief Unpack general PDP header of the NYSE Order Imbalances feed
 *******************************************************************************
 * Endianness of the unpacked data is that of the host.
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-25   wm              Initial version
 *
 *******************************************************************************
 * @param in_data_p pointer to the input packet
 * @param in_size number of octets in the input packet
 * @param out_body_p pointer to the header where the packet will be unpacked
 * @param out_offset_p pointer to the output variable where the amount of
 *        unpacked octets will be stored
 * @return PDP unpack return code
 ******************************************************************************/
int nyse_ordimb_unpack_pdp_header(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_ordimb_pdp_header_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p)
{
#define __STRUCT_FILE "nyse_ordimb_pdp_header.i"
#define __STRUCT_SIZE NYSE_ORDIMB_PDP_HEADER_SIZE

#include "unpack_generic.i"
}

/*******************************************************************************
 * @brief Unpack Opening Imbalance message of the NYSE Order Imbalances feed
 *******************************************************************************
 * Endianness of the unpacked data is that of the host.
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-25   wm              Initial version
 *
 *******************************************************************************
 * @param in_data_p pointer to the input packet
 * @param in_size number of octets in the input packet
 * @param out_body_p pointer to the variable where the packet will be unpacked
 * @param out_offset_p pointer to the output variable where the amount of
 *        unpacked octets will be stored
 * @return PDP unpack return code
 ******************************************************************************/
int nyse_ordimb_unpack_opening_imbalance_msg(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_ordimb_opening_imb_msg_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p)
{
#define __STRUCT_FILE "nyse_ordimb_opening_imb_msg.i"
#define __STRUCT_SIZE NYSE_ORDIMB_OPENING_IMBALANCE_MSG_SIZE

#include "unpack_generic.i"
}

/*******************************************************************************
 * @brief Unpack Closing Imbalance message of the NYSE Order Imbalances feed
 *******************************************************************************
 * Endianness of the unpacked data is that of the host.
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-25   wm              Initial version
 *
 *******************************************************************************
 * @param in_data_p pointer to the input packet
 * @param in_size number of octets in the input packet
 * @param out_body_p pointer to the variable where the packet will be unpacked
 * @param out_offset_p pointer to the output variable where the amount of
 *        unpacked octets will be stored
 * @return PDP unpack return code
 ******************************************************************************/
int nyse_ordimb_unpack_closing_imbalance_msg(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_ordimb_closing_imb_msg_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p)
{
#define __STRUCT_FILE "nyse_ordimb_closing_imb_msg.i"
#define __STRUCT_SIZE NYSE_ORDIMB_CLOSING_IMBALANCE_MSG_SIZE

#include "unpack_generic.i"
}
