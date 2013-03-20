/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: test_nyse_alerts_unpack.hpp
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
 * 2013-03-20   wm              Initial version
 *
 ******************************************************************************/

#include <cxxtest/TestSuite.h>
#include <gmock/gmock.h>

#include <stdint.h>
#include <stddef.h>
#include <ctime>
#include <algorithm>
#include <string.h>

#include "nyse_alerts_unpack.h"
#include "serialize.h"
#include "nyse_alerts_pdp.h"
#include "unpack_status.h"

class NyseAlertsUnpack : public CxxTest::TestSuite
{
private:

testing::internal::Random * m_random;

void compose_random_pdp_header(nyse_alerts_pdp_header_t * const out_p)
{
#define ASSIGN_RAND(x) do{x = m_random->Generate(std::min((size_t)std::numeric_limits<typeof(x)>::max(), (size_t)m_random->kMaxRange));}while(0)
    ASSIGN_RAND(out_p->msg_size);
    ASSIGN_RAND(out_p->msg_type);
    ASSIGN_RAND(out_p->msg_seq_num);
    ASSIGN_RAND(out_p->send_time);
    ASSIGN_RAND(out_p->product_id);
    ASSIGN_RAND(out_p->retrans_flag);
    ASSIGN_RAND(out_p->num_body_entries);
    ASSIGN_RAND(out_p->filler);
#undef ASSIGN_RAND
}

uint8_t * format_pdp_header(nyse_alerts_pdp_header_t const * const i_hdr_p, uint8_t * o_buffer, const size_t o_buf_size)
{
    assert(o_buf_size >= NYSE_ALERTS_PDP_HEADER_SIZE);

    size_t      random_offset =
        m_random->Generate(1 + o_buf_size - NYSE_ALERTS_PDP_HEADER_SIZE);

    __serialize_be16(i_hdr_p->msg_size,     &o_buffer[random_offset + 0]);
    __serialize_be16(i_hdr_p->msg_type,     &o_buffer[random_offset + 2]);
    __serialize_be32(i_hdr_p->msg_seq_num,  &o_buffer[random_offset + 4]);
    __serialize_be32(i_hdr_p->send_time,    &o_buffer[random_offset + 8]);

    o_buffer[random_offset + 12] = i_hdr_p->product_id;
    o_buffer[random_offset + 13] = i_hdr_p->retrans_flag;
    o_buffer[random_offset + 14] = i_hdr_p->num_body_entries;
    o_buffer[random_offset + 15] = i_hdr_p->filler;

    return &o_buffer[random_offset];
}

public:

NyseAlertsUnpack()
{
    m_random = new testing::internal::Random(time(0));
}
~NyseAlertsUnpack()
{
    delete m_random;
}

void test_00100_fails_when_input_packet_ptr_is_null(void)
{
    size_t                      in_size = m_random->Generate(m_random->kMaxRange);

    nyse_alerts_pdp_header_t    out_data;
    size_t                      out_size;
    int                         result;

    result = nyse_alerts_unpack_pdp_header(NULL, in_size, &out_data, &out_size);

    TS_ASSERT_EQUALS(XDP_UNPACK_NULL_INPUT_PACKET_PTR, result);
}

void test_00101_fails_when_input_packet_is_too_short(void)
{
    uint8_t                     in_packet[1];
    size_t                      in_size = m_random->Generate(sizeof (nyse_alerts_pdp_header_t));

    nyse_alerts_pdp_header_t    out_data;
    size_t                      out_size;
    int                         result;

    result = nyse_alerts_unpack_pdp_header(in_packet, in_size, &out_data, &out_size);

    TS_ASSERT_EQUALS(XDP_UNPACK_INPUT_PACKET_TOO_SHORT, result);
}

void test_00200_proper_packet_is_unpacked(void)
{
    nyse_alerts_pdp_header_t    in_data;

    compose_random_pdp_header(&in_data);

    uint8_t                     in_packet[2 * NYSE_ALERTS_PDP_HEADER_SIZE];
    uint8_t *                   in_packet_p;

    in_packet_p = format_pdp_header(&in_data, in_packet, sizeof (in_packet));

    size_t                      in_size = NYSE_ALERTS_PDP_HEADER_SIZE + m_random->Generate(NYSE_ALERTS_PDP_HEADER_SIZE);

    nyse_alerts_pdp_header_t    out_data;
    size_t                      out_size;
    int                         result;

    result = nyse_alerts_unpack_pdp_header(in_packet_p, in_size, &out_data, &out_size);

    TS_ASSERT_EQUALS(XDP_UNPACK_SUCCESS, result);

    TS_ASSERT_EQUALS(out_data.msg_size,         in_data.msg_size);
    TS_ASSERT_EQUALS(out_data.msg_type,         in_data.msg_type);
    TS_ASSERT_EQUALS(out_data.msg_seq_num,      in_data.msg_seq_num);
    TS_ASSERT_EQUALS(out_data.send_time,        in_data.send_time);
    TS_ASSERT_EQUALS(out_data.product_id,       in_data.product_id);
    TS_ASSERT_EQUALS(out_data.retrans_flag,     in_data.retrans_flag);
    TS_ASSERT_EQUALS(out_data.num_body_entries, in_data.num_body_entries);

    TS_ASSERT_EQUALS(out_size, (size_t)NYSE_ALERTS_PDP_HEADER_SIZE);
}

};