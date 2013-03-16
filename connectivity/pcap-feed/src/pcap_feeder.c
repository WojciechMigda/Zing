/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All Rights Reserved.
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: pcap_feeder.c
 *
 * Description:
 *      PCAP Feeder public interface implementation.
 *
 * Authors:
 *          Wojciech Migda (wm)
 *
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-16   wm              Initial version
 *
 ******************************************************************************/

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <pcap/pcap.h>

#include "i_pcap_lib.h"
#include "pcap_feeder.h"

/*******************************************************************************
 * @brief null packet handler (null object)
 *******************************************************************************
 * Null packet handler used by @c pcap_feed when the one supplied by the user
 * is NULL.
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-16   wm              Initial version
 *
 *******************************************************************************
 * @param in_data_p pointer to the packet body
 * @param in_size number of octets in the body
 * @param user_data_p pointer to the user data
 ******************************************************************************/
static
void null_packet_handler(const uint8_t * in_data_p, const size_t in_size, void * user_data_p)
{
    ;
}

/*******************************************************************************
 * @brief Process pcap file calling callback for each packet read
 *******************************************************************************
 * Process supplied pcap dumpfile @c in_file_p and call user supplied callback
 * @c packet_handler for each packet read. Callback will be passed custom user
 * data @c in_user_data_p as one of the arguments (@c packet_handler_t).
 * The function uses @c i_pcap_lib interface to call libpcap functions. This
 * interface can be mutated to supply mocks in unit tests.
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 16-03-2013   wm              Initial version
 *
 *******************************************************************************
 * @param in_file_p input pcap dump file
 * @param packet_handler user-supplied packet handler
 * @param in_user_data_p pointer to the custom user data
 *
 * @return return code @c pcap_feeder_exit_values
 ******************************************************************************/
int pcap_feeder_(
    FILE *              in_file_p,
    packet_handler_t    packet_handler,
    void *              in_user_data_p)
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

    capture_inst_p = i_pcap_lib.fopen_offline(in_file_p, errbuf);

    if (NULL == capture_inst_p)
    {
        return PCAP_FEED_ERR_PCAP_FOPEN_OFFLINE_FAIL;
    }

    while ((pcap_next_retval = i_pcap_lib.next_ex(capture_inst_p, &pkthdr_p, &pktdata_p)) > 0)
    {
        packet_handler(pktdata_p, pkthdr_p->caplen, in_user_data_p);
    }

    return pcap_next_retval != -1 ? PCAP_FEED_SUCCESS : PCAP_FEED_ERR_PCAP_NEXT_EX_FAIL;
}
