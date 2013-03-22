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
#include "nyse_lrp_pdp.h"
#include "unpack_status.h"
#include "nyse_lrp_unpack.h"

class NyseLrpUnpackPdpHeader : public CxxTest::TestSuite
{
private:

testing::internal::Random * m_random;

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

    size_t      random_offset =
        m_random->Generate(1 + o_buf_size - NYSE_LRP_PDP_HEADER_SIZE);

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
    size_t                      in_size = m_random->Generate(m_random->kMaxRange);

    nyse_lrp_pdp_header_t       out_data;
    size_t                      out_size;
    int                         result;

    result = nyse_lrp_unpack_pdp_header(NULL, in_size, &out_data, &out_size);

    TS_ASSERT_EQUALS(XDP_UNPACK_NULL_INPUT_PACKET_PTR, result);
}

void test_00101_fails_when_input_packet_is_too_short(void)
{
    uint8_t                     in_packet[1];
    size_t                      in_size = m_random->Generate(NYSE_LRP_PDP_HEADER_SIZE);

    nyse_lrp_pdp_header_t       out_data;
    size_t                      out_size;
    int                         result;

    result = nyse_lrp_unpack_pdp_header(in_packet, in_size, &out_data, &out_size);

    TS_ASSERT_EQUALS(XDP_UNPACK_INPUT_PACKET_TOO_SHORT, result);
}

void test_00200_proper_packet_is_unpacked(void)
{
    nyse_lrp_pdp_header_t       in_data;

    compose_random_pdp_header(&in_data);

    uint8_t                     in_packet[2 * NYSE_LRP_PDP_HEADER_SIZE];
    uint8_t *                   in_packet_p;

    in_packet_p = format_pdp_header(&in_data, in_packet, sizeof (in_packet));

    size_t                      in_size = NYSE_LRP_PDP_HEADER_SIZE + m_random->Generate(NYSE_LRP_PDP_HEADER_SIZE);

    nyse_lrp_pdp_header_t       out_data;
    size_t                      out_size;
    int                         result;

    result = nyse_lrp_unpack_pdp_header(in_packet_p, in_size, &out_data, &out_size);

    TS_ASSERT_EQUALS(XDP_UNPACK_SUCCESS, result);

    TS_ASSERT_EQUALS(out_data.msg_size,         in_data.msg_size);
    TS_ASSERT_EQUALS(out_data.msg_type,         in_data.msg_type);
    TS_ASSERT_EQUALS(out_data.msg_seq_num,      in_data.msg_seq_num);
    TS_ASSERT_EQUALS(out_data.send_time,        in_data.send_time);
    TS_ASSERT_EQUALS(out_data.product_id,       in_data.product_id);
    TS_ASSERT_EQUALS(out_data.retrans_flag,     in_data.retrans_flag);
    TS_ASSERT_EQUALS(out_data.num_body_entries, in_data.num_body_entries);

    TS_ASSERT_EQUALS(out_size, (size_t)NYSE_LRP_PDP_HEADER_SIZE);
}
};
