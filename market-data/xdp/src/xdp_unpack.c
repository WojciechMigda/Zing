#include <stdint.h>
#include <stddef.h>
#include <arpa/inet.h>

#include "xdp_unpack.h"

int xdp_unitdata_unpack(
        const uint8_t * in_data_p,
        const size_t in_size,
        xdp_header_t * const out_xdp_header_p,
        size_t * const out_offset_p)
{
    int retval;

    if (NULL == in_data_p)
    {
        return -1;
    }

    if (in_size < sizeof (xdp_header_t))
    {
        return -2;
    }

    if (out_xdp_header_p != NULL)
    {
        *out_xdp_header_p = *((xdp_header_t *)in_data_p);
        out_xdp_header_p->size = ntohs(out_xdp_header_p->size);
        out_xdp_header_p->type = ntohs(out_xdp_header_p->type);
    }
    if (out_offset_p != NULL)
    {
        *out_offset_p = sizeof (xdp_header_t);
    }

    return 0;
}
