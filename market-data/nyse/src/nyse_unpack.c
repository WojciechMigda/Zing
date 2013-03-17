#include <stdint.h>
#include <stddef.h>
#include <arpa/inet.h>

#include "nyse_unpack.h"

int nyse_unitdata_unpack(
        const uint8_t * in_data_p,
        const size_t in_size,
        nyse_msg_header_t * const out_nyse_msg_header_p,
        size_t * const out_offset_p)
{
    int retval;

    if (NULL == in_data_p)
    {
        return -1;
    }

    if (in_size < sizeof (nyse_msg_header_t))
    {
        return -2;
    }

    if (out_nyse_msg_header_p != NULL)
    {
        *out_nyse_msg_header_p = *((nyse_msg_header_t *)in_data_p);
        out_nyse_msg_header_p->size = ntohs(out_nyse_msg_header_p->size);
        out_nyse_msg_header_p->type = ntohs(out_nyse_msg_header_p->type);
        out_nyse_msg_header_p->lsn = ntohl(out_nyse_msg_header_p->lsn);
        out_nyse_msg_header_p->send_time = ntohl(out_nyse_msg_header_p->send_time);
    }
    if (out_offset_p != NULL)
    {
        *out_offset_p = sizeof (nyse_msg_header_t);
    }

    return 0;

}
