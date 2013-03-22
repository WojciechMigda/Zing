/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: pdp_retrans_flag.h
 *
 * Description:
 *      PDP Retransmission Flag field definitions
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


#ifndef PDP_RETRANS_FLAG_H_
#define PDP_RETRANS_FLAG_H_

#ifdef __cplusplus
extern "C"
{
#endif

enum retrans_flag_values
{
    RETX_F_ORIGINAL_MSG             = 1,
    RETX_F_RETRANSMITTED_MSG        = 2,
    RETX_F_MSG_REPLAY               = 3,
    RETX_F_RETX_OF_REPLAYED_MSG     = 4,
    RETX_F_REFRESH_RETX             = 5,
};

#ifdef __cplusplus
} // extern C
#endif

#endif /* PDP_RETRANS_FLAG_H_ */
