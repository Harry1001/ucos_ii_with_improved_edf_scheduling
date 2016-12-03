#ifndef _TIME_WHEEL_H_
#define _TIME_WHEEL_H_

#include <os_cpu.h>
#include <ucos_ii.h>

typedef struct wheel {
	INT32U pm;
	struct os_tcb **headArr;
	struct os_tcb **tailArr;
}TimeWheel;

TimeWheel * initTimeWheel(INT32U pMax);
struct os_tcb * getReleasedTask(TimeWheel *wheel, INT32U currentTime);
void insertWaitTask(TimeWheel *wheel, struct os_tcb *ptcb);

#endif