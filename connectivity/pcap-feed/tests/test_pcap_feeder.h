/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All Rights Reserved.
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: test_pcap_feeder.h
 *
 * Description:
 *      pcap_feed unit tests
 *
 * Authors:
 *          Wojciech Migda (wm)
 *
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 16-03-2013   wm              Initial version
 *
 ******************************************************************************/

#include <cxxtest/TestSuite.h>
#include <gmock/gmock.h>
#include <stdio.h>
#include <stdint.h>
#include <cstddef>
#include <pcap/pcap.h>
#include <ctime>
#include <stdlib.h>

#include "i_pcap_lib.h"
#include "pcap_feeder.h"

using ::testing::_;
using ::testing::Return;
using ::testing::SetArgPointee;
using ::testing::Invoke;
using ::testing::WithArgs;
using ::testing::IgnoreResult;

///////////////////////////////////////////////////////////////////////////////

class PcapMocks
{
public:

PcapMocks(){}
~PcapMocks(){}
MOCK_METHOD2(pcap_fopen_offline, pcap_t* (FILE * i_file, char * errbuf));
MOCK_METHOD3(pcap_next_ex, int (pcap_t * capture_inst_p, struct pcap_pkthdr ** pkthdr_pp, const u_char ** pktdata_pp));
};

PcapMocks   pcapMocks;

static
pcap_t * mock_pcap_fopen_offline(FILE * i_file, char * errbuf)
{
    return pcapMocks.pcap_fopen_offline(i_file, errbuf);
}

static
int mock_pcap_next_ex(pcap_t * capture_inst_p, struct pcap_pkthdr ** pkthdr_pp, const u_char ** pktdata_pp)
{
    return pcapMocks.pcap_next_ex(capture_inst_p, pkthdr_pp, pktdata_pp);
}

///////////////////////////////////////////////////////////////////////////////

class UpstreamMocks
{
public:

UpstreamMocks(){}
~UpstreamMocks(){}
MOCK_METHOD3(packet_handler, void (const uint8_t * in_data_p, const size_t in_size, void * user_data_p));
};

UpstreamMocks upstreamMocks;

static
void mock_packet_handler(const uint8_t * in_data_p, const size_t in_size, void * user_data_p)
{
    upstreamMocks.packet_handler(in_data_p, in_size, user_data_p);
}

///////////////////////////////////////////////////////////////////////////////

ACTION(SetRandomCaplen)
{
    (*arg1)->caplen = random();
}

MATCHER_P(CaplenEquals, val, "")
{
    return arg == *val;
}

///////////////////////////////////////////////////////////////////////////////

class PcapFeed : public CxxTest::TestSuite
{
private:
    i_pcap_lib_t                i_pcap_lib_backup;
    testing::internal::Random * m_random;

public:
    PcapFeed()
    :
        i_pcap_lib_backup(i_pcap_lib)
    {
        i_pcap_lib.fopen_offline = mock_pcap_fopen_offline;
        i_pcap_lib.next_ex = mock_pcap_next_ex;
        m_random = new testing::internal::Random(time(0));
        srandom(time(0));
    }
    ~PcapFeed()
    {
        delete m_random;
    }

void test_00100_fails_when_input_file_is_null(void)
{
    int     retval;

    retval = pcap_feeder(NULL, NULL, NULL);

    TS_ASSERT_EQUALS(retval, PCAP_FEED_ERR_BAD_FILE_PTR);
}

void test_00101_fails_when_fopen_offline_fails(void)
{
    FILE            i_file;
    int             retval;

    EXPECT_CALL(pcapMocks, pcap_fopen_offline(_, _))
        .WillRepeatedly(Return((pcap_t *)NULL));

    retval = pcap_feeder(&i_file, NULL, NULL);

    TS_ASSERT_EQUALS(retval, PCAP_FEED_ERR_PCAP_FOPEN_OFFLINE_FAIL);
    TS_ASSERT(testing::Mock::VerifyAndClearExpectations(&pcapMocks));
}

void test_00102_fails_when_next_ex_fails(void)
{
    FILE            i_file;
    int             retval;
    char            pcap_inst;

    EXPECT_CALL(pcapMocks, pcap_fopen_offline(_, _))
        .WillRepeatedly(Return((pcap_t *)&pcap_inst));
    EXPECT_CALL(pcapMocks, pcap_next_ex(_, _, _))
        .WillRepeatedly(Return(-1));

    retval = pcap_feeder(&i_file, NULL, NULL);

    TS_ASSERT_EQUALS(retval, PCAP_FEED_ERR_PCAP_NEXT_EX_FAIL);
    TS_ASSERT(testing::Mock::VerifyAndClearExpectations(&pcapMocks));
}

void test_00110_exits_after_processing_all_packets(void)
{
    FILE                    in_file;

    char                    user_data;
    void *                  user_data_p = &user_data;

    char                    pcap_inst;
    pcap_t *                pcap_inst_p = (pcap_t *)&pcap_inst;

    struct pcap_pkthdr      pkthdr;
    u_char                  pktdata;

    EXPECT_CALL(pcapMocks, pcap_fopen_offline(&in_file, _))
        .WillRepeatedly(Return(pcap_inst_p));

    size_t                  n_packets = m_random->Generate(123);

    {
        ::testing::InSequence   seq;

        for (size_t cnt = 0; cnt < n_packets; ++cnt)
        {
            // 1 == packet read
            EXPECT_CALL(pcapMocks,
                pcap_next_ex(pcap_inst_p, _, _))
                .WillOnce(DoAll(
                    SetArgPointee<1>(&pkthdr),
                    SetArgPointee<2>(&pktdata),
                    SetRandomCaplen(),
                    Return(1)))
                .RetiresOnSaturation();
            EXPECT_CALL(upstreamMocks,
                packet_handler(&pktdata, CaplenEquals(&pkthdr.caplen), user_data_p))
                .Times(1)
                .RetiresOnSaturation();
        }
        // -2 == end of data
        EXPECT_CALL(pcapMocks, pcap_next_ex(pcap_inst_p, _, _))
            .WillOnce(Return(-2))
            .RetiresOnSaturation();
        EXPECT_CALL(upstreamMocks, packet_handler(_, _, _))
            .Times(0)
            .RetiresOnSaturation();
    }

    int             retval;
    retval = pcap_feeder(&in_file, mock_packet_handler, user_data_p);

    TS_ASSERT_EQUALS(retval, PCAP_FEED_SUCCESS);
    TS_ASSERT(testing::Mock::VerifyAndClearExpectations(&pcapMocks));
}

};
