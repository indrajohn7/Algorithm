#include<stdio.h>
#include<stdlib.h>

static char* A[]={
	"jhvjh",
	"kjbjb",
	"jbkjb",
	"jhvjh",
	"jhvjh",
	"jhvjh",
	"kjbjb",
	"jbkjb",
	"kjbjb",
	"jbkjb",
	"kjbjb",
	"jbkjb",
};

int main()
{
	char* s=(char*)malloc(1000);
	int i;
	for(i=0;i<1000;i++)
		s[i]='\0';
	strncpy(s,"|",1);
	for(i=0;i<10;i++){
		if(i)
			strncat(s,A[i],strlen(A[i]));
	}
	printf("A::%s\n",s);
	return 0;
}
