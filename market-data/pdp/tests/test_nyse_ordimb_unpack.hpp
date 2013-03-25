/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: test_nyse_ordimb_unpack.hpp
 *
 * Description:
 *      Testcases for the NYSE Order Imbalances unpacking routines
 *
 * Authors:
 *          Wojciech Migda (wm)
 *
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-25   wm              Initial version
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

#include "nyse_ordimb_unpack.h"
#include "nyse_ordimb_pdp_header.h"
#include "nyse_ordimb_opening_imbalance_msg.h"
#include "nyse_ordimb_closing_imbalance_msg.h"

////////////////////////////////////////////////////////////////////////////////

void compose_random_pdp_header(nyse_ordimb_pdp_header_t * const out_p)
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

uint8_t * format_pdp_header(nyse_ordimb_pdp_header_t const * const i_hdr_p, uint8_t * o_buffer, const size_t o_buf_size)
{
    assert(o_buf_size >= NYSE_ORDIMB_PDP_HEADER_SIZE);

    size_t      random_offset = random() % (1 + o_buf_size - NYSE_ORDIMB_PDP_HEADER_SIZE);

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

void assert_pdp_headers_are_equal(const nyse_ordimb_pdp_header_t & lhs, const nyse_ordimb_pdp_header_t & rhs)
{
    TS_ASSERT_EQUALS(lhs.msg_size,          rhs.msg_size);
    TS_ASSERT_EQUALS(lhs.msg_type,          rhs.msg_type);
    TS_ASSERT_EQUALS(lhs.msg_seq_num,       rhs.msg_seq_num);
    TS_ASSERT_EQUALS(lhs.send_time,         rhs.send_time);
    TS_ASSERT_EQUALS(lhs.product_id,        rhs.product_id);
    TS_ASSERT_EQUALS(lhs.retrans_flag,      rhs.retrans_flag);
    TS_ASSERT_EQUALS(lhs.num_body_entries,  rhs.num_body_entries);
    TS_ASSERT_SAME_DATA(lhs.filler, rhs.filler, sizeof (lhs.filler));
}


class NyseOrdimbUnpackPdpHeader : public CxxTest::TestSuite
{
private:

testing::internal::Random * m_random;

public:
NyseOrdimbUnpackPdpHeader()
{
    m_random = new testing::internal::Random(time(0));
    srandom(time(0));
}
~NyseOrdimbUnpackPdpHeader()
{
    delete m_random;
}

void test_00100_fails_when_input_packet_ptr_is_null(void)
{
    gen_test_input_packet_ptr_is_null<nyse_ordimb_pdp_header_t>
        (nyse_ordimb_unpack_pdp_header, m_random);
}

void test_00101_fails_when_input_packet_is_too_short(void)
{
    gen_test_input_packet_is_too_short<nyse_ordimb_pdp_header_t>
        (nyse_ordimb_unpack_pdp_header, NYSE_ORDIMB_PDP_HEADER_SIZE, m_random);
}

void test_00200_proper_packet_is_unpacked(void)
{
    gen_test_input_packet_is_unpacked<nyse_ordimb_pdp_header_t>
        (
            compose_random_pdp_header,
            format_pdp_header,
            nyse_ordimb_unpack_pdp_header,
            assert_pdp_headers_are_equal,
            NYSE_ORDIMB_PDP_HEADER_SIZE,
            m_random);
}

};

////////////////////////////////////////////////////////////////////////////////

void compose_random_msg(nyse_ordimb_opening_imb_msg_t * const out_p)
{
    ANON_ARRAY(out_p->symbol);
    ANON_VAR(out_p->stock_open_indicator);
    ANON_VAR(out_p->imbalance_side);
    ANON_VAR(out_p->price_scale_code);
    ANON_VAR(out_p->reference_price_numerator);
    ANON_VAR(out_p->imbalance_quantity);
    ANON_VAR(out_p->paired_quantity);
    ANON_VAR(out_p->clearing_price_numerator);
    ANON_VAR(out_p->source_time);
    ANON_VAR(out_p->ssr_filing_price_numerator);
}

uint8_t * format_message(
    nyse_ordimb_opening_imb_msg_t const * const i_msg_p,
    uint8_t * o_buffer,
    const size_t o_buf_size)
{
    assert(o_buf_size >= NYSE_ORDIMB_OPENING_IMBALANCE_MSG_SIZE);

    size_t      random_offset = random() % (1 + o_buf_size - NYSE_ORDIMB_OPENING_IMBALANCE_MSG_SIZE);

    std::vector<uint8_t>    work_vec;

    work_vec.insert(work_vec.end(), i_msg_p->symbol, i_msg_p->symbol + sizeof (i_msg_p->symbol));
    serialize(i_msg_p->stock_open_indicator, work_vec);
    serialize(i_msg_p->imbalance_side, work_vec);
    serialize(i_msg_p->price_scale_code, work_vec);
    serialize(i_msg_p->reference_price_numerator, work_vec);
    serialize(i_msg_p->imbalance_quantity, work_vec);
    serialize(i_msg_p->paired_quantity, work_vec);
    serialize(i_msg_p->clearing_price_numerator, work_vec);
    serialize(i_msg_p->source_time, work_vec);
    serialize(i_msg_p->ssr_filing_price_numerator, work_vec);

    std::copy(work_vec.begin(), work_vec.end(), &o_buffer[random_offset]);

    return &o_buffer[random_offset];
}

void assert_messages_are_equal(const nyse_ordimb_opening_imb_msg_t & lhs, const nyse_ordimb_opening_imb_msg_t & rhs)
{
    TS_ASSERT_SAME_DATA(lhs.symbol, rhs.symbol, sizeof (lhs.symbol));
    TS_ASSERT_EQUALS(lhs.stock_open_indicator,              rhs.stock_open_indicator);
    TS_ASSERT_EQUALS(lhs.imbalance_side,                    rhs.imbalance_side);
    TS_ASSERT_EQUALS(lhs.price_scale_code,                  rhs.price_scale_code);
    TS_ASSERT_EQUALS(lhs.reference_price_numerator,         rhs.reference_price_numerator);
    TS_ASSERT_EQUALS(lhs.imbalance_quantity,                rhs.imbalance_quantity);
    TS_ASSERT_EQUALS(lhs.paired_quantity,                   rhs.paired_quantity);
    TS_ASSERT_EQUALS(lhs.clearing_price_numerator,          rhs.clearing_price_numerator);
    TS_ASSERT_EQUALS(lhs.source_time,                       rhs.source_time);
    TS_ASSERT_EQUALS(lhs.ssr_filing_price_numerator,        rhs.ssr_filing_price_numerator);
}

class NyseOrdimbUnpackOpeningImbalanceMsg : public CxxTest::TestSuite
{
private:

testing::internal::Random * m_random;

public:

NyseOrdimbUnpackOpeningImbalanceMsg()
{
    m_random = new testing::internal::Random(time(0));
    srandom(time(0));
}
~NyseOrdimbUnpackOpeningImbalanceMsg()
{
    delete m_random;
}

void test_00100_fails_when_input_packet_ptr_is_null(void)
{
    gen_test_input_packet_ptr_is_null<nyse_ordimb_opening_imb_msg_t>
        (nyse_ordimb_unpack_opening_imbalance_msg, m_random);
}

void test_00101_fails_when_input_packet_is_too_short(void)
{
    gen_test_input_packet_is_too_short<nyse_ordimb_opening_imb_msg_t>
        (nyse_ordimb_unpack_opening_imbalance_msg, NYSE_ORDIMB_OPENING_IMBALANCE_MSG_SIZE, m_random);
}

void test_00200_proper_packet_is_unpacked(void)
{
    gen_test_input_packet_is_unpacked<nyse_ordimb_opening_imb_msg_t>
        (
            compose_random_msg,
            format_message,
            nyse_ordimb_unpack_opening_imbalance_msg,
            assert_messages_are_equal,
            NYSE_ORDIMB_OPENING_IMBALANCE_MSG_SIZE,
            m_random);
}

};

////////////////////////////////////////////////////////////////////////////////

void compose_random_msg(nyse_ordimb_closing_imb_msg_t * const out_p)
{
    ANON_ARRAY(out_p->symbol);
    ANON_VAR(out_p->regulatory_imbalance_indicator);
    ANON_VAR(out_p->imbalance_side);
    ANON_VAR(out_p->price_scale_code);
    ANON_VAR(out_p->reference_price_numerator);
    ANON_VAR(out_p->imbalance_quantity);
    ANON_VAR(out_p->paired_quantity);
    ANON_VAR(out_p->continuous_book_clearing_price_numerator);
    ANON_VAR(out_p->closing_only_book_clearing_price_numerator);
    ANON_VAR(out_p->source_time);
}

uint8_t * format_message(
    nyse_ordimb_closing_imb_msg_t const * const i_msg_p,
    uint8_t * o_buffer,
    const size_t o_buf_size)
{
    assert(o_buf_size >= NYSE_ORDIMB_CLOSING_IMBALANCE_MSG_SIZE);

    size_t      random_offset = random() % (1 + o_buf_size - NYSE_ORDIMB_CLOSING_IMBALANCE_MSG_SIZE);

    std::vector<uint8_t>    work_vec;

    work_vec.insert(work_vec.end(), i_msg_p->symbol, i_msg_p->symbol + sizeof (i_msg_p->symbol));
    serialize(i_msg_p->regulatory_imbalance_indicator, work_vec);
    serialize(i_msg_p->imbalance_side, work_vec);
    serialize(i_msg_p->price_scale_code, work_vec);
    serialize(i_msg_p->reference_price_numerator, work_vec);
    serialize(i_msg_p->imbalance_quantity, work_vec);
    serialize(i_msg_p->paired_quantity, work_vec);
    serialize(i_msg_p->continuous_book_clearing_price_numerator, work_vec);
    serialize(i_msg_p->closing_only_book_clearing_price_numerator, work_vec);
    serialize(i_msg_p->source_time, work_vec);

    std::copy(work_vec.begin(), work_vec.end(), &o_buffer[random_offset]);

    return &o_buffer[random_offset];
}

void assert_messages_are_equal(const nyse_ordimb_closing_imb_msg_t & lhs, const nyse_ordimb_closing_imb_msg_t & rhs)
{
    TS_ASSERT_SAME_DATA(lhs.symbol, rhs.symbol, sizeof (lhs.symbol));
    TS_ASSERT_EQUALS(lhs.regulatory_imbalance_indicator,    rhs.regulatory_imbalance_indicator);
    TS_ASSERT_EQUALS(lhs.imbalance_side,                    rhs.imbalance_side);
    TS_ASSERT_EQUALS(lhs.price_scale_code,                  rhs.price_scale_code);
    TS_ASSERT_EQUALS(lhs.reference_price_numerator,         rhs.reference_price_numerator);
    TS_ASSERT_EQUALS(lhs.imbalance_quantity,                rhs.imbalance_quantity);
    TS_ASSERT_EQUALS(lhs.paired_quantity,                   rhs.paired_quantity);
    TS_ASSERT_EQUALS(lhs.continuous_book_clearing_price_numerator, rhs.continuous_book_clearing_price_numerator);
    TS_ASSERT_EQUALS(lhs.closing_only_book_clearing_price_numerator, rhs.closing_only_book_clearing_price_numerator);
    TS_ASSERT_EQUALS(lhs.source_time,                       rhs.source_time);
}

class NyseOrdimbUnpackClosingImbalanceMsg : public CxxTest::TestSuite
{
private:

testing::internal::Random * m_random;

public:

NyseOrdimbUnpackClosingImbalanceMsg()
{
    m_random = new testing::internal::Random(time(0));
    srandom(time(0));
}
~NyseOrdimbUnpackClosingImbalanceMsg()
{
    delete m_random;
}

void test_00100_fails_when_input_packet_ptr_is_null(void)
{
    gen_test_input_packet_ptr_is_null<nyse_ordimb_closing_imb_msg_t>
        (nyse_ordimb_unpack_closing_imbalance_msg, m_random);
}

void test_00101_fails_when_input_packet_is_too_short(void)
{
    gen_test_input_packet_is_too_short<nyse_ordimb_closing_imb_msg_t>
        (nyse_ordimb_unpack_closing_imbalance_msg, NYSE_ORDIMB_CLOSING_IMBALANCE_MSG_SIZE, m_random);
}

void test_00200_proper_packet_is_unpacked(void)
{
    gen_test_input_packet_is_unpacked<nyse_ordimb_closing_imb_msg_t>
        (
            compose_random_msg,
            format_message,
            nyse_ordimb_unpack_closing_imbalance_msg,
            assert_messages_are_equal,
            NYSE_ORDIMB_CLOSING_IMBALANCE_MSG_SIZE,
            m_random);
}

};
