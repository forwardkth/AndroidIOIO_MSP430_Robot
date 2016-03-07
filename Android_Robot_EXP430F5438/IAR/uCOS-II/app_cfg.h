/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                          (c) Copyright 2003-2007; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                       APPLICATION CONFIGURATION
*
*                                             TI MSP430X
*                                             MSP430x5xx
*
* Filename      : app_cfg.h
* Version       : V1.00
* Programmer(s) : Hong Soong
*********************************************************************************************************
*/

#ifndef  __APP_CFG_H__
#define  __APP_CFG_H__

/*
*********************************************************************************************************
*                                       ADDITIONAL uC/MODULE ENABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            TASK PRIORITIES
*********************************************************************************************************
*/


#define  OS_TASK_TMR_PRIO            (OS_LOWEST_PRIO - 4)
#define  APP_START_TASK_PRIO                   5
#define  APP_START_TASK1_PRIO                  6
#define  APP_START_TASK2_PRIO                  7
#define  APP_START_TASK3_PRIO                  8

/*
*********************************************************************************************************
*                                            TASK STACK SIZES
*********************************************************************************************************
*/

#define  APP_START_TASK_STK_SIZE            256
#define  APP_TASK1_STK_SIZE                 256
#define  APP_TASK2_STK_SIZE                 256
#define  APP_TASK3_STK_SIZE                 256

#endif
