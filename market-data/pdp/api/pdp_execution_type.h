/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: pdp_execution_type.h
 *
 * Description:
 *      PDP Execution Type element definitions
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


#ifndef PDP_EXECUTION_TYPE_H_
#define PDP_EXECUTION_TYPE_H_

#ifdef __cplusplus
extern "C"
{
#endif

enum execution_type_values
{
    EXEC_TYPE_PROGRAM_TRADING               = 3,
    EXEC_TYPE_INDEX_ARB                     = 4,
    EXEC_TYPE_ALGORITHMIC                   = 5,
    EXEC_TYPE_NON_ALGORITHMIC               = 6,
};

#ifdef __cplusplus
} // extern C
#endif

#endif /* PDP_EXECUTION_TYPE_H_ */
