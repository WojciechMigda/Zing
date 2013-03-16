/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All Rights Reserved.
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: pcap_feeder.h
 *
 * Description:
 *      PCAP Feeder public interface.
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

#ifndef PCAP_FEEDER_H_
#define PCAP_FEEDER_H_

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

/**
 * @c pcap_feeder return codes
 */
enum pcap_feeder_exit_values
{
    PCAP_FEED_SUCCESS                       = 0,
    PCAP_FEED_ERR_BAD_FILE_PTR              = -1,
    PCAP_FEED_ERR_PCAP_FOPEN_OFFLINE_FAIL   = -2,
    PCAP_FEED_ERR_PCAP_NEXT_EX_FAIL         = -3,
};

/**
 * @brief pcap packet handler routine signature type
 *
 * Users of @c pcap_feeder may define their own custom routine to be called
 * for each packet read from the pcap stream.
 * The arguments passed are: pointer to the packet body, packet body size
 * in octets, and pointer to any user-defined custom data.
 */
typedef void (*packet_handler_t)(const uint8_t * in_data_p, const size_t in_size, void *user_data_p);

int pcap_feeder(
    FILE *              in_file_p,
    packet_handler_t    packet_handler,
    void *              in_user_data_p);

#endif /* PCAP_FEEDER_H_ */
