/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: test_nyse_bbo_unpack.hpp
 *
 * Description:
 *      NYSE BBO feed unpack interface unit tests
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

#include <cxxtest/TestSuite.h>
#include <gmock/gmock.h>
#include <stdint.h>
#include <stddef.h>
#include <cassert>

#include "anon_var.hpp"
#include "serializer.hpp"
#include "nyse_bbo_pdp_header.h"
#include "unpack_status.h"
#include "nyse_bbo_unpack.h"
#include "gen_test.hpp"

////////////////////////////////////////////////////////////////////////////////

void compose_random_pdp_header(nyse_bbo_pdp_header_t * const out_p)
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

uint8_t * format_pdp_header(nyse_bbo_pdp_header_t const * const i_hdr_p, uint8_t * o_buffer, const size_t o_buf_size)
{
    assert(o_buf_size >= NYSE_BBO_PDP_HEADER_SIZE);

    size_t      random_offset = random() % (1 + o_buf_size - NYSE_BBO_PDP_HEADER_SIZE);
//        m_random->Generate(1 + o_buf_size - NYSE_BBO_PDP_HEADER_SIZE);

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

void assert_pdp_headers_are_equal(const nyse_bbo_pdp_header_t & lhs, const nyse_bbo_pdp_header_t & rhs)
{
    TS_ASSERT_EQUALS(lhs.msg_size,         rhs.msg_size);
    TS_ASSERT_EQUALS(lhs.msg_type,         rhs.msg_type);
    TS_ASSERT_EQUALS(lhs.msg_seq_num,      rhs.msg_seq_num);
    TS_ASSERT_EQUALS(lhs.send_time,        rhs.send_time);
    TS_ASSERT_EQUALS(lhs.product_id,       rhs.product_id);
    TS_ASSERT_EQUALS(lhs.retrans_flag,     rhs.retrans_flag);
    TS_ASSERT_EQUALS(lhs.num_body_entries, rhs.num_body_entries);
}

class NyseBboUnpackPdpHeader : public CxxTest::TestSuite
{
private:

testing::internal::Random * m_random;

public:
NyseBboUnpackPdpHeader()
{
    m_random = new testing::internal::Random(time(0));
    srandom(time(0));
}
~NyseBboUnpackPdpHeader()
{
    delete m_random;
}

void test_00100_fails_when_input_packet_ptr_is_null(void)
{
    gen_test_input_packet_ptr_is_null<nyse_bbo_pdp_header_t>
        (nyse_bbo_unpack_pdp_header, m_random);
}

void test_00101_fails_when_input_packet_is_too_short(void)
{
    gen_test_input_packet_is_too_short<nyse_bbo_pdp_header_t>
        (nyse_bbo_unpack_pdp_header, NYSE_BBO_PDP_HEADER_SIZE, m_random);
}

void test_00200_proper_packet_is_unpacked(void)
{
    gen_test_input_packet_is_unpacked<nyse_bbo_pdp_header_t>
        (
            compose_random_pdp_header,
            format_pdp_header,
            nyse_bbo_unpack_pdp_header,
            assert_pdp_headers_are_equal,
            NYSE_BBO_PDP_HEADER_SIZE,
            m_random);
}

};

////////////////////////////////////////////////////////////////////////////////

void compose_random_msg(nyse_bbo_quote_msg_t * const out_p)
{
    ANON_VAR(out_p->source_time);
    ANON_ARRAY(out_p->filler);
    ANON_VAR(out_p->rpi_interest);
    ANON_VAR(out_p->ask_price_nominator);
    ANON_VAR(out_p->ask_size);
    ANON_VAR(out_p->bid_price_numerator);
    ANON_VAR(out_p->bid_size);
    ANON_VAR(out_p->price_scale_code);
    ANON_VAR(out_p->exchange_id);
    ANON_VAR(out_p->security_type);
    ANON_VAR(out_p->quote_condition);
    ANON_ARRAY(out_p->symbol);
}

uint8_t * format_message(
    nyse_bbo_quote_msg_t const * const i_msg_p,
    uint8_t * o_buffer,
    const size_t o_buf_size)
{
    assert(o_buf_size >= NYSE_BBO_QUOTE_MSG_SIZE);

    size_t      random_offset = random() % (1 + o_buf_size - NYSE_BBO_QUOTE_MSG_SIZE);
//        m_random->Generate(1 + o_buf_size - NYSE_BBO_QUOTE_MSG_SIZE);

    std::vector<uint8_t>    work_vec;

    serialize(i_msg_p->source_time, work_vec);
    work_vec.insert(work_vec.end(), i_msg_p->filler, i_msg_p->filler + sizeof (i_msg_p->filler));
    serialize(i_msg_p->rpi_interest, work_vec);
    serialize(i_msg_p->ask_price_nominator, work_vec);
    serialize(i_msg_p->ask_size, work_vec);
    serialize(i_msg_p->bid_price_numerator, work_vec);
    serialize(i_msg_p->bid_size, work_vec);
    serialize(i_msg_p->price_scale_code, work_vec);
    serialize(i_msg_p->exchange_id, work_vec);
    serialize(i_msg_p->security_type, work_vec);
    serialize(i_msg_p->quote_condition, work_vec);
    work_vec.insert(work_vec.end(), i_msg_p->symbol, i_msg_p->symbol + sizeof (i_msg_p->symbol));

    std::copy(work_vec.begin(), work_vec.end(), &o_buffer[random_offset]);

    return &o_buffer[random_offset];
}

void assert_messages_are_equal(const nyse_bbo_quote_msg_t & lhs, const nyse_bbo_quote_msg_t & rhs)
{
    TS_ASSERT_EQUALS(lhs.source_time,                      rhs.source_time);
    TS_ASSERT_SAME_DATA(lhs.filler, rhs.filler, sizeof (lhs.filler));
    TS_ASSERT_EQUALS(lhs.rpi_interest,                     rhs.rpi_interest);
    TS_ASSERT_EQUALS(lhs.ask_price_nominator,              rhs.ask_price_nominator);
    TS_ASSERT_EQUALS(lhs.ask_size,                         rhs.ask_size);
    TS_ASSERT_EQUALS(lhs.bid_price_numerator,              rhs.bid_price_numerator);
    TS_ASSERT_EQUALS(lhs.bid_size,                         rhs.bid_size);
    TS_ASSERT_EQUALS(lhs.price_scale_code,                 rhs.price_scale_code);
    TS_ASSERT_EQUALS(lhs.exchange_id,                      rhs.exchange_id);
    TS_ASSERT_EQUALS(lhs.security_type,                    rhs.security_type);
    TS_ASSERT_EQUALS(lhs.quote_condition,                  rhs.quote_condition);
    TS_ASSERT_SAME_DATA(lhs.symbol, rhs.symbol, sizeof (lhs.symbol));
}

class NyseBboUnpackQuoteMsg : public CxxTest::TestSuite
{
private:

testing::internal::Random * m_random;

public:

NyseBboUnpackQuoteMsg()
{
    m_random = new testing::internal::Random(time(0));
    srandom(time(0));
}
~NyseBboUnpackQuoteMsg()
{
    delete m_random;
}

void test_00100_fails_when_input_packet_ptr_is_null(void)
{
    gen_test_input_packet_ptr_is_null<nyse_bbo_quote_msg_t>
        (nyse_bbo_unpack_quote_msg, m_random);
}

void test_00101_fails_when_input_packet_is_too_short(void)
{
    gen_test_input_packet_is_too_short<nyse_bbo_quote_msg_t>
        (nyse_bbo_unpack_quote_msg, NYSE_BBO_QUOTE_MSG_SIZE, m_random);
}

void test_00200_proper_packet_is_unpacked(void)
{
    gen_test_input_packet_is_unpacked<nyse_bbo_quote_msg_t>
        (
            compose_random_msg,
            format_message,
            nyse_bbo_unpack_quote_msg,
            assert_messages_are_equal,
            NYSE_BBO_QUOTE_MSG_SIZE,
            m_random);
}

};
