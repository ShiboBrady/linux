/*************************************************************************
	> File Name: bash.h
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Wed 25 Jun 2014 06:22:29 AM PDT
 ************************************************************************/

#ifndef BASH_H
#define BASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_LEN 100
#define DISPLAY "[shibo @localhost ~] $"

void del_enter(char *str);
void process(char *cmd_line, char ***cmd);
#endif
