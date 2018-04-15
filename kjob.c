#include "header.h"
#include "variables.h"
#include "kjob.h"
void kjob(char db[][100])
{
	int pno=atoi(db[1]);
	int i,j=0;
	for(i = 0; i < back_c ; i++)
	{
		if(background[i].state==1)
			j++;
		if(j==pno)
			break;
	}
	if(i==back_c)
		printf("No such job exists\n");
	else
		kill(background[i].pi,atoi(db[2]));

}
