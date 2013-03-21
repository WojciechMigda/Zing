/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 * Filename: nyse_alerts_circuit_breaker.h
 *
 * Description:
 *      NYSE Alerts Circuit Breaker message definitions
 *
 *      References:
 *      [1] NYSE ALERTS CLIENT SPECIFICATION, Version 2.12, 2013-01-24
 *          Sec. 4.13
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


#ifndef NYSE_ALERTS_CIRCUIT_BREAKER_H_
#define NYSE_ALERTS_CIRCUIT_BREAKER_H_

#include <stdint.h>
#include "static_assert.h"
#include "compiler.h"

#ifdef __cplusplus
extern "C"
{
#endif

enum circuit_breaker_status_values
{
    CIRCUIT_BREAKER_STS_NOT_IN_EFFECT           = 0,
    CIRCUIT_BREAKER_STS_HALTED_RESUME_HALF_HR   = 1,
    CIRCUIT_BREAKER_STS_HALTED_RESUME_1_HR      = 2,
    CIRCUIT_BREAKER_STS_HALTED_RESUME_2_HR      = 3,
    CIRCUIT_BREAKER_STS_HALTED_RESUME_NOT_TODAY = 4,
};

enum {CIRCUIT_BREAKER_URL_LEN = 128 };

typedef struct PACKED
{
    uint32_t        event_time;
    uint8_t         status;
    char            url[CIRCUIT_BREAKER_URL_LEN];
} nyse_alerts_circuit_breaker_msg_t;

enum { NYSE_ALERTS_CIRCUIT_BREAKER_MSG_SIZE = 133 };

STATIC_ASSERT(sizeof (nyse_alerts_circuit_breaker_msg_t) == NYSE_ALERTS_CIRCUIT_BREAKER_MSG_SIZE);

#ifdef __cplusplus
} // extern C
#endif

#endif /* NYSE_ALERTS_CIRCUIT_BREAKER_H_ */
