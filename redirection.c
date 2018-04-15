#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include "redirection.h"

void redirection(char *buf)
{
    char *re[10];
    char *argv[3];
	argv[2]=NULL;    
	char *token;
	int pid,status,in,out;
    
    int i=0;
    re[0]=strtok(buf,">");
    re[1]=strtok(NULL,">");
    int j=0;
    char *del2[10];

    del2[0]=strtok(re[0],"<");
    del2[1]=strtok(NULL,"<");

    token=strtok(del2[0]," \n\t\r");
    argv[0]=token;
    token=strtok(NULL," \n\t\r");
    if(token)
        argv[1]=token;
    else
        argv[1]=NULL;
    char *new_tok;
    pid=fork();
    if(del2[1]!=NULL)
    {
        new_tok=strtok(del2[1]," \n\t\r");
        if(new_tok!=NULL)
        {
            in=open(new_tok, O_RDONLY);
			if(in<0 && pid==0)
			{
                printf("File does not exist\n");
                return;
			}
            if(pid==0 && in >=0)
                dup2(in,0);
        }
        else
        {	
            printf("Invalid input\n");
        }
    }
    char *new_tok2;
    if(re[1]!=NULL)
    {
        new_tok2=strtok(re[1]," \n\t\r");
        if(new_tok2!=NULL)
        {
            out=open(new_tok2,O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR );
            if(pid==0)
                dup2(out,1);
        }
        else
        {
            printf("Invalid input\n");
        }
    }
    if(pid==0)
    {
        execvp(argv[0],argv);
        exit(0);
    }
    else
    {
        while(wait(&status)!=pid);
    }
    return;
}
