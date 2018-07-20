
#ifndef		__TASK_H__   
#define		__TASK_H__ 

#include "common.h"

typedef enum _TaskState
{
	DORMANT = 0, 
	RUNING,
	READY,
	SUSPEND,
	ISR,
}TaskState;

// task 
typedef struct _TaskTypeDef
{  
	TaskState State;                 // RUN, READY, SUSPEND
	u8 Timer;              // 
	u8 ItvTime;              // 
	void (*TaskInit)(volatile u32 *);
	void (*TaskHook)(void);    // 
} TaskTypeDef;       // 

extern TaskTypeDef xdata Task_Array[];

extern int TaskInitial(u8 task_max, volatile u32 *ulSysClock);

extern int TaskScheduler(void);

extern void TaskTickHandler(void);

extern void Idle_Task(void);



#endif /* __TASK_H__ */