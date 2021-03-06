/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: nyse_lrp_pdp_header.h
 *
 * Description:
 *      NYSE LRP PDP header definitions
 *
 *      References:
 *      [1] NYSE LIQUIDITY REPLENISHMENT POINTS® (LRP),
 *          Version 1.2a, 2012-08-31,
 *          Sec. 4.7
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

#ifndef NYSE_LRP_PDP_HEADER_H_
#define NYSE_LRP_PDP_HEADER_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

enum nyse_lrp_message_type_values
{
    NYSE_LRP_LRP_MSG        = 210,
};

typedef struct
{
    uint16_t        msg_size;
    uint16_t        msg_type;
    uint32_t        msg_seq_num;
    uint32_t        send_time;
    uint8_t         product_id;
    uint8_t         retrans_flag;
    uint8_t         num_body_entries;
    char            filler[1];
} nyse_lrp_pdp_header_t;

enum { NYSE_LRP_PDP_HEADER_SIZE = 16 };

#ifdef __cplusplus
} // extern C
#endif

#endif /* NYSE_LRP_PDP_HEADER_H_ */
