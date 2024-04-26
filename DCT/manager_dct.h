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


#ifndef _MANAGER_DCT_H
#define _MANAGER_DCT_H

#include "wiced.h"
#include "string.h"
#include "stdbool.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"

#include "dct_data_write.h"
#include "TXT/manager_menssage_vh.h"

#define EVACUACION      3
#define CONFIRMACION    1
#define AYUDA           2
#define ENABLE_A1       4
#define FALLENMEN       5
#define INACTIVITY      6
#define SOUND_ONOFF     7
#define RESET_WIFI      8
#define LOG_ID_LASET    9


wiced_bool_t EnableRx=WICED_FALSE;

uint8_t get_gpio_menssage(int index);
void set_gpio_menssage(uint8_t index,uint8_t value);
static wiced_result_t Set_config();
static wiced_result_t Down_net();
static wiced_result_t Up_net();
static wiced_result_t Un_Set_config(uint8_t value);
void Set_flag_charger(uint8_t value);
uint8_t  is_charger();
//void save_nvram_passenger(char *mac,int a);
void save_nvram_passenger(char *mac,int a, char *start, char *date, uint8_t cass);
void chec_passenger_save(void);
void delete_all_passenger(void);                                                        /* Delete all passenger */

static wiced_result_t  is_Access();


void set_value_imu(uint8_t index,uint8_t value);
uint8_t get_value_imu(int index);
uint8_t get_times(int index);
void set_times(uint8_t index,uint8_t value);



/*
 * 1->  CONFIRMACION EVACUACION
 * 2->  AYUDA
 * 3->  EVACUACION
 * 4->  ENABLE_A1
 * 5->  FALLENMEN
 * 6->  INACTIVITY
 * 7->  SOUND ON/OFF
 * 8->  RESET WIFI
 * */
uint8_t get_gpio_menssage(int index){
    dct_read_write_app_dct_t*       app_dct                  = NULL;
    uint8_t result_value=0;
    wiced_result_t res;

    /* get the App config section for modifying, any memory allocation required would be done inside wiced_dct_read_lock() */
    wiced_dct_read_lock( (void**) &app_dct, WICED_TRUE, DCT_APP_SECTION, 0, sizeof( *app_dct ) );

    /* Modify string_var by writing the whole DCT */
    switch (index) {
           case 1:
               result_value=app_dct->gpio_recib;

               break;
           case 2:
               result_value=app_dct->gpio_aux;
               break;
           case 3:
               result_value= app_dct->gpio_evac;
               break;
           case 4:
               result_value=app_dct->F_enable_btn;
               break;
           case 5:
              result_value=app_dct->gpio_fall;
              break;
           case 6:
              result_value=app_dct->gpio_inacty;
              break;
           case 7:
              result_value=app_dct->DCT0;
              break;
           case 8:
              result_value=app_dct->DCT1;
              break;
           case 9:
              result_value=app_dct->DCT2;
              break;
           case 10:
               result_value=app_dct->DCT4;
               break;
           default:
               break;
       }

//    res=wiced_dct_write( (const void*) app_dct, DCT_APP_SECTION, 0, sizeof(dct_read_write_app_dct_t) );
//    if(res==WICED_SUCCESS){
//          // wiced_uart_transmit_bytes( WICED_UART_1, OK, sizeof( OK ) - 1 );
//       }
//       else{
//         //  wiced_uart_transmit_bytes( WICED_UART_1, NOT, sizeof( NOT ) - 1 );
//       }
    /* release the read lock */
    wiced_dct_read_unlock( app_dct, WICED_FALSE);

    return result_value;
}

/*
 * 1->  CONFIRMACION EVACUACION
 * 2->  AYUDA
 * 3->  EVACUACION
 * 4->  ENABLE_A1
 * 5->  FALLENMEN
 * 6->  INACTIVITY
 * 7->  SOUND ON/OFF
 * 8->  RESET WIFI
 * 9->  LOG_ID_LAST
 * */
void set_gpio_menssage(uint8_t index,uint8_t value){
     dct_read_write_app_dct_t*       app_dct                  = NULL;
     wiced_result_t res;
     /* get the App config section for modifying, any memory allocation required would be done inside wiced_dct_read_lock() */
     wiced_dct_read_lock( (void**) &app_dct, WICED_TRUE, DCT_APP_SECTION, 0, sizeof( *app_dct ) );

     /* Modify string_var by writing the whole DCT */
     switch (index) {
         case 1:
             app_dct->gpio_recib=value;
             break;
         case 2:
             app_dct->gpio_aux=value;
             break;
         case 3:
             app_dct->gpio_evac=value;
             break;
         case 4:
             app_dct->F_enable_btn=value;
             break;
         case 5:
             app_dct->gpio_fall=value;
             break;
         case 6:
             app_dct->gpio_inacty=value;
             break;
         case 7:
             app_dct->DCT0=value;
             break;
         case 8:
             app_dct->DCT1=value;
             break;
         case 9:
             app_dct->DCT2=value;
             break;
         default:
             break;
     }
    res=wiced_dct_write( (const void*) app_dct, DCT_APP_SECTION, 0, sizeof(dct_read_write_app_dct_t) );
     /* release the read lock */
     wiced_dct_read_unlock( app_dct, WICED_FALSE);

     if(res==WICED_SUCCESS){
//           wiced_uart_transmit_bytes( WICED_UART_1, OK_S, sizeof( OK_S ) - 1 );
             }
             else{
//                wiced_uart_transmit_bytes( WICED_UART_1, NOT_S, sizeof( NOT_S ) - 1 );
             }

     /* Read & print all DCT sections to check that nothing has changed */

}

void set_value_imu(uint8_t index,uint8_t value){
     dct_read_write_app_dct_t*       app_dct                  = NULL;

     /* get the App config section for modifying, any memory allocation required would be done inside wiced_dct_read_lock() */
     wiced_dct_read_lock( (void**) &app_dct, WICED_TRUE, DCT_APP_SECTION, 0, sizeof( *app_dct ) );

     /* Modify string_var by writing the whole DCT */
     switch (index) {
         case 1:
             app_dct->acc_xy=value;
             break;
         case 2:
             app_dct->acc_z_min=value;
             break;
         case 3:
             app_dct->acc_z_plus=value;
             break;
         default:
             break;
     }
     wiced_dct_write( (const void*) app_dct, DCT_APP_SECTION, 0, sizeof(dct_read_write_app_dct_t) );
     /* release the read lock */
     wiced_dct_read_unlock( app_dct, WICED_FALSE);

     /* Read & print all DCT sections to check that nothing has changed */

}

uint8_t get_value_imu(int index){
    dct_read_write_app_dct_t*       app_dct                  = NULL;
    uint8_t result_value=0;
    wiced_result_t res;

    /* get the App config section for modifying, any memory allocation required would be done inside wiced_dct_read_lock() */
    wiced_dct_read_lock( (void**) &app_dct, WICED_TRUE, DCT_APP_SECTION, 0, sizeof( *app_dct ) );

    /* Modify string_var by writing the whole DCT */
    switch (index) {
           case 1:
               result_value=app_dct->acc_xy;

               break;
           case 2:
               result_value=app_dct->acc_z_min;
               break;
           case 3:
               result_value=app_dct->acc_z_plus;
               break;
           default:
               break;
       }

    res=wiced_dct_write( (const void*) app_dct, DCT_APP_SECTION, 0, sizeof(dct_read_write_app_dct_t) );
    if(res==WICED_SUCCESS){
          // wiced_uart_transmit_bytes( WICED_UART_1, OK, sizeof( OK ) - 1 );
       }
       else{
         //  wiced_uart_transmit_bytes( WICED_UART_1, NOT, sizeof( NOT ) - 1 );
       }
    /* release the read lock */
    wiced_dct_read_unlock( app_dct, WICED_FALSE);

    return result_value;
}

void set_times(uint8_t index,uint8_t value){
     dct_read_write_app_dct_t*       app_dct                  = NULL;

     /* get the App config section for modifying, any memory allocation required would be done inside wiced_dct_read_lock() */
     wiced_dct_read_lock( (void**) &app_dct, WICED_TRUE, DCT_APP_SECTION, 0, sizeof( *app_dct ) );

     /* Modify string_var by writing the whole DCT */
     switch (index) {
         case 1:
             app_dct->blink_awake=value;
             break;
         case 2:
             app_dct->blink_tcp=value;
             break;
         case 3:
             //app_dct->acc_z_plus=value;
             break;
         default:
             break;
     }
     wiced_dct_write( (const void*) app_dct, DCT_APP_SECTION, 0, sizeof(dct_read_write_app_dct_t) );
     /* release the read lock */
     wiced_dct_read_unlock( app_dct, WICED_FALSE);

     /* Read & print all DCT sections to check that nothing has changed */

}

uint8_t get_times(int index){
    dct_read_write_app_dct_t*       app_dct                  = NULL;
    int result_value=0;
    wiced_result_t res;

    /* get the App config section for modifying, any memory allocation required would be done inside wiced_dct_read_lock() */
    wiced_dct_read_lock( (void**) &app_dct, WICED_TRUE, DCT_APP_SECTION, 0, sizeof( *app_dct ) );

    /* Modify string_var by writing the whole DCT */
    switch (index) {
           case 1:
               result_value=app_dct->blink_awake;
               break;
           case 2:
               result_value=app_dct->blink_tcp;
               break;
           case 3:
              // result_value= app_dct->gpio_evac;
               break;
           default:
               break;
       }

    res=wiced_dct_write( (const void*) app_dct, DCT_APP_SECTION, 0, sizeof(dct_read_write_app_dct_t) );
    if(res==WICED_SUCCESS){
          // wiced_uart_transmit_bytes( WICED_UART_1, OK, sizeof( OK ) - 1 );
       }
       else{
         //  wiced_uart_transmit_bytes( WICED_UART_1, NOT, sizeof( NOT ) - 1 );
       }
    /* release the read lock */
    wiced_dct_read_unlock( app_dct, WICED_FALSE);

    return result_value;
}

static wiced_result_t Set_config(){
    dct_read_write_app_dct_t*       app_dct                  = NULL;

    /* get the App config section for modifying, any memory allocation required would be done inside wiced_dct_read_lock() */
    wiced_dct_read_lock( (void**) &app_dct, WICED_TRUE, DCT_APP_SECTION, 0, sizeof( *app_dct ) );

    /* Modify string_var by writing the whole DCT */
        app_dct->F_config=1;
        app_dct->F_Sate=3;
//        app_dct->F_save=1;
    wiced_dct_write( (const void*) app_dct, DCT_APP_SECTION, 0, sizeof(dct_read_write_app_dct_t) );
    /* release the read lock */
    wiced_dct_read_unlock( app_dct, WICED_FALSE);

    /* Read & print all DCT sections to check that nothing has changed */
    return WICED_SUCCESS;
}

static wiced_result_t Down_net(){
    dct_read_write_app_dct_t*       app_dct                  = NULL;
    wiced_result_t res;

    /* get the App config section for modifying, any memory allocation required would be done inside wiced_dct_read_lock() */
    wiced_dct_read_lock( (void**) &app_dct, WICED_TRUE, DCT_APP_SECTION, 0, sizeof( *app_dct ) );

    /* Modify string_var by writing the whole DCT */
        app_dct->F_config=0;
        app_dct->F_Sate=0;
//        app_dct->F_save=0;

    res=wiced_dct_write( (const void*) app_dct, DCT_APP_SECTION, 0, sizeof(dct_read_write_app_dct_t) );
    /* release the read lock */
    if(res==WICED_SUCCESS){
        WPRINT_APP_INFO( ("Down net %d \r\n",app_dct->F_Sate) );

    }
    else{
        WPRINT_APP_INFO( ("Down net falied \r\n") );

    }
    wiced_dct_read_unlock( app_dct, WICED_FALSE);

    /* Read & print all DCT sections to check that nothing has changed */
    return WICED_SUCCESS;

}


static wiced_result_t Up_net(){
    dct_read_write_app_dct_t*       app_dct                  = NULL;

    /* get the App config section for modifying, any memory allocation required would be done inside wiced_dct_read_lock() */
    wiced_dct_read_lock( (void**) &app_dct, WICED_TRUE, DCT_APP_SECTION, 0, sizeof( *app_dct ) );

    /* Modify string_var by writing the whole DCT */
        app_dct->F_config=1;
    wiced_dct_write( (const void*) app_dct, DCT_APP_SECTION, 0, sizeof(dct_read_write_app_dct_t) );
    /* release the read lock */
    wiced_dct_read_unlock( app_dct, WICED_FALSE);

    /* Read & print all DCT sections to check that nothing has changed */
    return WICED_SUCCESS;
}
/*
 * 0->net_config() entra en modo confiuguracion
 * 1->
 * 2->entra en modo cargador
 * 3->net_lamp() entrra enm modo lampara
 * */
static wiced_result_t Un_Set_config(uint8_t value){

    dct_read_write_app_dct_t*       app_dct                  = NULL;

       /* get the App config section for modifying, any memory allocation required would be done inside wiced_dct_read_lock() */
       wiced_dct_read_lock( (void**) &app_dct, WICED_TRUE, DCT_APP_SECTION, 0, sizeof( *app_dct ) );

       switch(value){
       case 0:
           break;
       case 1:
             break;
       case 2:
           app_dct->F_Sate=2;
             break;
       case 3:
           if(app_dct->F_config==1){
               app_dct->F_Sate=3;
           }
           else{
               app_dct->F_Sate=0;

           }

             break;
       default:
           break;



       }

   //    app_dct->F_config=value;

       wiced_dct_write( (const void*) app_dct, DCT_APP_SECTION, 0, sizeof(dct_read_write_app_dct_t) );
       /* release the read lock */
       wiced_dct_read_unlock( app_dct, WICED_FALSE);

       /* Read & print all DCT sections to check that nothing has changed */
       return WICED_SUCCESS;


}

void Set_flag_charger(uint8_t value){
    dct_read_write_app_dct_t*       app_dct                  = NULL;
    wiced_result_t res;

    /* get the App config section for modifying, any memory allocation required would be done inside wiced_dct_read_lock() */
    wiced_dct_read_lock( (void**) &app_dct, WICED_TRUE, DCT_APP_SECTION, 0, sizeof( *app_dct ) );


    /* get the App config section for modifying, any memory allocation required would be done inside wiced_dct_read_lock() */
       wiced_dct_read_lock( (void**) &app_dct, WICED_TRUE, DCT_APP_SECTION, 0, sizeof( *app_dct ) );


           /* Modify string_var by writing the whole DCT */
//       if(  app_dct->F_chr==1){
//           app_dct->F_chr=0;
//       }
//       else{
//           app_dct->F_chr=1;
//       }
                  app_dct->F_chr=value;


       res=wiced_dct_write( (const void*) app_dct, DCT_APP_SECTION, 0, sizeof(dct_read_write_app_dct_t) );
       /* release the read lock */


    if(res==WICED_SUCCESS){
        wiced_uart_transmit_bytes( WICED_UART_1, OK_S, sizeof( OK_S ) - 1 );
          }
          else{
             wiced_uart_transmit_bytes( WICED_UART_1, NOT_S, sizeof( NOT_S ) - 1 );
          }
    /* release the read lock */
    wiced_dct_read_unlock( app_dct, WICED_FALSE);

    /* Read & print all DCT sections to check that nothing has changed */

}

uint8_t  is_charger(){
    dct_read_write_app_dct_t* dct_app = NULL;
    uint8_t res;
    if ( wiced_dct_read_lock( (void**) &dct_app, WICED_FALSE, DCT_APP_SECTION, 0, sizeof( *dct_app ) ) != WICED_SUCCESS )
    {
    return WICED_ERROR;
//        wiced_uart_transmit_bytes( WICED_UART_1, NOT, sizeof( NOT ) - 1 );
    }
    else{
//        wiced_uart_transmit_bytes( WICED_UART_1, OK, sizeof( OK ) - 1 );
    }

    // Get a copy of the WIFT config from the DCT into RAM

    res=dct_app->F_chr;

    wiced_dct_read_unlock( dct_app, WICED_FALSE );


return res;
}


void set_mac_bt(uint8_t *data){
    dct_read_write_app_dct_t*       app_dct                  = NULL;
    uint8_t len;
    len=strlen(&data);

    unsigned char str_r[len];
    strcpy(str_r,&data);

       /* get the App config section for modifying, any memory allocation required would be done inside wiced_dct_read_lock() */
       wiced_dct_read_lock( (void**) &app_dct, WICED_TRUE, DCT_APP_SECTION, 0, sizeof( *app_dct ) );

       /* Modify string_var by writing the whole DCT */
       strcpy(app_dct->MAC_BT,str_r);
       wiced_dct_write( (const void*) app_dct, DCT_APP_SECTION, 0, sizeof(dct_read_write_app_dct_t) );
       /* release the read lock */
       wiced_dct_read_unlock( app_dct, WICED_FALSE);
}
void get_mac_bt (){
    char* mac;
    dct_read_write_app_dct_t* dct_app = NULL;

        if ( wiced_dct_read_lock( (void**) &dct_app, WICED_FALSE, DCT_APP_SECTION, 0, sizeof( *dct_app ) ) != WICED_SUCCESS )
        {

        }
        // Get a copy of the WIFT config from the DCT into RAM

//        strcpy(MAC_BT_FACTORY,dct_app->MAC_BT);

        wiced_dct_read_unlock( dct_app, WICED_FALSE );


}

void save_nvram_passenger(char *mac,int a, char *start, char *date, uint8_t cass)
{
    printf("\n Mac a guardar %s Posicion %d \n",mac,a);
    dct_read_write_app_dct_t*       app_dct                  = NULL;

        /* get the App config section for modifying, any memory allocation required would be done inside wiced_dct_read_lock() */
        wiced_dct_read_lock( (void**) &app_dct, WICED_TRUE, DCT_APP_SECTION, 0, sizeof( *app_dct ) );
        switch(a)
        {
        case 1:
            memcpy(app_dct->passenger1, mac,strlen(mac));   /* Mac */
            app_dct->caso1[0] = cass;                       /* Caso de IN / OUT */
            memcpy(app_dct->start1,start, strlen(start));
            memcpy(app_dct->date1,date, strlen(date));
            break;
        case 2:
            memcpy(app_dct->passenger2, mac,strlen(mac));
            app_dct->caso1[1] = cass;
            memcpy(app_dct->start2,start, strlen(start));
            memcpy(app_dct->date2,date, strlen(date));
            break;
        case 3:
            memcpy(app_dct->passenger3, mac,strlen(mac));
            app_dct->caso1[2] = cass;
            memcpy(app_dct->start3,start, strlen(start));
            memcpy(app_dct->date3,date, strlen(date));
            break;
        case 4:
            memcpy(app_dct->passenger4, mac,strlen(mac));
            app_dct->caso1[3] = cass;
            memcpy(app_dct->start4,start, strlen(start));
            memcpy(app_dct->date4,date, strlen(date));
            break;
        }
        app_dct->DCT4 = 1;  /* Something is inside of the passenger */
        wiced_dct_write( (const void*) app_dct, DCT_APP_SECTION, 0, sizeof(dct_read_write_app_dct_t) );
}

chec_passenger_save()
{
    dct_read_write_app_dct_t*       app_dct                  = NULL;

    /* get the App config section for modifying, any memory allocation required would be done inside wiced_dct_read_lock() */
    wiced_dct_read_lock( (void**) &app_dct, WICED_TRUE, DCT_APP_SECTION, 0, sizeof( *app_dct ) );


    if(strlen(app_dct->passenger1) != 0)
    {
        memcpy(passenger[0].mac_bt,app_dct->passenger1, strlen(app_dct->passenger1));
        passenger[0].Pass_number=1;
        passenger[0].caso = app_dct->caso1[0];
        memcpy(passenger[0].time_start,app_dct->start1, strlen(app_dct->start1));
        memcpy(passenger[0].date,app_dct->date1, strlen(app_dct->date1));
        printf("\n **was save 1 \n");
    }
    if(strlen(app_dct->passenger2) != 0)
    {
        memcpy(passenger[1].mac_bt,app_dct->passenger2, strlen(app_dct->passenger2));
        passenger[1].Pass_number=2;
        passenger[1].caso = app_dct->caso1[1];
        memcpy(passenger[1].time_start,app_dct->start2, strlen(app_dct->start2));
        memcpy(passenger[1].date,app_dct->date2, strlen(app_dct->date2));
        printf("\n **was save 2 \n");
    }
    if(strlen(app_dct->passenger3) != 0)
    {
        memcpy(passenger[2].mac_bt,app_dct->passenger3, strlen(app_dct->passenger3));
        passenger[2].Pass_number=3;
        passenger[2].caso = app_dct->caso1[2];
        memcpy(passenger[2].time_start,app_dct->start3, strlen(app_dct->start3));
        memcpy(passenger[2].date,app_dct->date3, strlen(app_dct->date3));
        printf("\n **was save 3 \n");
    }
    if(strlen(app_dct->passenger4) != 0)
    {
        memcpy(passenger[3].mac_bt,app_dct->passenger4, strlen(app_dct->passenger4));
        passenger[3].Pass_number=4;
        passenger[3].caso = app_dct->caso1[3];
        memcpy(passenger[3].time_start,app_dct->start4, strlen(app_dct->start4));
        memcpy(passenger[3].date,app_dct->date4, strlen(app_dct->date4));
        printf("\n **was save 4 \n");
    }

}

void delete_all_passenger(void)
{
    dct_read_write_app_dct_t*       app_dct                  = NULL;

    /* get the App config section for modifying, any memory allocation required would be done inside wiced_dct_read_lock() */
    wiced_dct_read_lock( (void**) &app_dct, WICED_TRUE, DCT_APP_SECTION, 0, sizeof( *app_dct ) );

    app_dct->DCT4=0;

    memset(app_dct->passenger1,NULL,strlen(app_dct->passenger1));
    memset(app_dct->passenger2,NULL,strlen(app_dct->passenger2));
    memset(app_dct->passenger3,NULL,strlen(app_dct->passenger3));
    memset(app_dct->passenger4,NULL,strlen(app_dct->passenger4));

    app_dct->caso1[0] = 0;
    app_dct->caso1[1] = 0;
    app_dct->caso1[2] = 0;
    app_dct->caso1[3] = 0;

    memset(app_dct->start1,NULL,strlen(app_dct->start1));
    memset(app_dct->start2,NULL,strlen(app_dct->start2));
    memset(app_dct->start3,NULL,strlen(app_dct->start3));
    memset(app_dct->start4,NULL,strlen(app_dct->start4));

    memset(app_dct->date1,NULL,strlen(app_dct->date1));
    memset(app_dct->date2,NULL,strlen(app_dct->date2));
    memset(app_dct->date3,NULL,strlen(app_dct->date3));
    memset(app_dct->date4,NULL,strlen(app_dct->date4));

    wiced_dct_write( (const void*) app_dct, DCT_APP_SECTION, 0, sizeof(dct_read_write_app_dct_t) );

    memset(passenger[0].mac_bt,0,strlen(passenger[0].mac_bt));
    memset(passenger[1].mac_bt,0,strlen(passenger[1].mac_bt));
    memset(passenger[2].mac_bt,0,strlen(passenger[2].mac_bt));
    memset(passenger[3].mac_bt,0,strlen(passenger[3].mac_bt));

    passenger[0].caso = 0;
    passenger[1].caso = 0;
    passenger[2].caso = 0;
    passenger[3].caso = 0;

}


#endif  /* stdbool.h */
