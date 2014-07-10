/*************************************************************************
	> File Name: strstr.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Wed 18 Jun 2014 07:32:07 PM PDT
 ************************************************************************/

#include<stdio.h>

int strstr(char *str1, char *str2)
{
	char *l= str1, *s = str2;
	int pos = 0, sign = 1;
	while(*l){
		sign=1;
		while(*l && *l != *s){
			++l;
			++pos;
		}

		if(*l == *s){
			while(*s && *l){
				if(*s != *l){
					sign = 0;
					break;
				}
				++s;
				++l;
			}
			if(*l==0){
				return -1;
			}
			else if(!sign){

				l=str1+pos+1;
				s=str2;
			}
			else{
				return pos;
			}
		}
	}
	return -1;
}

int main()
{

	char str[1000],sub_str[500];
	printf("Please input a long string:\n");
	gets(str);
	printf("Please input a short string:\n");
	gets(sub_str);
	int position=strstr(str,sub_str);
	if(position==-1)
		printf("Isn't substring\n");
	else
		printf("The position is %d.\n",position);
	return 0;
}
