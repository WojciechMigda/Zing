/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 * Filename: nyse_obultra_pdp_header.h
 *
 * Description:
 *      NYSE OpenBook Ultra PDP header definitions
 *
 *      References:
 *      [1] NYSE OPENBOOK ULTRA CLIENT SPECIFICATION, Version 1.8, 2012-09-03
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
 * 2013-03-24   wm              Initial version
 *
 ******************************************************************************/

#ifndef NYSE_OBULTRA_PDP_HEADER_H_
#define NYSE_OBULTRA_PDP_HEADER_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

enum nyse_obultra_message_type_values
{
    NYSE_OBULTRA_MSG_OB_FULL_UPDATE         = 230,
    NYSE_OBULTRA_MSG_OB_DELTA_UPDATE        = 231,
};

enum { NYSE_OBULTRA_PDP_HEADER_SIZE = 16 };

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
} nyse_obultra_pdp_header_t;

#ifdef __cplusplus
} // extern C
#endif

#endif /* NYSE_OBULTRA_PDP_HEADER_H_ */
