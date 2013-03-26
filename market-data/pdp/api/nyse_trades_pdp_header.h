/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: nyse_trades_pdp_header.h
 *
 * Description:
 *      NYSE Trades PDP header definitions
 *
 *      References:
 *      [1] NYSE TRADES – QUICK REFERENCE CARD, 2012-08-10
 *
 * Authors:
 *          Wojciech Migda (wm)
 *
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-26   wm              Initial version
 *
 ******************************************************************************/


#ifndef NYSE_TRADES_PDP_HEADER_H_
#define NYSE_TRADES_PDP_HEADER_H_

#ifdef __cplusplus
extern "C"
{
#endif

enum nyse_trades_message_type_values
{
    NYSE_TRADES_MSG_TRADE                   = 220,
    NYSE_TRADES_MSG_TRADE_CANCEL_OR_ERROR   = 221,
    NYSE_TRADES_MSG_TRADE_CORRECTION        = 222,
};

enum { NYSE_TRADES_PDP_HEADER_SIZE = 16 };

typedef struct
{
    uint16_t        msg_size;
    uint16_t        msg_type;
    uint32_t        msg_seq_num;
    uint32_t        send_time;
    uint8_t         product_id;
    uint8_t         retrans_flag;
    uint8_t         num_body_entries;
    char            FILLER[1];
} nyse_trades_pdp_header_t;

#ifdef __cplusplus
} // extern C
#endif

#endif /* NYSE_TRADES_PDP_HEADER_H_ */
