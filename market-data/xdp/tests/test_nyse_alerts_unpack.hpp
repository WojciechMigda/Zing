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
#include <endian.h>

#include "nyse_alerts_unpack.h"

class NyseAlertsUnpack : public CxxTest::TestSuite
{
private:

testing::internal::Random * m_random;

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
    size_t                      in_size;

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
    nyse_alerts_pdp_header_t    in_packet;
    uint8_t *                   in_packet_p;
    size_t                      in_size;

    nyse_alerts_pdp_header_t    out_data;
    size_t                      out_size;
    int                         result;

    result = nyse_alerts_unpack_pdp_header(in_packet_p, in_size, &out_data, &out_size);

    TS_ASSERT_EQUALS(XDP_UNPACK_SUCCESS, result);

    TS_ASSERT_EQUALS(out_data.msg_size,         be16toh(in_packet.msg_size));
    TS_ASSERT_EQUALS(out_data.msg_type,         be16toh(in_packet.msg_type));
    TS_ASSERT_EQUALS(out_data.msg_seq_num,      be32toh(in_packet.msg_seq_num));
    TS_ASSERT_EQUALS(out_data.send_time,        be32toh(in_packet.send_time));
    TS_ASSERT_EQUALS(out_data.product_id,       in_packet.product_id);
    TS_ASSERT_EQUALS(out_data.retrans_flag,     in_packet.retrans_flag);
    TS_ASSERT_EQUALS(out_data.num_body_entries, in_packet.num_body_entries);

    TS_ASSERT_EQUALS(out_size, sizeof (nyse_alerts_pdp_header_t));
}

};
