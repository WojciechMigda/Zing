/*******************************************************************************
 * Copyright (c) 2013, Wojciech Migda
 * All rights reserved
 * Distributed under the terms of the GNU LGPL v3
 *******************************************************************************
 * Filename: nyse_alerts_security_info.h
 *
 * Description:
 *      NYSE Alerts Security Info message definitions
 *
 *      References:
 *      [1] NYSE ALERTS CLIENT SPECIFICATION, Version 2.12, 2013-01-24
 *          Section 4.8
 *
 * Authors:
 *          Wojciech Migda (wm)
 *
 *******************************************************************************
 * History:
 * --------
 * Date         Who  Ticket     Description
 * ----------   ---  ---------  ------------------------------------------------
 * 2013-03-18   wm              Initial version
 *
 ******************************************************************************/


#ifndef NYSE_ALERTS_SECURITY_INFO_H_
#define NYSE_ALERTS_SECURITY_INFO_H_

#include <stdint.h>
#include "xdp_symbol.h"
#include "static_assert.h"
#include "compiler.h"

#ifdef __cplusplus
extern "C"
{
#endif

enum { PANEL_LEN = 2 };
enum { COUNTRY_CODE_LEN = 3 };
enum { EX_DIVIDEND_DATE_LEN = 5 };

enum nyse_alerts_security_type_values
{
    SEC_TYPE_COMMON_STOCK                = 'A',
    SEC_TYPE_PREFERRED_STOCK             = 'B',
    SEC_TYPE_WARRANT                     = 'C',
    SEC_TYPE_RIGHT                       = 'D',
    SEC_TYPE_CORPORATE_BOND              = 'E',
    SEC_TYPE_TREASURY_BOND               = 'F',
    SEC_TYPE_STRUCTURED_PRODUCT          = 'G',
    SEC_TYPE_ADR_COMMON                  = 'H',
    SEC_TYPE_ADR_PREFERRED               = 'I',
    SEC_TYPE_ADR_WARRANTS                = 'J',
    SEC_TYPE_ADR_RIGHTS                  = 'K',
    SEC_TYPE_ADR_CORPORATE_BOND          = 'L',
    SEC_TYPE_NY_REGISTERED_SHARE         = 'M',
    SEC_TYPE_GLOBAL_REGISTERED_SHARE     = 'N',
    SEC_TYPE_INDEX                       = 'O',
    SEC_TYPE_FUND                        = 'P',
    SEC_TYPE_BASKET                      = 'Q',
    SEC_TYPE_UNIT                        = 'R',
    SEC_TYPE_LIQUIDATING_TRUST           = 'S',
    SEC_TYPE_UNKNOWN                     = 'T',
};

static const char PANEL_NA[] = "~";

enum ticker_designation_values
{
    TICKER_DESGN_NYSE         = 'A',
    TICKER_DESGN_NYSE_MKT     = 'B',
    TICKER_DESGN_NASDAQ       = 'Q',
    TICKER_DESGN_DEFAULT      = ' ',
};

enum ipo_flag_values
{
    IPO_F_YES        = 'Y',
    IPO_F_NO         = 'N',
    IPO_F_NA         = ' ',
};

enum bankruptcy_flag_values
{
    BKPT_F_YES          = 'Y',
    BKPT_F_NO           = 'N',
};

enum financial_status_values
{
    FIN_STS_NORMAL       = 0,
    FIN_STS_BC           = 1,
    FIN_STS_LF           = 2,
    FIN_STS_BC_LF        = 3,
};

enum ex_distribution_flag_values
{
    X_DIST_F_NO          = 'N',
    X_DIST_F_YES         = 'Y',
};

enum ex_rights_flag_values
{
    X_RIGHTS_F_NO          = 'N',
    X_RIGHTS_F_YES         = 'Y',
};

enum ex_dividend_flag_values
{
    X_DIV_F_NO          = 'N',
    X_DIV_F_YES         = 'Y',
};

enum spec_dividend_flag_values
{
    SPEC_DIV_F_NO          = 'N',
    SPEC_DIV_F_YES         = 'Y',
};

enum stock_split_values
{
    STOCK_SPLIT_NO          = 'N',
    STOCK_SPLIT_YES         = 'Y',
};

enum rule_19C3_values
{
    RULE_19C3_NO          = 'N',
    RULE_19C3_YES         = 'Y',
};

enum its_eligible_values
{
    ITS_ELIG_NO          = 'N',
    ITS_ELIG_YES         = 'Y',
};

typedef struct PACKED
{
    uint32_t        source_time;
    char            symbol[NYSE_ALERTS_SYMBOL_LEN];
    uint8_t         security_type;
    uint16_t        filler;
    uint16_t        mpv;
    uint8_t         post;
    char            panel[PANEL_LEN];
    char            ticker_designation;
    char            ipo_flag;
    char            country_code[COUNTRY_CODE_LEN];
    uint16_t        uot;
    uint8_t         price_scale_code;
    uint8_t         lrp_price_scale_code;
    uint16_t        lrp;
    char            bankruptcy_flag;
    uint8_t         financial_status;
    char            ex_distribution_flag;
    char            ex_rights_flag;
    char            ex_dividend_flag;
    uint8_t         ex_div_amount_price_scale_code;
    uint32_t        ex_div_amount;
    char            ex_div_date[EX_DIVIDEND_DATE_LEN];
    char            special_div_flag;
    char            stock_splt;
    char            rule_19C3;
    char            its_eligible;
} nyse_alerts_security_info_msg_t;

enum { NYSE_ALERTS_SECURITY_INFO_MSG_SIZE = 53 };

STATIC_ASSERT(sizeof (nyse_alerts_security_info_msg_t) == NYSE_ALERTS_SECURITY_INFO_MSG_SIZE);

#ifdef __cplusplus
} // extern C
#endif

#endif /* NYSE_ALERTS_SECURITY_INFO_H_ */
