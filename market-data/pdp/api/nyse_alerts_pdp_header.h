/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 * Filename: nyse_alerts_pdp_header.h
 *
 * Description:
 *      NYSE Alerts PDP header definitions
 *
 *      References:
 *      [1] NYSE ALERTS CLIENT SPECIFICATION, Version 2.12, 2013-01-24
 *          Section 4.7
 *
 * Authors:
 *          Wojciech Migda (wm)
 *
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-18   wm              Initial version
 *
 ******************************************************************************/

#ifndef NYSE_ALERTS_PDP_HEADER_H_
#define NYSE_ALERTS_PDP_HEADER_H_

#include <stdint.h>
#include "static_assert.h"

#ifdef __cplusplus
extern "C"
{
#endif

enum nyse_alerts_message_type_values
{
    NYSE_ALERTS_MSG_SECURITY_INFO            = 36,
    NYSE_ALERTS_MSG_MARKET_IMBALANCE         = 120,
    NYSE_ALERTS_MSG_DELAY_HALTS              = 121,
    NYSE_ALERTS_MSG_INDICATION               = 122,
    NYSE_ALERTS_MSG_T_TIME                   = 123,
    NYSE_ALERTS_MSG_CIRCUIT_BREAKER          = 124,
    NYSE_ALERTS_MSG_SHORT_SALE_RESTRICTION   = 125,
    NYSE_ALERTS_MSG_RPI                      = 126,
};

enum { NYSE_ALERTS_PDP_HEADER_SIZE = 16 };

typedef struct
{
    uint16_t        msg_size;
    uint16_t        msg_type;
    uint32_t        msg_seq_num;
    uint32_t        send_time;
    uint8_t         product_id;
    uint8_t         retrans_flag;
    uint8_t         num_body_entries;
    uint8_t         filler;
} nyse_alerts_pdp_header_t;

#ifdef __cplusplus
} // extern C
#endif

#endif /* NYSE_ALERTS_PDP_HEADER_H_ */
