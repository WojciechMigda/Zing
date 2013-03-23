/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: nyse_alerts_circuit_breaker_msg.i
 *
 * Description:
 *      NYSE Alerts Circuit Breaker message definition
 *
 * Authors:
 *          Wojciech Migda (wm)
 *
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-23   wm              Initial version
 *
 ******************************************************************************/

__OP_FIELD( event_time,             uint32_t    )
__OP_FIELD( status,                 uint8_t     )
__OP_ARRAY( url,                    char,       CIRCUIT_BREAKER_URL_LEN  )
