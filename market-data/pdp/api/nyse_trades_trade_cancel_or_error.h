/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: nyse_trades_trade_cancel_or_error.h
 *
 * Description:
 *      NYSE Trades feed Trade Cancel or Error message definitions
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

#ifndef NYSE_TRADES_TRADE_CANCEL_OR_ERROR_H_
#define NYSE_TRADES_TRADE_CANCEL_OR_ERROR_H_

#include <stdint.h>
#include "pdp_symbol.h"

#ifdef __cplusplus
extern "C"
{
#endif

enum { NYSE_TRADES_TRADE_CANCEL_OR_ERROR_MSG_SIZE = 32 };

typedef struct
{
    uint32_t        source_time;
    uint32_t        source_seq_num;
    uint32_t        original_trade_ref_num;
    uint8_t         source_session_id;
    char            exchange_id;
    char            security_type;
    char            filler[1];
    char            symbol[NYSE_SYMBOL_LEN];
} nyse_trades_trade_cancel_or_error_msg_t;

#ifdef __cplusplus
} // extern C
#endif

#endif /* NYSE_TRADES_TRADE_CANCEL_OR_ERROR_H_ */
