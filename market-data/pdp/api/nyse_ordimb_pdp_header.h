/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 * Filename: nyse_ordimb_pdp_header.h
 *
 * Description:
 *      NYSE Oeder Imbalances PDP header definitions
 *
 *      References:
 *      [1] NYSE ORDER IMBALANCES CLIENT SPECIFICATION, Version 1.12, 2012-11-09
 *          Section 4.8
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

#ifndef NYSE_ORDIMB_PDP_HEADER_H_
#define NYSE_ORDIMB_PDP_HEADER_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

enum nyse_ordimb_message_type_values
{
    NYSE_ORDIMB_MSG_OPENING_IMBALANCE       = 240,
    NYSE_ORDIMB_MSG_CLOSING_IMBALANCE       = 241,
};

enum { NYSE_ORDIMB_PDP_HEADER_SIZE = 16 };

typedef struct
{
    uint16_t        msg_size;
    uint16_t        msg_type;
    uint32_t        msg_seq_num;
    uint32_t        send_time;
    uint8_t         product_id;
    uint8_t         retrans_flag;
    uint8_t         num_body_entries;
    uint8_t         link_flag;
} nyse_ordimb_pdp_header_t;

#ifdef __cplusplus
} // extern C
#endif

#endif /* NYSE_ORDIMB_PDP_HEADER_H_ */
