/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: pdp_quote_condition.h
 *
 * Description:
 *      PDP Quote Condition values
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


#ifndef PDP_QUOTE_CONDITION_H_
#define PDP_QUOTE_CONDITION_H_

#ifdef __cplusplus
extern "C"
{
#endif

enum quote_condition_values
{
    QUOTE_COND_SLOW_ON_ASK_SIDE                                     = 'A',
    QUOTE_COND_SLOW_ON_BID_SIDE                                     = 'B',
    QUOTE_COND_CLOSING                                              = 'C',
    QUOTE_COND_SLOW_ON_THE_BID_DUE_TO_AN_LRP_OR_GAP_QUOTE           = 'E',
    QUOTE_COND_SLOW_ON_THE_ASK_DUE_TO_AN_LRP_OR_GAP_QUOTE           = 'F',
    QUOTE_COND_SLOW_ON_BOTH_ASK_AND_BID                             = 'H',
    QUOTE_COND_NON_FIRM_QUOTE                                       = 'N',
    QUOTE_COND_OPENING_QUOTE                                        = 'O',
    QUOTE_COND_REGULAR_QUOTE                                        = 'R',
    QUOTE_COND_SLOW_ON_THE_BID_AND_ASK_DUE_TO_AN_LRP_OR_GAP_QUOTE   = 'U',
    QUOTE_COND_SLOW_ON_THE_BID_AND_ASK_DUE_TO_A_SET_SLOW_LIST       = 'W',
};

#ifdef __cplusplus
} // extern C
#endif

#endif /* PDP_QUOTE_CONDITION_H_ */
