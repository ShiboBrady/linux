/*************************************************************************
	> File Name: cmd_process.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Wed 25 Jun 2014 06:20:28 AM PDT
 ************************************************************************/
#include "bash.h"

void del_enter(char *str)
{
	while(*str != '\n'){
		++str;
	}
	*str = '\0';
}

void process1(char *cmd_line, char ***cmd)
{
	int pos = 0, i = 0;
	char word[20] = "";
	char *p = cmd_line;
	while(*p == 32){
		++p;
	}
	while(sscanf(p + pos, "%s", word) == 1){
		if(i == 0){
			*cmd = (char**)malloc(sizeof(char*));
		}
		else{
			*cmd = (char**)realloc(*cmd, (i + 1) * sizeof(char*));
		}
		(*cmd)[i] = (char*)malloc((strlen(word) + 1) * sizeof(char));
		strcpy((*cmd)[i], word);
		++i;
		pos += strlen(word) + 1;
		while(*(p + pos) == 32){
			++pos;
		}
	}
	(*cmd)[i] = NULL;
}

void process2(char *cmd_line, char ***cmd)
{
	char *p = cmd_line;
	int i = 0;
	while(*p != '\0'){
		if(*p != 32 && *(p + 1) == 32){
			*(++p) = '\0';
		    ++i;
		}
		if(*p != 32 && *(p + 1) == '\0'){
			++i;
		}
		++p;
	}
	*cmd = (char **)malloc((i+1) * sizeof(char*));
	char *q = cmd_line;
	int k = 0, flag = 0;
	while(k != i){
		if(*q != 32 && k == 0){
			(*cmd)[k++] = q;printf("***%s\n", (*cmd)[k - 1]);
		}
		if(*q == '\0'){
			flag = 1;
		}
		if(*q != 32 && *q != '\0' && flag == 1){
			flag = 0;
			(*cmd)[k++] = q;printf("***%s\n", (*cmd)[k - 1]);
		}
		++q;
	}
	(*cmd)[i] = NULL;
}

void process3(char *cmd_line, char ***cmd)
{
	int i = 0, flag = 0;
	char *p = cmd_line;
	if(*p != 32){
		flag = 1;
	}
	while(*p != '\0'){
		if(*p != 32 && *(p + 1) == 32){
			*(p + 1) = '\0';
			++p;
		}
		if(flag == 1  || ((*p == 32 || *p == '\0') && *(p + 1) != 32 && *(p + 1) != '\0')){
			if(flag == 0){
				++p;
			}
			if(i == 0){
				*cmd = (char**)malloc(sizeof(char*));
			}
			else{
				*cmd = (char**)realloc(*cmd, (i + 1) * sizeof(char*));
			}
			(*cmd)[i++] = p;
		}
		flag = 0;
		++p;
	}
}
