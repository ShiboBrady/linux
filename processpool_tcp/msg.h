/*************************************************************************
	> File Name: msg.h
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Wed 02 Jul 2014 06:58:14 PM PDT
 ************************************************************************/

#ifndef MSG_H
#define MSG_H

#define MSG_SIZE 8188
#define MSG_LEN (8192 - MSG_SIZE)
typedef struct tag
{
	int s_len;
	char s_buf[MSG_SIZE];
}MSG;

#endif
