/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: nyse_bbo_quote.h
 *
 * Description:
 *      NYSE BBO Quote message definitions
 *
 *      References:
 *      [1] NYSE BEST BID AND OFFER (BBO) CLIENT SPECIFICATION,
 *          Version 1.9, 2012-09-03,
 *          Sec. 4.8
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


#ifndef NYSE_BBO_QUOTE_H_
#define NYSE_BBO_QUOTE_H_

#include <stdint.h>
#include "pdp_symbol.h"

#ifdef __cplusplus
extern "C"
{
#endif

enum rpi_interest_values
{
    RPI_INTEREST_NONE                       = ' ',
    RPI_INTEREST_ON_BID_QUOTE               = 'A',
    RPI_INTEREST_ON_OFFER_QUOTE             = 'B',
    RPI_INTEREST_ON_BID_AND_OFFER_QUOTES    = 'C',
};

enum nyse_bbo_security_type_values
{
    SEC_TYPE_EQUITY         = 'E',
};

typedef struct
{
    uint32_t        source_time;
    uint8_t         filler[3];
    char            rpi_interest;
    uint32_t        ask_price_nominator;
    uint32_t        ask_size;
    uint32_t        bid_price_numerator;
    uint32_t        bid_size;
    uint8_t         price_scale_code;
    char            exchange_id;
    char            security_type;
    char            quote_condition;
    char            symbol[NYSE_SYMBOL_LEN];
} nyse_bbo_quote_msg_t;

enum { NYSE_BBO_QUOTE_MSG_SIZE = 44 };

#ifdef __cplusplus
} // extern C
#endif

#endif /* NYSE_BBO_QUOTE_H_ */
