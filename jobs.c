#include "header.h"
#include "variables.h"
void execute_jobs()
{
	int i,j=1;
	for (i = 0; i <back_c ; i++)
		if(background[i].state == 1 && background[i].pi>0)
			printf("[%d] %s %s [%d]\n",j++,background[i].name,"Running",background[i].pi);
//		else
//			printf("[%d] %s %s [%d]\n",j++,background[i].name,"Stopped",background[i].pi);		
}
