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
 * @param unpacker function pointer to the packet unpacking routine
 * @param random_p pointer to the GMock random number genarator instance
 ******************************************************************************/
template<typename _Tp>
void gen_test_input_packet_ptr_is_null(
    int (*unpacker)
    (
        const uint8_t * RESTRICT,
        const size_t,
        _Tp * const RESTRICT,
        size_t * const RESTRICT
    ),
    testing::internal::Random * random_p)
{
    size_t      in_size = random_p->Generate(random_p->kMaxRange);

    _Tp         out_data;
    size_t      out_size;
    int         result;

    result = unpacker(NULL, in_size, &out_data, &out_size);

    TS_ASSERT_EQUALS(PDP_UNPACK_NULL_INPUT_PACKET_PTR, result);
}

/*******************************************************************************
 * @brief Generic test case body for scenario when input packet length is too
 *        short
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-24   wm              Initial version
 *
 *******************************************************************************
 * @param _Tp data type representing unpacked packet contents
 * @param unpacker function pointer to the packet unpacking routine
 * @param limiting_size length of the input data
 * @param random_p pointer to the GMock random number genarator instance
 ******************************************************************************/
template<typename _Tp>
void gen_test_input_packet_is_too_short(
    int (*unpacker)
    (
        const uint8_t * RESTRICT,
        const size_t,
        _Tp * const RESTRICT,
        size_t * const RESTRICT
    ),
    const size_t limiting_size,
    testing::internal::Random * random_p)
{
    uint8_t     in_packet[1];
    size_t      in_size = random_p->Generate(limiting_size);

    _Tp         out_data;
    size_t      out_size;
    int         result;

    result = unpacker(in_packet, in_size, &out_data, &out_size);

    TS_ASSERT_EQUALS(PDP_UNPACK_INPUT_PACKET_TOO_SHORT, result);
}

/*******************************************************************************
 * @brief Generic test case body for scenario when input packet is properly
 *        unpacked
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-24   wm              Initial version
 *
 *******************************************************************************
 * @param _Tp data type representing unpacked packet contents
 * @param composer function pointer to the input data composer routine
 * @param formatter function pointer to the routine which formats input data
 *        into a packet
 * @param unpacker function pointer to the packet unpacking routine
 * @param asserter function pointer to the routine which executes custom
 *        assertions involving input and output data
 * @param packet_size length of the packet
 * @param random_p pointer to the GMock random number genarator instance
 ******************************************************************************/
template<typename _Tp>
void gen_test_input_packet_is_unpacked(
    void (*composer)(_Tp * const),
    uint8_t * (formatter)(_Tp const * const, uint8_t *, const size_t),
    int (*unpacker)
    (
        const uint8_t * RESTRICT,
        const size_t,
        _Tp * const RESTRICT,
        size_t * const RESTRICT
    ),
    void (*asserter)(const _Tp & lhs, const _Tp & rhs),
    const size_t packet_size,
    testing::internal::Random * random_p)
{
    _Tp        in_data;

    // compose random contents
    composer(&in_data);

    // reserved space twice the size of the packet
    uint8_t     in_packet[2 * packet_size];
    uint8_t *   in_packet_p;

    // format contents into varied offset inside the packet
    in_packet_p = formatter(&in_data, in_packet, sizeof (in_packet));

    // vary packet size passed to the unpacker [packet_size, 2 * packet_size]
    size_t      in_size = packet_size + random_p->Generate(packet_size + 1);

    _Tp         out_data;
    size_t      out_size;
    int         result;

    result = unpacker(in_packet_p, in_size, &out_data, &out_size);

    TS_ASSERT_EQUALS(PDP_UNPACK_SUCCESS, result);

    TS_ASSERT_EQUALS(out_size, packet_size);

    asserter(out_data, in_data);
}

#endif /* GEN_TEST_HPP_ */
