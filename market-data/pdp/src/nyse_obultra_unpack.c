/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: nyse_obultra_unpack.c
 *
 * Description:
 *      NYSE OpenBook Ultra feed unpacking implementations
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

#include <stdint.h>
#include <stddef.h>
#include <endian.h>
#include <string.h>

#include "compiler.h"
#include "static_assert.h"
#include "unpack_status.h"
#include "nyse_obultra_pdp_header.h"
#include "nyse_obultra_full_update.h"
#include "nyse_obultra_delta_update.h"

/*******************************************************************************
 * @brief Unpack general PDP header of the NYSE OpenBook Ultra feed
 *******************************************************************************
 * Endianness of the unpacked data is that of the host.
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-24   wm              Initial version
 *
 *******************************************************************************
 * @param in_data_p pointer to the input packet
 * @param in_size number of octets in the input packet
 * @param out_body_p pointer to the header where the packet will be unpacked
 * @param out_offset_p pointer to the output variable where the amount of
 *        unpacked octets will be stored
 * @return PDP unpack return code
 ******************************************************************************/
int nyse_obultra_unpack_pdp_header(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_obultra_pdp_header_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p)
{
#define __STRUCT_FILE "nyse_obultra_pdp_header.i"
#define __STRUCT_SIZE NYSE_OBULTRA_PDP_HEADER_SIZE

#include "unpack_generic.i"
}

/*******************************************************************************
 * @brief Unpack single pricepoint element of the Full Update message
 *******************************************************************************
 * Endianness of the unpacked data is that of the host.
 * Since this is internal stuff we assume all input pointer are non-null and
 * there's enough data for reading and writting.
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-25   wm              Initial version
 *
 *******************************************************************************
 * @param in_data_p pointer to the input packet
 * @param out_body_p pointer to the data body where the packet will be unpacked
 ******************************************************************************/
static inline
void nyse_obultra_unpack_full_update_price_point(
    const uint8_t * RESTRICT in_data_p,
    nyse_obultra_full_update_price_point_t * const RESTRICT out_body_p)
{
    #define __STRUCT_FILE "nyse_obultra_full_update_price_point.i"
    #define __STRUCT_SIZE NYSE_OBULTRA_FULL_UPDATE_PRICE_POINT_SIZE

    #include "unpack_struct.i"
}

/*******************************************************************************
 * @brief Unpack Full Update message of the NYSE OpenBook Ultra feed
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
int nyse_obultra_unpack_full_update_msg(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_obultra_full_update_msg_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p)
{
    /* due to presence of optional elements (price_points) we need to execute
     * unpacking giving up use of our fully-fledged unpacker template ;)
     * We will resort to the simplest unpacking template for the bare data
     * stuff, though. */

    if (NULL == in_data_p)
    {
        return PDP_UNPACK_NULL_INPUT_PACKET_PTR;
    }

    /* absolute required minimum */
    if (in_size < NYSE_OBULTRA_FULL_UPDATE_FIXED_MSG_SIZE)
    {
        return PDP_UNPACK_INPUT_PACKET_TOO_SHORT;
    }
    else
    {
        uint16_t    msg_size = be16toh(*(uint16_t *)in_data_p);

        /* minimum based on message contents */
        if (in_size < msg_size)
        {
            return PDP_UNPACK_INPUT_PACKET_TOO_SHORT;
        }
    }

    if (out_body_p != NULL)
    {
        size_t      idx;

        #define __STRUCT_FILE "nyse_obultra_full_update_fixed.i"
        #define __STRUCT_SIZE NYSE_OBULTRA_FULL_UPDATE_FIXED_MSG_SIZE
        #include "unpack_struct.i"

        out_body_p->num_price_points =
            (out_body_p->msg_size - NYSE_OBULTRA_FULL_UPDATE_FIXED_MSG_SIZE) / NYSE_OBULTRA_FULL_UPDATE_PRICE_POINT_SIZE;

        for (idx = 0; idx < out_body_p->num_price_points; ++idx)
        {
            nyse_obultra_unpack_full_update_price_point(
                &in_data_p[NYSE_OBULTRA_FULL_UPDATE_FIXED_MSG_SIZE + NYSE_OBULTRA_FULL_UPDATE_PRICE_POINT_SIZE * idx],
                &out_body_p->price_points[idx]);
        }
    }
    if (out_offset_p != NULL)
    {
        *out_offset_p = out_body_p->msg_size;
    }

    return PDP_UNPACK_SUCCESS;
}

/*******************************************************************************
 * @brief Unpack single pricepoint element of the Delta Update message
 *******************************************************************************
 * Endianness of the unpacked data is that of the host.
 * Since this is internal stuff we assume all input pointer are non-null and
 * there's enough data for reading and writting.
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-25   wm              Initial version
 *
 *******************************************************************************
 * @param in_data_p pointer to the input packet
 * @param out_body_p pointer to the data body where the packet will be unpacked
 ******************************************************************************/
static inline
void nyse_obultra_unpack_delta_update_price_point(
    const uint8_t * RESTRICT in_data_p,
    nyse_obultra_delta_update_price_point_t * const RESTRICT out_body_p)
{
    #define __STRUCT_FILE "nyse_obultra_delta_update_price_point.i"
    #define __STRUCT_SIZE NYSE_OBULTRA_DELTA_UPDATE_PRICE_POINT_SIZE

    #include "unpack_struct.i"
}

/*******************************************************************************
 * @brief Unpack Delta Update message of the NYSE OpenBook Ultra feed
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
int nyse_obultra_unpack_delta_update_msg(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_obultra_delta_update_msg_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p)
{
    /* due to presence of optional elements (price_points) we need to execute
     * unpacking giving up use of our fully-fledged unpacker template ;)
     * We will resort to the simplest unpacking template for the bare data
     * stuff, though. */

    if (NULL == in_data_p)
    {
        return PDP_UNPACK_NULL_INPUT_PACKET_PTR;
    }

    /* absolute required minimum */
    if (in_size < NYSE_OBULTRA_FULL_UPDATE_FIXED_MSG_SIZE)
    {
        return PDP_UNPACK_INPUT_PACKET_TOO_SHORT;
    }
    else
    {
        uint16_t    msg_size = be16toh(*(uint16_t *)in_data_p);

        /* minimum based on message contents */
        if (in_size < msg_size)
        {
            return PDP_UNPACK_INPUT_PACKET_TOO_SHORT;
        }
    }

    if (out_body_p != NULL)
    {
        size_t      idx;

        #define __STRUCT_FILE "nyse_obultra_delta_update_fixed.i"
        #define __STRUCT_SIZE NYSE_OBULTRA_DELTA_UPDATE_FIXED_MSG_SIZE
        #include "unpack_struct.i"

        out_body_p->num_price_points =
            (out_body_p->msg_size - NYSE_OBULTRA_DELTA_UPDATE_FIXED_MSG_SIZE) / NYSE_OBULTRA_DELTA_UPDATE_PRICE_POINT_SIZE;

        for (idx = 0; idx < out_body_p->num_price_points; ++idx)
        {
            nyse_obultra_unpack_delta_update_price_point(
                &in_data_p[NYSE_OBULTRA_DELTA_UPDATE_FIXED_MSG_SIZE + NYSE_OBULTRA_DELTA_UPDATE_PRICE_POINT_SIZE * idx],
                &out_body_p->price_points[idx]);
        }
    }
    if (out_offset_p != NULL)
    {
        *out_offset_p = out_body_p->msg_size;
    }

    return PDP_UNPACK_SUCCESS;
}
