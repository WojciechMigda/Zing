/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: pdp_trade_condition.h
 *
 * Description:
 *      PDP Trade Condition element definitions
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


#ifndef PDP_TRADE_CONDITION_H_
#define PDP_TRADE_CONDITION_H_

#ifdef __cplusplus
extern "C"
{
#endif

enum trade_condition_values
{
    TRADE_COND_REGULAR_SALE             = '@',
    TRADE_COND_CASH                     = 'A',
    TRADE_COND_NEXT_DAY_TRADE           = 'N',
    TRADE_COND_SELLER                   = 'R',
    TRADE_COND_SOLD_LAST                = 'L',
    TRADE_COND_OPENED                   = 'O',
    TRADE_COND_SOLD                     = 'Z',
    TRADE_COND_AVERAGE_PRICE_TRADE      = 'B',
    TRADE_COND_AUTOEXECUTION            = 'E',
    TRADE_COND_RULE_127                 = 'J',
    TRADE_COND_N_A                      = 0,
};

#ifdef __cplusplus
} // extern C
#endif

#endif /* PDP_TRADE_CONDITION_H_ */
