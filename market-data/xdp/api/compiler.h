/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: compiler.h
 *
 * Description:
 *      Compiler-specific macros and definitions
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


#ifndef COMPILER_H_
#define COMPILER_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define PACKED __attribute__((packed))

#ifdef __cplusplus
} // extern C
#endif

#endif /* COMPILER_H_ */
