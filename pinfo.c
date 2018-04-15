#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <sys/resource.h>
#include "pinfo.h"

void pinfo(char* token)
{
	struct stat sts;
	char del[2]=" ";
	token=strtok(NULL,del);
	if(token==NULL)
	{
		int pid=getpid();
		printf("PID=%d\n",pid);
		char buffer[40];
		sprintf(buffer,"%d",pid);
		int lineNumber = 2;
		char str[]="/proc/";
		strcat(str,buffer);
		char execute[1000];
		char exec[1000];
		strcpy(execute,str);
		strcat(execute,"/exe");
		char str2[]="/status";
		strcat(str,str2);
		FILE *file = fopen(str, "r");
		int count = 0;
		struct rusage usage;
		readlink(execute,exec,1000);
		getrusage(RUSAGE_SELF,&usage);
		if ( file != NULL )
		{
			char line[1024]; /* or other suitable maximum line size */
			while (fgets(line, sizeof line, file) != NULL) /* read a line */
			{
				if (count == lineNumber)
				{
					printf("%s",line);
					break;
					//in case of a return first close the file with "fclose(file);"
				}
				else
				{
					count++;
				}
			}
			printf("Executable path: %s\n",exec);
			printf("Memory Usage: %ld\n",usage.ru_maxrss);
			fclose(file);
		}
		else
		{
			printf("file doesn't exist\n");
		}

	}
	else
	{
		char str3[]="/proc/";
		char execute[1000],exec[1000];
		strcat(str3,token);
		if (stat(str3, &sts) == -1 && errno == ENOENT) 
		{
			printf("invalid pid\n");
		}
		else
		{
			strcpy(execute,str3);
			strcat(execute,"/exe");
			printf("PID=%s\n",token);
			int lineNumber=2;
			char str4[]="/status";
			strcat(str3,str4);
			FILE *file = fopen(str3,"r");
			int count=0;
			struct rusage usage;
			readlink(execute,exec,1000);
			getrusage(RUSAGE_SELF,&usage);
			if ( file != NULL )
			{
				char line[1024]; /* or other suitable maximum line size */
				while (fgets(line, sizeof line, file) != NULL) /* read a line */
				{

					if (count == lineNumber)
					{
						printf("%s",line);
						break;
						//in case of a return first close the file with "fclose(file);"
					}
					else
					{
						count++;
					}
				}
				fclose(file);
				printf("Executable path: %s\n",exec);
				printf("Memory Usage: %ld\n",usage.ru_maxrss);

			}
			else
			{
				printf("file doesn't exist\n");
			}
		}
	}
	return;
}
