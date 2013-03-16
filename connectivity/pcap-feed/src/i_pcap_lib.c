/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All Rights Reserved.
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: i_pcap_lib.c
 *
 * Description:
 *      desctiption
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

#include <pcap/pcap.h>
#include "i_pcap_lib.h"

/**
 * pcap library interface
 */
i_pcap_lib_t    i_pcap_lib =
{
    pcap_fopen_offline,
    pcap_next_ex
};
