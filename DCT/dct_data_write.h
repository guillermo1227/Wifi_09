/**********************************************************************************
* Copyright (C) 2018-2021 LASECÂ®ï¸� Telecomunicaciones S.A.P.I. de C.V.
* All rights reserved.
*
* This document is the property of LASECÂ®ï¸� Telecomunicaciones S.A.P.I. de C.V.
* It is considered confidential and proprietary.
*
* This document may not be reproduced or transmitted in any form,
* in whole or in part, without the express written permission of
* LASECÂ®ï¸� Telecomunicaciones S.A.P.I. de C.V.
*
*********************************************************************************/


#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


/******************************************************
 *                    Structures
 ******************************************************/
#pragma pack (1)
typedef struct
{
    char        MASK[20];
    char        GATE[20];
    char        IP[20];
    char        SERVER[20];
    char        MAC_BT[20];
    uint8_t         F_config;
    uint8_t         F_save;
    uint8_t         enable_rx;
    uint8_t         gpio_aux;
    uint8_t         gpio_recib;
    uint8_t         gpio_evac;
    uint8_t         gpio_fall;
    uint8_t         gpio_inacty;
    uint8_t         acc_xy;// sin uso
    uint8_t         acc_z_min;// sin uso
    uint8_t         acc_z_plus;// sin uso
    uint8_t         blink_tcp; // sin uso
    uint8_t         blink_awake;// sin uso
    uint8_t         F_charger;// sin uso
    uint8_t         F_chr;// sin uso
    uint8_t         F_enable_btn;
    uint8_t         F_Sate;
    uint8_t         DCT0;
    uint8_t         DCT1;
    uint8_t         DCT2;
    uint8_t         DCT3;
    uint8_t         DCT4;
    char            DCT5;
    char            DCT6;
    char            DCT7;
    char            DCT8;
    char            DCT9;
    uint8_t         TxPower;
    char       passenger1[19];
    char       passenger2[19];
    char       passenger3[19];
    char       passenger4[19];
    uint8_t    caso1[4];
    char       start1[12];
    char       start2[12];
    char       start3[12];
    char       start4[12];
    char       date1[12];
    char       date2[12];
    char       date3[12];
    char       date4[12];

} dct_read_write_app_dct_t;

#pragma pack ()
/******************************************************
 *                 Global Variables
 ******************************************************/

/******************************************************
 *               Function Declarations
 ******************************************************/

#ifdef __cplusplus
} /*extern "C" */
#endif
