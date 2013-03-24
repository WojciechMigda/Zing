/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: nyse_obultra_delta_update.h
 *
 * Description:
 *      NYSE OpenBook Ultra Delta Update message definitions
 *
 *      References:
 *      [1] NYSE OPENBOOK ULTRA CLIENT SPECIFICATION, Version 1.8, 2012-09-03
 *          Section 4.10
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


#ifndef NYSE_OBULTRA_DELTA_UPDATE_H_
#define NYSE_OBULTRA_DELTA_UPDATE_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

enum
{
    NYSE_OBULTRA_DELTA_UPDATE_FIXED_MSG_SIZE    = 18,
    NYSE_OBULTRA_DELTA_UPDATE_PRICE_POINT_SIZE  = 28,
};

enum
{
    MAX_NUM_PRICE_POINTS_DELTA_UPDATE =
        (1500 - NYSE_OBULTRA_DELTA_UPDATE_FIXED_MSG_SIZE + NYSE_OBULTRA_DELTA_UPDATE_PRICE_POINT_SIZE - 1) / NYSE_OBULTRA_DELTA_UPDATE_PRICE_POINT_SIZE,
};

enum reason_code_values
{
    REASON_NEW_ORDER_ADDITIONAL_INTEREST        = 'O',
    REASON_CANCEL                               = 'C',
    REASON_EXECUTION                            = 'E',
    REASON_MULTIPLE_EVENTS                      = 'X',
};

typedef struct
{
    uint32_t        price_numerator;
    uint32_t        volume;
    uint32_t        chg_qty;
    uint16_t        num_orders;
    char            side;
    char            reason_code;
    uint32_t        link_id_1;
    uint32_t        link_id_2;
    uint32_t        link_id_3;
} nyse_obultra_delta_update_price_point_t;

typedef struct
{
    uint16_t        msg_size;
    uint16_t        security_index;
    uint32_t        source_time;
    uint16_t        source_time_ms;
    uint32_t        symbol_seq_num;
    uint8_t         source_session_id;
    char            quote_condition;
    char            trading_status;
    uint8_t         price_scale_code;

    size_t          num_price_points;
    nyse_obultra_delta_update_price_point_t
                    price_points[MAX_NUM_PRICE_POINTS_DELTA_UPDATE];
} nyse_obultra_delta_update_msg_t;

#ifdef __cplusplus
} // extern C
#endif

#endif /* NYSE_OBULTRA_DELTA_UPDATE_H_ */
