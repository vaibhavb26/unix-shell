#include <stdio.h>
#include <string.h>
#include <pwd.h>
#include <unistd.h>
#include "cd.h"

void cd(char *token,struct passwd *home,char* home_dir)
{
	char del[]=" \n\t\r";
	token=strtok(NULL,del);
//	printf("%s\n",token);
	if(token==NULL)
		chdir(home_dir);
	else if((strcmp(token,"~"))==0)
		chdir(home_dir);
	else if(chdir(token)!=0)
		printf("directory doesn't exist\n");
//	char cwd[1024];
//	printf("%s\n",getcwd(cwd,1024));
}
