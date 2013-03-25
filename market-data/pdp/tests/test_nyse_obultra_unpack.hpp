/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: test_nyse_obultra_unpack.hpp
 *
 * Description:
 *      Testcases for the BYSE OpenBook Ultra unpacking routines
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

#include <cxxtest/TestSuite.h>
#include <gmock/gmock.h>
#include <stdint.h>
#include <stddef.h>
#include <cassert>

#include "anon_var.hpp"
#include "serializer.hpp"
#include "unpack_status.h"
#include "gen_test.hpp"

#include "nyse_obultra_unpack.h"
#include "nyse_obultra_pdp_header.h"

////////////////////////////////////////////////////////////////////////////////

void compose_random_pdp_header(nyse_obultra_pdp_header_t * const out_p)
{
    ANON_VAR(out_p->msg_size);
    ANON_VAR(out_p->msg_type);
    ANON_VAR(out_p->msg_seq_num);
    ANON_VAR(out_p->send_time);
    ANON_VAR(out_p->product_id);
    ANON_VAR(out_p->retrans_flag);
    ANON_VAR(out_p->num_body_entries);
    ANON_VAR(out_p->link_flag);
}

uint8_t * format_pdp_header(nyse_obultra_pdp_header_t const * const i_hdr_p, uint8_t * o_buffer, const size_t o_buf_size)
{
    assert(o_buf_size >= NYSE_OBULTRA_PDP_HEADER_SIZE);

    size_t      random_offset = random() % (1 + o_buf_size - NYSE_OBULTRA_PDP_HEADER_SIZE);

    std::vector<uint8_t>    work_vec;

    serialize(i_hdr_p->msg_size, work_vec);
    serialize(i_hdr_p->msg_type, work_vec);
    serialize(i_hdr_p->msg_seq_num, work_vec);
    serialize(i_hdr_p->send_time, work_vec);
    serialize(i_hdr_p->product_id, work_vec);
    serialize(i_hdr_p->retrans_flag, work_vec);
    serialize(i_hdr_p->num_body_entries, work_vec);
    serialize(i_hdr_p->link_flag, work_vec);

    std::copy(work_vec.begin(), work_vec.end(), &o_buffer[random_offset]);

    return &o_buffer[random_offset];
}

void assert_pdp_headers_are_equal(const nyse_obultra_pdp_header_t & lhs, const nyse_obultra_pdp_header_t & rhs)
{
    TS_ASSERT_EQUALS(lhs.msg_size,          rhs.msg_size);
    TS_ASSERT_EQUALS(lhs.msg_type,          rhs.msg_type);
    TS_ASSERT_EQUALS(lhs.msg_seq_num,       rhs.msg_seq_num);
    TS_ASSERT_EQUALS(lhs.send_time,         rhs.send_time);
    TS_ASSERT_EQUALS(lhs.product_id,        rhs.product_id);
    TS_ASSERT_EQUALS(lhs.retrans_flag,      rhs.retrans_flag);
    TS_ASSERT_EQUALS(lhs.num_body_entries,  rhs.num_body_entries);
    TS_ASSERT_EQUALS(lhs.link_flag,         rhs.link_flag);
}

class NyseObultraUnpackPdpHeader : public CxxTest::TestSuite
{
private:

testing::internal::Random * m_random;

public:
NyseObultraUnpackPdpHeader()
{
    m_random = new testing::internal::Random(time(0));
    srandom(time(0));
}
~NyseObultraUnpackPdpHeader()
{
    delete m_random;
}

void test_00100_fails_when_input_packet_ptr_is_null(void)
{
    gen_test_input_packet_ptr_is_null<nyse_obultra_pdp_header_t>
        (nyse_obultra_unpack_pdp_header, m_random);
}

void test_00101_fails_when_input_packet_is_too_short(void)
{
    gen_test_input_packet_is_too_short<nyse_obultra_pdp_header_t>
        (nyse_obultra_unpack_pdp_header, NYSE_OBULTRA_PDP_HEADER_SIZE, m_random);
}

void test_00200_proper_packet_is_unpacked(void)
{
    gen_test_input_packet_is_unpacked<nyse_obultra_pdp_header_t>
        (
            compose_random_pdp_header,
            format_pdp_header,
            nyse_obultra_unpack_pdp_header,
            assert_pdp_headers_are_equal,
            NYSE_OBULTRA_PDP_HEADER_SIZE,
            m_random);
}

};

////////////////////////////////////////////////////////////////////////////////

void compose_random_msg(nyse_obultra_full_update_msg_t * const out_p)
{
    out_p->num_price_points = random() % (sizeof (out_p->price_points) / sizeof (out_p->price_points[0]));

    out_p->msg_size = NYSE_OBULTRA_FULL_UPDATE_FIXED_MSG_SIZE + out_p->num_price_points * NYSE_OBULTRA_FULL_UPDATE_PRICE_POINT_SIZE;

    ANON_VAR(out_p->security_index);
    ANON_VAR(out_p->source_time);
    ANON_VAR(out_p->source_time_ms);
    ANON_VAR(out_p->symbol_seq_num);
    ANON_VAR(out_p->source_session_id);
    ANON_ARRAY(out_p->symbol);
    ANON_VAR(out_p->price_scale_code);
    ANON_VAR(out_p->quote_condition);
    ANON_VAR(out_p->trading_status);
    ANON_VAR(out_p->filler);
    ANON_VAR(out_p->mpv);

    for (size_t idx = 0; idx < out_p->num_price_points; ++idx)
    {
        ANON_VAR(out_p->price_points[idx].price_numerator);
        ANON_VAR(out_p->price_points[idx].volume);
        ANON_VAR(out_p->price_points[idx].num_orders);
        ANON_VAR(out_p->price_points[idx].side);
        ANON_VAR(out_p->price_points[idx].filler);
    }
}

uint8_t * format_message(
    nyse_obultra_full_update_msg_t const * const i_msg_p,
    uint8_t * o_buffer,
    const size_t o_buf_size)
{
    size_t      required_space = i_msg_p->msg_size;

    assert(o_buf_size >= required_space);

    size_t      random_offset = random() % (1 + o_buf_size - required_space);

    std::vector<uint8_t>    work_vec;

    serialize(i_msg_p->msg_size, work_vec);
    serialize(i_msg_p->security_index, work_vec);
    serialize(i_msg_p->source_time, work_vec);
    serialize(i_msg_p->source_time_ms, work_vec);
    serialize(i_msg_p->symbol_seq_num, work_vec);
    serialize(i_msg_p->source_session_id, work_vec);
    work_vec.insert(work_vec.end(), i_msg_p->symbol, i_msg_p->symbol + sizeof (i_msg_p->symbol));
    serialize(i_msg_p->price_scale_code, work_vec);
    serialize(i_msg_p->quote_condition, work_vec);
    serialize(i_msg_p->trading_status, work_vec);
    serialize(i_msg_p->filler, work_vec);
    serialize(i_msg_p->mpv, work_vec);

    for (size_t idx = 0; idx < i_msg_p->num_price_points; ++idx)
    {
        serialize(i_msg_p->price_points[idx].price_numerator, work_vec);
        serialize(i_msg_p->price_points[idx].volume, work_vec);
        serialize(i_msg_p->price_points[idx].num_orders, work_vec);
        serialize(i_msg_p->price_points[idx].side, work_vec);
        serialize(i_msg_p->price_points[idx].filler, work_vec);
    }

    std::copy(work_vec.begin(), work_vec.end(), &o_buffer[random_offset]);

    return &o_buffer[random_offset];
}

void assert_messages_are_equal(const nyse_obultra_full_update_msg_t & lhs, const nyse_obultra_full_update_msg_t & rhs)
{
    TS_ASSERT_EQUALS(lhs.msg_size,                          rhs.msg_size);
    TS_ASSERT_EQUALS(lhs.security_index,                    rhs.security_index);
    TS_ASSERT_EQUALS(lhs.source_time,                       rhs.source_time);
    TS_ASSERT_EQUALS(lhs.source_time_ms,                    rhs.source_time_ms);
    TS_ASSERT_EQUALS(lhs.symbol_seq_num,                    rhs.symbol_seq_num);
    TS_ASSERT_EQUALS(lhs.source_session_id,                 rhs.source_session_id);
    TS_ASSERT_SAME_DATA(lhs.symbol, rhs.symbol, sizeof (lhs.symbol));
    TS_ASSERT_EQUALS(lhs.price_scale_code,                  rhs.price_scale_code);
    TS_ASSERT_EQUALS(lhs.quote_condition,                   rhs.quote_condition);
    TS_ASSERT_EQUALS(lhs.trading_status,                    rhs.trading_status);
//    TS_ASSERT_EQUALS(lhs.filler,                            rhs.filler);
    TS_ASSERT_EQUALS(lhs.mpv,                               rhs.mpv);

    TS_ASSERT_EQUALS(lhs.num_price_points,                  rhs.num_price_points);

    for (size_t idx = 0; idx < lhs.num_price_points; ++idx)
    {
        TS_ASSERT_EQUALS(lhs.price_points[idx].price_numerator, rhs.price_points[idx].price_numerator);
        TS_ASSERT_EQUALS(lhs.price_points[idx].volume,          rhs.price_points[idx].volume);
        TS_ASSERT_EQUALS(lhs.price_points[idx].num_orders,      rhs.price_points[idx].num_orders);
        TS_ASSERT_EQUALS(lhs.price_points[idx].side,            rhs.price_points[idx].side);
    }
}

class NyseObultraUnpackFullUpdateMsg : public CxxTest::TestSuite
{
private:

testing::internal::Random * m_random;

public:

NyseObultraUnpackFullUpdateMsg()
{
    m_random = new testing::internal::Random(time(0));
    srandom(time(0));
}
~NyseObultraUnpackFullUpdateMsg()
{
    delete m_random;
}

void test_00100_fails_when_input_packet_ptr_is_null(void)
{
    gen_test_input_packet_ptr_is_null<nyse_obultra_full_update_msg_t>
        (nyse_obultra_unpack_full_update_msg, m_random);
}

void test_00101_fails_when_input_packet_is_too_short__fixed(void)
{
    gen_test_input_packet_is_too_short<nyse_obultra_full_update_msg_t>
        (nyse_obultra_unpack_full_update_msg, NYSE_OBULTRA_FULL_UPDATE_FIXED_MSG_SIZE, m_random);
}

void test_00110_fails_when_input_packet_is_too_short__optional(void)
{
    nyse_obultra_full_update_msg_t        in_data;

    // compose random contents
    compose_random_msg(&in_data);

    // reserved space twice the size of the packet
    uint8_t     in_packet[2 * in_data.msg_size];
    uint8_t *   in_packet_p;

    // format contents at a varied offset inside the packet
    in_packet_p = format_message(&in_data, in_packet, sizeof (in_packet));

    size_t      in_size = m_random->Generate(in_data.msg_size);
    int         result;

    nyse_obultra_full_update_msg_t         out_data;

    result = nyse_obultra_unpack_full_update_msg(in_packet_p, in_size, NULL, NULL);

    TS_ASSERT_EQUALS(PDP_UNPACK_INPUT_PACKET_TOO_SHORT, result);
}

void test_00200_proper_packet_is_unpacked(void)
{
    nyse_obultra_full_update_msg_t        in_data;

    // compose random contents
    compose_random_msg(&in_data);

    // reserved space twice the size of the packet
    uint8_t     in_packet[2 * in_data.msg_size];
    uint8_t *   in_packet_p;

    // format contents at a varied offset inside the packet
    in_packet_p = format_message(&in_data, in_packet, sizeof (in_packet));

    // vary packet size passed to the unpacker [packet_size, 2 * packet_size]
    size_t      in_size = in_data.msg_size + m_random->Generate(in_data.msg_size + 1);

    nyse_obultra_full_update_msg_t         out_data;
    size_t      out_size;
    int         result;

    result = nyse_obultra_unpack_full_update_msg(in_packet_p, in_size, &out_data, &out_size);

    TS_ASSERT_EQUALS(PDP_UNPACK_SUCCESS, result);

    TS_ASSERT_EQUALS(out_size, in_data.msg_size);

    assert_messages_are_equal(out_data, in_data);
}

};
