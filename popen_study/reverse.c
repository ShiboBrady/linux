/*************************************************************************
	> File Name: reverse.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Wed 25 Jun 2014 06:55:44 PM PDT
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char *p, char *q)
{
	char temp;
	while(p < q){
		temp = *p;
		*p = *q;
		*q = temp;
		++p;
		--q;
	}
}

int main()
{
	char str[1024];
	int flag = 0;
	char *p, *q, *r, temp;
		
	while(fgets(str, 1024, stdin) != NULL){
		str[strlen(str) - 1] = '\0';

		p = str;
		while(*p == 32){
			++p;
		}
		q = p;
		while(*q != '\0'){
			if(*q == 32){
				if(flag == 0){
					flag = 1;
					r = q - 1;
				}
			}
			if(*q != 32){
				if(flag == 1){
					flag = 0;
				}
				r = q;
			}	
			++q;
		}
		q = r;
		reverse(p, q);
		q = p;
		flag = 0;
		while(q != (r + 1)){
			if(*q != 32 && flag == 0 ){
				flag = 1;
				p = q;
			}
			if(*q != 32 && (*(q + 1) == 32 || *(q + 1) == '\0') && flag == 1){
				flag = 0;
				reverse(p, q);
			}
			++q;
		}
		printf("%s\n", str);
	}
	return 0;
}
