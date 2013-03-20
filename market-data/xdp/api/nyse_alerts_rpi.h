/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 * Filename: nyse_alerts_rpi.h
 *
 * Description:
 *      NYSE Alerts RPI (Retail Price Improvement) message definitions
 *
 *      References:
 *      [1] NYSE ALERTS CLIENT SPECIFICATION, Version 2.12, 2013-01-24
 *          Sec. 4.15
 *
 * Authors:
 *          Wojciech Migda (wm)
 *
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-19   wm              Initial version
 *
 ******************************************************************************/


#ifndef NYSE_ALERTS_RPI_H_
#define NYSE_ALERTS_RPI_H_

#include <stdint.h>
#include "xdp_symbol.h"
#include "static_assert.h"
#include "compiler.h"

#ifdef __cplusplus
extern "C"
{
#endif

enum rpi_indicator_values
{
    RPI_IND_NEITHER         = 0,
    RPI_IND_BID             = 1,
    RPI_IND_OFFER           = 2,
    RPI_IND_BID_AND_OFFER   = 3,
};

typedef struct PACKED
{
    uint32_t        source_time;
    char            symbol[NYSE_ALERTS_SYMBOL_LEN];
    uint8_t         rpi_indicator;
} nyse_alerts_rpi_msg_t;

STATIC_ASSERT(sizeof (nyse_alerts_rpi_msg_t) == 16);

#ifdef __cplusplus
} // extern C
#endif

#endif /* NYSE_ALERTS_RPI_H_ */
