/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: gen_test.hpp
 *
 * Description:
 *      Generic unit test utilities
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


#ifndef GEN_TEST_HPP_
#define GEN_TEST_HPP_

#include <stdint.h>
#include <stddef.h>
#include <gmock/gmock.h>
#include <cxxtest/TestSuite.h>

#include "compiler.h"
#include "unpack_status.h"

/*******************************************************************************
 * @brief Generic test case body for scenario when input packet pointer is NULL
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-24   wm              Initial version
 *
 *******************************************************************************
 * @param _Tp data type representing unpacked packet contents
 * @param fn function pointer to the packet unpacking routine
 * @param random_p pointer to the GMock random number genarator instance
 ******************************************************************************/
template<typename _Tp>
void gen_test_input_packet_ptr_is_null(
    int (*fn)
    (
        const uint8_t * RESTRICT in_data_p,
        const size_t in_size,
        _Tp * const RESTRICT out_body_p,
        size_t * const RESTRICT out_offset_p
    ),
    testing::internal::Random * random_p)
{
    size_t      in_size = random_p->Generate(random_p->kMaxRange);

    _Tp         out_data;
    size_t      out_size;
    int         result;

    result = fn(NULL, in_size, &out_data, &out_size);

    TS_ASSERT_EQUALS(PDP_UNPACK_NULL_INPUT_PACKET_PTR, result);
}

#endif /* GEN_TEST_HPP_ */
