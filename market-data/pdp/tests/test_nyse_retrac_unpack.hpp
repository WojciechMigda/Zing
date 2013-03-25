/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: test_nyse_retrac_unpack.hpp
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

#include "nyse_retrac_unpack.h"
#include "nyse_retrac_pdp_header.h"
#include "nyse_retrac_execution_report.h"
#include "nyse_retrac_execution_report_cancellation.h"
#include "nyse_retrac_summary.h"

////////////////////////////////////////////////////////////////////////////////

void compose_random_pdp_header(nyse_retrac_pdp_header_t * const out_p)
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

uint8_t * format_pdp_header(nyse_retrac_pdp_header_t const * const i_hdr_p, uint8_t * o_buffer, const size_t o_buf_size)
{
    assert(o_buf_size >= NYSE_RETRAC_PDP_HEADER_SIZE);

    size_t      random_offset = random() % (1 + o_buf_size - NYSE_RETRAC_PDP_HEADER_SIZE);

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

void assert_pdp_headers_are_equal(const nyse_retrac_pdp_header_t & lhs, const nyse_retrac_pdp_header_t & rhs)
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

class NyseRetracUnpackPdpHeader : public CxxTest::TestSuite
{
private:

testing::internal::Random * m_random;

public:
NyseRetracUnpackPdpHeader()
{
    m_random = new testing::internal::Random(time(0));
    srandom(time(0));
}
~NyseRetracUnpackPdpHeader()
{
    delete m_random;
}

void test_00100_fails_when_input_packet_ptr_is_null(void)
{
    gen_test_input_packet_ptr_is_null<nyse_retrac_pdp_header_t>
        (nyse_retrac_unpack_pdp_header, m_random);
}

void test_00101_fails_when_input_packet_is_too_short(void)
{
    gen_test_input_packet_is_too_short<nyse_retrac_pdp_header_t>
        (nyse_retrac_unpack_pdp_header, NYSE_RETRAC_PDP_HEADER_SIZE, m_random);
}

void test_00200_proper_packet_is_unpacked(void)
{
    gen_test_input_packet_is_unpacked<nyse_retrac_pdp_header_t>
        (
            compose_random_pdp_header,
            format_pdp_header,
            nyse_retrac_unpack_pdp_header,
            assert_pdp_headers_are_equal,
            NYSE_RETRAC_PDP_HEADER_SIZE,
            m_random);
}

};

////////////////////////////////////////////////////////////////////////////////

void compose_random_msg(nyse_retrac_execution_report_msg_t * const out_p)
{
    ANON_VAR(out_p->exec_time);
    ANON_ARRAY(out_p->symbol);
    ANON_VAR(out_p->volume);
    ANON_VAR(out_p->link_id);
    ANON_VAR(out_p->execution_type);
}

uint8_t * format_message(
    nyse_retrac_execution_report_msg_t const * const i_msg_p,
    uint8_t * o_buffer,
    const size_t o_buf_size)
{
    assert(o_buf_size >= NYSE_RETRAC_EXECUTION_REPORT_MSG_SIZE);

    size_t      random_offset = random() % (1 + o_buf_size - NYSE_RETRAC_EXECUTION_REPORT_MSG_SIZE);

    std::vector<uint8_t>    work_vec;

    serialize(i_msg_p->exec_time, work_vec);
    work_vec.insert(work_vec.end(), i_msg_p->symbol, i_msg_p->symbol + sizeof (i_msg_p->symbol));
    serialize(i_msg_p->volume, work_vec);
    serialize(i_msg_p->link_id, work_vec);
    serialize(i_msg_p->execution_type, work_vec);

    std::copy(work_vec.begin(), work_vec.end(), &o_buffer[random_offset]);

    return &o_buffer[random_offset];
}

void assert_messages_are_equal(const nyse_retrac_execution_report_msg_t & lhs, const nyse_retrac_execution_report_msg_t & rhs)
{
    TS_ASSERT_EQUALS(lhs.exec_time,             rhs.exec_time);
    TS_ASSERT_SAME_DATA(lhs.symbol, rhs.symbol, sizeof (lhs.symbol));
    TS_ASSERT_EQUALS(lhs.volume,                rhs.volume);
    TS_ASSERT_EQUALS(lhs.link_id,               rhs.link_id);
    TS_ASSERT_EQUALS(lhs.execution_type,        rhs.execution_type);
}

class NyseRetracUnpackExecutionReportMsg : public CxxTest::TestSuite
{
private:

testing::internal::Random * m_random;

public:

NyseRetracUnpackExecutionReportMsg()
{
    m_random = new testing::internal::Random(time(0));
    srandom(time(0));
}
~NyseRetracUnpackExecutionReportMsg()
{
    delete m_random;
}

void test_00100_fails_when_input_packet_ptr_is_null(void)
{
    gen_test_input_packet_ptr_is_null<nyse_retrac_execution_report_msg_t>
        (nyse_retrac_unpack_execution_report_msg, m_random);
}

void test_00101_fails_when_input_packet_is_too_short(void)
{
    gen_test_input_packet_is_too_short<nyse_retrac_execution_report_msg_t>
        (nyse_retrac_unpack_execution_report_msg, NYSE_RETRAC_EXECUTION_REPORT_MSG_SIZE, m_random);
}

void test_00200_proper_packet_is_unpacked(void)
{
    gen_test_input_packet_is_unpacked<nyse_retrac_execution_report_msg_t>
        (
            compose_random_msg,
            format_message,
            nyse_retrac_unpack_execution_report_msg,
            assert_messages_are_equal,
            NYSE_RETRAC_EXECUTION_REPORT_MSG_SIZE,
            m_random);
}

};

////////////////////////////////////////////////////////////////////////////////

void compose_random_msg(nyse_retrac_execution_report_cancellation_msg_t * const out_p)
{
    ANON_VAR(out_p->exec_time);
    ANON_ARRAY(out_p->symbol);
    ANON_VAR(out_p->volume);
    ANON_VAR(out_p->link_id);
    ANON_VAR(out_p->execution_type);
}

uint8_t * format_message(
    nyse_retrac_execution_report_cancellation_msg_t const * const i_msg_p,
    uint8_t * o_buffer,
    const size_t o_buf_size)
{
    assert(o_buf_size >= NYSE_RETRAC_EXECUTION_REPORT_CANCELLATION_MSG_SIZE);

    size_t      random_offset = random() % (1 + o_buf_size - NYSE_RETRAC_EXECUTION_REPORT_CANCELLATION_MSG_SIZE);

    std::vector<uint8_t>    work_vec;

    serialize(i_msg_p->exec_time, work_vec);
    work_vec.insert(work_vec.end(), i_msg_p->symbol, i_msg_p->symbol + sizeof (i_msg_p->symbol));
    serialize(i_msg_p->volume, work_vec);
    serialize(i_msg_p->link_id, work_vec);
    serialize(i_msg_p->execution_type, work_vec);

    std::copy(work_vec.begin(), work_vec.end(), &o_buffer[random_offset]);

    return &o_buffer[random_offset];
}

void assert_messages_are_equal(const nyse_retrac_execution_report_cancellation_msg_t & lhs, const nyse_retrac_execution_report_cancellation_msg_t & rhs)
{
    TS_ASSERT_EQUALS(lhs.exec_time,             rhs.exec_time);
    TS_ASSERT_SAME_DATA(lhs.symbol, rhs.symbol, sizeof (lhs.symbol));
    TS_ASSERT_EQUALS(lhs.volume,                rhs.volume);
    TS_ASSERT_EQUALS(lhs.link_id,               rhs.link_id);
    TS_ASSERT_EQUALS(lhs.execution_type,        rhs.execution_type);
}

class NyseRetracUnpackExecutionReportCancellationMsg : public CxxTest::TestSuite
{
private:

testing::internal::Random * m_random;

public:

NyseRetracUnpackExecutionReportCancellationMsg()
{
    m_random = new testing::internal::Random(time(0));
    srandom(time(0));
}
~NyseRetracUnpackExecutionReportCancellationMsg()
{
    delete m_random;
}

void test_00100_fails_when_input_packet_ptr_is_null(void)
{
    gen_test_input_packet_ptr_is_null<nyse_retrac_execution_report_cancellation_msg_t>
        (nyse_retrac_unpack_execution_report_cancellation_msg, m_random);
}

void test_00101_fails_when_input_packet_is_too_short(void)
{
    gen_test_input_packet_is_too_short<nyse_retrac_execution_report_cancellation_msg_t>
        (nyse_retrac_unpack_execution_report_cancellation_msg, NYSE_RETRAC_EXECUTION_REPORT_CANCELLATION_MSG_SIZE, m_random);
}

void test_00200_proper_packet_is_unpacked(void)
{
    gen_test_input_packet_is_unpacked<nyse_retrac_execution_report_cancellation_msg_t>
        (
            compose_random_msg,
            format_message,
            nyse_retrac_unpack_execution_report_cancellation_msg,
            assert_messages_are_equal,
            NYSE_RETRAC_EXECUTION_REPORT_CANCELLATION_MSG_SIZE,
            m_random);
}

};

////////////////////////////////////////////////////////////////////////////////

void compose_random_msg(nyse_retrac_summary_msg_t * const out_p)
{
    ANON_ARRAY(out_p->symbol);
    ANON_VAR(out_p->total_volume);
    ANON_VAR(out_p->execution_type);
}

uint8_t * format_message(
    nyse_retrac_summary_msg_t const * const i_msg_p,
    uint8_t * o_buffer,
    const size_t o_buf_size)
{
    assert(o_buf_size >= NYSE_RETRAC_SUMMARY_MSG_SIZE);

    size_t      random_offset = random() % (1 + o_buf_size - NYSE_RETRAC_SUMMARY_MSG_SIZE);

    std::vector<uint8_t>    work_vec;

    work_vec.insert(work_vec.end(), i_msg_p->symbol, i_msg_p->symbol + sizeof (i_msg_p->symbol));
    serialize(i_msg_p->total_volume, work_vec);
    serialize(i_msg_p->execution_type, work_vec);

    std::copy(work_vec.begin(), work_vec.end(), &o_buffer[random_offset]);

    return &o_buffer[random_offset];
}

void assert_messages_are_equal(const nyse_retrac_summary_msg_t & lhs, const nyse_retrac_summary_msg_t & rhs)
{
    TS_ASSERT_SAME_DATA(lhs.symbol, rhs.symbol, sizeof (lhs.symbol));
    TS_ASSERT_EQUALS(lhs.total_volume,          rhs.total_volume);
    TS_ASSERT_EQUALS(lhs.execution_type,        rhs.execution_type);
}

class NyseRetracUnpackSummaryMsg : public CxxTest::TestSuite
{
private:

testing::internal::Random * m_random;

public:

NyseRetracUnpackSummaryMsg()
{
    m_random = new testing::internal::Random(time(0));
    srandom(time(0));
}
~NyseRetracUnpackSummaryMsg()
{
    delete m_random;
}

void test_00100_fails_when_input_packet_ptr_is_null(void)
{
    gen_test_input_packet_ptr_is_null<nyse_retrac_summary_msg_t>
        (nyse_retrac_unpack_summary_msg, m_random);
}

void test_00101_fails_when_input_packet_is_too_short(void)
{
    gen_test_input_packet_is_too_short<nyse_retrac_summary_msg_t>
        (nyse_retrac_unpack_summary_msg, NYSE_RETRAC_SUMMARY_MSG_SIZE, m_random);
}

void test_00200_proper_packet_is_unpacked(void)
{
    gen_test_input_packet_is_unpacked<nyse_retrac_summary_msg_t>
        (
            compose_random_msg,
            format_message,
            nyse_retrac_unpack_summary_msg,
            assert_messages_are_equal,
            NYSE_RETRAC_SUMMARY_MSG_SIZE,
            m_random);
}

};
