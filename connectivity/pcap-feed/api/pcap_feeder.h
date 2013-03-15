/*
 * pcap_feeder.h
 *
 *  Created on: 15-03-2013
 *      Author: wojtek
 */

#ifndef PCAP_FEEDER_H_
#define PCAP_FEEDER_H_

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

enum pcap_feeder_exit_values
{
    PCAP_FEED_SUCCESS                       = 0,
    PCAP_FEED_ERR_BAD_FILE_PTR              = -1,
    PCAP_FEED_ERR_PCAP_FOPEN_OFFLINE_FAIL   = -2,
    PCAP_FEED_ERR_PCAP_NEXT_EX_FAIL         = -3,
};

typedef void (*packet_handler_t)(const uint8_t * in_data_p, const size_t in_size, void *user_data_p);

int pcap_feeder(
    FILE * in_file_p,
    packet_handler_t packet_handler,
    void *user_data_p);

#endif /* PCAP_FEEDER_H_ */
