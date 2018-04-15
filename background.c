#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "background.h"
#include "variables.h"

void background_proc(char st[][100],int k) 
{
    char* argv[3];
	argv[2]=NULL;
    int status;
    argv[0]=st[0];
    if(strcmp(st[1],"&")==0)
		argv[1]=NULL;
	else
		argv[1]=st[1];
    int pid = fork();
    if (pid < 0)
    {
        printf("Fork Failed\n");
        return;
    }
    else if (pid==0)
    {
        execvp(argv[0],argv);
    }
    else
    {
        printf("pid : %d\n",pid);
    }
    background[back_c].pi=pid;
    background[back_c].state=1;
    char temp[200];
    strcpy(temp,argv[0]);
    int x=1;
    while(x<k-1){
    strcat(temp," ");
    strcat(temp,st[x++]);
    }
    strcpy(background[back_c].name,temp);
    back_c++;
    return;
}
