#include "variables.h"

void ssetenv(char st[][100])
{
	if(st[1]==NULL) 
		printf("Invalid arguments to setenv");
	else
	{
		if(st[2]==NULL)
			setenv (st[1], "", 1);
		else
			setenv (st[1], st[2], 1);
	}
	return ;
}

void uunsetenv(char st[][100])
{
	unsetenv(st[1]);
}
