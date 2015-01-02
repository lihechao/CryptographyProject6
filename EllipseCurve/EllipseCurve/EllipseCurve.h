#ifndef ELLIPSECURVE_H
#define ELLIPSECURVE_H
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#define TEST_TIMES	5		/*���Բ��ԵĲ��Դ���*/
#define INFINITE 65536
typedef struct point
{
	long long x,y;
}Point;
typedef struct ellipsecurve
{
	long long p,a,b;
}EllipseCurve;
typedef struct publickey
{
	EllipseCurve EC;
	Point P,Q;
	long long n;		/*��P������n*/
}PublicKey;
typedef struct cipherdata
{
	long long x1,y1;
	long long c;
}CipherData;
typedef struct signature
{
	long long r,s;
}Signature;
unsigned long long PowerMod(unsigned long long BaseNum,unsigned long long Exponent,unsigned long long Modulus);	/*ģ������*/
bool IsPrime(unsigned long long Num);		/*Miller-Rabin���Բ���*/
long long Legendre(unsigned long long n,unsigned long long p);	/*�������õ·���(n/p)*/
long long Inverse(long long Num,long long Modulus);	/*����ModulusΪģ��Num����*/
long long Extend_Euclid(long long a,long long b,long long* x,long long* y);//��չŷ������㷨
Point PointAdd(Point P,Point Q,EllipseCurve EC);		/*����P+Q=R*/
Point DoublePoint(Point P,EllipseCurve EC);		/*����2P=R*/
Point kPoint(long long k,Point P,EllipseCurve EC);		/*����kP=R*/
CipherData EncrpytByte(EllipseCurve EC,PublicKey PU,char m);
char DecrpytByte(CipherData CD,EllipseCurve EC,long long d);
Signature MakeSignature(char m,PublicKey PU,long long d,EllipseCurve EC);	/*ǩ��*/
bool VerifySignature(char m,Signature sig,PublicKey PU,EllipseCurve EC);	/*��֤ǩ��*/
long long Quadratic_Congruence(long long a,long long p);		/*�����ͬ�෽��x^2=a(mod p)*/
#endif


