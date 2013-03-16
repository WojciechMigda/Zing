/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All Rights Reserved.
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: i_pcap_lib.h
 *
 * Description:
 *      PCAP lib interface
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


#ifndef I_PCAP_LIB_H_
#define I_PCAP_LIB_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <pcap/pcap.h>

/**
 * pcap library interface type
 */
typedef struct
{
    pcap_t *    (*fopen_offline)(FILE *, char *);
    int         (*next_ex)(pcap_t *, struct pcap_pkthdr **, const u_char **);
} i_pcap_lib_t;

extern i_pcap_lib_t    i_pcap_lib;

#ifdef __cplusplus
} // extern C
#endif

#endif /* I_PCAP_LIB_H_ */
