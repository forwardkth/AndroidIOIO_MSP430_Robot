/*
*********************************************************************************************************
*                                               uC/OS-II
*                                         The Real-Time Kernel
*
*                             (c) Copyright 2008, Micrium, Inc., Weston, FL
*                                          All Rights Reserved
*
*
*                                              Sample code
*
* File : APP.C
* By   : Hong Soong
*********************************************************************************************************
*/

#include <includes.h>

/*
*********************************************************************************************************
*                                                 DEFINES
*********************************************************************************************************
*/

#define  LCD_LINE_BUF       18                                          /* The last character should always be a null character     */
#define  LCD_NUM_LINES       9

#define  PB_LEFT            DEF_BIT_01
#define  PB_RIGHT           DEF_BIT_02
#define  PB_SELECT          DEF_BIT_03
#define  PB_UP              DEF_BIT_04
#define  PB_DOWN            DEF_BIT_05
#define  PB_S1              DEF_BIT_06
#define  PB_S2              DEF_BIT_07

/*
*********************************************************************************************************
*                                                VARIABLES
*********************************************************************************************************
*/

static  OS_STK      AppTaskStartStk[APP_START_TASK_STK_SIZE];
static  OS_STK      AppTask1Stk[APP_TASK1_STK_SIZE];
static  OS_STK      AppTask2Stk[APP_TASK2_STK_SIZE];
static  OS_STK      AppTask3Stk[APP_TASK3_STK_SIZE];
        
static  CPU_CHAR    AppLCDTxt0[LCD_LINE_BUF];
static  CPU_CHAR    AppLCDTxt1[LCD_LINE_BUF];
static  CPU_CHAR    AppLCDTxt2[LCD_LINE_BUF];
static  CPU_CHAR    AppLCDTxt3[LCD_LINE_BUF];
static  CPU_CHAR    AppLCDTxt4[LCD_LINE_BUF];
static  CPU_CHAR    AppLCDTxt5[LCD_LINE_BUF];
static  CPU_CHAR    AppLCDTxt6[LCD_LINE_BUF];
static  CPU_CHAR    AppLCDTxt7[LCD_LINE_BUF];
static  CPU_CHAR    AppLCDTxt8[LCD_LINE_BUF];

static  CPU_CHAR    AppLCDTxt[(LCD_LINE_BUF * LCD_NUM_LINES)] = "  0  Micrium      000 uCOS-II  00   0 ---------                     Time Ticks                        Context Switches                                   ";


/*
*********************************************************************************************************
*                                            FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  AppDispInit   (void);
static  void  AppDispUpdate (void);
static  void  AppTaskCreate (void);
static  void  AppTaskStart  (void        *p_arg);
static  void  AppTask1      (void        *p_arg);
static  void  AppTask2      (void        *p_arg);
static  void  AppTask3      (void        *p_arg);
static  void  AppUpdatePB   (CPU_INT08U   pb_pressed); 
static  void  AppFormatDec  (CPU_CHAR    *dst, CPU_INT32U  val, CPU_INT08U  len);

/*$PAGE*/
/*
*********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.  It is assumed that your code will call
*               main() once you have performed all necessary CPU and C initialization.
*
* Arguments   : none
*********************************************************************************************************
*/

void  main (void)
{
    CPU_INT08U  err;


    BSP_IntDisAll();                                                    /* Disable all interrupts until we are ready to accept them */

    OSInit();                                                           /* Initialize "uC/OS-II, The Real-Time Kernel"              */

    OSTaskCreateExt(AppTaskStart,                                       /* Create the start task                                    */
                    (void *)0,
                    (OS_STK *)&AppTaskStartStk[APP_START_TASK_STK_SIZE - 1],
                    APP_START_TASK_PRIO,
                    APP_START_TASK_PRIO,
                    (OS_STK *)&AppTaskStartStk[0],
                    APP_START_TASK_STK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);

#if OS_TASK_NAME_EN > 0
    OSTaskNameSet(APP_START_TASK_PRIO, "Startup", &err);
#endif

    OSStart();                                                          /* Start multitasking (i.e. give control to uC/OS-II)       */
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                          STARTUP TASK
*
* Description : This is an example of a startup task.  As mentioned in the book's text, you MUST
*               initialize the ticker only once multitasking has started.
*
* Arguments   : p_arg   is the argument passed to 'AppStartTask()' by 'OSTaskCreate()'.
*
* Note(s)     : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                  used.  The compiler should not generate any code for this statement.
*               2) Interrupts are enabled once the task start because the I-bit of the CCR register was
*                  set to 0 by 'OSTaskCreate()'.
*********************************************************************************************************
*/

static  void  AppTaskStart (void *p_arg)
{
    (void)p_arg;

    BSP_Init();                                                         /* Initialize BSP functions                                 */

#if (OS_TASK_STAT_EN > 0)
    OSStatInit();                                                       /* Determine CPU capacity                                   */
#endif

    AppDispInit();                                                      /* Initialize the Display layout                            */

    AppTaskCreate();                                                    /* Create application tasks                                 */
    
    while (1) {                                                         /* Task body, always written as an infinite loop.           */
        AppDispUpdate();  
        OSTimeDlyHMSM(0, 0, 0, 100);
    }
}


/*$PAGE*/
/*
*********************************************************************************************************
*                                        CREATE APPLICATION TASKS
*
* Description: This function creates the application tasks.
*
* Arguments  : none.
*
* Note(s)    : none.
*********************************************************************************************************
*/

static  void  AppTaskCreate (void)
{
    CPU_INT08U  err;
    
    
    OSTaskCreateExt(AppTask1,                                           /* Create start task 1                                      */
                   (void *)0,
                   (OS_STK *)&AppTask1Stk[APP_TASK1_STK_SIZE - 1],
                    APP_START_TASK1_PRIO,
                    APP_START_TASK1_PRIO,
                   (OS_STK *)&AppTask1Stk[0],
                    APP_TASK1_STK_SIZE,
                   (void *)0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
                    
#if OS_TASK_NAME_EN > 0
    OSTaskNameSet(APP_START_TASK1_PRIO, "Task 1", &err);
#endif
                    
                    
    OSTaskCreateExt(AppTask2,                                           /* Create start task 2                                      */
                   (void *)0,
                   (OS_STK *)&AppTask2Stk[APP_TASK2_STK_SIZE - 1],
                    APP_START_TASK2_PRIO,
                    APP_START_TASK2_PRIO,
                   (OS_STK *)&AppTask2Stk[0],
                    APP_TASK2_STK_SIZE,
                   (void *)0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
                    
#if OS_TASK_NAME_EN > 0
    OSTaskNameSet(APP_START_TASK2_PRIO, "Task 2", &err);
#endif
                 
                      
    OSTaskCreateExt(AppTask3,                                           /* Create start task 3                                      */
                   (void *)0,
                   (OS_STK *)&AppTask3Stk[APP_TASK3_STK_SIZE - 1],
                    APP_START_TASK3_PRIO,
                    APP_START_TASK3_PRIO,
                   (OS_STK *)&AppTask3Stk[0],
                    APP_TASK3_STK_SIZE,
                   (void *)0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
                    
#if OS_TASK_NAME_EN > 0
    OSTaskNameSet(APP_START_TASK3_PRIO, "Task 3", &err);
#endif                    
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                          STARTUP TASK 1
*
* Description : This task updates the OSCPUUsage value to be displayed on the LCD.
*
* Arguments   : p_arg   is the argument passed to 'AppTask1()' by 'OSTaskCreate()'.
*
* Returns     : none
*********************************************************************************************************
*/

void  AppTask1 (void *p_arg)
{
    while (1) {
        AppFormatDec(&AppLCDTxt5[0], OSTime, LCD_LINE_BUF);             /* Update the value to be displayed                         */
        OSTimeDlyHMSM(0, 0, 0, 50);
    }
}

/*
*********************************************************************************************************
*                                          STARTUP TASK 2
*
* Description : 
*
* Arguments   : p_arg   is the argument passed to 'AppTask2()' by 'OSTaskCreate()'.
*
* Returns     : none
*********************************************************************************************************
*/

void  AppTask2 (void *p_arg)
{
    while (1) {
        AppFormatDec(&AppLCDTxt7[0], OSCtxSwCtr, LCD_LINE_BUF);         /* Update the value to be displayed                         */
        OSTimeDlyHMSM(0, 0, 0, 50);
    }
}

/*
*********************************************************************************************************
*                                          STARTUP TASK 3
*
* Description : 
*
* Arguments   : p_arg   is the argument passed to 'AppTask3()' by 'OSTaskCreate()'.
*
* Returns     : none
*********************************************************************************************************
*/

void  AppTask3 (void *p_arg)
{
    while (1) {
        AppUpdatePB(PB_Rd());                                           /* Update the PB layout to be displayed on the LCD          */
        OSTimeDlyHMSM(0, 0, 0, 100);
    }
}

/*
*********************************************************************************************************
*                                         DISPLAY INIT
*
* Description : This initializes the display text.
*
* Arguments   : p_arg   is the argument passed to 'AppTask3()' by 'OSTaskCreate()'.
*
* Returns     : none
*********************************************************************************************************
*/

void  AppDispInit (void)
{
    CPU_CHAR    *tmp;
    CPU_INT08U   i;
    
        
    i = 0;
    
    while (i < ((LCD_LINE_BUF - 1) * LCD_NUM_LINES)) {                  /* Break the initial display string into smaller strings    */
        switch (i / (LCD_LINE_BUF - 1)) {
            case 0:
                 tmp = &AppLCDTxt0[0];
                 break;
            case 1:
                 tmp = &AppLCDTxt1[0];
                 break;
            case 2:
                 tmp = &AppLCDTxt2[0];
                 break;
            case 3:
                 tmp = &AppLCDTxt3[0];
                 break;
            case 4:
                 tmp = &AppLCDTxt4[0];
                 break;
            case 5:
                 tmp = &AppLCDTxt5[0];
                 break;
            case 6:
                 tmp = &AppLCDTxt6[0];
                 break;
            case 7:
                 tmp = &AppLCDTxt7[0];
                 break;
            case 8:
                 tmp = &AppLCDTxt8[0];
                 break;
            default:
                 tmp = 0;                                               /* Error, set exit conditions                               */
                 i   = ((LCD_LINE_BUF - 1) * LCD_NUM_LINES);
                 break;
        }
        
        do {
            tmp[i % 17] = AppLCDTxt[i];
            i++;
        } while (((i % 17) != 0));
        
        tmp[17] = 0;
    }
}

/*
*********************************************************************************************************
*                                         DISPLAY UPDATE
*
* Description : This updates the display.
*
* Arguments   : p_arg   is the argument passed to 'AppTask3()' by 'OSTaskCreate()'.
*
* Returns     : none
*********************************************************************************************************
*/

void  AppDispUpdate (void)
{
    LCD_PrintLineCol (&AppLCDTxt0[0], 0, 0);
    LCD_PrintLineCol (&AppLCDTxt1[0], 1, 0);
    LCD_PrintLineCol (&AppLCDTxt2[0], 2, 0);
    LCD_PrintLineCol (&AppLCDTxt3[0], 3, 0);
    LCD_PrintLineCol (&AppLCDTxt4[0], 4, 0);
    LCD_PrintLineCol (&AppLCDTxt5[0], 5, 0);
    LCD_PrintLineCol (&AppLCDTxt6[0], 6, 0);
    LCD_PrintLineCol (&AppLCDTxt7[0], 7, 0);
    LCD_PrintLineCol (&AppLCDTxt8[0], 8, 0);  
}

/*
*********************************************************************************************************
*                                         FORMAT DECIMAL
*
* Description : This formats a right aligned decimal string.
*
* Arguments   : dst     pointer to the memory location to store the formatted string
*               val     the value to format to string
*               len     the length of the string
*
* Returns     : none
*********************************************************************************************************
*/

void  AppFormatDec (CPU_CHAR  *dst, CPU_INT32U  val, CPU_INT08U  len)
{
    CPU_INT08U  i;
    CPU_INT08U  j;
    CPU_INT08U  k;
    CPU_INT08U    tmp[LCD_LINE_BUF];
    
    
    BSP_FormatDec(&tmp[0], val, 10);                                    /* Get a string representation of the value                 */
    
    tmp[10] = 0;                                                        /* Null terminator                                          */
    
    i = 0;
    
    while ((tmp[i] == '0') && (i < (len - 2)) && (tmp[i] != 0)) {       /* Find the number of leading 0 characters                  */
        i++;
    };

    if (i == (len - 2)){                                                /* If the entire string is 0...                             */
        dst[len - 2] = '0';                                             /* Set the last character as 0                              */
    } else {
        j = i;
        
        while (tmp[j++] != 0);                                          /* Iterate to the end of the string (null terminated)       */
        
        k = j - i - 1;                                                  /*  Determine the number of actual digits                   */
        j = k;
        
        while (k--) {
            dst[len - (k + 2)] = tmp[i++];                              /* Copy the digits with a right alignment                   */
        } 

        i -= j;                                                         /* Determine the number of non-digits                       */
        
        while (i < (len - (j + 1))) {
            dst[i++] = ' ';                                             /* "Erase" the unimportant characters                       */
        }
    }
        
    dst[len - 1] = 0;                                                   /* Null terminate the string                                */
}

/*
*********************************************************************************************************
*                                    PUSH BUTTON UPDATE
*
* Description : This updates the push buttons pressed and the strings to display.
*
* Arguments   : p_arg   is the argument passed to 'AppTask3()' by 'OSTaskCreate()'.
*
* Returns     : none
*********************************************************************************************************
*/

void  AppUpdatePB (CPU_INT08U  pb_pressed) 
{   
    if (pb_pressed & PB_LEFT) {
        AppLCDTxt1[1]  = '0';
    } else {
        AppLCDTxt1[1]  = 'o';
    }
    
    if (pb_pressed & PB_RIGHT) {
        AppLCDTxt1[3]  = '0';
    } else {
        AppLCDTxt1[3]  = 'o';
    }
    
    if (pb_pressed & PB_SELECT) {
        AppLCDTxt1[2]  = '0';
    } else {
        AppLCDTxt1[2]  = 'o';
    }
    
    if (pb_pressed & PB_UP) {
        AppLCDTxt0[2]  = '0';
    } else {
        AppLCDTxt0[2]  = 'o';
    }
    
    if (pb_pressed & PB_DOWN) {
        AppLCDTxt2[2]  = '0';
    } else {
        AppLCDTxt2[2]  = 'o';
    }   
    
    if (pb_pressed & PB_S1) {
        AppLCDTxt1[14] = '0';
    } else {
        AppLCDTxt1[14] = 'o';
    }
    
    if (pb_pressed & PB_S2) {
        AppLCDTxt1[15] = '0';
    } else {
        AppLCDTxt1[15] = 'o';
    }
}