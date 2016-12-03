/*
*********************************************************************************************************
*                                            EXAMPLE CODE
*
*                          (c) Copyright 2009-2011; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*
*               Please feel free to use any application code labeled as 'EXAMPLE CODE' in
*               your application products.  Example code may be used as is, in whole or in
*               part, or may be used as a reference only.
*
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*
*               You can contact us at www.micrium.com.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                          APPLICATION CODE
*
*                                          Microsoft Windows
*
* Filename      : app.c
* Version       : V1.00
* Programmer(s) : JJL
*                 FGK
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include <includes.h>


/*
*********************************************************************************************************
*                                             LOCAL DEFINES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            LOCAL VARIABLES
*********************************************************************************************************
*/

#if OS_TASK_EDF_EN > 0u
static  CPU_STK  Task1Stk[APP_TASK_START_STK_SIZE];
static  CPU_STK  Task2Stk[APP_TASK_START_STK_SIZE];
static  CPU_STK  Task3Stk[APP_TASK_START_STK_SIZE];
static  CPU_STK  Task4Stk[APP_TASK_START_STK_SIZE];
static  CPU_STK  Task5Stk[APP_TASK_START_STK_SIZE];

static  EDF_TCB_DATA  Task1EDFData = {.c_value=1u, .p_value=3u, .comp_time=1u, .ddl=3u, .start=0, .end=0};
static  EDF_TCB_DATA  Task2EDFData = {.c_value=3u, .p_value=5u, .comp_time=3u, .ddl=5u, .start=0, .end=0};
static  EDF_TCB_DATA  Task3EDFData = {.c_value=1u, .p_value=4u, .comp_time=1u, .ddl=4u, .start=0, .end=0};
static  EDF_TCB_DATA  Task4EDFData = {.c_value=2u, .p_value=5u, .comp_time=2u, .ddl=5u, .start=0, .end=0};
static  EDF_TCB_DATA  Task5EDFData = {.c_value=2u, .p_value=10u, .comp_time=2u, .ddl=10u, .start=0, .end=0};
#else
static  CPU_STK  AppTaskStartStk[APP_TASK_START_STK_SIZE];
#endif

/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

#if OS_TASK_EDF_EN > 0u
static  void  Task1(void  *p_arg);
static  void  Task2(void  *p_arg);
static  void  Task3(void  *p_arg);
static  void  Task4(void  *p_arg);
static  void  Task5(void  *p_arg);
#else
static  void  AppTaskStart(void  *p_arg);
#endif

/*
*********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.  It is assumed that your code will call
*               main() once you have performed all necessary initialization.
*
* Argument(s) : none.
*
* Return(s)   : none.
*********************************************************************************************************
*/

int  main (void)
{
    OSInit();                                                   /* Init uC/OS-II.                                       */

#if OS_TASK_EDF_EN > 0u
	maxPeriod = 0u;
	readyTaskHeap = heapInitialize();
	/*
	OSTaskCreateExt((void(*)(void *))Task1,
		(void          *) 0,
		(OS_STK        *)&Task1Stk[APP_TASK_START_STK_SIZE - 1],
		(INT8U          ) 1+3,
		(INT16U         ) 1,
		(OS_STK        *)&Task1Stk[0],
		(INT32U         ) APP_TASK_START_STK_SIZE,
		(void          *)&Task1EDFData,
		(INT16U         )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

	OSTaskCreateExt((void(*)(void *))Task2,
		(void          *) 0,
		(OS_STK        *)&Task2Stk[APP_TASK_START_STK_SIZE - 1],
		(INT8U          ) 2+3,
		(INT16U         ) 2,
		(OS_STK        *)&Task2Stk[0],
		(INT32U         ) APP_TASK_START_STK_SIZE,
		(void          *)&Task2EDFData,
		(INT16U         )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));
	*/
	OSTaskCreateExt((void(*)(void *))Task3,
		(void          *) 0,
		(OS_STK        *)&Task3Stk[APP_TASK_START_STK_SIZE - 1],
		(INT8U          ) 3+3,
		(INT16U         ) 3,
		(OS_STK        *)&Task3Stk[0],
		(INT32U         ) APP_TASK_START_STK_SIZE,
		(void          *)&Task3EDFData,
		(INT16U         )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

	OSTaskCreateExt((void(*)(void *))Task4,
		(void          *) 0,
		(OS_STK        *)&Task4Stk[APP_TASK_START_STK_SIZE - 1],
		(INT8U          ) 4+3,
		(INT16U         ) 4,
		(OS_STK        *)&Task4Stk[0],
		(INT32U         ) APP_TASK_START_STK_SIZE,
		(void          *)&Task4EDFData,
		(INT16U         )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

	OSTaskCreateExt((void(*)(void *))Task5,
		(void          *)0,
		(OS_STK        *)&Task5Stk[APP_TASK_START_STK_SIZE - 1],
		(INT8U          ) 5+3,
		(INT16U         ) 5,
		(OS_STK        *)&Task5Stk[0],
		(INT32U)APP_TASK_START_STK_SIZE,
		(void          *)&Task5EDFData,
		(INT16U)(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));
		

	waitTaskWheel = initTimeWheel(maxPeriod);
#else
    OSTaskCreateExt((void(*)(void *))AppTaskStart,              /* Create the start task                                */
        (void          *) 0,
        (OS_STK        *)&AppTaskStartStk[APP_TASK_START_STK_SIZE - 1],
        (INT8U          ) APP_TASK_START_PRIO,
        (INT16U         ) APP_TASK_START_PRIO,
        (OS_STK        *)&AppTaskStartStk[0],
        (INT32U         ) APP_TASK_START_STK_SIZE,
        (void          *) 0,
        (INT16U         )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));
#endif

    OSStart();                                                  /* Start multitasking (i.e. give control to uC/OS-II).  */
}


/*
*********************************************************************************************************
*                                          STARTUP TASK
*
* Description : This is an example of a startup task.  As mentioned in the book's text, you MUST
*               initialize the ticker only once multitasking has started.
*
* Argument(s) : p_arg       is the argument passed to 'AppTaskStart()' by 'OSTaskCreate()'.
*
* Return(s)   : none.
*
* Note(s)     : (1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                   used.  The compiler should not generate any code for this statement.
*********************************************************************************************************
*/

#if OS_TASK_EDF_EN > 0u
static  void  Task1(void  *p_arg)
{
	//APP_TRACE("Task1 is running...\n\r");
	p_arg = p_arg;
	while (1);
}

static  void  Task2(void  *p_arg)
{
	//APP_TRACE("Task2 is running...\n\r");
	p_arg = p_arg;
	while (1);
}

static  void  Task3(void  *p_arg)
{
	//APP_TRACE("Task3 is running...\n\r");
	p_arg = p_arg;
	while (1);
}

static  void  Task4(void  *p_arg)
{
	//APP_TRACE("Task4 is running...\n\r");
	p_arg = p_arg;
	while (1);
}

static  void  Task5(void  *p_arg)
{
	//APP_TRACE("Task5 is running...\n\r");
	p_arg = p_arg;
	while (1);
}

#else
static  void  AppTaskStart (void *p_arg)
{
   
   (void)p_arg;

    BSP_Init();                                                 /* Initialize BSP functions                             */
    CPU_Init();                                                 /* Initialize uC/CPU services                           */

#if OS_CFG_STAT_TASK_EN > 0u
    OSStatTaskCPUUsageInit(&err);                               /* Compute CPU capacity with no task running            */
#endif

    APP_TRACE_DBG(("uCOS-II is Running...\n\r"));

    while (DEF_ON) {                                            /* Task body, always written as an infinite loop.       */
        OSTimeDlyHMSM(0, 0, 1, 0);

        APP_TRACE_DBG(("Time: %d\n\r", OSTimeGet()));
    }
}
#endif
