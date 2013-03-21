/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: anon_var.hpp
 *
 * Description:
 *      Anonymous variable utilities
 *
 * Authors:
 *          Wojciech Migda (wm)
 *
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-21   wm              Initial version
 *
 ******************************************************************************/


#ifndef ANON_VAR_HPP_
#define ANON_VAR_HPP_

#include <cstdlib>
#include <algorithm>

#define ANON_ARRAY(x) do{std::generate_n(x, sizeof (x), random);}while(0)
#define ANON_VAR(x) do{x = random();}while(0)

#endif /* ANON_VAR_HPP_ */
