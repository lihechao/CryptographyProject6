#ifndef ELLIPSECURVE_H
#define ELLIPSECURVE_H
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#define TEST_TIMES	5		/*素性测试的测试次数*/
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
	long long n;		/*点P的周期n*/
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
unsigned long long PowerMod(unsigned long long BaseNum,unsigned long long Exponent,unsigned long long Modulus);	/*模幂运算*/
bool IsPrime(unsigned long long Num);		/*Miller-Rabin素性测试*/
long long Legendre(unsigned long long n,unsigned long long p);	/*计算勒让德符号(n/p)*/
long long Inverse(long long Num,long long Modulus);	/*求以Modulus为模的Num的逆*/
long long Extend_Euclid(long long a,long long b,long long* x,long long* y);//扩展欧几里德算法
Point PointAdd(Point P,Point Q,EllipseCurve EC);		/*计算P+Q=R*/
Point DoublePoint(Point P,EllipseCurve EC);		/*计算2P=R*/
Point kPoint(long long k,Point P,EllipseCurve EC);		/*计算kP=R*/
CipherData EncrpytByte(EllipseCurve EC,PublicKey PU,char m);
char DecrpytByte(CipherData CD,EllipseCurve EC,long long d);
Signature MakeSignature(char m,PublicKey PU,long long d,EllipseCurve EC);	/*签名*/
bool VerifySignature(char m,Signature sig,PublicKey PU,EllipseCurve EC);	/*验证签名*/
long long Quadratic_Congruence(long long a,long long p);		/*解二次同余方程x^2=a(mod p)*/
#endif


