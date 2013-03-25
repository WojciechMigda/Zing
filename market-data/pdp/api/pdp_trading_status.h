/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: pdp_trading_status.h
 *
 * Description:
 *      PDP Trading Status element definitions
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


#ifndef PDP_TRADING_STATUS_H_
#define PDP_TRADING_STATUS_H_

#ifdef __cplusplus
extern "C"
{
#endif

enum trading_status_values
{
    TRADING_STS_PRE_OPENING         = 'P',
    TRADING_STS_OPENED_REOPENED     = 'O',
    TRADING_STS_CLOSED              = 'C',
    TRADING_STS_HALTED              = 'H',
};

#ifdef __cplusplus
} // extern C
#endif

#endif /* PDP_TRADING_STATUS_H_ */
