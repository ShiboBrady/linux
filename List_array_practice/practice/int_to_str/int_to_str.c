/*************************************************************************
	> File Name: int_to_str.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Wed 18 Jun 2014 07:17:38 PM PDT
 ************************************************************************/

#include<stdio.h>

void int_to_str(char *str, int a)
{
	int sum, i;
	int arr[20],k=0;
	if(a < 0){
		*str='-';
		++str;
		a=0-a;
	}
	do
	arr[k++]=(a%10);
	while(a/=10);
	for(i=k-1;i>=0;--i)
		*(str++)=arr[i]+48;
	*str=0;
}

int main()
{
	int a;
	char str[20];
	printf("Please input a number:\n");
	scanf("%d",&a);
	int_to_str(str,a);
	puts(str);
	return 0;
}
