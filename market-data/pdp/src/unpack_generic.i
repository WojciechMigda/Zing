/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: unpack_generic.i
 *
 * Description:
 *      Generic unpacking function body template
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

#ifndef __STRUCT_FILE
    #error You need to specify the __STRUCT_FILE macro, which points to the unpacked struct definition
#endif
#ifndef __STRUCT_SIZE
    #error You need to specify the __STRUCT_SIZE macro, which equals to the expected size of the unpacked struct
#endif

{
    if (NULL == in_data_p)
    {
        return PDP_UNPACK_NULL_INPUT_PACKET_PTR;
    }

    if (in_size < __STRUCT_SIZE)
    {
        return PDP_UNPACK_INPUT_PACKET_TOO_SHORT;
    }
    if (out_offset_p != NULL)
    {
        *out_offset_p = __STRUCT_SIZE;
    }
    if (out_body_p != NULL)
    {
        #include "unpack_struct.i"
    }
    return PDP_UNPACK_SUCCESS;
}
#undef __STRUCT_FILE
#undef __STRUCT_SIZE
