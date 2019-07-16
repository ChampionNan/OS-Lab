#include<stdio.h>
#include<string.h>
int main(){
	char str[20];
	long int a, b;
	int str_len;
	int ret;
	str_len = 0;
	printf("Give me a string:\n");
	scanf("%s",str);
	str_len = strlen(str);
	a = syscall(328, str, str_len, &ret);
	b = syscall(327, ret);
	return 0;
}

		
