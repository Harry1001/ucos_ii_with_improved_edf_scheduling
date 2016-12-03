#include <time_wheel.h>
#include <stdlib.h>

TimeWheel * initTimeWheel(INT32U pMax)
{
	TimeWheel *wheel;
	wheel = (TimeWheel *)malloc(sizeof(TimeWheel));
	if (wheel == 0){
		exit(1);
	}
	wheel->pm = pMax;
	wheel->headArr = (OS_TCB **)malloc(pMax*sizeof(OS_TCB*));
	wheel->tailArr = (OS_TCB **)malloc(pMax*sizeof(OS_TCB*));
	INT32U i = 0u;
	for (; i < pMax; i++){
		wheel->headArr[i] = wheel->tailArr[i] = (OS_TCB *)0;
	}

	return wheel;
}

OS_TCB * getReleasedTask(TimeWheel *wheel, INT32U currentTime)
{
	INT32U index = currentTime%wheel->pm;
	OS_TCB *p = wheel->headArr[index];
	wheel->headArr[index] = wheel->tailArr[index] = (OS_TCB *)0;
	return p;
}

void insertWaitTask(TimeWheel *wheel, OS_TCB *ptcb)
{
	INT32U index = ((EDF_TCB_DATA *)ptcb->OSTCBExtPtr)->start%wheel->pm;
	ptcb->TimeWheelNext = (OS_TCB *)0;
	if (wheel->tailArr[index] == (OS_TCB *)0) {
		wheel->headArr[index] = wheel->tailArr[index] = ptcb;
	}
	else {
		wheel->tailArr[index]->TimeWheelNext = ptcb;
		wheel->tailArr[index] = ptcb;
	}
}