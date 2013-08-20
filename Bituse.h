#ifndef _BITUSE_H
#define _BITUSE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxNum 1000000000
#define Number 100000000

//�������ҷ�ת��������Ϊ8�ı���
//ÿ8�ֽڷ�תһ�Σ�copyһ�������Ч��
void TurnRighttoLift(unsigned char *src, unsigned char *dest, int wid, int high);

//����8�ֽ�������2������������1�ĸ���
int getbitnumofone(long long nValue);

//�󻺴���10ȡ8��������Դ󻺴���ÿ10bitȡ8bit�Ĳ���
//�������ֿռ��ѴﵽЧ�ʵ�������Ԥ�ȼ���һ�εõ�û16λ��Ӧת�����8bit���ݣ�ÿ4��10bitͨ�����5�����õ�5��8bit����
//Ч�ʴ������λ����
//Mode : 3-��8λ��2-��8λ��1-��8λ
int NewGet8BitOf10(unsigned char * buf, int nBufLen,unsigned char * Outbuf, int nOutBufLen, int Mode);

//����λ������Ͱ����
unsigned int * _sort(unsigned int *a);

#endif