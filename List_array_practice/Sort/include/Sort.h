/*************************************************************************
	> File Name: Sort.h
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Wed 18 Jun 2014 12:41:29 AM PDT
 ************************************************************************/

#ifndef SORT_H
#define SORT_H

#define N 10

#include <stdio.h>

void swap(int *a, int *b);
void bubbleSort(int *a, int n);
void quickSort(int *a, int n);
void insertSort(int *a, int n);
void chooseSort(int *a, int n);
void init(int *a, int n);
void show(int *a, int n);

#endif

