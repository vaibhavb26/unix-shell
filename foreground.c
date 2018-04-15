#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "foreground.h"
#include "variables.h"
void foreground(char st[][100])
{

	char *argv[3];
	int i=0;
	int  status;
	argv[0]=st[0];
	char *token;
	token=strtok(st[1]," \n\t\r");
	if(token==NULL)
	{
		argv[1]=NULL;
	}
	else
	{
		argv[1]=st[1];
	}
	int pid = fork();
	if (pid < 0)
	{
		printf("Fork Failed\n");
		return;
	}
	else if (pid==0)
	{
		execvp(argv[0],argv);
		printf("no such command\n");
		exit(0);
	}
	else
	{       
		while(wait(&status)!=pid);
	}
	int x;
	curid=pid;

	if(WIFSTOPPED(x))
	{
		background[back_c].pi=pid;
		background[back_c].state=1;
		strcpy(background[back_c].name,argv[0]);
		back_c++;
	}
	else
	{
		background[back_c].pi=pid;
		background[back_c].state=0;
		strcpy(background[back_c].name,argv[0]);
		back_c++;
	}
	return;
}
