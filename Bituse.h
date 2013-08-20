#ifndef _BITUSE_H
#define _BITUSE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxNum 1000000000
#define Number 100000000

//矩阵左右翻转，矩阵宽度为8的倍数
//每8字节翻转一次，copy一次来提高效率
void TurnRighttoLift(unsigned char *src, unsigned char *dest, int wid, int high);

//计算8字节数字中2进制数包含的1的个数
int getbitnumofone(long long nValue);

//大缓存区10取8操作，针对大缓存区每10bit取8bit的操作
//牺牲部分空间已达到效率的提升，预先计算一次得到没16位对应转换后的8bit数据，每4个10bit通过查表5次来得到5个8bit数据
//效率大大优于位操作
//Mode : 3-低8位；2-中8位；1-高8位
int NewGet8BitOf10(unsigned char * buf, int nBufLen,unsigned char * Outbuf, int nOutBufLen, int Mode);

//基于位操作的桶排序
unsigned int * _sort(unsigned int *a);

#endif