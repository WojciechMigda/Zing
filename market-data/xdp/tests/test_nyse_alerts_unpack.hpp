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

#include "anon_var.hpp"
#include "nyse_alerts_unpack.h"
#include "serializer.hpp"
#include "nyse_alerts_pdp.h"
#include "unpack_status.h"
#include "nyse_alerts_security_info.h"

class NyseAlertsUnpackPdpHeader : public CxxTest::TestSuite
{
private:

testing::internal::Random * m_random;

void compose_random_pdp_header(nyse_alerts_pdp_header_t * const out_p)
{
    ANON_VAR(out_p->msg_size);
    ANON_VAR(out_p->msg_type);
    ANON_VAR(out_p->msg_seq_num);
    ANON_VAR(out_p->send_time);
    ANON_VAR(out_p->product_id);
    ANON_VAR(out_p->retrans_flag);
    ANON_VAR(out_p->num_body_entries);
    ANON_VAR(out_p->filler);
}

uint8_t * format_pdp_header(nyse_alerts_pdp_header_t const * const i_hdr_p, uint8_t * o_buffer, const size_t o_buf_size)
{
    assert(o_buf_size >= NYSE_ALERTS_PDP_HEADER_SIZE);

    size_t      random_offset =
        m_random->Generate(1 + o_buf_size - NYSE_ALERTS_PDP_HEADER_SIZE);

    std::vector<uint8_t>    work_vec;

    serialize(i_hdr_p->msg_size, work_vec);
    serialize(i_hdr_p->msg_type, work_vec);
    serialize(i_hdr_p->msg_seq_num, work_vec);
    serialize(i_hdr_p->send_time, work_vec);
    serialize(i_hdr_p->product_id, work_vec);
    serialize(i_hdr_p->retrans_flag, work_vec);
    serialize(i_hdr_p->num_body_entries, work_vec);
    serialize(i_hdr_p->filler, work_vec);

    std::copy(work_vec.begin(), work_vec.end(), &o_buffer[random_offset]);

    return &o_buffer[random_offset];
}

public:

NyseAlertsUnpackPdpHeader()
{
    m_random = new testing::internal::Random(time(0));
}
~NyseAlertsUnpackPdpHeader()
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
    size_t                      in_size = m_random->Generate(NYSE_ALERTS_PDP_HEADER_SIZE);

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

////////////////////////////////////////////////////////////////////////////////

class NyseAlertsUnpackSecurityInfoMsg : public CxxTest::TestSuite
{
private:

testing::internal::Random * m_random;

void compose_random_msg(nyse_alerts_security_info_msg_t * const out_p)
{
    ANON_VAR(out_p->source_time);
    ANON_ARRAY(out_p->symbol);
    ANON_VAR(out_p->security_type);
    ANON_VAR(out_p->filler);
    ANON_VAR(out_p->mpv);
    ANON_VAR(out_p->post);
    ANON_ARRAY(out_p->panel);
    ANON_VAR(out_p->ticker_designation);
    ANON_VAR(out_p->ipo_flag);
    ANON_ARRAY(out_p->country_code);
    ANON_VAR(out_p->uot);
    ANON_VAR(out_p->price_scale_code);
    ANON_VAR(out_p->lrp_price_scale_code);
    ANON_VAR(out_p->lrp);
    ANON_VAR(out_p->bankruptcy_flag);
    ANON_VAR(out_p->financial_status);
    ANON_VAR(out_p->ex_distribution_flag);
    ANON_VAR(out_p->ex_rights_flag);
    ANON_VAR(out_p->ex_dividend_flag);
    ANON_VAR(out_p->ex_div_amount_price_scale_code);
    ANON_VAR(out_p->ex_div_amount);
    ANON_ARRAY(out_p->ex_div_date);
    ANON_VAR(out_p->special_div_flag);
    ANON_VAR(out_p->stock_splt);
    ANON_VAR(out_p->rule_19C3);
    ANON_VAR(out_p->its_eligible);
}

uint8_t * format_message(
    nyse_alerts_security_info_msg_t const * const i_hdr_p,
    uint8_t * o_buffer,
    const size_t o_buf_size)
{
    assert(o_buf_size >= NYSE_ALERTS_SECURITY_INFO_MSG_SIZE);

    size_t      random_offset =
        m_random->Generate(1 + o_buf_size - NYSE_ALERTS_SECURITY_INFO_MSG_SIZE);

    std::vector<uint8_t>    work_vec;

    serialize(i_hdr_p->source_time, work_vec);
    work_vec.insert(work_vec.end(), i_hdr_p->symbol, i_hdr_p->symbol + sizeof (i_hdr_p->symbol));
    serialize(i_hdr_p->security_type, work_vec);
    serialize(i_hdr_p->filler, work_vec);
    serialize(i_hdr_p->mpv, work_vec);
    serialize(i_hdr_p->post, work_vec);
    work_vec.insert(work_vec.end(), i_hdr_p->panel, i_hdr_p->panel + sizeof (i_hdr_p->panel));
    serialize(i_hdr_p->ticker_designation, work_vec);
    serialize(i_hdr_p->ipo_flag, work_vec);
    work_vec.insert(work_vec.end(), i_hdr_p->country_code, i_hdr_p->country_code + sizeof (i_hdr_p->country_code));
    serialize(i_hdr_p->uot, work_vec);
    serialize(i_hdr_p->price_scale_code, work_vec);
    serialize(i_hdr_p->lrp_price_scale_code, work_vec);
    serialize(i_hdr_p->lrp, work_vec);
    serialize(i_hdr_p->bankruptcy_flag, work_vec);
    serialize(i_hdr_p->financial_status, work_vec);
    serialize(i_hdr_p->ex_distribution_flag, work_vec);
    serialize(i_hdr_p->ex_rights_flag, work_vec);
    serialize(i_hdr_p->ex_dividend_flag, work_vec);
    serialize(i_hdr_p->ex_div_amount_price_scale_code, work_vec);
    serialize(i_hdr_p->ex_div_amount, work_vec);
    work_vec.insert(work_vec.end(), i_hdr_p->ex_div_date, i_hdr_p->ex_div_date + sizeof (i_hdr_p->ex_div_date));
    serialize(i_hdr_p->special_div_flag, work_vec);
    serialize(i_hdr_p->stock_splt, work_vec);
    serialize(i_hdr_p->rule_19C3, work_vec);
    serialize(i_hdr_p->its_eligible, work_vec);

    std::copy(work_vec.begin(), work_vec.end(), &o_buffer[random_offset]);

    return &o_buffer[random_offset];
}

public:

NyseAlertsUnpackSecurityInfoMsg()
{
    m_random = new testing::internal::Random(time(0));
}
~NyseAlertsUnpackSecurityInfoMsg()
{
    delete m_random;
}

void test_00100_fails_when_input_packet_ptr_is_null(void)
{
    size_t                              in_size = m_random->Generate(m_random->kMaxRange);

    nyse_alerts_security_info_msg_t     out_data;
    size_t                              out_size;
    int                                 result;

    result = nyse_alerts_unpack_security_info_msg(NULL, in_size, &out_data, &out_size);

    TS_ASSERT_EQUALS(XDP_UNPACK_NULL_INPUT_PACKET_PTR, result);
}

void test_00101_fails_when_input_packet_is_too_short(void)
{
    uint8_t                             in_packet[1];
    size_t                              in_size = m_random->Generate(NYSE_ALERTS_SECURITY_INFO_MSG_SIZE);

    nyse_alerts_security_info_msg_t     out_data;
    size_t                              out_size;
    int                                 result;

    result = nyse_alerts_unpack_security_info_msg(in_packet, in_size, &out_data, &out_size);

    TS_ASSERT_EQUALS(XDP_UNPACK_INPUT_PACKET_TOO_SHORT, result);
}

void test_00200_proper_packet_is_unpacked(void)
{
    nyse_alerts_security_info_msg_t     in_data;

    compose_random_msg(&in_data);

    uint8_t                     in_packet[2 * NYSE_ALERTS_SECURITY_INFO_MSG_SIZE];
    uint8_t *                   in_packet_p;

    in_packet_p = format_message(&in_data, in_packet, sizeof (in_packet));

    size_t                      in_size = NYSE_ALERTS_SECURITY_INFO_MSG_SIZE + m_random->Generate(NYSE_ALERTS_SECURITY_INFO_MSG_SIZE);

    nyse_alerts_security_info_msg_t     out_data;
    size_t                              out_size;
    int                                 result;

    result = nyse_alerts_unpack_security_info_msg(in_packet_p, in_size, &out_data, &out_size);

    TS_ASSERT_EQUALS(XDP_UNPACK_SUCCESS, result);

    TS_ASSERT_EQUALS(out_data.source_time,                      in_data.source_time);
    TS_ASSERT_SAME_DATA(out_data.symbol, in_data.symbol, sizeof (out_data.symbol));
    TS_ASSERT_EQUALS(out_data.security_type,                    in_data.security_type);
    TS_ASSERT_EQUALS(out_data.mpv,                              in_data.mpv);
    TS_ASSERT_EQUALS(out_data.post,                             in_data.post);
    TS_ASSERT_SAME_DATA(out_data.panel, in_data.panel, sizeof (out_data.panel));
    TS_ASSERT_EQUALS(out_data.ticker_designation,               in_data.ticker_designation);
    TS_ASSERT_EQUALS(out_data.ipo_flag,                         in_data.ipo_flag);
    TS_ASSERT_SAME_DATA(out_data.country_code, in_data.country_code, sizeof (out_data.country_code));
    TS_ASSERT_EQUALS(out_data.uot,                              in_data.uot);
    TS_ASSERT_EQUALS(out_data.price_scale_code,                 in_data.price_scale_code);
    TS_ASSERT_EQUALS(out_data.lrp_price_scale_code,             in_data.lrp_price_scale_code);
    TS_ASSERT_EQUALS(out_data.lrp,                              in_data.lrp);
    TS_ASSERT_EQUALS(out_data.bankruptcy_flag,                  in_data.bankruptcy_flag);
    TS_ASSERT_EQUALS(out_data.financial_status,                 in_data.financial_status);
    TS_ASSERT_EQUALS(out_data.ex_distribution_flag,             in_data.ex_distribution_flag);
    TS_ASSERT_EQUALS(out_data.ex_rights_flag,                   in_data.ex_rights_flag);
    TS_ASSERT_EQUALS(out_data.ex_dividend_flag,                 in_data.ex_dividend_flag);
    TS_ASSERT_EQUALS(out_data.ex_div_amount_price_scale_code,   in_data.ex_div_amount_price_scale_code);
    TS_ASSERT_EQUALS(out_data.ex_div_amount,                    in_data.ex_div_amount);
    TS_ASSERT_SAME_DATA(out_data.ex_div_date, in_data.ex_div_date, sizeof (out_data.ex_div_date));
    TS_ASSERT_EQUALS(out_data.special_div_flag,                 in_data.special_div_flag);
    TS_ASSERT_EQUALS(out_data.stock_splt,                       in_data.stock_splt);
    TS_ASSERT_EQUALS(out_data.rule_19C3,                        in_data.rule_19C3);
    TS_ASSERT_EQUALS(out_data.its_eligible,                     in_data.its_eligible);

    TS_ASSERT_EQUALS(out_size, (size_t)NYSE_ALERTS_SECURITY_INFO_MSG_SIZE);
}

};
