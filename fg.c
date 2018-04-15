#include "variables.h"
#include "header.h"
#include "fg.h"
void fg(char db[][100])
{
	int pno=atoi(db[1]),s,i,j;
	for(i = 0; i < back_c ; i++)
	{
		if(background[i].state==1)
			j++;
		if(j==pno)
			break;
	}
	if(i==back_c)
		printf("No such background process exists\n");
	else
	{
		printf("%s\n",background[i].name);
		waitpid(background[i].pi,&s,0);
		background[i].pi=0;
	}
}
