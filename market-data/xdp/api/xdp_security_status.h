/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 * Filename: xdp_security_status.h
 *
 * Description:
 *      Security Status field definitions
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


#ifndef XDP_SECURITY_STATUS_H_
#define XDP_SECURITY_STATUS_H_

#ifdef __cplusplus
extern "C"
{
#endif

enum security_status_values
{
    SEC_STS_REGULATORY_IMBALANCE                    = 1,
    SEC_STS_CANCEL_REGULATORY_IMBALANCE             = 2,
    SEC_STS_OPENING_DELAY                           = 3,
    SEC_STS_TRADING_HALT                            = 4,
    SEC_STS_RESUME                                  = 5,
    SEC_STS_NO_OPEN_NO_RESUME                       = 6,
    SEC_STS_PRICE_INDICATION                        = 7,
    SEC_STS_TRADING_RANGE_INDICATION                = 8,
    SEC_STS_NYSE_MANDATORY_PRE_OPENING_INDICATION   = 9,
    SEC_STS_TRADE_DISSEMINATION_TIME                = 10,
    SEC_STS_SHORT_SALE_RESTRICTION_INDICATION       = 11,
};

#ifdef __cplusplus
} // extern C
#endif

#endif /* XDP_SECURITY_STATUS_H_ */
