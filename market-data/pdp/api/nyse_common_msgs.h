/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: nyse_common_msgs.h
 *
 * Description:
 *      NYSE Common PDP Messages definitions
 *
 *      References:
 *      [1] NYSE ALERTS CLIENT SPECIFICATION, Version 2.12, 2013-01-24
 *          Appendix A
 *      [2] NYSE BEST BID AND OFFER (BBO) CLIENT SPECIFICATION,
 *          Version 1.9, 2012-09-03, Appendix A
 *      [3] NYSE LIQUIDITY REPLENISHMENT POINTS® (LRP),
 *          Version 1.2a, 2012-08-31, Appendix A
 *
 * Authors:
 *          Wojciech Migda (wm)
 *
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-22   wm              Initial version
 *
 ******************************************************************************/


#ifndef NYSE_COMMON_MSGS_H_
#define NYSE_COMMON_MSGS_H_

#include <stdint.h>

#include "compiler.h"
#include "static_assert.h"
#include "pdp_symbol.h"

#ifdef __cplusplus
extern "C"
{
#endif

enum nyse_common_message_type_values
{
    NYSE_COMMON_SEQUENCE_NUMBER_RESET       = 1,
    NYSE_COMMON_HEARTBEAT                   = 2,
    NYSE_COMMON_MESSAGE_UNAVAILABLE         = 5,
    NYSE_COMMON_RETRANSMISSION_RES          = 10,
    NYSE_COMMON_HEARTBEAT_SUBSCRIPTION      = 19,
    NYSE_COMMON_RETRANSMISSION_REQ          = 20,
    NYSE_COMMON_REFRESH_REQ                 = 22,
    NYSE_COMMON_HEARTBEAT_RES               = 24,
};

/******************************************************************************/

typedef struct PACKED
{
    uint32_t        next_seq_number;
} nyse_common_sequence_number_reset_msg_t;

enum { NYSE_COMMON_SEQUENCE_NUMBER_RESET_MSG_SIZE = 4 };

STATIC_ASSERT(sizeof (nyse_common_sequence_number_reset_msg_t) == NYSE_COMMON_SEQUENCE_NUMBER_RESET_MSG_SIZE);

/******************************************************************************/

enum { SOURCE_ID_LEN = 20 };

/******************************************************************************/

typedef struct PACKED
{
    char            source_id[SOURCE_ID_LEN];
} nyse_common_heartbeat_subscription_msg_t;

enum { NYSE_COMMON_HEARTBEAT_SUBSCRIPTION_MSG_SIZE = 20 };

STATIC_ASSERT(sizeof (nyse_common_heartbeat_subscription_msg_t) == NYSE_COMMON_HEARTBEAT_SUBSCRIPTION_MSG_SIZE);

/******************************************************************************/

typedef struct PACKED
{
    char            source_id[SOURCE_ID_LEN];
} nyse_common_heartbeat_res_msg_t;

enum { NYSE_COMMON_HEARTBEAT_RES_MSG_SIZE = 20 };

STATIC_ASSERT(sizeof (nyse_common_heartbeat_res_msg_t) == NYSE_COMMON_HEARTBEAT_RES_MSG_SIZE);

/******************************************************************************/

typedef struct PACKED
{
    uint32_t        begin_seq_num;
    uint32_t        end_seq_num;
    char            source_id[SOURCE_ID_LEN];
} nyse_common_retransmission_req_msg_t;

enum { NYSE_COMMON_RETRANSMISSION_REQ_MSG_SIZE = 28 };

STATIC_ASSERT(sizeof (nyse_common_retransmission_req_msg_t) == NYSE_COMMON_RETRANSMISSION_REQ_MSG_SIZE);

/******************************************************************************/

enum retransmission_status_values
{
    RETX_STS_ACCEPTED       = 'A',
    RETX_STS_REJECTED       = 'R',
};

enum retransmission_reject_reason_values
{
    RETX_REJECT_REASON_MSG_ACCEPTED                     = 0,
    RETX_REJECT_REASON_DUE_TO_PERMISSIONS               = 1,
    RETX_REJECT_REASON_DUE_TO_INVALID_SEQ_RANGE         = 2,
    RETX_REJECT_REASON_DUE_TO_MAX_SEQ_RANGE             = 3,
    RETX_REJECT_REASON_DUE_TO_MAX_REQS_IN_DAY           = 4,
    RETX_REJECT_REASON_DUE_TO_MAX_REFRESH_REQS_IN_DAY   = 5,
};

typedef struct PACKED
{
    uint32_t        source_seq_num;
    char            source_id[SOURCE_ID_LEN];
    char            status;
    uint8_t         reject_reason;
#if 0
    // WARNING:
    // Alerts and BBO feeds have a 2-char filler, but LRP feed has a 6-char one
    // so, since this is the last one in the message we can safely skip it
    char            filler[];
#endif
} nyse_common_retransmission_res_msg_t;

enum { NYSE_COMMON_RETRANSMISSION_RES_MSG_SIZE = 26 };

STATIC_ASSERT(sizeof (nyse_common_retransmission_res_msg_t) == NYSE_COMMON_RETRANSMISSION_RES_MSG_SIZE);

/******************************************************************************/

typedef struct PACKED
{
    uint32_t        begin_seq_num;
    uint32_t        end_seq_num;
} nyse_common_message_unavailable_msg_t;

enum { NYSE_COMMON_MESSAGE_UNAVAILABLE_MSG_SIZE = 8 };

STATIC_ASSERT(sizeof (nyse_common_message_unavailable_msg_t) == NYSE_COMMON_MESSAGE_UNAVAILABLE_MSG_SIZE);

/******************************************************************************/

typedef struct PACKED
{
    char            symbol[NYSE_SYMBOL_LEN];
    char            source_id[SOURCE_ID_LEN];
} nyse_common_refresh_req_msg_t;

enum { NYSE_COMMON_REFRESH_REQ_MSG_SIZE = 36 };

STATIC_ASSERT(sizeof (nyse_common_refresh_req_msg_t) == NYSE_COMMON_REFRESH_REQ_MSG_SIZE);

/******************************************************************************/

#ifdef __cplusplus
} // extern C
#endif

#endif /* NYSE_COMMON_MSGS_H_ */
