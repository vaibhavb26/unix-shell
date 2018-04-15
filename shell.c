#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include <pwd.h>
#include <unistd.h>
#include "ls.h"
#include "cd.h"
#include "background.h"
#include "foreground.h"
#include "pwd.h"
#include "pinfo.h"
#include "echo.h"
#include "variables.h"
#include "jobs.h"
#include "kjob.h"
#include "redirection.h"
#include "pipe.h"
#include "overkill.h"
#include "fg.h"
#include "setenv.h"

struct utsname a;

int checkredirection(char *s)
{
	int i=0;
	while(s[i]!=0)
	{
		if(s[i]=='<' || s[i]=='>')
			return 1;
		i++;
	}
	return 0;
}

int checkpipe(char *s)
{
	int i=0;
	while(s[i]!=0)
	{
		if(s[i]=='|')
			return 1;
		i++;
	}
	return 0;
}

void print(struct utsname a,char home_dir[][500])
{
	char *cwd=(char *)malloc(sizeof(char)*1024);
	cwd=getcwd(cwd,1024);
	if( strcmp(home_dir[0],a.nodename)==0 && strcmp(home_dir[1],a.sysname)==0 && strcmp(home_dir[2],cwd)==0)
		printf("<%s@%s:~>",a.nodename,a.sysname);
	else printf("<%s@%s:%s>",a.nodename,a.sysname,cwd);
	free(cwd);
	return ;
}
void sig_handle(int sign)
{
	if (sign==2 ||sign==3)
	{
		fflush(stdout);
		printf("\n");
		char home_dir[3][500];
		strcpy(home_dir[0],a.nodename);
		strcpy(home_dir[1],a.sysname);
		char *cwd=(char *)malloc(sizeof(char)*1024);
		cwd=getcwd(cwd,1024);
		free(cwd);
		strcpy(home_dir[2],cwd);		
		signal(SIGQUIT,sig_handle);
		signal(SIGINT,sig_handle);
		
	}
		if(sign == 20)
			kill(curid,SIGTSTP);
	
	return;
}
void child_sig(int signo)
{
	pid_t pid;
	int r;
	pid=waitpid(WAIT_ANY,&r, WNOHANG);
	int i;
	for(i=0;i<back_c;i++)
	{
		if(background[i].pi==pid && background[i].state==1)
		{
			background[i].state=0;
			printf("\n%s %d exited normally\n",background[i].name,background[i].pi);
			char home_dir[3][500];
			strcpy(home_dir[0],a.nodename);
			strcpy(home_dir[1],a.sysname);
			char *cwd=(char *)malloc(sizeof(char)*1024);
			cwd=getcwd(cwd,1024);
			free(cwd);
			strcpy(home_dir[2],cwd);			
			print(a,home_dir);
			fflush(stdout);
			printf("\n");
		}
	}
	signal(SIGCHLD, child_sig);
	return;
}
int main()
{
	struct passwd *home;
	uname(&a);
	char home_dir[3][500];

	char *cwd=(char *)malloc(sizeof(char)*1024);
	cwd=getcwd(cwd,1024);
	free(cwd);

	strcpy(home_dir[0],a.nodename);
	strcpy(home_dir[1],a.sysname);
	strcpy(home_dir[2],cwd);
	
	
	print(a,home_dir);
	signal(SIGINT,SIG_IGN);
	signal(SIGINT,sig_handle);
	signal(SIGCHLD,SIG_IGN);
	signal(SIGCHLD,child_sig);
	signal(SIGTSTP,SIG_IGN);
	signal(SIGTSTP,sig_handle);
	signal(SIGQUIT,SIG_IGN);
	signal(SIGQUIT,sig_handle);
	while(1)
	{
		char *buf2,*buf;
		buf = (char *)malloc(sizeof(char)*1024);
		char *token;
		char *token_col[100];
		ssize_t size=0;
		getline(&buf2,&size,stdin);
		if(strcmp(buf2,"\n")==0)
		{
			print(a,home_dir);
			continue;
		}
		strcpy(buf,buf2);
		int i=0,j=0;
		token_col[j]=strtok(buf,";");
		while(token_col[j]!=NULL)
		{
			j++;
			token_col[j]=strtok(NULL,";");
		}
		while(i<j)
		{
			int k=0,cr=0,cp=0;
			char st[100][100]={0};
			char *temp=token_col[i];
			cp=checkpipe(token_col[i]);
			if(cp)
			{

				parse_pipe(token_col[i]);
				i++;
				continue;
			}

			cr=checkredirection(token_col[i]);
			if(cr)
			{

				redirection(token_col[i]);
				i++;
				continue;
			}
			token=strtok(token_col[i]," \n\t\r");
			if(token==NULL)
			{
				i++;
				continue;
			}
			if(strcmp(token,"quit")==0)
				return 0;
			else if((strcmp(token,"ls"))==0)
				ls(token);
			else if((strcmp(token,"cd"))==0)
				cd(token,home,home_dir[2]);
			else if((strcmp(token,"pwd"))==0)
				pwd();
			else if((strcmp(token,"pinfo"))==0)
				pinfo(token);
			else if((strcmp(token,"echo"))==0)
				echo(token);		
			else if((strcmp(token,"jobs"))==0)
				execute_jobs();
			else if((strcmp(token,"overkill"))==0)
				overkill();
				
			else
			{
				int k=0;
				while(token!=NULL)
				{
					strcpy(st[k++],token);
					token=strtok(NULL," \n\t\r");
				}
				if((strcmp(st[0],"kjob"))==0)
					kjob(st);
				else if((strcmp(st[0],"fg"))==0)
					fg(st);
				else if((strcmp(st[0],"setenv"))==0)
					ssetenv(st);
				else if((strcmp(st[0],"unsetenv"))==0)
					uunsetenv(st);
				else if(strcmp(st[k-1],"&")==0)
				{
					background_proc(st,k);
				}
				else
				{
					foreground(st);
				}
			}
			i++;
		}
		print(a,home_dir);		
		free(buf);
	}
}
