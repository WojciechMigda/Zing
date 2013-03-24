/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: nyse_obultra_full_update.h
 *
 * Description:
 *      NYSE OpenBook Ultra Full Update message definitions
 *
 *      References:
 *      [1] NYSE OPENBOOK ULTRA CLIENT SPECIFICATION, Version 1.8, 2012-09-03
 *          Section 4.9
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


#ifndef NYSE_OBULTRA_FULL_UPDATE_H_
#define NYSE_OBULTRA_FULL_UPDATE_H_

#include <stdint.h>

#include "pdp_symbol.h"

#ifdef __cplusplus
extern "C"
{
#endif

enum
{
    NYSE_OBULTRA_FULL_UPDATE_FIXED_MSG_SIZE     = 32,
    NYSE_OBULTRA_FULL_UPDATE_PRICE_POINT_SIZE   = 12,
};

enum
{
    MAX_NUM_PRICE_POINTS_FULL_UPDATE =
        (1500 - NYSE_OBULTRA_FULL_UPDATE_FIXED_MSG_SIZE + NYSE_OBULTRA_FULL_UPDATE_PRICE_POINT_SIZE - 1) / NYSE_OBULTRA_FULL_UPDATE_PRICE_POINT_SIZE,
};

typedef struct
{
    uint32_t        price_numerator;
    uint32_t        volume;
    uint16_t        num_orders;
    char            side;
    uint8_t         filler;
} nyse_obultra_full_update_price_point_t;

typedef struct
{
    uint16_t        msg_size;
    uint16_t        security_index;
    uint32_t        source_time;
    uint16_t        source_time_ms;
    uint32_t        symbol_seq_num;
    uint8_t         source_session_id;
    char            symbol[NYSE_SHORT_SYMBOL_LEN];
    uint8_t         price_scale_code;
    char            quote_condition;
    char            trading_status;
    uint8_t         filler;
    uint16_t        mpv;

    size_t          num_price_points;
    nyse_obultra_full_update_price_point_t
                    price_points[MAX_NUM_PRICE_POINTS_FULL_UPDATE];
} nyse_obultra_full_update_msg_t;

#ifdef __cplusplus
} // extern C
#endif

#endif /* NYSE_OBULTRA_FULL_UPDATE_H_ */
