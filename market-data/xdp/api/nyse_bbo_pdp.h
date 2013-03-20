/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: nyse_bbo_pdp.h
 *
 * Description:
 *      NYSE BBO PDP header unpacking interface
 *
 *      References:
 *      [1] NYSE BEST BID AND OFFER (BBO) CLIENT SPECIFICATION,
 *          Version 1.9, 2012-09-03,
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
 * 2013-03-19   wm              Initial version
 *
 ******************************************************************************/

#ifndef NYSE_BBO_PDP_H_
#define NYSE_BBO_PDP_H_

#include <stdint.h>
#include "static_assert.h"
#include "compiler.h"

#ifdef __cplusplus
extern "C"
{
#endif

enum nyse_bbo_message_type_values
{
    NYSE_BBO_MSG_QUOTE_MSG      = 140,
};

typedef struct PACKED
{
    uint16_t        msg_size;
    uint16_t        msg_type;
    uint32_t        msg_seq_num;
    uint32_t        send_time;
    uint8_t         product_id;
    uint8_t         retrans_flag;
    uint8_t         num_body_entries;
    char            filler[1];
} nyse_bbo_pdp_header_t;

STATIC_ASSERT(sizeof (nyse_bbo_pdp_header_t) == 16);

#ifdef __cplusplus
} // extern C
#endif

#endif /* NYSE_BBO_PDP_H_ */
