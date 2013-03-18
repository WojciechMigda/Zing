/*
 * nyse_alerts.h
 *
 *  Created on: 15-03-2013
 *      Author: wojtek
 */

#ifndef NYSE_ALERTS_H_
#define NYSE_ALERTS_H_

#include <stdint.h>

enum { SI_SYMBOL_LEN = 11 };
enum { SI_PANEL_LEN = 2 };
enum { COUNTRY_CODE_LEN = 3 };
enum { EX_DIVIDEND_DATE_LEN = 5 };

enum security_type_values
{
    ST_COMMON_STOCK                = 'A',
    ST_PREFERRED_STOCK             = 'B',
    ST_WARRANT                     = 'C',
    ST_RIGHT                       = 'D',
    ST_CORPORATE_BOND              = 'E',
    ST_TREASURY_BOND               = 'F',
    ST_STRUCTURED_PRODUCT          = 'G',
    ST_ADR_COMMON                  = 'H',
    ST_ADR_PREFERRED               = 'I',
    ST_ADR_WARRANTS                = 'J',
    ST_ADR_RIGHTS                  = 'K',
    ST_ADR_CORPORATE_BOND          = 'L',
    ST_NY_REGISTERED_SHARE         = 'M',
    ST_GLOBAL_REGISTERED_SHARE     = 'N',
    ST_INDEX                       = 'O',
    ST_FUND                        = 'P',
    ST_BASKET                      = 'Q',
    ST_UNIT                        = 'R',
    ST_LIQUIDATING_TRUST           = 'S',
    ST_UNKNOWN                     = 'T',
};

enum ticker_designation_values
{
    TD_NYSE         = 'A',
    TD_NYSE_MKT     = 'B',
    TD_NASDAQ       = 'Q',
    TD_DEFAULT      = ' ',
};

enum ipo_flag_values
{
    IPOF_YES        = 'Y',
    IPOF_NO         = 'N',
    IPOF_NA         = ' ',
};

enum bankruptcy_flag_values
{
    BF_YES          = 'Y',
    BF_NO           = 'N',
};

enum financial_status_values
{
    FS_NORMAL       = '0',
    FS_BC           = '1',
    FS_LF           = '2',
    FS_BC_LF        = '3',
};

enum ex_distribution_flag_values
{
    EDF_NO          = 'N',
    EDF_YES         = 'Y',
};

static const char PANEL_NA[] = "~";

typedef struct
{
    uint32_t        source_time;
    char            symbol[SI_SYMBOL_LEN];
    uint8_t         security_type;
    uint16_t        filler;
    uint16_t        mpv;
    uint8_t         post;
    char            panel[SI_PANEL_LEN];
    char            ticker_designation;
    char            ipo_flag;
    char            cc[COUNTRY_CODE_LEN];
    uint16_t        uot;
    uint8_t         price_scale_code;
    uint8_t         lrp_price_scale_code;
    uint16_t        lrp;
    char            bankruptcy_flag;
    uint8_t         financial_status;
    char            ex_distribution_flag;
    char            ex_rights_flag;
    char            ex_dividend_flag;
    uint8_t         ex_dividend_amount_scale_code;
    uint32_t        ex_dividend_amount;
    char            ex_dividend_date[EX_DIVIDEND_DATE_LEN];
    char            special_dividend_flag;
    char            stock_splt;
    char            rule_19C3;
    char            its_eligible;
} nyse_security_info_msg_t;

#endif /* NYSE_ALERTS_H_ */
