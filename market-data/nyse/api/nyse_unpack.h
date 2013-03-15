/*
 * nyse_unpack.h
 *
 *  Created on: 15-03-2013
 *      Author: wojtek
 */

#ifndef NYSE_UNPACK_H_
#define NYSE_UNPACK_H_

#include <stdint.h>
#include <stddef.h>

enum msg_type_values
{
    SEQUENCE_NUMBER_RESET           = 1,
    HEARTBEAT                       = 2,
    MESSAGE_UNAVAILABLE             = 5,
    RE_TX_RESPONSE                  = 10,
    HEARTBEAT_SUBSCRIPTION          = 19,
    RE_TX_REQUEST                   = 20,
    REFRESH_REQUEST                 = 22,
    HEARTBEAT_RESPONSE              = 24,
    EXTEND_REFRESH                  = 27,
    SYMBOL_UPDATE_REQUEST           = 34,
    SYMBOL_UPDATE                   = 35,
    OPENBOOK_FULL_UPDATE            = 230,
    OPENBOOK_DELTA_UPDATE           = 231,
};

enum nyse_product_values
{
    ALERTS                      = 104,
    QUOTES                      = 107,
    OPENBOOK                    = 108,
    LRP                         = 110,
    PROTRAC                     = 111,
    RETRAC                      = 112,
    TRADES                      = 113,
    RT_REFERENCE                = 114,
    OPENBOOK_ULTRA              = 115,
    IMBALANCE                   = 116,
    ARCA_BONDS_QUOTES           = 117,
};

enum re_tx_flag_values
{
    ORIGINAL_MSG                = 1,
    RETXD_MSG                   = 2,
    MSG_REPLAY                  = 3,
    REPLAYED_MSG_RETX           = 4,
    REFRESH_RETX                = 5,
    ENDOF_REFRESH_RETX          = 6,
    TEST_ORIGINAL_MSG           = 129,
    TEST_MSG_RETX               = 130,
    TEST_MSG_REPLAY             = 131,
    TEST_MSG_REPLAY_RETX        = 132,
};

typedef struct
{
    uint16_t        size;
    uint16_t        type;
    uint32_t        lsn;
    uint32_t        send_time;
    uint8_t         product_type;
    uint8_t         re_tx_flag;
    uint8_t         num_body_entries;
    uint8_t         link_flag;
} nyse_msg_header_t;

int nyse_unitdata_unpack(
        const uint8_t * in_data_p,
        const size_t in_size,
        nyse_msg_header_t * const out_nyse_msg_header_p,
        size_t * const out_offset_p);

#endif /* NYSE_UNPACK_H_ */
