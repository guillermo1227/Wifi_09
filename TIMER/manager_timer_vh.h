/**********************************************************************************
t* Copyright (C) 2018-2021 LASECÂ®ï¸� Telecomunicaciones S.A.P.I. de C.V.
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



#ifndef _MANAGER_TIMER_VH_H
#define _MANAGER_TIMER_VH_H

#include "wiced.h"
#include "stdbool.h"
#include "string.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"

#include "GPIO/manager_gpio_vh.h"

void Time_reboot(void* arg);
#define TIMER_TIME (1000)
#define TIME_LOC (6)


static wiced_timer_t timerHandle_reset;
static wiced_timer_t timer_Handle_reset_lcd;

uint32_t c_down_net=1;
uint8_t c_down_TASK=1;

#define limit_save_file 400

static wiced_timed_event_t guardian;
static wiced_timed_event_t guardian2;
static wiced_timed_event_t sound_dog;

static wiced_timed_event_t Beacon_guardian;
static wiced_timed_event_t Geo_guardian;

static wiced_timed_event_t Collision_guardian;
static wiced_timed_event_t H_passenger;
//static wiced_thread_t passengerThreadHandle;

static wiced_result_t guardian_v( void );
static wiced_result_t guardian_V2( void );
static wiced_result_t T_passenger( void );


uint8_t last_count_l=1;
uint8_t last_count_v=1;
//wiced_bool_t any_proximity=10;

wiced_bool_t first_seen_vh=WICED_TRUE;
wiced_bool_t first_seen_lm=WICED_TRUE;
wiced_bool_t first_seen_both=WICED_FALSE;

uint8_t rz_c=1;
void publish30sec(void* arg);
static wiced_result_t Beacon_V( void );
static wiced_result_t Collision_V( void );
//static wiced_result_t Acarreo_V( void );



void collision_event_log(wiced_thread_arg_t arg);
void SearchWifi(wiced_thread_arg_t arg);
//void passengerthread(wiced_thread_arg_t arg);

void timer_lcd(void* arg);
//void passenger1(char *input);
wiced_result_t result2;

void init_all_timer(){
/*  Initialize timer*/
    WPRINT_APP_INFO( ("Initialize timer\n") );

//    wiced_rtos_init_timer(&timer_Handle_reset_lcd, 60*TIMER_TIME, timer_lcd, NULL);

    wiced_rtos_init_timer(&timerHandle_reset, TIMER_TIME, Time_reboot, NULL);
//timer_Handle_reset_lcd
    wiced_rtos_start_timer(&timerHandle_reset);
//    wiced_rtos_start_timer(&timer_Handle_reset_lcd);

//        wiced_rtos_init_timer(&publishTimer, TIMER_TIME, publish30sec, NULL);
//        wiced_rtos_start_timer(&publishTimer);
        wiced_rtos_register_timed_event( &guardian, WICED_NETWORKING_WORKER_THREAD, &guardian_v, 1200, 0 );
        wiced_rtos_register_timed_event( &guardian2, WICED_NETWORKING_WORKER_THREAD, &guardian_V2, 1000, 0 );
        wiced_rtos_register_timed_event( &Geo_guardian, WICED_NETWORKING_WORKER_THREAD, &Beacon_V, 2100, 0 );
        wiced_rtos_register_timed_event( &H_passenger, WICED_NETWORKING_WORKER_THREAD, &T_passenger, 2800, 0 );

        //wiced_rtos_create_thread(&passengerThreadHandle, THREAD_BASE_PRIORITY+4, NULL, passengerthread, THREAD_STACK_SIZE, NULL);
        //wiced_rtos_register_timed_event( &Beacon_guardian, WICED_NETWORKING_WORKER_THREAD, &Acarreo_V, 4500, 0 );

//        wiced_rtos_create_thread(&ThreadHandle_W, THREAD_BASE_PRIORITY+5, "WIFI", SearchWifi, THREAD_STACK_SIZE, NULL);

//        wiced_rtos_register_timed_event( &Collision_guardian, WICED_NETWORKING_WORKER_THREAD, &Collision_V, 2000, 0 );

//        wiced_rtos_register_timed_event( &sound_dog, THREAD_BASE_PRIORITY+2, &commandThread, 3000, 0 );

}

//void passengerthread(wiced_thread_arg_t arg)
//{
//    printf("\n hola desde mi hilo \n");
//}
static wiced_result_t T_passenger( void )
{
    if(send_passanger_sd == 0)
    {
        for(uint8_t i=0;i<4;i++)
        {
            if(passenger[i].save_in_sd == out_sd)
            {
                printf(" Inside timer save something ----> ");
                memcpy(aux_p.mac_bt,passenger[i].mac_bt,strlen(passenger[i].mac_bt));                /* mac */
                memcpy(aux_p.date,passenger[i].date,strlen(passenger[i].date));                      /* fecha */
                memcpy(aux_p.time_start,passenger[i].time_start,strlen(passenger[i].time_start));    /* time */
                aux_p.Pass_number=passenger[i].Pass_number;                                          /* Numero de pasajero */
                aux_p.caso=passenger[i].caso;                                                        /* Caso, in/out */

                printf("\n ------> Caso %d\n",aux_p.caso);
                write_passenger(PASAJEROS_ROOT,date_get(&i2c_rtc),&aux_p,&fs_handle,s_Mac_W);
                passenger[i].save_in_sd = in_sd;
            }
            else if(passenger[i].save_in_sd == in_sd)
                printf("\n La mac ya esta guardada pero no borro, mantengo para cuado haya conexion %s \n",passenger[i].mac_bt);
        }
    }

    if((Product_f==WICED_TRUE)&&(GEOSF_F==WICED_TRUE)){
             Product_f=WICED_FALSE;
             GEOSF_F=WICED_FALSE;

             buzz(200,0);
             printf("prendio");
         }
        else if((Product_f==WICED_FALSE)&&(GEOSF_F==WICED_FALSE)){
            Product_f=WICED_TRUE;
            printf("no prendio nada\n");

        }
        printf("\t%d\t%d\n",Product_f,GEOSF_F);
        GEOSF_F=WICED_FALSE;
}


static wiced_result_t Collision_V( void ){

//    for(int b=1;b<buff_aux;b++){
//
//               if(strlen(aux_log_collision[b].mac_bt)!=0){
//                   printf("CCC %s,\n",aux_log_collision[b].mac_bt);
//                   }
//       }

       if(count_save_collision==3){
           for(int b=1;b<buff_aux;b++){
               aux_log_collision[b].flag=0;
           }
   //        count_save_collision=1;

       }
       else if(count_save_collision==6){
           for(int e=1;e<buff_aux;e++){
//
               if((strlen(aux_log_collision[e].mac_bt)!=0)&&(aux_log_collision[e].flag==0)){
//                   wiced_rtos_lock_mutex(&HTTPMutex);

                   read_data_collision(ANTICOLISION_ROOT,date_get(&i2c_rtc),&fs_handle);

                   strcpy( bt_joined.id,id_count_collision);

                   memset(filebuf,NULL,LOCAL_BUFFER_SIZE);


                   if(atoi(id_count_collision)<=limit_save_file){
                       write_data_collision(ANTICOLISION_ROOT,date_get(&i2c_rtc),&fs_handle,&bt_joined,&aux_log_collision[e],date_get_log(&i2c_rtc),s_Mac_W);
                       memset(aux_log_collision[e].mac_bt,NULL,18);
                       memset(bt_joined.mac_lamp,NULL,254);
                       memset(bt_joined.mac_vehc,NULL,254);
                       memset(bt_joined.mac_beacon,NULL,40);
                   }

                   printf("Index : %d",count_collision);
//
//                   printf("%s",filebuf);
//                   wiced_rtos_delay_milliseconds(10);

                   memset(aux_log_collision[e].mac_bt,NULL,18);
                   memset(bt_joined.mac_lamp,NULL,254);
                   memset(bt_joined.mac_vehc,NULL,254);
                   memset(bt_joined.mac_beacon,NULL,40);
//                   wiced_rtos_unlock_mutex(&HTTPMutex);

               }
           }


           count_save_collision=1;
           if(count_collision==buff_aux){
               count_collision=1;
           }
       }
       count_save_collision=count_save_collision+1;

}



static wiced_result_t Beacon_V( void ){

//    for(int b=0;b<20;b++){
//
//            if(strlen(AUX_BEACON[b].mac_bt)!=0){
//                printf("%s,%s,%s\n",AUX_BEACON[b].mac_bt,AUX_BEACON[b].time_start,AUX_BEACON[b].time_end);}
//    }

    if(count_save==(TIME_LOC/2)){
        for(int b=1;b<buff_aux;b++){
            AUX_BEACON[b].flag=0;
        }
//        count_save=1;

    }
    else if(count_save==TIME_LOC){
        for(int b=1;b<buff_aux;b++){

            if((strlen(AUX_BEACON[b].mac_bt)!=0)&&(AUX_BEACON[b].flag==0)&&(strlen(AUX_BEACON[b].time_end)!=0)){
                wiced_filesystem_unmount(&fs_handle);
                init_sd(&fs_handle);


//                printf("%s,%s\n",AUX_BEACON[b].mac_bt,AUX_BEACON[b].time_start);

                strcpy(master_data.bt_device.mac_bt,AUX_BEACON[b].mac_bt);
                strcpy(master_data.date,date_get_log(&i2c_rtc));
                strcpy(master_data.time_start,AUX_BEACON[b].time_start);
                strcpy(master_data.time_end,AUX_BEACON[b].time_end);
                strcpy(master_data.bt_device.mac_wifi,s_Mac_W);
                strcpy(master_data.state,"off");


//                printf("%s\n",read_data(SF_ROOT,date_get(&i2c_rtc),&fs_handle));
//               strcpy(master_data.id,read_data(SF_ROOT,date_get(&i2c_rtc),&fs_handle));
                read_data(SF_ROOT,date_get(&i2c_rtc),&fs_handle);
                strcpy(master_data.id,id_count);
                memset(filebuf,NULL,LOCAL_BUFFER_SIZE);


//                trabjar desde aquii con las funciones de condicional de guardado

//                printf("%d",atoi(id_count));

                if(atoi(id_count)<=limit_save_file){
                    write_data(SF_ROOT,date_get(&i2c_rtc),master_data,&fs_handle);
                    memset(AUX_BEACON[b].mac_bt,NULL,17);
                    memset(AUX_BEACON[b].time_start,NULL,11);
                    memset(AUX_BEACON[b].time_end,NULL,11);
                }
                else{
                    printf("Excedio el limite %d\n",atoi(id_count));
                }
//                printf("%s",filebuf);
                reg_incoming=WICED_FALSE;

            }
        }
        count_save=1;
        if(count_beacon<buff_aux){  /* Que pasa cuando count_beacon es mayo a 100, si encotro */
            count_beacon=1;
        }
//        else                  // --- Agregado por mi
//            count_beacon=1;   // --- Agregado por mi
    }
    count_save=count_save+1;

}

void timer_lcd(void* arg){
    flag_lcd_timer=WICED_TRUE;
    printf("TIMER LCD DOS SEGUNDOS\n");
    //wiced_rtos_set_semaphore(&tcpGatewaySemaphore);

}

static wiced_result_t guardian_v( void ){

//    WPRINT_APP_INFO( ("LAMPARA Last count %d  actual count %d \r\n",last_count_l,count_l) );
//    WPRINT_APP_INFO( ("VEHICULO Last count %d  actual count %d \r\n",last_count_v,count_v) );


//    WPRINT_APP_INFO( ("its worked timed event\n") );
    if((count_v>=1)&&(first_seen_vh==WICED_FALSE)){
        if(last_count_v<count_v){
            first_seen_vh=WICED_TRUE;
        }
        else{
            first_seen_vh=WICED_FALSE;
        }
    }

    if((count_v>=1)&&(first_seen_vh==WICED_TRUE)){
        first_seen_vh=WICED_FALSE;
        if(silent==WICED_FALSE){
            buzz(150,0);
        }
    }



    if(((count_l>=1)||(count_v>=1))&&(proximity==1)){
        if(silent==WICED_FALSE){
            buzz(150,1);
        }
    }

    last_count_v=count_v;

    if(button_down_net==WICED_TRUE){
        Down_net();
        wiced_rtos_delay_milliseconds( 100);
        wiced_framework_reboot();
    }
//
////    first_seen_lm=WICED_FALSE;
//
//    WPRINT_APP_INFO( ("FRIST LAMP %d \r\n",first_seen_lm) );
//    WPRINT_APP_INFO( ("FRIST VEHC %d \r\n",first_seen_vh) );
//



    }

static wiced_result_t guardian_V2( void ){

//    WPRINT_APP_INFO( ("LAMPARA Last count %d  actual count %d \r\n",last_count_l,count_l) );
//    WPRINT_APP_INFO( ("VEHICULO Last count %d  actual count %d \r\n",last_count_v,count_v) );
    check_sound();

//    WPRINT_APP_INFO( ("its worked timed event\n") );
    if((count_l>=1)&&(first_seen_lm==WICED_FALSE)){
        if(last_count_l<count_l){
            first_seen_lm=WICED_TRUE;
        }
        else{
            first_seen_lm=WICED_FALSE;
        }
    }

    if((count_l>=1)&&(first_seen_lm==WICED_TRUE)){
            first_seen_lm=WICED_FALSE;
            if(silent==WICED_FALSE){
                buzz(85,0);
            }
        }
    last_count_l=count_l;

//    if(_flag_driver == WICED_TRUE)
//            {
//            printf("\n *** Sound driver *** \n");
//            buzz(200,2);
//            _flag_driver = WICED_FALSE;
//            }

    }

/*************** Timer to publish weather data every 30sec ***************/


void Time_reboot(void* arg){
    wiced_bool_t upnet=WICED_FALSE;
//                     c_down_net=c_down_net+1;
//    WPRINT_APP_INFO( ("down %d \r\n",c_down_net) );

     if(main_c==3){
         upnet=wiced_network_is_up(WICED_STA_INTERFACE);
         if(upnet==WICED_FALSE){
                 WPRINT_APP_INFO( ("leave %d \r\n",c_down_net) );
                 c_down_net=c_down_net+1;
             if(c_down_net==7200){
                 wiced_framework_reboot();
             }
         }
         else{
//             wiced_gpio_output_high(Sat_WiFi);
//             wiced_gpio_output_high(Sat_WiFi);
//             platform_gpio_output_high(Sat_WiFi);

//             c_down_net=0;
//             if((send_data_task==WICED_FALSE)){
//                 c_down_TASK=c_down_TASK+1;
//                 if((c_down_TASK>=200)){   //
//                     wiced_framework_reboot();
//                 }
//             }
//
//             else{
//                 c_down_TASK=0;
//                 send_data_task=WICED_FALSE;
//             }

//             wiced_gpio_output_high(Sat_WiFi);
//             wiced_gpio_output_high(Sat_WiFi);
//             platform_gpio_output_high(Sat_WiFi);
//             blink_vehicle();


         }
     }

     wiced_bool_t on_off_b;
     wiced_gpio_input_get_bool(GPIO_ON_OF,&on_off_b);

     if(on_off_b==WICED_FALSE){
         c_silent=c_silent+1;
         if((c_silent==2)&&(silent==WICED_FALSE)){
             _sound_flag=WICED_TRUE;
             silent=WICED_TRUE;
             frist_seen_silent=WICED_TRUE;
             wiced_rtos_set_semaphore(&displaySemaphore);

         }
         else if((c_silent==2)&&(silent==WICED_TRUE)){
             silent=WICED_FALSE;
             frist_seen_silent=WICED_TRUE;
             _sound_flag=WICED_TRUE;
             wiced_rtos_set_semaphore(&displaySemaphore);

         }
     }
     else{
         c_silent=0;
     }


     if((tcp_down_connect==WICED_TRUE)&&(reg_incoming==WICED_FALSE)){

         wiced_framework_reboot();
     }

}

//void passenger1(char *input){
//    if(strstr(input,_Passenger_in))
//    {
//        int x=0, number_p;
//        unsigned char str_split[128];
//
//        memcpy(str_split, input, strlen(input));
//        char * frist_split;
//        frist_split=strtok(str_split,_split_tama_2);
//
//        while(frist_split!=NULL)
//        {
//            switch (x)
//            {
//            case 0:
//                /* No hago nada */
//                break;
//            case 1:
//                number_p = atoi(frist_split);
//                passenger[0].Pass_number= number_p;
//                printf("\n Paasenger number %d \n",passenger[0].Pass_number);
//                break;
//            case 2:
//                memcpy(passenger[0].mac_bt,frist_split,strlen(frist_split));
//                printf("\n mac: %s \n",passenger[0].mac_bt);
//                break;
//            default:
//                break;
//            }
//            x++;
//            frist_split=strtok(NULL,_split_tama_2);
//        }
//        /* Tomo la hora de llegada/salida del pasajero y mac y el numero de pasajero */
//        strcpy(passenger[0].time_start,time_get(&i2c_rtc));
//        strcpy(passenger[0].date,date_get_log(&i2c_rtc));
//        passenger[0].caso = 1;                                 /* Variable para saber el caso IN/OUT */
//
//        write_passenger(PASAJEROS_ROOT,date_get(&i2c_rtc),&passenger,&fs_handle);
//    }
//    else if(strstr(input,_Passenger_out))
//    {
//        int x=0, number_p;
//        unsigned char str_split[50];
//        memcpy(str_split,input, strlen(input));
//
//        char * frist_split;
//        frist_split=strtok(str_split,_split_tama_2);
//        while(frist_split!=NULL)
//        {
//            switch(x)
//            {
//            case 0:
//                /* No hago nada */
//                break;
//            case 1:
//                number_p = atoi(frist_split);
//                passenger[0].Pass_number= number_p;
//                printf("\n Paasenger number %d \n",passenger[0].Pass_number);
//                break;
//            case 2:
//                memcpy(passenger[0].mac_bt,frist_split,strlen(frist_split));
//                printf("\n mac: %s \n",passenger[0].mac_bt);
//                break;
//            default:
//                break;
//            }
//            x++;
//            frist_split=strtok(NULL,_split_tama_2);
//        }
//        /* Tomo la hora de llegada/salida del pasajero y mac y el numero de pasajero */
//        strcpy(passenger[0].time_start,time_get(&i2c_rtc));
//        strcpy(passenger[0].date,date_get_log(&i2c_rtc));
//        passenger[0].caso = 2;                                 /* Variable para saber el caso IN/OUT */
//        write_passenger(PASAJEROS_ROOT,date_get(&i2c_rtc),&passenger,&fs_handle);
//
//    }
//}

#endif  /* stdbool.h */
