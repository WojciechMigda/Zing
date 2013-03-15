/*
 * pcap_feeder.c
 *
 *  Created on: 14-03-2013
 *      Author: wojtek
 */

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <pcap/pcap.h>

#include "pcap_feeder.h"


static
void null_packet_handler(const uint8_t * in_data_p, const size_t in_size, void * user_data_p)
{

}

int pcap_feeder(
        FILE * in_file_p,
        packet_handler_t packet_handler,
        void *user_data_p)
{
    pcap_t *                capture_inst_p;
    char                    errbuf[PCAP_ERRBUF_SIZE];
    int                     pcap_next_retval;

    struct pcap_pkthdr *    pkthdr_p;
    const u_char *          pktdata_p;


    if (NULL == in_file_p)
    {
        return PCAP_FEED_ERR_BAD_FILE_PTR;
    }

    if (NULL == packet_handler)
    {
        packet_handler = null_packet_handler;
    }

    capture_inst_p = pcap_fopen_offline(in_file_p, errbuf);

    if (NULL == capture_inst_p)
    {
        return PCAP_FEED_ERR_PCAP_FOPEN_OFFLINE_FAIL;
    }

    while ((pcap_next_retval = pcap_next_ex(capture_inst_p, &pkthdr_p, &pktdata_p)) > 0)
    {
//        printf("%ld.%ld\n", pkthdr_p->ts.tv_sec, pkthdr_p->ts.tv_usec);
//        printf("%u, %u\n", pkthdr_p->len, pkthdr_p->caplen);
//        printf("%02X%02X%02X%02X\n", pktdata_p[0], pktdata_p[1], pktdata_p[2], pktdata_p[3]);
        packet_handler(pktdata_p, pkthdr_p->caplen, user_data_p);
    }

    return pcap_next_retval != -1 ? PCAP_FEED_SUCCESS : PCAP_FEED_ERR_PCAP_NEXT_EX_FAIL;
}
