/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: unpack_struct.i
 *
 * Description:
 *      Generic template for unpacking of a struct
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
    #define __OP_FIELD(n,t) t n;
    #define __OP_ARRAY(n,t,c) t n[c];

    struct PACKED __unpack_msg_cast
    {
        #include __STRUCT_FILE
    };
    STATIC_ASSERT(sizeof (struct __unpack_msg_cast) == __STRUCT_SIZE);
    struct __unpack_msg_cast const * const in_body_p = (struct __unpack_msg_cast const * const)in_data_p;;

    #undef __OP_FIELD
    #undef __OP_ARRAY

    #define __OP_FIELD(n,t) \
    do \
    { \
        STATIC_ASSERT(sizeof (t) == 1 || sizeof (t) == 2 || sizeof (t) == 4); \
        switch (sizeof (t)) \
        { \
            case 1: out_body_p->n = in_body_p->n; break; \
            case 2: out_body_p->n = be16toh(in_body_p->n); break; \
            case 4: out_body_p->n = be32toh(in_body_p->n); break; \
        } \
    } while(0);
    #define __OP_ARRAY(n,t,c) \
    do \
    { \
        /* Initial assumption that arrays consist of octets */ \
        STATIC_ASSERT(sizeof (t) == 1); \
        memcpy(out_body_p->n, in_body_p->n, sizeof (out_body_p->n)); \
    } while(0);

    #include __STRUCT_FILE

    #undef __OP_FIELD
    #undef __OP_ARRAY
}
#undef __STRUCT_FILE
#undef __STRUCT_SIZE
