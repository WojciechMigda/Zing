/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: serialize.h
 *
 * Description:
 *      Helper serialization routines
 *
 * Authors:
 *          Wojciech Migda (wm)
 *
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-20   wm              Initial version
 *
 ******************************************************************************/


#ifndef SERIALIZE_H_
#define SERIALIZE_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * @brief Serialize 16-bit integer into big endian octet stream
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-20   wm              Initial version
 *
 *******************************************************************************
 * @param in_value input integer
 * @param out_data_p pointer to the output array of octets
 ******************************************************************************/
static inline
void __serialize_be16(const uint16_t in_value, uint8_t * out_data_p)
{
    out_data_p[0] = in_value >> 8;
    out_data_p[1] = in_value >> 0;
}

/*******************************************************************************
 * @brief Serialize 32-bit integer into big endian octet stream
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-20   wm              Initial version
 *
 *******************************************************************************
 * @param in_value input integer
 * @param out_data_p pointer to the output array of octets
 ******************************************************************************/
static inline
void __serialize_be32(const uint32_t in_value, uint8_t * const out_data_p)
{
    out_data_p[0] = in_value >> 24;
    out_data_p[1] = in_value >> 16;
    out_data_p[2] = in_value >> 8;
    out_data_p[3] = in_value >> 0;
}

#ifdef __cplusplus
} // extern C
#endif

#endif /* SERIALIZE_H_ */
