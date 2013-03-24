/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: test_nyse_alerts_unpack.hpp
 *
 * Description:
 *      NYSE Alerts feed unpack interface unit tests
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
#include <cassert>

#include "anon_var.hpp"
#include "nyse_alerts_unpack.h"
#include "serializer.hpp"
#include "nyse_alerts_pdp_header.h"
#include "unpack_status.h"
#include "nyse_alerts_security_info.h"
#include "nyse_alerts_market_imbalance.h"
#include "nyse_alerts_delay_halts.h"
#include "nyse_alerts_indication.h"
#include "nyse_alerts_t_time.h"
#include "nyse_alerts_circuit_breaker.h"
#include "nyse_alerts_short_sale_restriction.h"
#include "nyse_alerts_rpi.h"
#include "gen_test.hpp"

////////////////////////////////////////////////////////////////////////////////

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

uint8_t * format_pdp_header(
    nyse_alerts_pdp_header_t const * const i_hdr_p,
    uint8_t * o_buffer,
    const size_t o_buf_size)
{
    assert(o_buf_size >= NYSE_ALERTS_PDP_HEADER_SIZE);

    size_t      random_offset = random() % (1 + o_buf_size - NYSE_ALERTS_PDP_HEADER_SIZE);
//        m_random->Generate(1 + o_buf_size - NYSE_ALERTS_PDP_HEADER_SIZE);

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

void assert_pdp_header_equality(const nyse_alerts_pdp_header_t & lhs, const nyse_alerts_pdp_header_t & rhs)
{
    TS_ASSERT_EQUALS(lhs.msg_size,         rhs.msg_size);
    TS_ASSERT_EQUALS(lhs.msg_type,         rhs.msg_type);
    TS_ASSERT_EQUALS(lhs.msg_seq_num,      rhs.msg_seq_num);
    TS_ASSERT_EQUALS(lhs.send_time,        rhs.send_time);
    TS_ASSERT_EQUALS(lhs.product_id,       rhs.product_id);
    TS_ASSERT_EQUALS(lhs.retrans_flag,     rhs.retrans_flag);
    TS_ASSERT_EQUALS(lhs.num_body_entries, rhs.num_body_entries);
}

class NyseAlertsUnpackPdpHeader : public CxxTest::TestSuite
{
private:

testing::internal::Random * m_random;

public:

NyseAlertsUnpackPdpHeader()
{
    m_random = new testing::internal::Random(time(0));
    srandom(time(0));
}
~NyseAlertsUnpackPdpHeader()
{
    delete m_random;
}

void test_00100_fails_when_input_packet_ptr_is_null(void)
{
    gen_test_input_packet_ptr_is_null<nyse_alerts_pdp_header_t>
        (nyse_alerts_unpack_pdp_header, m_random);
}

void test_00101_fails_when_input_packet_is_too_short(void)
{
    gen_test_input_packet_is_too_short<nyse_alerts_pdp_header_t>
        (nyse_alerts_unpack_pdp_header, NYSE_ALERTS_PDP_HEADER_SIZE, m_random);
}

void test_00200_proper_packet_is_unpacked(void)
{
    gen_test_input_packet_is_unpacked<nyse_alerts_pdp_header_t>
        (
            compose_random_pdp_header,
            format_pdp_header,
            nyse_alerts_unpack_pdp_header,
            assert_pdp_header_equality,
            NYSE_ALERTS_PDP_HEADER_SIZE,
            m_random);
}

};

////////////////////////////////////////////////////////////////////////////////

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
    ANON_VAR(out_p->stock_split);
    ANON_VAR(out_p->rule_19C3);
    ANON_VAR(out_p->its_eligible);
}

uint8_t * format_message(
    nyse_alerts_security_info_msg_t const * const i_msg_p,
    uint8_t * o_buffer,
    const size_t o_buf_size)
{
    assert(o_buf_size >= NYSE_ALERTS_SECURITY_INFO_MSG_SIZE);

    size_t      random_offset = random() % (1 + o_buf_size - NYSE_ALERTS_SECURITY_INFO_MSG_SIZE);
//        m_random->Generate(1 + o_buf_size - NYSE_ALERTS_SECURITY_INFO_MSG_SIZE);

    std::vector<uint8_t>    work_vec;

    serialize(i_msg_p->source_time, work_vec);
    work_vec.insert(work_vec.end(), i_msg_p->symbol, i_msg_p->symbol + sizeof (i_msg_p->symbol));
    serialize(i_msg_p->security_type, work_vec);
    serialize(i_msg_p->filler, work_vec);
    serialize(i_msg_p->mpv, work_vec);
    serialize(i_msg_p->post, work_vec);
    work_vec.insert(work_vec.end(), i_msg_p->panel, i_msg_p->panel + sizeof (i_msg_p->panel));
    serialize(i_msg_p->ticker_designation, work_vec);
    serialize(i_msg_p->ipo_flag, work_vec);
    work_vec.insert(work_vec.end(), i_msg_p->country_code, i_msg_p->country_code + sizeof (i_msg_p->country_code));
    serialize(i_msg_p->uot, work_vec);
    serialize(i_msg_p->price_scale_code, work_vec);
    serialize(i_msg_p->lrp_price_scale_code, work_vec);
    serialize(i_msg_p->lrp, work_vec);
    serialize(i_msg_p->bankruptcy_flag, work_vec);
    serialize(i_msg_p->financial_status, work_vec);
    serialize(i_msg_p->ex_distribution_flag, work_vec);
    serialize(i_msg_p->ex_rights_flag, work_vec);
    serialize(i_msg_p->ex_dividend_flag, work_vec);
    serialize(i_msg_p->ex_div_amount_price_scale_code, work_vec);
    serialize(i_msg_p->ex_div_amount, work_vec);
    work_vec.insert(work_vec.end(), i_msg_p->ex_div_date, i_msg_p->ex_div_date + sizeof (i_msg_p->ex_div_date));
    serialize(i_msg_p->special_div_flag, work_vec);
    serialize(i_msg_p->stock_split, work_vec);
    serialize(i_msg_p->rule_19C3, work_vec);
    serialize(i_msg_p->its_eligible, work_vec);

    std::copy(work_vec.begin(), work_vec.end(), &o_buffer[random_offset]);

    return &o_buffer[random_offset];
}

class NyseAlertsUnpackSecurityInfoMsg : public CxxTest::TestSuite
{
private:

testing::internal::Random * m_random;

public:

NyseAlertsUnpackSecurityInfoMsg()
{
    m_random = new testing::internal::Random(time(0));
    srandom(time(0));
}
~NyseAlertsUnpackSecurityInfoMsg()
{
    delete m_random;
}

void test_00100_fails_when_input_packet_ptr_is_null(void)
{
    gen_test_input_packet_ptr_is_null<nyse_alerts_security_info_msg_t>
        (nyse_alerts_unpack_security_info_msg, m_random);
}

void test_00101_fails_when_input_packet_is_too_short(void)
{
    gen_test_input_packet_is_too_short<nyse_alerts_security_info_msg_t>
        (nyse_alerts_unpack_security_info_msg, NYSE_ALERTS_SECURITY_INFO_MSG_SIZE, m_random);
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

    TS_ASSERT_EQUALS(PDP_UNPACK_SUCCESS, result);

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
    TS_ASSERT_EQUALS(out_data.stock_split,                      in_data.stock_split);
    TS_ASSERT_EQUALS(out_data.rule_19C3,                        in_data.rule_19C3);
    TS_ASSERT_EQUALS(out_data.its_eligible,                     in_data.its_eligible);

    TS_ASSERT_EQUALS(out_size, (size_t)NYSE_ALERTS_SECURITY_INFO_MSG_SIZE);
}

};

////////////////////////////////////////////////////////////////////////////////

void compose_random_msg(nyse_alerts_market_imbalance_msg_t * const out_p)
{
    ANON_VAR(out_p->source_time);
    ANON_ARRAY(out_p->symbol);
    ANON_VAR(out_p->security_status);
    ANON_VAR(out_p->imbalance_quantity);
    ANON_VAR(out_p->imbalance_side);
}

uint8_t * format_message(
    nyse_alerts_market_imbalance_msg_t const * const i_msg_p,
    uint8_t * o_buffer,
    const size_t o_buf_size)
{
    assert(o_buf_size >= NYSE_ALERTS_MARKET_IMBALANCE_MSG_SIZE);

    size_t      random_offset = random() % (1 + o_buf_size - NYSE_ALERTS_MARKET_IMBALANCE_MSG_SIZE);
//        m_random->Generate(1 + o_buf_size - NYSE_ALERTS_MARKET_IMBALANCE_MSG_SIZE);

    std::vector<uint8_t>    work_vec;

    serialize(i_msg_p->source_time, work_vec);
    work_vec.insert(work_vec.end(), i_msg_p->symbol, i_msg_p->symbol + sizeof (i_msg_p->symbol));
    serialize(i_msg_p->security_status, work_vec);
    serialize(i_msg_p->imbalance_quantity, work_vec);
    serialize(i_msg_p->imbalance_side, work_vec);

    std::copy(work_vec.begin(), work_vec.end(), &o_buffer[random_offset]);

    return &o_buffer[random_offset];
}

class NyseAlertsUnpackMarketImbalanceMsg : public CxxTest::TestSuite
{
private:

testing::internal::Random * m_random;

public:

NyseAlertsUnpackMarketImbalanceMsg()
{
    m_random = new testing::internal::Random(time(0));
    srandom(time(0));
}
~NyseAlertsUnpackMarketImbalanceMsg()
{
    delete m_random;
}

void test_00100_fails_when_input_packet_ptr_is_null(void)
{
    gen_test_input_packet_ptr_is_null<nyse_alerts_market_imbalance_msg_t>
        (nyse_alerts_unpack_market_imbalance_msg, m_random);
}

void test_00101_fails_when_input_packet_is_too_short(void)
{
    gen_test_input_packet_is_too_short<nyse_alerts_market_imbalance_msg_t>
        (nyse_alerts_unpack_market_imbalance_msg, NYSE_ALERTS_MARKET_IMBALANCE_MSG_SIZE, m_random);
}

void test_00200_proper_packet_is_unpacked(void)
{
    nyse_alerts_market_imbalance_msg_t  in_data;

    compose_random_msg(&in_data);

    uint8_t                     in_packet[2 * NYSE_ALERTS_MARKET_IMBALANCE_MSG_SIZE];
    uint8_t *                   in_packet_p;

    in_packet_p = format_message(&in_data, in_packet, sizeof (in_packet));

    size_t                      in_size = NYSE_ALERTS_MARKET_IMBALANCE_MSG_SIZE + m_random->Generate(NYSE_ALERTS_MARKET_IMBALANCE_MSG_SIZE);

    nyse_alerts_market_imbalance_msg_t  out_data;
    size_t                              out_size;
    int                                 result;

    result = nyse_alerts_unpack_market_imbalance_msg(in_packet_p, in_size, &out_data, &out_size);

    TS_ASSERT_EQUALS(PDP_UNPACK_SUCCESS, result);

    TS_ASSERT_EQUALS(out_data.source_time,                      in_data.source_time);
    TS_ASSERT_SAME_DATA(out_data.symbol, in_data.symbol, sizeof (out_data.symbol));
    TS_ASSERT_EQUALS(out_data.security_status,                  in_data.security_status);
    TS_ASSERT_EQUALS(out_data.imbalance_quantity,               in_data.imbalance_quantity);
    TS_ASSERT_EQUALS(out_data.imbalance_side,                   in_data.imbalance_side);

    TS_ASSERT_EQUALS(out_size, (size_t)NYSE_ALERTS_MARKET_IMBALANCE_MSG_SIZE);
}

};

////////////////////////////////////////////////////////////////////////////////

void compose_random_msg(nyse_alerts_delay_halts_msg_t * const out_p)
{
    ANON_VAR(out_p->source_time);
    ANON_ARRAY(out_p->symbol);
    ANON_VAR(out_p->security_status);
    ANON_VAR(out_p->halt_condition);
}

uint8_t * format_message(
    nyse_alerts_delay_halts_msg_t const * const i_msg_p,
    uint8_t * o_buffer,
    const size_t o_buf_size)
{
    assert(o_buf_size >= NYSE_ALERTS_DELAY_HALTS_MSG_SIZE);

    size_t      random_offset = random() % (1 + o_buf_size - NYSE_ALERTS_DELAY_HALTS_MSG_SIZE);
//        m_random->Generate(1 + o_buf_size - NYSE_ALERTS_DELAY_HALTS_MSG_SIZE);

    std::vector<uint8_t>    work_vec;

    serialize(i_msg_p->source_time, work_vec);
    work_vec.insert(work_vec.end(), i_msg_p->symbol, i_msg_p->symbol + sizeof (i_msg_p->symbol));
    serialize(i_msg_p->security_status, work_vec);
    serialize(i_msg_p->halt_condition, work_vec);

    std::copy(work_vec.begin(), work_vec.end(), &o_buffer[random_offset]);

    return &o_buffer[random_offset];
}

class NyseAlertsUnpackDelayHaltsMsg : public CxxTest::TestSuite
{
private:

testing::internal::Random * m_random;

public:

NyseAlertsUnpackDelayHaltsMsg()
{
    m_random = new testing::internal::Random(time(0));
    srandom(time(0));
}
~NyseAlertsUnpackDelayHaltsMsg()
{
    delete m_random;
}

void test_00100_fails_when_input_packet_ptr_is_null(void)
{
    gen_test_input_packet_ptr_is_null<nyse_alerts_delay_halts_msg_t>
        (nyse_alerts_unpack_delay_halts_msg, m_random);
 }

void test_00101_fails_when_input_packet_is_too_short(void)
{
    uint8_t                             in_packet[1];
    size_t                              in_size = m_random->Generate(NYSE_ALERTS_DELAY_HALTS_MSG_SIZE);

    nyse_alerts_delay_halts_msg_t       out_data;
    size_t                              out_size;
    int                                 result;

    result = nyse_alerts_unpack_delay_halts_msg(in_packet, in_size, &out_data, &out_size);

    TS_ASSERT_EQUALS(PDP_UNPACK_INPUT_PACKET_TOO_SHORT, result);
}

void test_00200_proper_packet_is_unpacked(void)
{
    nyse_alerts_delay_halts_msg_t   in_data;

    compose_random_msg(&in_data);

    uint8_t                     in_packet[2 * NYSE_ALERTS_DELAY_HALTS_MSG_SIZE];
    uint8_t *                   in_packet_p;

    in_packet_p = format_message(&in_data, in_packet, sizeof (in_packet));

    size_t                      in_size = NYSE_ALERTS_DELAY_HALTS_MSG_SIZE + m_random->Generate(NYSE_ALERTS_DELAY_HALTS_MSG_SIZE);

    nyse_alerts_delay_halts_msg_t       out_data;
    size_t                              out_size;
    int                                 result;

    result = nyse_alerts_unpack_delay_halts_msg(in_packet_p, in_size, &out_data, &out_size);

    TS_ASSERT_EQUALS(PDP_UNPACK_SUCCESS, result);

    TS_ASSERT_EQUALS(out_data.source_time,                      in_data.source_time);
    TS_ASSERT_SAME_DATA(out_data.symbol, in_data.symbol, sizeof (out_data.symbol));
    TS_ASSERT_EQUALS(out_data.security_status,                  in_data.security_status);
    TS_ASSERT_EQUALS(out_data.halt_condition,                   in_data.halt_condition);

    TS_ASSERT_EQUALS(out_size, (size_t)NYSE_ALERTS_DELAY_HALTS_MSG_SIZE);
}

};

////////////////////////////////////////////////////////////////////////////////

void compose_random_msg(nyse_alerts_indication_msg_t * const out_p)
{
    ANON_VAR(out_p->source_time);
    ANON_ARRAY(out_p->symbol);
    ANON_VAR(out_p->security_status);
    ANON_VAR(out_p->bid_price);
    ANON_VAR(out_p->ask_price);
    ANON_VAR(out_p->price_scale_code);
    ANON_VAR(out_p->adjustment);
}

uint8_t * format_message(
    nyse_alerts_indication_msg_t const * const i_msg_p,
    uint8_t * o_buffer,
    const size_t o_buf_size)
{
    assert(o_buf_size >= NYSE_ALERTS_INDICATION_MSG_SIZE);

    size_t      random_offset = random() % (1 + o_buf_size - NYSE_ALERTS_INDICATION_MSG_SIZE);
//        m_random->Generate(1 + o_buf_size - NYSE_ALERTS_INDICATION_MSG_SIZE);

    std::vector<uint8_t>    work_vec;

    serialize(i_msg_p->source_time, work_vec);
    work_vec.insert(work_vec.end(), i_msg_p->symbol, i_msg_p->symbol + sizeof (i_msg_p->symbol));
    serialize(i_msg_p->security_status, work_vec);
    serialize(i_msg_p->bid_price, work_vec);
    serialize(i_msg_p->ask_price, work_vec);
    serialize(i_msg_p->price_scale_code, work_vec);
    serialize(i_msg_p->adjustment, work_vec);

    std::copy(work_vec.begin(), work_vec.end(), &o_buffer[random_offset]);

    return &o_buffer[random_offset];
}

class NyseAlertsUnpackIndicationMsg : public CxxTest::TestSuite
{
private:

testing::internal::Random * m_random;

public:

NyseAlertsUnpackIndicationMsg()
{
    m_random = new testing::internal::Random(time(0));
    srandom(time(0));
}
~NyseAlertsUnpackIndicationMsg()
{
    delete m_random;
}

void test_00100_fails_when_input_packet_ptr_is_null(void)
{
    gen_test_input_packet_ptr_is_null<nyse_alerts_indication_msg_t>
        (nyse_alerts_unpack_indication_msg, m_random);
}

void test_00101_fails_when_input_packet_is_too_short(void)
{
    gen_test_input_packet_is_too_short<nyse_alerts_indication_msg_t>
        (nyse_alerts_unpack_indication_msg, NYSE_ALERTS_INDICATION_MSG_SIZE, m_random);
}

void test_00200_proper_packet_is_unpacked(void)
{
    nyse_alerts_indication_msg_t    in_data;

    compose_random_msg(&in_data);

    uint8_t                     in_packet[2 * NYSE_ALERTS_INDICATION_MSG_SIZE];
    uint8_t *                   in_packet_p;

    in_packet_p = format_message(&in_data, in_packet, sizeof (in_packet));

    size_t                      in_size = NYSE_ALERTS_INDICATION_MSG_SIZE + m_random->Generate(NYSE_ALERTS_INDICATION_MSG_SIZE);

    nyse_alerts_indication_msg_t        out_data;
    size_t                              out_size;
    int                                 result;

    result = nyse_alerts_unpack_indication_msg(in_packet_p, in_size, &out_data, &out_size);

    TS_ASSERT_EQUALS(PDP_UNPACK_SUCCESS, result);

    TS_ASSERT_EQUALS(out_data.source_time,                      in_data.source_time);
    TS_ASSERT_SAME_DATA(out_data.symbol, in_data.symbol, sizeof (out_data.symbol));
    TS_ASSERT_EQUALS(out_data.security_status,                  in_data.security_status);
    TS_ASSERT_EQUALS(out_data.bid_price,                        in_data.bid_price);
    TS_ASSERT_EQUALS(out_data.ask_price,                        in_data.ask_price);
    TS_ASSERT_EQUALS(out_data.price_scale_code,                 in_data.price_scale_code);
    TS_ASSERT_EQUALS(out_data.adjustment,                       in_data.adjustment);

    TS_ASSERT_EQUALS(out_size, (size_t)NYSE_ALERTS_INDICATION_MSG_SIZE);
}

};

////////////////////////////////////////////////////////////////////////////////

void compose_random_msg(nyse_alerts_t_time_msg_t * const out_p)
{
    ANON_VAR(out_p->source_time);
    ANON_ARRAY(out_p->symbol);
    ANON_VAR(out_p->security_status);
    ANON_VAR(out_p->trade_dissemination_time);
}

uint8_t * format_message(
    nyse_alerts_t_time_msg_t const * const i_msg_p,
    uint8_t * o_buffer,
    const size_t o_buf_size)
{
    assert(o_buf_size >= NYSE_ALERTS_T_TIME_MSG_SIZE);

    size_t      random_offset = random() % (1 + o_buf_size - NYSE_ALERTS_T_TIME_MSG_SIZE);
//        m_random->Generate(1 + o_buf_size - NYSE_ALERTS_T_TIME_MSG_SIZE);

    std::vector<uint8_t>    work_vec;

    serialize(i_msg_p->source_time, work_vec);
    work_vec.insert(work_vec.end(), i_msg_p->symbol, i_msg_p->symbol + sizeof (i_msg_p->symbol));
    serialize(i_msg_p->security_status, work_vec);
    serialize(i_msg_p->trade_dissemination_time, work_vec);

    std::copy(work_vec.begin(), work_vec.end(), &o_buffer[random_offset]);

    return &o_buffer[random_offset];
}

class NyseAlertsUnpackTTimeMsg : public CxxTest::TestSuite
{
private:

testing::internal::Random * m_random;

public:

NyseAlertsUnpackTTimeMsg()
{
    m_random = new testing::internal::Random(time(0));
    srandom(time(0));
}
~NyseAlertsUnpackTTimeMsg()
{
    delete m_random;
}

void test_00100_fails_when_input_packet_ptr_is_null(void)
{
    gen_test_input_packet_ptr_is_null<nyse_alerts_t_time_msg_t>
        (nyse_alerts_unpack_t_time_msg, m_random);
}

void test_00101_fails_when_input_packet_is_too_short(void)
{
    gen_test_input_packet_is_too_short<nyse_alerts_t_time_msg_t>
        (nyse_alerts_unpack_t_time_msg, NYSE_ALERTS_T_TIME_MSG_SIZE, m_random);
}

void test_00200_proper_packet_is_unpacked(void)
{
    nyse_alerts_t_time_msg_t    in_data;

    compose_random_msg(&in_data);

    uint8_t                     in_packet[2 * NYSE_ALERTS_T_TIME_MSG_SIZE];
    uint8_t *                   in_packet_p;

    in_packet_p = format_message(&in_data, in_packet, sizeof (in_packet));

    size_t                      in_size = NYSE_ALERTS_T_TIME_MSG_SIZE + m_random->Generate(NYSE_ALERTS_T_TIME_MSG_SIZE);

    nyse_alerts_t_time_msg_t        out_data;
    size_t                          out_size;
    int                             result;

    result = nyse_alerts_unpack_t_time_msg(in_packet_p, in_size, &out_data, &out_size);

    TS_ASSERT_EQUALS(PDP_UNPACK_SUCCESS, result);

    TS_ASSERT_EQUALS(out_data.source_time,                      in_data.source_time);
    TS_ASSERT_SAME_DATA(out_data.symbol, in_data.symbol, sizeof (out_data.symbol));
    TS_ASSERT_EQUALS(out_data.security_status,                  in_data.security_status);
    TS_ASSERT_EQUALS(out_data.trade_dissemination_time,         in_data.trade_dissemination_time);

    TS_ASSERT_EQUALS(out_size, (size_t)NYSE_ALERTS_T_TIME_MSG_SIZE);
}

};

////////////////////////////////////////////////////////////////////////////////

void compose_random_msg(nyse_alerts_circuit_breaker_msg_t * const out_p)
{
    ANON_VAR(out_p->event_time);
    ANON_VAR(out_p->status);
    ANON_ARRAY(out_p->url);
}

uint8_t * format_message(
    nyse_alerts_circuit_breaker_msg_t const * const i_msg_p,
    uint8_t * o_buffer,
    const size_t o_buf_size)
{
    assert(o_buf_size >= NYSE_ALERTS_CIRCUIT_BREAKER_MSG_SIZE);

    size_t      random_offset = random() % (1 + o_buf_size - NYSE_ALERTS_CIRCUIT_BREAKER_MSG_SIZE);
//        m_random->Generate(1 + o_buf_size - NYSE_ALERTS_CIRCUIT_BREAKER_MSG_SIZE);

    std::vector<uint8_t>    work_vec;

    serialize(i_msg_p->event_time, work_vec);
    serialize(i_msg_p->status, work_vec);
    work_vec.insert(work_vec.end(), i_msg_p->url, i_msg_p->url + sizeof (i_msg_p->url));

    std::copy(work_vec.begin(), work_vec.end(), &o_buffer[random_offset]);

    return &o_buffer[random_offset];
}

class NyseAlertsUnpackCircuitBreakerMsg : public CxxTest::TestSuite
{
private:

testing::internal::Random * m_random;

public:

NyseAlertsUnpackCircuitBreakerMsg()
{
    m_random = new testing::internal::Random(time(0));
    srandom(time(0));
}
~NyseAlertsUnpackCircuitBreakerMsg()
{
    delete m_random;
}

void test_00100_fails_when_input_packet_ptr_is_null(void)
{
    gen_test_input_packet_ptr_is_null<nyse_alerts_circuit_breaker_msg_t>
        (nyse_alerts_unpack_circuit_breaker_msg, m_random);
}

void test_00101_fails_when_input_packet_is_too_short(void)
{
    gen_test_input_packet_is_too_short<nyse_alerts_circuit_breaker_msg_t>
        (nyse_alerts_unpack_circuit_breaker_msg, NYSE_ALERTS_CIRCUIT_BREAKER_MSG_SIZE, m_random);
}

void test_00200_proper_packet_is_unpacked(void)
{
    nyse_alerts_circuit_breaker_msg_t   in_data;

    compose_random_msg(&in_data);

    uint8_t                             in_packet[2 * NYSE_ALERTS_CIRCUIT_BREAKER_MSG_SIZE];
    uint8_t *                           in_packet_p;

    in_packet_p = format_message(&in_data, in_packet, sizeof (in_packet));

    size_t                      in_size = NYSE_ALERTS_CIRCUIT_BREAKER_MSG_SIZE + m_random->Generate(NYSE_ALERTS_CIRCUIT_BREAKER_MSG_SIZE);

    nyse_alerts_circuit_breaker_msg_t   out_data;
    size_t                              out_size;
    int                                 result;

    result = nyse_alerts_unpack_circuit_breaker_msg(in_packet_p, in_size, &out_data, &out_size);

    TS_ASSERT_EQUALS(PDP_UNPACK_SUCCESS, result);

    TS_ASSERT_EQUALS(out_data.event_time,                   in_data.event_time);
    TS_ASSERT_EQUALS(out_data.status,                       in_data.status);
    TS_ASSERT_SAME_DATA(out_data.url, in_data.url, sizeof (out_data.url));

    TS_ASSERT_EQUALS(out_size, (size_t)NYSE_ALERTS_CIRCUIT_BREAKER_MSG_SIZE);
}

};

////////////////////////////////////////////////////////////////////////////////

void compose_random_msg(nyse_alerts_short_sale_restriction_msg_t * const out_p)
{
    ANON_VAR(out_p->source_time);
    ANON_ARRAY(out_p->symbol);
    ANON_VAR(out_p->security_status);
    ANON_VAR(out_p->short_sale_restriction_indicator);
    ANON_VAR(out_p->triggering_exchange_id);
    ANON_VAR(out_p->short_sale_trigger_time);
    ANON_VAR(out_p->trade_price);
    ANON_VAR(out_p->price_scale_code);
    ANON_VAR(out_p->trade_volume);
}

uint8_t * format_message(
    nyse_alerts_short_sale_restriction_msg_t const * const i_msg_p,
    uint8_t * o_buffer,
    const size_t o_buf_size)
{
    assert(o_buf_size >= NYSE_ALERTS_SHORT_SALE_RESTRICTION_MSG_SIZE);

    size_t      random_offset = random() % (1 + o_buf_size - NYSE_ALERTS_SHORT_SALE_RESTRICTION_MSG_SIZE);
//        m_random->Generate(1 + o_buf_size - NYSE_ALERTS_SHORT_SALE_RESTRICTION_MSG_SIZE);

    std::vector<uint8_t>    work_vec;

    serialize(i_msg_p->source_time, work_vec);
    work_vec.insert(work_vec.end(), i_msg_p->symbol, i_msg_p->symbol + sizeof (i_msg_p->symbol));
    serialize(i_msg_p->security_status, work_vec);
    serialize(i_msg_p->short_sale_restriction_indicator, work_vec);
    serialize(i_msg_p->triggering_exchange_id, work_vec);
    serialize(i_msg_p->short_sale_trigger_time, work_vec);
    serialize(i_msg_p->trade_price, work_vec);
    serialize(i_msg_p->price_scale_code, work_vec);
    serialize(i_msg_p->trade_volume, work_vec);

    std::copy(work_vec.begin(), work_vec.end(), &o_buffer[random_offset]);

    return &o_buffer[random_offset];
}

class NyseAlertsUnpackShortSaleRestrictionMsg : public CxxTest::TestSuite
{
private:

testing::internal::Random * m_random;

public:

NyseAlertsUnpackShortSaleRestrictionMsg()
{
    m_random = new testing::internal::Random(time(0));
    srandom(time(0));
}
~NyseAlertsUnpackShortSaleRestrictionMsg()
{
    delete m_random;
}

void test_00100_fails_when_input_packet_ptr_is_null(void)
{
    gen_test_input_packet_ptr_is_null<nyse_alerts_short_sale_restriction_msg_t>
        (nyse_alerts_unpack_short_sale_restriction_msg, m_random);
}

void test_00101_fails_when_input_packet_is_too_short(void)
{
    gen_test_input_packet_is_too_short<nyse_alerts_short_sale_restriction_msg_t>
        (nyse_alerts_unpack_short_sale_restriction_msg, NYSE_ALERTS_SHORT_SALE_RESTRICTION_MSG_SIZE, m_random);
}

void test_00200_proper_packet_is_unpacked(void)
{
    nyse_alerts_short_sale_restriction_msg_t    in_data;

    compose_random_msg(&in_data);

    uint8_t                     in_packet[2 * NYSE_ALERTS_SHORT_SALE_RESTRICTION_MSG_SIZE];
    uint8_t *                   in_packet_p;

    in_packet_p = format_message(&in_data, in_packet, sizeof (in_packet));

    size_t                      in_size = NYSE_ALERTS_SHORT_SALE_RESTRICTION_MSG_SIZE + m_random->Generate(NYSE_ALERTS_SHORT_SALE_RESTRICTION_MSG_SIZE);

    nyse_alerts_short_sale_restriction_msg_t    out_data;
    size_t                                      out_size;
    int                                         result;

    result = nyse_alerts_unpack_short_sale_restriction_msg(in_packet_p, in_size, &out_data, &out_size);

    TS_ASSERT_EQUALS(PDP_UNPACK_SUCCESS, result);

    TS_ASSERT_EQUALS(out_data.source_time,                      in_data.source_time);
    TS_ASSERT_SAME_DATA(out_data.symbol, in_data.symbol, sizeof (out_data.symbol));
    TS_ASSERT_EQUALS(out_data.security_status,                  in_data.security_status);
    TS_ASSERT_EQUALS(out_data.short_sale_restriction_indicator, in_data.short_sale_restriction_indicator);
    TS_ASSERT_EQUALS(out_data.triggering_exchange_id,           in_data.triggering_exchange_id);
    TS_ASSERT_EQUALS(out_data.short_sale_trigger_time,          in_data.short_sale_trigger_time);
    TS_ASSERT_EQUALS(out_data.trade_price,                      in_data.trade_price);
    TS_ASSERT_EQUALS(out_data.price_scale_code,                 in_data.price_scale_code);
    TS_ASSERT_EQUALS(out_data.trade_volume,                     in_data.trade_volume);

    TS_ASSERT_EQUALS(out_size, (size_t)NYSE_ALERTS_SHORT_SALE_RESTRICTION_MSG_SIZE);
}

};

////////////////////////////////////////////////////////////////////////////////

void compose_random_msg(nyse_alerts_rpi_msg_t * const out_p)
{
    ANON_VAR(out_p->source_time);
    ANON_ARRAY(out_p->symbol);
    ANON_VAR(out_p->rpi_indicator);
}

uint8_t * format_message(
    nyse_alerts_rpi_msg_t const * const i_msg_p,
    uint8_t * o_buffer,
    const size_t o_buf_size)
{
    assert(o_buf_size >= NYSE_ALERTS_RPI_MSG_SIZE);

    size_t      random_offset = random() % (1 + o_buf_size - NYSE_ALERTS_RPI_MSG_SIZE);
//        m_random->Generate(1 + o_buf_size - NYSE_ALERTS_RPI_MSG_SIZE);

    std::vector<uint8_t>    work_vec;

    serialize(i_msg_p->source_time, work_vec);
    work_vec.insert(work_vec.end(), i_msg_p->symbol, i_msg_p->symbol + sizeof (i_msg_p->symbol));
    serialize(i_msg_p->rpi_indicator, work_vec);

    std::copy(work_vec.begin(), work_vec.end(), &o_buffer[random_offset]);

    return &o_buffer[random_offset];
}

class NyseAlertsUnpackRpiMsg : public CxxTest::TestSuite
{
private:

testing::internal::Random * m_random;

public:

NyseAlertsUnpackRpiMsg()
{
    m_random = new testing::internal::Random(time(0));
    srandom(time(0));
}
~NyseAlertsUnpackRpiMsg()
{
    delete m_random;
}

void test_00100_fails_when_input_packet_ptr_is_null(void)
{
    gen_test_input_packet_ptr_is_null<nyse_alerts_rpi_msg_t>
        (nyse_alerts_unpack_rpi_msg, m_random);
}

void test_00101_fails_when_input_packet_is_too_short(void)
{
    gen_test_input_packet_is_too_short<nyse_alerts_rpi_msg_t>
        (nyse_alerts_unpack_rpi_msg, NYSE_ALERTS_RPI_MSG_SIZE, m_random);
}

void test_00200_proper_packet_is_unpacked(void)
{
    nyse_alerts_rpi_msg_t       in_data;

    compose_random_msg(&in_data);

    uint8_t                     in_packet[2 * NYSE_ALERTS_RPI_MSG_SIZE];
    uint8_t *                   in_packet_p;

    in_packet_p = format_message(&in_data, in_packet, sizeof (in_packet));

    size_t                      in_size = NYSE_ALERTS_RPI_MSG_SIZE + m_random->Generate(NYSE_ALERTS_RPI_MSG_SIZE);

    nyse_alerts_rpi_msg_t       out_data;
    size_t                      out_size;
    int                         result;

    result = nyse_alerts_unpack_rpi_msg(in_packet_p, in_size, &out_data, &out_size);

    TS_ASSERT_EQUALS(PDP_UNPACK_SUCCESS, result);

    TS_ASSERT_EQUALS(out_data.source_time,                      in_data.source_time);
    TS_ASSERT_SAME_DATA(out_data.symbol, in_data.symbol, sizeof (out_data.symbol));
    TS_ASSERT_EQUALS(out_data.rpi_indicator,                    in_data.rpi_indicator);

    TS_ASSERT_EQUALS(out_size, (size_t)NYSE_ALERTS_RPI_MSG_SIZE);
}

};
