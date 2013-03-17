#include <stdint.h>
#include <stddef.h>
#include <net/ethernet.h>
#include <arpa/inet.h>

#include "eth_unpack.h"
#include <netinet/ip.h>

int eth_unitdata_unpack(
        const uint8_t * in_data_p,
        const size_t in_size,
        eth_header_t * const out_eth_header_p,
        size_t * const out_offset_p)
{
    int retval;

    if (NULL == in_data_p)
    {
        return -1;
    }

    if (in_size < sizeof (eth_header_t))
    {
        return -2;
    }

    if (out_eth_header_p != NULL)
    {
        *out_eth_header_p = *((eth_header_t *)in_data_p);
        out_eth_header_p->ether_type = ntohs(out_eth_header_p->ether_type);
    }
    if (out_offset_p != NULL)
    {
        *out_offset_p = sizeof (eth_header_t);
    }

    return 0;
}

void eth_unitdata_ind_handler(const uint8_t * in_data_p, const size_t in_size, void *user_data_p)
{
    size_t          nbytes_read;
    eth_header_t    eth_header;

    if (eth_unitdata_unpack(in_data_p, in_size, &eth_header, &nbytes_read) != 0)
    {
        return;
    }
}
