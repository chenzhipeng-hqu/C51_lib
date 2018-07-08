
#include "task.h"

u8 Task_Max = 1;

int TaskInitial(u8 task_max)
{
	u8 i = 0;
	Task_Max = task_max;
	for (i=0; i<Task_Max; i++) 
	{  
		if(Task_Array[i].TaskInit != NULL)
		{
			Task_Array[i].TaskInit();		
		}
	} 
	return 0;
}

int TaskScheduler(void)
{
	u8 i;  
	
	for (i=0; i<Task_Max; i++) 
	{  
		if(Task_Array[i].State == READY)
		{
			Task_Array[i].State = RUNING;
			if(Task_Array[i].TaskHook != NULL)
			{				
				Task_Array[i].TaskHook();
			}
			Task_Array[i].State = SUSPEND;
		}	
	} 
	return 0;
}

void TaskTickHandler(void)
{
	u8 i;  

	for (i=0; i<Task_Max; i++) 
	{  
		if(Task_Array[i].State == SUSPEND
			|| Task_Array[i].State == RUNING
			|| Task_Array[i].State == READY
		)
		{
			if(Task_Array[i].Timer != 0)
			{
				Task_Array[i].Timer--;
				
				if(Task_Array[i].Timer == 0)
				{
					Task_Array[i].Timer = Task_Array[i].ItvTime;
					Task_Array[i].State = READY;
				}
			}			
		}
	}  
}

void Idle_Task(void)
{
	//TODO: calcule CPU usage
}

