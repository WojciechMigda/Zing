/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: nyse_retrac_pdp_header.h
 *
 * Description:
 *      NYSE ReTrac PDP header definitions
 *
 *      References:
 *      [1] NYSE RETAIL EXECUTION REPORT (RETRAC) CLIENT SPECIFICATION,
 *          Version 2.2a, 2012-08-10
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
 * 2013-03-25   wm              Initial version
 *
 ******************************************************************************/


#ifndef NYSE_RETRAC_PDP_HEADER_H_
#define NYSE_RETRAC_PDP_HEADER_H_

#ifdef __cplusplus
extern "C"
{
#endif

enum nyse_retrac_message_type_values
{
    NYSE_RETRAC_MSG_EXECUTION_REPORT                    = 190,
    NYSE_RETRAC_MSG_EXECUTION_REPORT_CANCELLATION       = 191,
    NYSE_RETRAC_MSG_SUMMARY                             = 192,
};

enum { NYSE_RETRAC_PDP_HEADER_SIZE = 16 };

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
} nyse_retrac_pdp_header_t;

#ifdef __cplusplus
} // extern C
#endif

#endif /* NYSE_RETRAC_PDP_HEADER_H_ */
