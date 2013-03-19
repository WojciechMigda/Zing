/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 *******************************************************************************
 * Filename: static_assert.h
 *
 * Description:
 *      Static assert (compile time)
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


#ifndef STATIC_ASSERT_H_
#define STATIC_ASSERT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define STATIC_ASSERT(expr) typedef char __static_assert[1 - 2 * !(expr)]

#ifdef __cplusplus
} // extern C
#endif

#endif /* STATIC_ASSERT_H_ */
