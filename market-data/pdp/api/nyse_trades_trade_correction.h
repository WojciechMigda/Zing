/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: nyse_trades_trade_correction.h
 *
 * Description:
 *      NYSE Trades feed Trade Correction message definitions
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

#ifndef NYSE_TRADES_TRADE_CORRECTION_H_
#define NYSE_TRADES_TRADE_CORRECTION_H_

#include <stdint.h>
#include "pdp_symbol.h"

#ifdef __cplusplus
extern "C"
{
#endif

enum { NYSE_TRADES_TRADE_CORRECTION_MSG_SIZE = 52 };

typedef struct
{
    uint32_t        source_time;
    uint32_t        filler1;
    uint32_t        filler2;
    uint32_t        price_numerator;
    uint32_t        volume;
    uint32_t        source_seq_num;
    uint32_t        original_trade_ref_num;
    uint8_t         source_session_id;
    uint8_t         price_scale_code;
    char            exchange_id;
    char            security_type;
    char            corrected_trade_cond_1;
    char            corrected_trade_cond_2;
    char            corrected_trade_cond_3;
    char            corrected_trade_cond_4;
    char            symbol[NYSE_SYMBOL_LEN];
} nyse_trades_trade_correction_msg_t;

#ifdef __cplusplus
} // extern C
#endif

#endif /* NYSE_TRADES_TRADE_CORRECTION_H_ */
