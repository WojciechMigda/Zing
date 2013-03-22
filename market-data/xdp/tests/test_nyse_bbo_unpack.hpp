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
#include "nyse_bbo_pdp.h"
#include "unpack_status.h"
#include "nyse_bbo_unpack.h"

class NyseBboUnpackPdpHeader : public CxxTest::TestSuite
{
private:

testing::internal::Random * m_random;

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

    size_t      random_offset =
        m_random->Generate(1 + o_buf_size - NYSE_BBO_PDP_HEADER_SIZE);

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
    size_t                      in_size = m_random->Generate(m_random->kMaxRange);

    nyse_bbo_pdp_header_t       out_data;
    size_t                      out_size;
    int                         result;

    result = nyse_bbo_unpack_pdp_header(NULL, in_size, &out_data, &out_size);

    TS_ASSERT_EQUALS(XDP_UNPACK_NULL_INPUT_PACKET_PTR, result);
}

void test_00101_fails_when_input_packet_is_too_short(void)
{
    uint8_t                     in_packet[1];
    size_t                      in_size = m_random->Generate(NYSE_BBO_PDP_HEADER_SIZE);

    nyse_bbo_pdp_header_t       out_data;
    size_t                      out_size;
    int                         result;

    result = nyse_bbo_unpack_pdp_header(in_packet, in_size, &out_data, &out_size);

    TS_ASSERT_EQUALS(XDP_UNPACK_INPUT_PACKET_TOO_SHORT, result);
}

void test_00200_proper_packet_is_unpacked(void)
{
    nyse_bbo_pdp_header_t       in_data;

    compose_random_pdp_header(&in_data);

    uint8_t                     in_packet[2 * NYSE_BBO_PDP_HEADER_SIZE];
    uint8_t *                   in_packet_p;

    in_packet_p = format_pdp_header(&in_data, in_packet, sizeof (in_packet));

    size_t                      in_size = NYSE_BBO_PDP_HEADER_SIZE + m_random->Generate(NYSE_BBO_PDP_HEADER_SIZE);

    nyse_bbo_pdp_header_t       out_data;
    size_t                      out_size;
    int                         result;

    result = nyse_bbo_unpack_pdp_header(in_packet_p, in_size, &out_data, &out_size);

    TS_ASSERT_EQUALS(XDP_UNPACK_SUCCESS, result);

    TS_ASSERT_EQUALS(out_data.msg_size,         in_data.msg_size);
    TS_ASSERT_EQUALS(out_data.msg_type,         in_data.msg_type);
    TS_ASSERT_EQUALS(out_data.msg_seq_num,      in_data.msg_seq_num);
    TS_ASSERT_EQUALS(out_data.send_time,        in_data.send_time);
    TS_ASSERT_EQUALS(out_data.product_id,       in_data.product_id);
    TS_ASSERT_EQUALS(out_data.retrans_flag,     in_data.retrans_flag);
    TS_ASSERT_EQUALS(out_data.num_body_entries, in_data.num_body_entries);

    TS_ASSERT_EQUALS(out_size, (size_t)NYSE_BBO_PDP_HEADER_SIZE);
}

};

////////////////////////////////////////////////////////////////////////////////

class NyseBboUnpackQuoteMsg : public CxxTest::TestSuite
{
private:

testing::internal::Random * m_random;

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

    size_t      random_offset =
        m_random->Generate(1 + o_buf_size - NYSE_BBO_QUOTE_MSG_SIZE);

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
    size_t                      in_size = m_random->Generate(m_random->kMaxRange);

    nyse_bbo_quote_msg_t        out_data;
    size_t                      out_size;
    int                         result;

    result = nyse_bbo_unpack_quote_msg(NULL, in_size, &out_data, &out_size);

    TS_ASSERT_EQUALS(XDP_UNPACK_NULL_INPUT_PACKET_PTR, result);
}

void test_00101_fails_when_input_packet_is_too_short(void)
{
    uint8_t                 in_packet[1];
    size_t                  in_size = m_random->Generate(NYSE_BBO_QUOTE_MSG_SIZE);

    nyse_bbo_quote_msg_t    out_data;
    size_t                  out_size;
    int                     result;

    result = nyse_bbo_unpack_quote_msg(in_packet, in_size, &out_data, &out_size);

    TS_ASSERT_EQUALS(XDP_UNPACK_INPUT_PACKET_TOO_SHORT, result);
}

void test_00200_proper_packet_is_unpacked(void)
{
    nyse_bbo_quote_msg_t        in_data;

    compose_random_msg(&in_data);

    uint8_t                     in_packet[2 * NYSE_BBO_QUOTE_MSG_SIZE];
    uint8_t *                   in_packet_p;

    in_packet_p = format_message(&in_data, in_packet, sizeof (in_packet));

    size_t                      in_size = NYSE_BBO_QUOTE_MSG_SIZE + m_random->Generate(NYSE_BBO_QUOTE_MSG_SIZE);

    nyse_bbo_quote_msg_t        out_data;
    size_t                      out_size;
    int                         result;

    result = nyse_bbo_unpack_quote_msg(in_packet_p, in_size, &out_data, &out_size);

    TS_ASSERT_EQUALS(XDP_UNPACK_SUCCESS, result);

    TS_ASSERT_EQUALS(out_data.source_time,                      in_data.source_time);
    TS_ASSERT_SAME_DATA(out_data.filler, in_data.filler, sizeof (out_data.filler));
    TS_ASSERT_EQUALS(out_data.rpi_interest,                     in_data.rpi_interest);
    TS_ASSERT_EQUALS(out_data.ask_price_nominator,              in_data.ask_price_nominator);
    TS_ASSERT_EQUALS(out_data.ask_size,                         in_data.ask_size);
    TS_ASSERT_EQUALS(out_data.bid_price_numerator,              in_data.bid_price_numerator);
    TS_ASSERT_EQUALS(out_data.bid_size,                         in_data.bid_size);
    TS_ASSERT_EQUALS(out_data.price_scale_code,                 in_data.price_scale_code);
    TS_ASSERT_EQUALS(out_data.exchange_id,                      in_data.exchange_id);
    TS_ASSERT_EQUALS(out_data.security_type,                    in_data.security_type);
    TS_ASSERT_EQUALS(out_data.quote_condition,                  in_data.quote_condition);
    TS_ASSERT_SAME_DATA(out_data.symbol, in_data.symbol, sizeof (out_data.symbol));

    TS_ASSERT_EQUALS(out_size, (size_t)NYSE_BBO_QUOTE_MSG_SIZE);
}

};
