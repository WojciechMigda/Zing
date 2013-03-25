/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: nyse_retrac_unpack.c
 *
 * Description:
 *      NYSE ReTrac feed unpacking routines implementation
 *
 * Authors:
 *          Wojciech Migda (wm)
 *
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-25   wm              Initial version
 *
 ******************************************************************************/

#include <stdint.h>
#include <stddef.h>
#include <endian.h>
#include <string.h>

#include "compiler.h"
#include "static_assert.h"
#include "unpack_status.h"
#include "nyse_retrac_pdp_header.h"
#include "nyse_retrac_execution_report.h"
#include "nyse_retrac_execution_report_cancellation.h"
#include "nyse_retrac_summary.h"

/*******************************************************************************
 * @brief Unpack general PDP header of the NYSE ReTrac feed
 *******************************************************************************
 * Endianness of the unpacked data is that of the host.
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-25   wm              Initial version
 *
 *******************************************************************************
 * @param in_data_p pointer to the input packet
 * @param in_size number of octets in the input packet
 * @param out_body_p pointer to the header where the packet will be unpacked
 * @param out_offset_p pointer to the output variable where the amount of
 *        unpacked octets will be stored
 * @return PDP unpack return code
 ******************************************************************************/
int nyse_retrac_unpack_pdp_header(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_retrac_pdp_header_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p)
{
//#define __STRUCT_FILE "nyse_retrac_pdp_header.i"
//#define __STRUCT_SIZE NYSE_RETRAC_PDP_HEADER_SIZE
//
//#include "unpack_generic.i"
    return 3;
}

/*******************************************************************************
 * @brief Unpack Execution Report message of the NYSE ReTrac feed
 *******************************************************************************
 * Endianness of the unpacked data is that of the host.
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-25   wm              Initial version
 *
 *******************************************************************************
 * @param in_data_p pointer to the input packet
 * @param in_size number of octets in the input packet
 * @param out_body_p pointer to the variable where the packet will be unpacked
 * @param out_offset_p pointer to the output variable where the amount of
 *        unpacked octets will be stored
 * @return PDP unpack return code
 ******************************************************************************/
int nyse_retrac_unpack_execution_report_msg(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_retrac_execution_report_msg_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p)
{
//#define __STRUCT_FILE "nyse_retrac_execution_report_msg.i"
//#define __STRUCT_SIZE NYSE_RETRAC_EXECUTION_REPORT_MSG_SIZE
//
//#include "unpack_generic.i"
    return 4;
}

/*******************************************************************************
 * @brief Unpack Execution Report Cancellation message of the NYSE ReTrac feed
 *******************************************************************************
 * Endianness of the unpacked data is that of the host.
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-25   wm              Initial version
 *
 *******************************************************************************
 * @param in_data_p pointer to the input packet
 * @param in_size number of octets in the input packet
 * @param out_body_p pointer to the variable where the packet will be unpacked
 * @param out_offset_p pointer to the output variable where the amount of
 *        unpacked octets will be stored
 * @return PDP unpack return code
 ******************************************************************************/
int nyse_retrac_unpack_execution_report_cancellation_msg(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_retrac_execution_report_cancellation_msg_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p)
{
//#define __STRUCT_FILE "nyse_retrac_execution_report_cancellation_msg.i"
//#define __STRUCT_SIZE NYSE_RETRAC_EXECUTION_REPORT_CANCELLATION_MSG_SIZE
//
//#include "unpack_generic.i"
    return 5;
}

/*******************************************************************************
 * @brief Unpack Summary message of the NYSE ReTrac feed
 *******************************************************************************
 * Endianness of the unpacked data is that of the host.
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-25   wm              Initial version
 *
 *******************************************************************************
 * @param in_data_p pointer to the input packet
 * @param in_size number of octets in the input packet
 * @param out_body_p pointer to the variable where the packet will be unpacked
 * @param out_offset_p pointer to the output variable where the amount of
 *        unpacked octets will be stored
 * @return PDP unpack return code
 ******************************************************************************/
int nyse_retrac_unpack_summary_msg(
    const uint8_t * RESTRICT in_data_p,
    const size_t in_size,
    nyse_retrac_summary_msg_t * const RESTRICT out_body_p,
    size_t * const RESTRICT out_offset_p)
{
//#define __STRUCT_FILE "nyse_retrac_summary_msg.i"
//#define __STRUCT_SIZE NYSE_RETRAC_SUMMARY_MSG_SIZE
//
//#include "unpack_generic.i"
    return 6;
}
