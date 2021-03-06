/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: serializer.hpp
 *
 * Description:
 *      description
 *
 * Authors:
 *          Wojciech Migda (wm)
 *
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 21-03-2013   wm              Initial version
 *
 ******************************************************************************/


#ifndef SERIALIZER_HPP_
#define SERIALIZER_HPP_

#include <stdint.h>
#include <vector>

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

static inline
void serialize(uint8_t in_val, std::vector<uint8_t> & out_vec)
{
    uint8_t *   in_p = &in_val;
    out_vec.insert(out_vec.end(), in_p, in_p + 1);
}

static inline
void serialize(char in_val, std::vector<uint8_t> & out_vec)
{
    char *   in_p = &in_val;
    out_vec.insert(out_vec.end(), in_p, in_p + 1);
}

static inline
void serialize(uint16_t in_val, std::vector<uint8_t> & out_vec)
{
    uint8_t     buf[sizeof (in_val)];

    __serialize_be16(in_val, buf);

    out_vec.insert(out_vec.end(), buf, buf + sizeof (buf));
}

static inline
void serialize(uint32_t in_val, std::vector<uint8_t> & out_vec)
{
    uint8_t     buf[sizeof (in_val)];

    __serialize_be32(in_val, buf);

    out_vec.insert(out_vec.end(), buf, buf + sizeof (buf));
}

#endif /* SERIALIZER_HPP_ */
