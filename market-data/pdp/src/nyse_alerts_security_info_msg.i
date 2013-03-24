/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 *
 * Filename: nyse_alerts_security_info_msg.i
 *
 * Description:
 *      NYSE Alerts Security Info message definition
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

__OP_FIELD( source_time,            uint32_t    )
__OP_ARRAY( symbol,                 char,       NYSE_SHORT_SYMBOL_LEN  )
__OP_FIELD( security_type,          uint8_t     )
__OP_FIELD( filler,                 uint16_t    )
__OP_FIELD( mpv,                    uint16_t    )
__OP_FIELD( post,                   uint8_t     )
__OP_ARRAY( panel,                  char,       PANEL_LEN )
__OP_FIELD( ticker_designation,     char        )
__OP_FIELD( ipo_flag,               char        )
__OP_ARRAY( country_code,           char,       COUNTRY_CODE_LEN )
__OP_FIELD( uot,                    uint16_t    )
__OP_FIELD( price_scale_code,       uint8_t     )
__OP_FIELD( lrp_price_scale_code,   uint8_t     )
__OP_FIELD( lrp,                    uint16_t    )
__OP_FIELD( bankruptcy_flag,        char        )
__OP_FIELD( financial_status,       uint8_t     )
__OP_FIELD( ex_distribution_flag,   char        )
__OP_FIELD( ex_rights_flag,         char        )
__OP_FIELD( ex_dividend_flag,       char        )
__OP_FIELD( ex_div_amount_price_scale_code, uint8_t )
__OP_FIELD( ex_div_amount,          uint32_t    )
__OP_ARRAY( ex_div_date,            char,       EX_DIVIDEND_DATE_LEN )
__OP_FIELD( special_div_flag,       char        )
__OP_FIELD( stock_split,            char        )
__OP_FIELD( rule_19C3,              char        )
__OP_FIELD( its_eligible,           char        )
