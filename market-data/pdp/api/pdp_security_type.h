/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: pdp_security_type.h
 *
 * Description:
 *      PDP Security Type element definitions
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


#ifndef PDP_SECURITY_TYPE_H_
#define PDP_SECURITY_TYPE_H_

#ifdef __cplusplus
extern "C"
{
#endif

enum nyse_security_type_values
{
    SEC_TYPE_EQUITY         = 'E',
};

#ifdef __cplusplus
} // extern C
#endif

#endif /* PDP_SECURITY_TYPE_H_ */
