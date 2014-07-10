/*************************************************************************
	> File Name: my_bash.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Wed 25 Jun 2014 03:52:24 AM PDT
 ************************************************************************/


#include "bash.h"

char user_name[30];
char host_name[30];
char file_name[30];
char display_name[100];

int main()
{
	char command_line[MAX_LEN];
	char **cmd;
	int i, irst;
	long int irtn;
	while(1){
		i = 0;
		do{
			printf("%s ", DISPLAY);
			if(fgets(command_line, MAX_LEN, stdin) == NULL){
				printf("exit\n");
				return 1;
			}
			del_enter(command_line);
		}while(strlen(command_line) == 0);
		//process1(command_line, &cmd);
		//process2(command_line, &cmd);
		process3(command_line, &cmd);
		irtn = fork();
		if(irtn > 0){
			wait(NULL);
		}
		else{
			irst = execvp(cmd[0], cmd);
			if(irst == -1){
				printf("-my_bash:%s:command not found.\n", cmd[0]);
			}
		}
	}
	return 0;
}
