/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: test_nyse_lrp_unpack.hpp
 *
 * Description:
 *      NYSE LRP feed unpack interface unit tests
 *
 * Authors:
 *          Wojciech Migda (wm)
 *
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-22   wm              Initial version
 *
 ******************************************************************************/

#include <cxxtest/TestSuite.h>
#include <gmock/gmock.h>
#include <stdint.h>
#include <stddef.h>
#include <cassert>

#include "anon_var.hpp"
#include "serializer.hpp"
#include "nyse_lrp_pdp_header.h"
#include "unpack_status.h"
#include "nyse_lrp_unpack.h"
#include "nyse_lrp_lrp_message.h"
#include "gen_test.hpp"

////////////////////////////////////////////////////////////////////////////////

void compose_random_pdp_header(nyse_lrp_pdp_header_t * const out_p)
{
    ANON_VAR(out_p->msg_size);
    ANON_VAR(out_p->msg_type);
    ANON_VAR(out_p->msg_seq_num);
    ANON_VAR(out_p->send_time);
    ANON_VAR(out_p->product_id);
    ANON_VAR(out_p->retrans_flag);
    ANON_VAR(out_p->num_body_entries);
    ANON_ARRAY(out_p->filler);
}

uint8_t * format_pdp_header(nyse_lrp_pdp_header_t const * const i_hdr_p, uint8_t * o_buffer, const size_t o_buf_size)
{
    assert(o_buf_size >= NYSE_LRP_PDP_HEADER_SIZE);

    size_t      random_offset = random() % (1 + o_buf_size - NYSE_LRP_PDP_HEADER_SIZE);
//        m_random->Generate(1 + o_buf_size - NYSE_LRP_PDP_HEADER_SIZE);

    std::vector<uint8_t>    work_vec;

    serialize(i_hdr_p->msg_size, work_vec);
    serialize(i_hdr_p->msg_type, work_vec);
    serialize(i_hdr_p->msg_seq_num, work_vec);
    serialize(i_hdr_p->send_time, work_vec);
    serialize(i_hdr_p->product_id, work_vec);
    serialize(i_hdr_p->retrans_flag, work_vec);
    serialize(i_hdr_p->num_body_entries, work_vec);
    work_vec.insert(work_vec.end(), i_hdr_p->filler, i_hdr_p->filler + sizeof (i_hdr_p->filler));

    std::copy(work_vec.begin(), work_vec.end(), &o_buffer[random_offset]);

    return &o_buffer[random_offset];
}

void assert_pdp_headers_are_equal(const nyse_lrp_pdp_header_t & lhs, const nyse_lrp_pdp_header_t & rhs)
{
    TS_ASSERT_EQUALS(lhs.msg_size,         rhs.msg_size);
    TS_ASSERT_EQUALS(lhs.msg_type,         rhs.msg_type);
    TS_ASSERT_EQUALS(lhs.msg_seq_num,      rhs.msg_seq_num);
    TS_ASSERT_EQUALS(lhs.send_time,        rhs.send_time);
    TS_ASSERT_EQUALS(lhs.product_id,       rhs.product_id);
    TS_ASSERT_EQUALS(lhs.retrans_flag,     rhs.retrans_flag);
    TS_ASSERT_EQUALS(lhs.num_body_entries, rhs.num_body_entries);
}

class NyseLrpUnpackPdpHeader : public CxxTest::TestSuite
{
private:

testing::internal::Random * m_random;

public:
NyseLrpUnpackPdpHeader()
{
    m_random = new testing::internal::Random(time(0));
    srandom(time(0));
}
~NyseLrpUnpackPdpHeader()
{
    delete m_random;
}

void test_00100_fails_when_input_packet_ptr_is_null(void)
{
    gen_test_input_packet_ptr_is_null<nyse_lrp_pdp_header_t>
        (nyse_lrp_unpack_pdp_header, m_random);
}

void test_00101_fails_when_input_packet_is_too_short(void)
{
    gen_test_input_packet_is_too_short<nyse_lrp_pdp_header_t>
        (nyse_lrp_unpack_pdp_header, NYSE_LRP_PDP_HEADER_SIZE, m_random);
}

void test_00200_proper_packet_is_unpacked(void)
{
    gen_test_input_packet_is_unpacked<nyse_lrp_pdp_header_t>
        (
            compose_random_pdp_header,
            format_pdp_header,
            nyse_lrp_unpack_pdp_header,
            assert_pdp_headers_are_equal,
            NYSE_LRP_PDP_HEADER_SIZE,
            m_random);
}

};

////////////////////////////////////////////////////////////////////////////////

void compose_random_msg(nyse_lrp_lrp_msg_t * const out_p)
{
    ANON_VAR(out_p->filler1);
    ANON_VAR(out_p->source_time);
    ANON_VAR(out_p->low_lrp_numerator);
    ANON_VAR(out_p->high_lrp_numerator);
    ANON_VAR(out_p->price_scale_code);
    ANON_VAR(out_p->lrp_change_indicator);
    ANON_VAR(out_p->filler2);
    ANON_ARRAY(out_p->symbol);
}

uint8_t * format_message(
    nyse_lrp_lrp_msg_t const * const i_msg_p,
    uint8_t * o_buffer,
    const size_t o_buf_size)
{
    assert(o_buf_size >= NYSE_LRP_LRP_MSG_SIZE);

    size_t      random_offset = random() % (1 + o_buf_size - NYSE_LRP_LRP_MSG_SIZE);
//        m_random->Generate(1 + o_buf_size - NYSE_LRP_LRP_MSG_SIZE);

    std::vector<uint8_t>    work_vec;

    serialize(i_msg_p->filler1, work_vec);
    serialize(i_msg_p->source_time, work_vec);
    serialize(i_msg_p->low_lrp_numerator, work_vec);
    serialize(i_msg_p->high_lrp_numerator, work_vec);
    serialize(i_msg_p->price_scale_code, work_vec);
    serialize(i_msg_p->lrp_change_indicator, work_vec);
    serialize(i_msg_p->filler2, work_vec);
    work_vec.insert(work_vec.end(), i_msg_p->symbol, i_msg_p->symbol + sizeof (i_msg_p->symbol));

    std::copy(work_vec.begin(), work_vec.end(), &o_buffer[random_offset]);

    return &o_buffer[random_offset];
}

void assert_messages_are_equal(const nyse_lrp_lrp_msg_t & lhs, const nyse_lrp_lrp_msg_t & rhs)
{
    TS_ASSERT_EQUALS(lhs.source_time,                      rhs.source_time);
    TS_ASSERT_EQUALS(lhs.low_lrp_numerator,                rhs.low_lrp_numerator);
    TS_ASSERT_EQUALS(lhs.high_lrp_numerator,               rhs.high_lrp_numerator);
    TS_ASSERT_EQUALS(lhs.price_scale_code,                 rhs.price_scale_code);
    TS_ASSERT_EQUALS(lhs.lrp_change_indicator,             rhs.lrp_change_indicator);
    TS_ASSERT_SAME_DATA(lhs.symbol, rhs.symbol, sizeof (lhs.symbol));
}

class NyseLrpUnpackLrpMsg : public CxxTest::TestSuite
{
private:

testing::internal::Random * m_random;

public:

NyseLrpUnpackLrpMsg()
{
    m_random = new testing::internal::Random(time(0));
    srandom(time(0));
}
~NyseLrpUnpackLrpMsg()
{
    delete m_random;
}

void test_00100_fails_when_input_packet_ptr_is_null(void)
{
    gen_test_input_packet_ptr_is_null<nyse_lrp_lrp_msg_t>
        (nyse_lrp_unpack_lrp_msg, m_random);
}

void test_00101_fails_when_input_packet_is_too_short(void)
{
    gen_test_input_packet_is_too_short<nyse_lrp_lrp_msg_t>
        (nyse_lrp_unpack_lrp_msg, NYSE_LRP_LRP_MSG_SIZE, m_random);
}

void test_00200_proper_packet_is_unpacked(void)
{
    gen_test_input_packet_is_unpacked<nyse_lrp_lrp_msg_t>
        (
            compose_random_msg,
            format_message,
            nyse_lrp_unpack_lrp_msg,
            assert_messages_are_equal,
            NYSE_LRP_LRP_MSG_SIZE,
            m_random);
}

};
