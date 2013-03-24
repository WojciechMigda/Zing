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
