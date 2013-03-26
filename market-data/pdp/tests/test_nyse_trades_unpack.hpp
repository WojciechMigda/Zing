/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: test_nyse_trades_unpack.hpp
 *
 * Description:
 *      description
 *
 * Authors:
 *          Wojciech Migda (wm)
 *
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-26   wm              Initial version
 *
 ******************************************************************************/


#include <cxxtest/TestSuite.h>
#include <gmock/gmock.h>
#include <stdint.h>
#include <stddef.h>
#include <cassert>
#include <ctime>

#include "anon_var.hpp"
#include "serializer.hpp"
#include "unpack_status.h"
#include "gen_test.hpp"

#include "nyse_trades_unpack.h"
#include "nyse_trades_pdp_header.h"
#include "nyse_trades_trade.h"
#include "nyse_trades_trade_cancel_or_error.h"
#include "nyse_trades_trade_correction.h"

////////////////////////////////////////////////////////////////////////////////

void compose_random_pdp_header(nyse_trades_pdp_header_t * const out_p)
{
    ANON_VAR(out_p->msg_size);
    ANON_VAR(out_p->msg_type);
    ANON_VAR(out_p->msg_seq_num);
    ANON_VAR(out_p->send_time);
    ANON_VAR(out_p->product_id);
    ANON_VAR(out_p->retrans_flag);
    ANON_VAR(out_p->num_body_entries);
    ANON_ARRAY(out_p->FILLER);
}

uint8_t * format_pdp_header(nyse_trades_pdp_header_t const * const i_hdr_p, uint8_t * o_buffer, const size_t o_buf_size)
{
    assert(o_buf_size >= NYSE_TRADES_PDP_HEADER_SIZE);

    size_t      random_offset = random() % (1 + o_buf_size - NYSE_TRADES_PDP_HEADER_SIZE);

    std::vector<uint8_t>    work_vec;

    serialize(i_hdr_p->msg_size, work_vec);
    serialize(i_hdr_p->msg_type, work_vec);
    serialize(i_hdr_p->msg_seq_num, work_vec);
    serialize(i_hdr_p->send_time, work_vec);
    serialize(i_hdr_p->product_id, work_vec);
    serialize(i_hdr_p->retrans_flag, work_vec);
    serialize(i_hdr_p->num_body_entries, work_vec);
    work_vec.insert(work_vec.end(), i_hdr_p->FILLER, i_hdr_p->FILLER + sizeof (i_hdr_p->FILLER));

    std::copy(work_vec.begin(), work_vec.end(), &o_buffer[random_offset]);

    return &o_buffer[random_offset];
}

void assert_pdp_headers_are_equal(const nyse_trades_pdp_header_t & lhs, const nyse_trades_pdp_header_t & rhs)
{
    TS_ASSERT_EQUALS(lhs.msg_size,          rhs.msg_size);
    TS_ASSERT_EQUALS(lhs.msg_type,          rhs.msg_type);
    TS_ASSERT_EQUALS(lhs.msg_seq_num,       rhs.msg_seq_num);
    TS_ASSERT_EQUALS(lhs.send_time,         rhs.send_time);
    TS_ASSERT_EQUALS(lhs.product_id,        rhs.product_id);
    TS_ASSERT_EQUALS(lhs.retrans_flag,      rhs.retrans_flag);
    TS_ASSERT_EQUALS(lhs.num_body_entries,  rhs.num_body_entries);
    TS_ASSERT_SAME_DATA(lhs.FILLER, rhs.FILLER, sizeof (lhs.FILLER));
}

class NyseTradesUnpackPdpHeader : public CxxTest::TestSuite
{
private:

testing::internal::Random * m_random;

public:
NyseTradesUnpackPdpHeader()
{
    m_random = new testing::internal::Random(time(0));
    srandom(time(0));
}
~NyseTradesUnpackPdpHeader()
{
    delete m_random;
}

void test_00100_fails_when_input_packet_ptr_is_null(void)
{
    gen_test_input_packet_ptr_is_null<nyse_trades_pdp_header_t>
        (nyse_trades_unpack_pdp_header, m_random);
}

void test_00101_fails_when_input_packet_is_too_short(void)
{
    gen_test_input_packet_is_too_short<nyse_trades_pdp_header_t>
        (nyse_trades_unpack_pdp_header, NYSE_TRADES_PDP_HEADER_SIZE, m_random);
}

void test_00200_proper_packet_is_unpacked(void)
{
    gen_test_input_packet_is_unpacked<nyse_trades_pdp_header_t>
        (
            compose_random_pdp_header,
            format_pdp_header,
            nyse_trades_unpack_pdp_header,
            assert_pdp_headers_are_equal,
            NYSE_TRADES_PDP_HEADER_SIZE,
            m_random);
}

};

////////////////////////////////////////////////////////////////////////////////

void compose_random_msg(nyse_trades_trade_msg_t * const out_p)
{
    ANON_VAR(out_p->source_time);
    ANON_VAR(out_p->link_id);
    ANON_VAR(out_p->filler);
    ANON_VAR(out_p->price_numerator);
    ANON_VAR(out_p->volume);
    ANON_VAR(out_p->source_seq_num);
    ANON_VAR(out_p->source_session_id);
    ANON_VAR(out_p->price_scale_code);
    ANON_VAR(out_p->exchange_id);
    ANON_VAR(out_p->security_type);
    ANON_VAR(out_p->trade_cond_1);
    ANON_VAR(out_p->trade_cond_2);
    ANON_VAR(out_p->trade_cond_3);
    ANON_VAR(out_p->trade_cond_4);
    ANON_ARRAY(out_p->symbol);
}

uint8_t * format_message(
    nyse_trades_trade_msg_t const * const i_msg_p,
    uint8_t * o_buffer,
    const size_t o_buf_size)
{
    assert(o_buf_size >= NYSE_TRADES_TRADE_MSG_SIZE);

    size_t      random_offset = random() % (1 + o_buf_size - NYSE_TRADES_TRADE_MSG_SIZE);

    std::vector<uint8_t>    work_vec;

    serialize(i_msg_p->source_time, work_vec);
    serialize(i_msg_p->link_id, work_vec);
    serialize(i_msg_p->filler, work_vec);
    serialize(i_msg_p->price_numerator, work_vec);
    serialize(i_msg_p->volume, work_vec);
    serialize(i_msg_p->source_seq_num, work_vec);
    serialize(i_msg_p->source_session_id, work_vec);
    serialize(i_msg_p->price_scale_code, work_vec);
    serialize(i_msg_p->exchange_id, work_vec);
    serialize(i_msg_p->security_type, work_vec);
    serialize(i_msg_p->trade_cond_1, work_vec);
    serialize(i_msg_p->trade_cond_2, work_vec);
    serialize(i_msg_p->trade_cond_3, work_vec);
    serialize(i_msg_p->trade_cond_4, work_vec);
    work_vec.insert(work_vec.end(), i_msg_p->symbol, i_msg_p->symbol + sizeof (i_msg_p->symbol));

    std::copy(work_vec.begin(), work_vec.end(), &o_buffer[random_offset]);

    return &o_buffer[random_offset];
}

void assert_messages_are_equal(const nyse_trades_trade_msg_t & lhs, const nyse_trades_trade_msg_t & rhs)
{
    TS_ASSERT_EQUALS(lhs.source_time,           rhs.source_time);
    TS_ASSERT_EQUALS(lhs.link_id,               rhs.link_id);
    TS_ASSERT_EQUALS(lhs.price_numerator,       rhs.price_numerator);
    TS_ASSERT_EQUALS(lhs.volume,                rhs.volume);
    TS_ASSERT_EQUALS(lhs.source_seq_num,        rhs.source_seq_num);
    TS_ASSERT_EQUALS(lhs.source_session_id,     rhs.source_session_id);
    TS_ASSERT_EQUALS(lhs.price_scale_code,      rhs.price_scale_code);
    TS_ASSERT_EQUALS(lhs.exchange_id,           rhs.exchange_id);
    TS_ASSERT_EQUALS(lhs.security_type,         rhs.security_type);
    TS_ASSERT_EQUALS(lhs.trade_cond_1,          rhs.trade_cond_1);
    TS_ASSERT_EQUALS(lhs.trade_cond_2,          rhs.trade_cond_2);
    TS_ASSERT_EQUALS(lhs.trade_cond_3,          rhs.trade_cond_3);
    TS_ASSERT_EQUALS(lhs.trade_cond_4,          rhs.trade_cond_4);
    TS_ASSERT_SAME_DATA(lhs.symbol, rhs.symbol, sizeof (lhs.symbol));
}

class NyseTradesUnpackTradeMsg : public CxxTest::TestSuite
{
private:

testing::internal::Random * m_random;

public:

NyseTradesUnpackTradeMsg()
{
    m_random = new testing::internal::Random(time(0));
    srandom(time(0));
}
~NyseTradesUnpackTradeMsg()
{
    delete m_random;
}

void test_00100_fails_when_input_packet_ptr_is_null(void)
{
    gen_test_input_packet_ptr_is_null<nyse_trades_trade_msg_t>
        (nyse_trades_unpack_trade_msg, m_random);
}

void test_00101_fails_when_input_packet_is_too_short(void)
{
    gen_test_input_packet_is_too_short<nyse_trades_trade_msg_t>
        (nyse_trades_unpack_trade_msg, NYSE_TRADES_TRADE_MSG_SIZE, m_random);
}

void test_00200_proper_packet_is_unpacked(void)
{
    gen_test_input_packet_is_unpacked<nyse_trades_trade_msg_t>
        (
            compose_random_msg,
            format_message,
            nyse_trades_unpack_trade_msg,
            assert_messages_are_equal,
            NYSE_TRADES_TRADE_MSG_SIZE,
            m_random);
}

};

////////////////////////////////////////////////////////////////////////////////

void compose_random_msg(nyse_trades_trade_cancel_or_error_msg_t * const out_p)
{
    ANON_VAR(out_p->source_time);
    ANON_VAR(out_p->source_seq_num);
    ANON_VAR(out_p->original_trade_ref_num);
    ANON_VAR(out_p->source_session_id);
    ANON_VAR(out_p->exchange_id);
    ANON_VAR(out_p->security_type);
    ANON_ARRAY(out_p->filler);
    ANON_ARRAY(out_p->symbol);
}

uint8_t * format_message(
    nyse_trades_trade_cancel_or_error_msg_t const * const i_msg_p,
    uint8_t * o_buffer,
    const size_t o_buf_size)
{
    assert(o_buf_size >= NYSE_TRADES_TRADE_CANCEL_OR_ERROR_MSG_SIZE);

    size_t      random_offset = random() % (1 + o_buf_size - NYSE_TRADES_TRADE_CANCEL_OR_ERROR_MSG_SIZE);

    std::vector<uint8_t>    work_vec;

    serialize(i_msg_p->source_time, work_vec);
    serialize(i_msg_p->source_seq_num, work_vec);
    serialize(i_msg_p->original_trade_ref_num, work_vec);
    serialize(i_msg_p->source_session_id, work_vec);
    serialize(i_msg_p->exchange_id, work_vec);
    serialize(i_msg_p->security_type, work_vec);
    work_vec.insert(work_vec.end(), i_msg_p->filler, i_msg_p->filler + sizeof (i_msg_p->filler));
    work_vec.insert(work_vec.end(), i_msg_p->symbol, i_msg_p->symbol + sizeof (i_msg_p->symbol));

    std::copy(work_vec.begin(), work_vec.end(), &o_buffer[random_offset]);

    return &o_buffer[random_offset];
}

void assert_messages_are_equal(const nyse_trades_trade_cancel_or_error_msg_t & lhs, const nyse_trades_trade_cancel_or_error_msg_t & rhs)
{
    TS_ASSERT_EQUALS(lhs.source_time,           rhs.source_time);
    TS_ASSERT_EQUALS(lhs.source_seq_num,        rhs.source_seq_num);
    TS_ASSERT_EQUALS(lhs.original_trade_ref_num, rhs.original_trade_ref_num);
    TS_ASSERT_EQUALS(lhs.source_session_id,     rhs.source_session_id);
    TS_ASSERT_EQUALS(lhs.exchange_id,           rhs.exchange_id);
    TS_ASSERT_EQUALS(lhs.security_type,         rhs.security_type);
    TS_ASSERT_SAME_DATA(lhs.symbol, rhs.symbol, sizeof (lhs.symbol));
}

class NyseTradesUnpackTradeCancelOrErrorMsg : public CxxTest::TestSuite
{
private:

testing::internal::Random * m_random;

public:

NyseTradesUnpackTradeCancelOrErrorMsg()
{
    m_random = new testing::internal::Random(time(0));
    srandom(time(0));
}
~NyseTradesUnpackTradeCancelOrErrorMsg()
{
    delete m_random;
}

void test_00100_fails_when_input_packet_ptr_is_null(void)
{
    gen_test_input_packet_ptr_is_null<nyse_trades_trade_cancel_or_error_msg_t>
        (nyse_trades_unpack_trade_cancel_or_error_msg, m_random);
}

void test_00101_fails_when_input_packet_is_too_short(void)
{
    gen_test_input_packet_is_too_short<nyse_trades_trade_cancel_or_error_msg_t>
        (nyse_trades_unpack_trade_cancel_or_error_msg, NYSE_TRADES_TRADE_CANCEL_OR_ERROR_MSG_SIZE, m_random);
}

void test_00200_proper_packet_is_unpacked(void)
{
    gen_test_input_packet_is_unpacked<nyse_trades_trade_cancel_or_error_msg_t>
        (
            compose_random_msg,
            format_message,
            nyse_trades_unpack_trade_cancel_or_error_msg,
            assert_messages_are_equal,
            NYSE_TRADES_TRADE_CANCEL_OR_ERROR_MSG_SIZE,
            m_random);
}

};

////////////////////////////////////////////////////////////////////////////////

void compose_random_msg(nyse_trades_trade_correction_msg_t * const out_p)
{
    ANON_VAR(out_p->source_time);
    ANON_VAR(out_p->filler1);
    ANON_VAR(out_p->filler2);
    ANON_VAR(out_p->price_numerator);
    ANON_VAR(out_p->volume);
    ANON_VAR(out_p->source_seq_num);
    ANON_VAR(out_p->original_trade_ref_num);
    ANON_VAR(out_p->source_session_id);
    ANON_VAR(out_p->price_scale_code);
    ANON_VAR(out_p->exchange_id);
    ANON_VAR(out_p->security_type);
    ANON_VAR(out_p->corrected_trade_cond_1);
    ANON_VAR(out_p->corrected_trade_cond_2);
    ANON_VAR(out_p->corrected_trade_cond_3);
    ANON_VAR(out_p->corrected_trade_cond_4);
    ANON_ARRAY(out_p->symbol);
}

uint8_t * format_message(
    nyse_trades_trade_correction_msg_t const * const i_msg_p,
    uint8_t * o_buffer,
    const size_t o_buf_size)
{
    assert(o_buf_size >= NYSE_TRADES_TRADE_CORRECTION_MSG_SIZE);

    size_t      random_offset = random() % (1 + o_buf_size - NYSE_TRADES_TRADE_CORRECTION_MSG_SIZE);

    std::vector<uint8_t>    work_vec;

    serialize(i_msg_p->source_time, work_vec);
    serialize(i_msg_p->filler1, work_vec);
    serialize(i_msg_p->filler2, work_vec);
    serialize(i_msg_p->price_numerator, work_vec);
    serialize(i_msg_p->volume, work_vec);
    serialize(i_msg_p->source_seq_num, work_vec);
    serialize(i_msg_p->original_trade_ref_num, work_vec);
    serialize(i_msg_p->source_session_id, work_vec);
    serialize(i_msg_p->price_scale_code, work_vec);
    serialize(i_msg_p->exchange_id, work_vec);
    serialize(i_msg_p->security_type, work_vec);
    serialize(i_msg_p->corrected_trade_cond_1, work_vec);
    serialize(i_msg_p->corrected_trade_cond_2, work_vec);
    serialize(i_msg_p->corrected_trade_cond_3, work_vec);
    serialize(i_msg_p->corrected_trade_cond_4, work_vec);
    work_vec.insert(work_vec.end(), i_msg_p->symbol, i_msg_p->symbol + sizeof (i_msg_p->symbol));

    std::copy(work_vec.begin(), work_vec.end(), &o_buffer[random_offset]);

    return &o_buffer[random_offset];
}

void assert_messages_are_equal(const nyse_trades_trade_correction_msg_t & lhs, const nyse_trades_trade_correction_msg_t & rhs)
{
    TS_ASSERT_EQUALS(lhs.source_time,           rhs.source_time);
    TS_ASSERT_EQUALS(lhs.price_numerator,       rhs.price_numerator);
    TS_ASSERT_EQUALS(lhs.volume,                rhs.volume);
    TS_ASSERT_EQUALS(lhs.source_seq_num,        rhs.source_seq_num);
    TS_ASSERT_EQUALS(lhs.original_trade_ref_num, rhs.original_trade_ref_num);
    TS_ASSERT_EQUALS(lhs.source_session_id,     rhs.source_session_id);
    TS_ASSERT_EQUALS(lhs.price_scale_code,      rhs.price_scale_code);
    TS_ASSERT_EQUALS(lhs.exchange_id,           rhs.exchange_id);
    TS_ASSERT_EQUALS(lhs.security_type,         rhs.security_type);
    TS_ASSERT_EQUALS(lhs.corrected_trade_cond_1,          rhs.corrected_trade_cond_1);
    TS_ASSERT_EQUALS(lhs.corrected_trade_cond_2,          rhs.corrected_trade_cond_2);
    TS_ASSERT_EQUALS(lhs.corrected_trade_cond_3,          rhs.corrected_trade_cond_3);
    TS_ASSERT_EQUALS(lhs.corrected_trade_cond_4,          rhs.corrected_trade_cond_4);
    TS_ASSERT_SAME_DATA(lhs.symbol, rhs.symbol, sizeof (lhs.symbol));
}

class NyseTradesUnpackTradeCorrectionMsg : public CxxTest::TestSuite
{
private:

testing::internal::Random * m_random;

public:

NyseTradesUnpackTradeCorrectionMsg()
{
    m_random = new testing::internal::Random(time(0));
    srandom(time(0));
}
~NyseTradesUnpackTradeCorrectionMsg()
{
    delete m_random;
}

void test_00100_fails_when_input_packet_ptr_is_null(void)
{
    gen_test_input_packet_ptr_is_null<nyse_trades_trade_correction_msg_t>
        (nyse_trades_unpack_trade_correction_msg, m_random);
}

void test_00101_fails_when_input_packet_is_too_short(void)
{
    gen_test_input_packet_is_too_short<nyse_trades_trade_correction_msg_t>
        (nyse_trades_unpack_trade_correction_msg, NYSE_TRADES_TRADE_CORRECTION_MSG_SIZE, m_random);
}

void test_00200_proper_packet_is_unpacked(void)
{
    gen_test_input_packet_is_unpacked<nyse_trades_trade_correction_msg_t>
        (
            compose_random_msg,
            format_message,
            nyse_trades_unpack_trade_correction_msg,
            assert_messages_are_equal,
            NYSE_TRADES_TRADE_CORRECTION_MSG_SIZE,
            m_random);
}

};
