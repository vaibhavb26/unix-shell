#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"echo.h"

void echo(char *a)
{

	char *s=(char *)malloc(sizeof(char));
	int i=5,l=0;
	int j=0;
	while(a[i]!='\n')
		s[j++]=a[i++];
	i=0;
	if(j==0)
	{
		printf("\n");
		return ;
	}
	char *token;
	if((strcmp(s,"\'")==0) || (strcmp(s,"\"")==0) )
	{
		printf("Invalid String\n");
		return ;
	}
	if((strcmp(s,"\'\'")==0) || (strcmp(s,"\"\"")==0) )
	{
		printf("\n");
		return ;
	}
	while(s[i]==32)
		i++;
	l=i;
	while(s[l]!='\0')
		l++;
	l--;
	if((s[i]!=34 && s[i]!=39) && (s[l]!=34 && s[l]!=39))
	{
		token = strtok(s," ");
		while( token != NULL ) 
		{
			printf("%s ", token );
			token = strtok(NULL," ");
		}
	}
	else
	{
		while((s[i]==34 && s[l]==34) || (s[i]==39 && s[l]==39))
		{
			i++;
			l--;
		}
		if((s[i]==34 || s[i]==39) || (s[l]==34 || s[l]==39))
		{
			printf("Invalid String\n");
			return;
		}
		l++;
		while(i!=l)
		{
			printf("%c",s[i]);
			i++;
		}
	}
	printf("\n");
	return;
}
