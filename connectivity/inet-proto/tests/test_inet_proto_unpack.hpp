/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All Rights Reserved.
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: test_inet_proto_unpack.h
 *
 * Description:
 *      Internet protocol unpacking unit tests
 *
 * Authors:
 *          Wojciech Migda (wm)
 *
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-17   wm              Initial version
 *
 ******************************************************************************/

#include <cxxtest/TestSuite.h>
#include <gmock/gmock.h>
#include <ctime>
#include <stdint.h>
#include <cstddef>
#include <limits>
#include <algorithm>
#include <string.h>
#include <cstdlib>

#include "anon_var.hpp"
#include "eth_unpack.h"
#include "ip_unpack.h"
#include "udp_unpack.h"
#include "inet_unpack_status.h"

////////////////////////////////////////////////////////////////////////////////

class EthUnitdataUnpack : public CxxTest::TestSuite
{
private:

testing::internal::Random * m_random;

uint8_t * format_header(eth_header_t const * const i_hdr_p, uint8_t * o_buffer, const size_t i_buf_size)
{
    size_t      n_bytes_to_copy = std::min(i_buf_size, sizeof (*i_hdr_p));
    size_t      random_offset =
        m_random->Generate(std::max(1 + i_buf_size - sizeof (*i_hdr_p), 1u));

    memcpy(&o_buffer[random_offset], i_hdr_p, n_bytes_to_copy);

    return &o_buffer[random_offset];
}

void compose_random_header(eth_header_t * o_header_p)
{
    ANON_ARRAY(o_header_p->ether_dhost);
    ANON_ARRAY(o_header_p->ether_shost);

    ANON_VAR(o_header_p->ether_type);
}

public:

EthUnitdataUnpack()
{
    m_random = new testing::internal::Random(time(0));
    srandom(time(0));
}
~EthUnitdataUnpack()
{
    delete m_random;
}

void test_00100_fails_when_packet_ptr_is_null(void)
{
    int     retval;
    size_t  ilen = m_random->Generate(2 * sizeof (eth_header_t));

    retval = eth_unitdata_unpack(NULL, ilen, NULL, NULL);

    TS_ASSERT_EQUALS(retval, INET_PROTO_UNPACK_NULL_PACKET_PTR);
}

void test_00101_fails_when_packet_is_too_short(void)
{
    int     retval;
    uint8_t packet;
    size_t  ilen = m_random->Generate(sizeof (eth_header_t));

    retval = eth_unitdata_unpack(&packet, ilen, NULL, NULL);

    TS_ASSERT_EQUALS(retval, INET_PROTO_UNPACK_PACKET_TOO_SHORT);
}

void test_00102_unpacks_valid_header(void)
{
    int             retval;
    eth_header_t    iheader;
    size_t          ilen = sizeof (eth_header_t) + m_random->Generate(sizeof (eth_header_t));
    eth_header_t    oheader;
    size_t          nbytes;
    uint8_t         packet[2 *sizeof (eth_header_t)];
    uint8_t         *packet_p;

    compose_random_header(&iheader);
    packet_p = format_header(&iheader, packet, sizeof (packet));

    retval = eth_unitdata_unpack(packet_p, ilen, &oheader, &nbytes);

    TS_ASSERT_EQUALS(retval, INET_PROTO_UNPACK_SUCCESS);
    TS_ASSERT_EQUALS(oheader.ether_type, ntohs(iheader.ether_type));
    TS_ASSERT_SAME_DATA(oheader.ether_dhost, iheader.ether_dhost, sizeof (oheader.ether_dhost));
    TS_ASSERT_SAME_DATA(oheader.ether_shost, iheader.ether_shost, sizeof (oheader.ether_shost));

    TS_ASSERT_EQUALS(nbytes, sizeof (eth_header_t));
}

};

////////////////////////////////////////////////////////////////////////////////

class IpUnitdataUnpack : public CxxTest::TestSuite
{
private:

testing::internal::Random * m_random;

uint8_t * format_header(ip_header_t const * const i_hdr_p, uint8_t * o_buffer, const size_t i_buf_size)
{
    size_t      n_bytes_to_copy = std::min(i_buf_size, sizeof (*i_hdr_p));
    size_t      random_offset =
        m_random->Generate(std::max(1 + i_buf_size - sizeof (*i_hdr_p), 1u));

    memcpy(&o_buffer[random_offset], i_hdr_p, n_bytes_to_copy);

    return &o_buffer[random_offset];
}

void compose_random_header(ip_header_t * o_header_p)
{
    ANON_VAR(o_header_p->ihl);
    ANON_VAR(o_header_p->version);
    ANON_VAR(o_header_p->tos);
    ANON_VAR(o_header_p->tot_len);
    ANON_VAR(o_header_p->id);
    ANON_VAR(o_header_p->frag_off);
    ANON_VAR(o_header_p->ttl);
    ANON_VAR(o_header_p->protocol);
    ANON_VAR(o_header_p->check);
    ANON_VAR(o_header_p->saddr);
    ANON_VAR(o_header_p->daddr);
}

public:

IpUnitdataUnpack()
{
    m_random = new testing::internal::Random(time(0));
}
~IpUnitdataUnpack()
{
    delete m_random;
}

void test_00100_fails_when_packet_ptr_is_null(void)
{
    int     retval;
    size_t  ilen = m_random->Generate(2 * sizeof (ip_header_t));

    retval = ip_unitdata_unpack(NULL, ilen, NULL, NULL);

    TS_ASSERT_EQUALS(retval, INET_PROTO_UNPACK_NULL_PACKET_PTR);
}

void test_00101_fails_when_packet_is_too_short(void)
{
    int     retval;
    uint8_t packet;
    size_t  ilen = m_random->Generate(sizeof (ip_header_t));

    retval = ip_unitdata_unpack(&packet, ilen, NULL, NULL);

    TS_ASSERT_EQUALS(retval, INET_PROTO_UNPACK_PACKET_TOO_SHORT);
}

void test_00102_unpacks_valid_header(void)
{
    int             retval;
    ip_header_t     iheader;
    size_t          ilen = sizeof (ip_header_t) + m_random->Generate(sizeof (ip_header_t));
    ip_header_t     oheader;
    size_t          nbytes;
    uint8_t         packet[2 *sizeof (ip_header_t)];
    uint8_t         *packet_p;

    compose_random_header(&iheader);
    packet_p = format_header(&iheader, packet, sizeof (packet));

    retval = ip_unitdata_unpack(packet_p, ilen, &oheader, &nbytes);

    TS_ASSERT_EQUALS(retval, INET_PROTO_UNPACK_SUCCESS);
    TS_ASSERT_EQUALS(oheader.ihl, iheader.ihl);
    TS_ASSERT_EQUALS(oheader.version, iheader.version);
    TS_ASSERT_EQUALS(oheader.tos, iheader.tos);
    TS_ASSERT_EQUALS(oheader.tot_len, ntohs(iheader.tot_len));
    TS_ASSERT_EQUALS(oheader.id, ntohs(iheader.id));
    TS_ASSERT_EQUALS(oheader.frag_off, ntohs(iheader.frag_off));
    TS_ASSERT_EQUALS(oheader.ttl, iheader.ttl);
    TS_ASSERT_EQUALS(oheader.protocol, iheader.protocol);
    TS_ASSERT_EQUALS(oheader.check, ntohs(iheader.check));
    TS_ASSERT_EQUALS(oheader.saddr, ntohl(iheader.saddr));
    TS_ASSERT_EQUALS(oheader.daddr, ntohl(iheader.daddr));

    TS_ASSERT_EQUALS(nbytes, sizeof (ip_header_t));
}

};

////////////////////////////////////////////////////////////////////////////////

class UdpUnitdataUnpack : public CxxTest::TestSuite
{
private:

testing::internal::Random * m_random;

uint8_t * format_header(udp_header_t const * const i_hdr_p, uint8_t * o_buffer, const size_t i_buf_size)
{
    size_t      n_bytes_to_copy = std::min(i_buf_size, sizeof (*i_hdr_p));
    size_t      random_offset =
        m_random->Generate(std::max(1 + i_buf_size - sizeof (*i_hdr_p), 1u));

    memcpy(&o_buffer[random_offset], i_hdr_p, n_bytes_to_copy);

    return &o_buffer[random_offset];
}

void compose_random_header(udp_header_t * o_header_p)
{
    ANON_VAR(o_header_p->source);
    ANON_VAR(o_header_p->dest);
    ANON_VAR(o_header_p->len);
    ANON_VAR(o_header_p->check);
}

public:

UdpUnitdataUnpack()
{
    m_random = new testing::internal::Random(time(0));
}
~UdpUnitdataUnpack()
{
    delete m_random;
}

void test_00100_fails_when_packet_ptr_is_null(void)
{
    int     retval;
    size_t  ilen = m_random->Generate(2 * sizeof (udp_header_t));

    retval = udp_unitdata_unpack(NULL, ilen, NULL, NULL);

    TS_ASSERT_EQUALS(retval, INET_PROTO_UNPACK_NULL_PACKET_PTR);
}

void test_00101_fails_when_packet_is_too_short(void)
{
    int     retval;
    uint8_t packet;
    size_t  ilen = m_random->Generate(sizeof (udp_header_t));

    retval = udp_unitdata_unpack(&packet, ilen, NULL, NULL);

    TS_ASSERT_EQUALS(retval, INET_PROTO_UNPACK_PACKET_TOO_SHORT);
}

void test_00102_unpacks_valid_header(void)
{
    int             retval;
    udp_header_t    iheader;
    size_t          ilen = sizeof (udp_header_t) + m_random->Generate(sizeof (udp_header_t));
    udp_header_t    oheader;
    size_t          nbytes;
    uint8_t         packet[2 *sizeof (udp_header_t)];
    uint8_t         *packet_p;

    compose_random_header(&iheader);
    packet_p = format_header(&iheader, packet, sizeof (packet));

    retval = udp_unitdata_unpack(packet_p, ilen, &oheader, &nbytes);

    TS_ASSERT_EQUALS(retval, INET_PROTO_UNPACK_SUCCESS);
    TS_ASSERT_EQUALS(oheader.source, ntohs(iheader.source));
    TS_ASSERT_EQUALS(oheader.dest, ntohs(iheader.dest));
    TS_ASSERT_EQUALS(oheader.len, ntohs(iheader.len));
    TS_ASSERT_EQUALS(oheader.check, ntohs(iheader.check));

    TS_ASSERT_EQUALS(nbytes, sizeof (udp_header_t));
}

};
