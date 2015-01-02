#include "stdafx.h"
#include "EllipseCurve.h"
int main()
{
	printf("\t\t\t————椭圆曲线上的密码————\n\n");
	char OpNum=0;
	EllipseCurve EC;
	FILE *fin,*fout,*fout1;
	char FileName[256]={0};
	printf("请选择：1-输入曲线参数 2-随机生成曲线\n\n");
	do 
	{
		OpNum=_getch();
	} while (OpNum<'1'||OpNum>'2');
	if ('1'==OpNum)
	{
		while(1)
		{
			printf("\n有限域p=");
			scanf("%lld",&EC.p);
			if (!IsPrime(EC.p))
			{
				printf("\np不是素数，请重新输入！\n\n");
				continue;
			}
			printf("\n曲线参数a=");
			scanf("%lld",&EC.a);
			printf("\n曲线参数b=");
			scanf("%lld",&EC.b);
			if (0==(4*PowerMod(EC.a,3,EC.p)+27*EC.b*EC.b%EC.p)%EC.p)
			{
				printf("4a^3+27b^2=0，不满足要求，请重新输入！\n");
				continue;
			}
			break;
		}
	}
	else
	{
		printf("随机曲线生成中，请稍候……\n\n");
		srand((unsigned int)time(NULL));
		do 
		{
			EC.p=2*rand()+1;
		} while (!IsPrime(EC.p));
		do 
		{
			EC.a=rand()%(EC.p-1)+1;
			EC.b=rand()%(EC.p-1)+1;
		} while (0==(4*PowerMod(EC.a,3,EC.p)+27*EC.b*EC.b%EC.p)%EC.p);
		printf("\n曲线方程为有限域%lld上的曲线：y^2=x^3+%lldx+%lld\n\n",EC.p,EC.a,EC.b);
	}
	while(1)
	{
		printf("\n请输入操作号：\n\n");
		printf("1-重选曲线方程\n\n");
		printf("2-计算曲线上点的个数\n\n");
		printf("3-曲线上点的运算\n\n");
		printf("4-椭圆曲线上的Elgmal加密\n\n");
		printf("5-椭圆曲线上的Elgmal签名\n\n");
		printf("6-退出\n\n");
		do 
		{
			OpNum=_getch();
		} while (OpNum<'1'||OpNum>'7');
		switch(OpNum)
		{
		case '1':
			printf("请选择：1-输入曲线参数 2-随机生成曲线 3-返回\n\n");
			do 
			{
				OpNum=_getch();
			} while (OpNum<'1'||OpNum>'3');
			if ('3'==OpNum) break;
			if ('1'==OpNum)
			{
				while(1)
				{
					printf("\n有限域p=");
					scanf("%lld",&EC.p);
					if (!IsPrime(EC.p))
					{
						printf("p不是素数，请重新输入！\n\n");
						continue;
					}
					printf("\n曲线参数a=");
					scanf("%lld",&EC.a);
					printf("\n曲线参数b=");
					scanf("%lld",&EC.b);
					if (0==(4*PowerMod(EC.a,3,EC.p)+27*EC.b*EC.b%EC.p)%EC.p)
					{
						printf("4a^3+27b^2=0，不满足要求，请重新输入！\n");
						continue;
					}
					break;
				}
			}
			else
			{
				printf("随机曲线生成中，请稍候……\n\n");
				srand((unsigned long long)time(NULL));
				do 
				{
					EC.p=2*rand()+1;
				} while (!IsPrime(EC.p));
				do 
				{
					EC.a=rand()%(EC.p-1)+1;
					EC.b=rand()%(EC.p-1)+1;
				} while (0==(4*PowerMod(EC.a,3,EC.p)+27*EC.b*EC.b%EC.p)%EC.p);
				printf("\n曲线方程为有限域%lld上的曲线：y^2=x^3+%lldx+%lld\n\n",EC.p,EC.a,EC.b);
			}
			system("pause");
			break;
		case '2':
			printf("正在计算曲线上点的个数，请稍候……\n\n");
			long long PointCount,i;
			fout=fopen("point.txt","w");
			fout1=fopen("primepoint.txt","w");
			for(i=0,PointCount=0;i<EC.p;i++)
			{
				long long y_2=(PowerMod(i,3,EC.p)+EC.a*i+EC.b)%EC.p;	/*y^2=(x^3+a^x+b) mod p*/
				long long legendre=Legendre(y_2,EC.p);	/*计算勒让德符号(y^2/p)*/
				if (1==legendre||0==legendre)
				{
					PointCount+=(legendre+1);
				}
			}
			PointCount++;	/*加上无穷远点*/
			for (i=0;i<EC.p;i++)
			{
				long long y_2=(PowerMod(i,3,EC.p)+EC.a*i+EC.b)%EC.p;	/*y^2=(x^3+a^x+b) mod p*/
				long long legendre=Legendre(y_2,EC.p);	/*计算勒让德符号(y^2/p)*/
				if (1==legendre||0==legendre)
				{
					long long y=Quadratic_Congruence(y_2,EC.p);	/*解二次同余式*/
					fprintf(fout,"(%lld,%lld) ",i,y);
					if (0==y)
					{
						continue;
					}
					fprintf(fout,"(%lld,%lld) ",i,EC.p-y);
					for (long long j=3;j<=PointCount;j+=2)
					{
						Point temp;
						temp.x=i;
						temp.y=y;
						if (0==PointCount%j&&IsPrime(j)&&INFINITE==kPoint(j,temp,EC).x)
						{
							fprintf(fout1,"(%lld,%lld) (%lld,%lld) 阶为%lld\n",i,y,i,EC.p-y,j);
						}
					}
				}
			}
			printf("加上无穷远点，曲线上共有%lld个点，全部点已输出至point.txt文件中，阶为素数的点已输出至primepoint.txt文件中\n\n",PointCount);
			fclose(fout);
			fclose(fout1);
			system("pause");
			break;
		case '3':
			while (1)
			{
				printf("请选择:1-计算P+Q 2-计算2P 3-计算kP 4-返回\n\n");
				do 
				{
					OpNum=_getch();
				} while (OpNum<'1'||OpNum>'4');
				if ('4'==OpNum)
					break;
				switch(OpNum)
				{
				case '1':
					Point P,Q,R;
					printf("点P坐标：\nXp=");
					scanf("%lld",&P.x);
					printf("Yp=");
					scanf("%lld",&P.y);
					printf("\n点Q坐标：\nXq=");
					scanf("%lld",&Q.x);
					printf("Yq=");
					scanf("%lld",&Q.y);
					R=PointAdd(P,Q,EC);
					if (INFINITE==R.x&&INFINITE==R.y)
					{
						printf("\nP(%lld,%lld)+Q(%lld,%lld)=O\n\n",P.x,P.y,Q.x,Q.y);
					}
					else
					{
						printf("\nP(%lld,%lld)+Q(%lld,%lld)=R(%lld,%lld)\n\n",P.x,P.y,Q.x,Q.y,R.x,R.y);
					}
					break;
				case '2':
					printf("点P坐标：\nXp=");
					scanf("%lld",&P.x);
					printf("Yp=");
					scanf("%lld",&P.y);
					R=DoublePoint(P,EC);
					printf("\n2P(%lld,%lld)=R(%lld,%lld)\n\n",P.x,P.y,R.x,R.y);
					break;
				case '3':
					long long k;
					printf("请输入k=");
					scanf("%lld",&k);
					printf("\n点P坐标：\nXp=");
					scanf("%lld",&P.x);
					printf("Yp=");
					scanf("%lld",&P.y);
					R=kPoint(k,P,EC);
					if (INFINITE==R.x&&INFINITE==R.y)
					{
						printf("\n%lldP(%lld,%lld)=O\n\n",k,P.x,P.y);
					}
					else
					{
						printf("\n%lldP(%lld,%lld)=R(%lld,%lld)\n\n",k,P.x,P.y,R.x,R.y);
					}
					break;
				default:
					break;
				}
			}
			break;
		case '4':
			while(1)
			{
				printf("请选择:1-密钥生成 2-加密 3-解密 4-返回\n\n");
				do 
				{
					OpNum=_getch();
				} while (OpNum<'1'||OpNum>'4');
				if ('4'==OpNum)
				{
					break;
				}
				switch(OpNum)
				{
				case '1':
					while (EC.p<256)
					{
						printf("请重选曲线方程，令有限域的模数p大于256\n");
						printf("\n有限域p=");
						scanf("%lld",&EC.p);
						printf("\n曲线参数a=");
						scanf("%lld",&EC.a);
						printf("\n曲线参数b=");
						scanf("%lld",&EC.b);
					}
					PublicKey PU;
					Point temp;
					long long d;
					srand((unsigned long long)time(NULL));
					while(1)
					{
						printf("请输入选择的P点坐标：\nXp=");
						scanf("%lld",&PU.P.x);
						PU.P.x%=EC.p;
						printf("Yp=");
						scanf("%lld",&PU.P.y);
						PU.P.y%=EC.p;
						long long legendre=Legendre((PowerMod(PU.P.x,3,EC.p)+EC.a*PU.P.x+EC.b)%EC.p,EC.p);
						if (!(1==legendre||0==legendre))
						{
							printf("输入的点不在曲线上！请重试\n\n");
							continue;
						}
						break;
					}
					for (PU.n=1,temp=PU.P;!(INFINITE==temp.x&&INFINITE==temp.y);PU.n++)
					{
						temp=PointAdd(temp,PU.P,EC);
					}
					d=rand()%(PU.n-1)+1;
					PU.Q=kPoint(d,PU.P,EC);
					printf("生成的公钥为PU={E(Fq),P,n,Q}={E(F%lld),P(%lld,%lld),%lld,Q(%lld,%lld)\n\n",EC.p,PU.P.x,PU.P.y,PU.n,PU.Q.x,PU.Q.y);
					printf("私钥为d=%lld\n\n",d);
					break;
				case '2':
					srand((unsigned long long)time(NULL));
					while(1)
					{
						printf("请输入选择的P点坐标：\nXp=");
						scanf("%lld",&PU.P.x);
						printf("Yp=");
						scanf("%lld",&PU.P.y);
						long long legendre=Legendre((PowerMod(PU.P.x,3,EC.p)+EC.a*PU.P.x+EC.b)%EC.p,EC.p);
						if (!(1==legendre||0==legendre))
						{
							printf("输入的点不在曲线上！请重试\n\n");
							continue;
						}
						break;
					}
					printf("请输入点P的周期n=");
					scanf("%lld",&PU.n);
					printf("\n请输入Q点坐标：\nXq=");
					scanf("%lld",&PU.Q.x);
					printf("Yq=");
					scanf("%lld",&PU.Q.y);
					while(1)
					{
						printf("请输入明文所在文件的文件名：");
						scanf("%s",FileName);
						if (NULL==(fin=fopen(FileName,"r")))
						{
							printf("打开文件失败，请重试！\n\n");
							continue;
						}
						break;
					}
					while(1)
					{
						printf("请输入要输出的文件名：");
						scanf("%s",FileName);
						if (NULL==(fout=fopen(FileName,"w")))
						{
							printf("打开文件失败，请重试！\n\n");
							continue;
						}
						break;
					}
					while(1)
					{
						char m;
						CipherData CD;
						m=fgetc(fin);
						if (EOF==m)
							break;
						CD=EncrpytByte(EC,PU,m);
						fprintf(fout,"%lld,%lld,%lld\n",CD.x1,CD.y1,CD.c);
					}
					printf("加密后的结果已输出至%s文件中\n\n",FileName);
					fclose(fin);
					fclose(fout);
					break;
				case '3':
					char FileName[256];
					FILE *fin;
					printf("请输入私钥d=");
					scanf("%lld",&d);
					printf("\n请输入密文所在文件名：");
					fflush(stdin);
					scanf("%s",FileName);
					while(NULL==(fin=fopen(FileName,"r")))
					{
						printf("打开文件失败，请重试！\n\n");
						printf("请输入密文所在文件名：");
						fflush(stdin);
						scanf("%s",FileName);
					}
					fout=fopen("plaintext.txt","w");

					CipherData CD;
					while(fscanf(fin,"%lld,%lld,%lld",&CD.x1,&CD.y1,&CD.c)>0)
					{
						fprintf(fout,"%c",DecrpytByte(CD,EC,d));
					}
					printf("\n\n");
					fclose(fin);
					fclose(fout);
					printf("解密结果已输出至plaintext.txt文件中\n\n");
					break;
				default:
					break;
				}
			}
			break;
		case '5':
			while(1)
			{
				printf("请选择:1-生成密钥 2-生成签名 3-验证签名 4-返回\n\n");
				do 
				{
					OpNum=_getch();
				} while (OpNum<'1'||OpNum>'4');
				if ('4'==OpNum)
				{
					break;
				}
				switch(OpNum)
				{
				case '1':
					PublicKey PU;
					Point temp;
					long long d;
					srand((unsigned long long)time(NULL));
					while(1)
					{
						printf("请输入选择的P点坐标：\nXp=");
						scanf("%lld",&PU.P.x);
						PU.P.x%=EC.p;
						printf("Yp=");
						scanf("%lld",&PU.P.y);
						PU.P.y%=EC.p;
						long long legendre=Legendre((PowerMod(PU.P.x,3,EC.p)+EC.a*PU.P.x+EC.b)%EC.p,EC.p);
						if (!(1==legendre||0==legendre))
						{
							printf("输入的点不在曲线上！请重试\n\n");
							continue;
						}
						for (PU.n=1,temp=PU.P;!(INFINITE==temp.x&&INFINITE==temp.y);PU.n++)
						{
							temp=PointAdd(temp,PU.P,EC);
						}
						if (!IsPrime(PU.n))
						{
							printf("点P的阶不是素数，请重新输入！\n\n");
							continue;
						}
						break;
					}
					d=rand()%(PU.n-1)+1;
					PU.Q=kPoint(d,PU.P,EC);
					printf("生成的公钥为PU={E(Fq),P,n,Q}={E(F%lld),P(%lld,%lld),%lld,Q(%lld,%lld)\n\n",EC.p,PU.P.x,PU.P.y,PU.n,PU.Q.x,PU.Q.y);
					printf("私钥为d=%lld\n\n",d);
					break;
				case '2':
					Signature sig;
					long long k;
					char h1;
					srand((unsigned long long)time(NULL));
					while(1)
					{
						printf("请输入选择的P点坐标：\nXp=");
						scanf("%lld",&PU.P.x);
						printf("Yp=");
						scanf("%lld",&PU.P.y);
						long long legendre=Legendre((PowerMod(PU.P.x,3,EC.p)+EC.a*PU.P.x+EC.b)%EC.p,EC.p);
						if (!(1==legendre||0==legendre))
						{
							printf("输入的点不在曲线上！请重试\n\n");
							continue;
						}
						printf("请输入点P的周期n=");
						scanf("%lld",&PU.n);
						if (!IsPrime(PU.n))
						{
							printf("P的周期不是素数，请重试\n\n");
							continue;
						}
						break;
					}
					printf("请输入私钥d=");
					scanf("%lld",&d);
					printf("请输入要进行签名的消息：\n");
					fflush(stdin);
					h1=0;
					while(1)
					{
						char m;
						m=getchar();
						if ('\n'==m)
							break;
						h1=h1^m;
					}
					sig=MakeSignature(h1,PU,d,EC);
					printf("生成的签名为(%lld,%lld)\n\n",sig.r,sig.s);
					break;
				case '3':
					while(1)
					{
						printf("请输入选择的P点坐标：\nXp=");
						scanf("%lld",&PU.P.x);
						printf("Yp=");
						scanf("%lld",&PU.P.y);
						long long legendre=Legendre((PowerMod(PU.P.x,3,EC.p)+EC.a*PU.P.x+EC.b)%EC.p,EC.p);
						if (!(1==legendre||0==legendre))
						{
							printf("输入的点不在曲线上！请重试\n\n");
							continue;
						}
						break;
					}
					printf("请输入点P的周期n=");
					scanf("%lld",&PU.n);
					printf("\n请输入Q点坐标：\nXq=");
					scanf("%lld",&PU.Q.x);
					printf("Yq=");
					scanf("%lld",&PU.Q.y);
					printf("请输入签名的消息：\n");
					fflush(stdin);
					h1=0;
					while(1)
					{
						char m;
						m=getchar();
						if ('\n'==m)	break;
						h1=h1^m;
					}
					printf("请输入签名：\n");
					printf("r=");
					scanf("%lld",&sig.r);
					printf("s=");
					scanf("%lld",&sig.s);
					VerifySignature(h1,sig,PU,EC)?printf("经验证，签名有效。\n\n"):printf("经验证，签名无效。\n\n");
					break;
				default:
					break;
				}
			}
			break;
		case '6':
			exit(0);
			break;
		default:
			break;
		}
	}
	return 0;
}

bool IsPrime(unsigned long long Num)		/*Miller-Rabin素性测试*/
{
	if (Num<=1||(Num>2&&0==Num%2))		/*小于等于1的数和大于2的偶数都不是素数*/
	{
		return false;
	}
	if (2==Num||3==Num)		/*2和3是素数，后面的测试要找随机数EC.a满足1<EC.a<n-1，2和3不可以*/
	{
		return true;
	}
	long long i,j,k=0;
	unsigned long long q=Num-1,a;
	srand((unsigned int)time(NULL));
	while (0==q%2)
	{
		k++;
		q/=2;
	}
	for (i=0;i<TEST_TIMES;i++)
	{
		long long t=1;
		a=rand()%(Num-3)+2;			/*随机数EC.a，1<a<n-1*/
		if (1==PowerMod(a,q,Num))	
		{
			continue;		/*本次测试结果不确定，继续下次测试*/
		}
		for (j=0;j<=k-1;j++)
		{
			if (Num-1==PowerMod(a,t*q,Num))
			{
				break;
			}
			t*=2;
		}
		if (j!=k)
		{
			continue;	/*本次测试结果不确定，继续下次测试*/
		}
		return false;	/*素数的两条性质都不满足，返回合数*/
	}
	return true;
}

unsigned long long PowerMod(unsigned long long BaseNum,unsigned long long Exponent,unsigned long long Modulus)	/*模幂运算*/
{
	unsigned long long Result=1;
	while (Exponent>0)
	{
		if (Exponent&1)
		{
			Result=(Result*BaseNum)%Modulus;
		}
		BaseNum=(BaseNum*BaseNum)%Modulus;
		Exponent>>=1;
	}
	return Result;
}

long long Legendre(unsigned long long n,unsigned long long p)	/*计算勒让德符号(n/p)*/
{
	return (long long)PowerMod(n,(p-1)/2,p);
}

long long Inverse(long long Num,long long Modulus)	/*求以Modulus为模的Num的逆*/
{
	long long t,InverseNum;
	Extend_Euclid(Modulus,Num,&t,&InverseNum);
	InverseNum=InverseNum>0?InverseNum:InverseNum+Modulus;
	return InverseNum;
}

long long Extend_Euclid(long long a,long long b,long long* x,long long* y)//扩展欧几里德算法
{
	if(0==b)
	{
		*x=1;
		*y=0;
		return a;
	}
	long long r;
	long long x_i_2=1,y_i_2=0,x_i_1=0,y_i_1=1,x_i=0,y_i=1;
	while(r=a%b)
	{
		x_i=x_i_2-a/b*x_i_1;
		y_i=y_i_2-a/b*y_i_1;
		x_i_2=x_i_1;
		y_i_2=y_i_1;
		x_i_1=x_i;
		y_i_1=y_i;
		a=b;
		b=r;
	}
	*x=x_i;
	*y=y_i;
	return b;
}

Point PointAdd(Point P,Point Q,EllipseCurve EC)		/*计算P+Q=R*/
{
	Point R;
	long long delty,deltx,alpha;
	if ((INFINITE==P.x&&INFINITE==P.y)||(INFINITE==Q.x&&INFINITE==Q.y))
	{
		return INFINITE==P.x?Q:P;
	}
	if (P.x==Q.x)
	{
		if (0==(P.y+Q.y)%EC.p)
		{
			R.x=INFINITE;
			R.y=INFINITE;
			return R;
		}
		else if (P.y==Q.y)
		{
			return DoublePoint(P,EC);
		}
	}
	delty=Q.y-P.y>=0?Q.y-P.y:Q.y-P.y+EC.p;
	deltx=Q.x-P.x>=0?Q.x-P.x:Q.x-P.x+EC.p;
	alpha=(delty*Inverse(deltx,EC.p))%EC.p;
	R.x=(alpha*alpha-P.x-Q.x)%EC.p;
	R.x=R.x>=0?R.x:R.x+EC.p;
	R.y=(alpha*(P.x-R.x)-P.y)%EC.p;
	R.y=R.y>=0?R.y:R.y+EC.p;
	return R;
}

Point DoublePoint(Point P,EllipseCurve EC)
{
	Point R;
	long long alpha;
	R.x=R.y=INFINITE;
	if (0==P.y)
	{
		return R;
	}
	alpha=((3*P.x*P.x%EC.p+EC.a)*Inverse(2*P.y,EC.p))%EC.p;
	R.x=(alpha*alpha-2*P.x)%EC.p;
	R.x=R.x>=0?R.x:R.x+EC.p;
	R.y=(alpha*(P.x-R.x)-P.y)%EC.p;
	R.y=R.y>=0?R.y:R.y+EC.p;
	return R;
}

Point kPoint(long long k,Point P,EllipseCurve EC)		/*计算kP=R*/
{
	Point R;
	R.x=R.y=INFINITE;
	if (0==P.y)
	{
		return R;
	}
	while(k>0)
	{
		if (k&1)
		{
			R=PointAdd(R,P,EC);
		}
		P=DoublePoint(P,EC);
		k>>=1;
	}
	return R;
}

CipherData EncrpytByte(EllipseCurve EC,PublicKey PU,char m)
{
	CipherData CD;
	long long k;
	Point kP,kQ;
	do 
	{
		k=rand()%(PU.n-1)+1;
		kP=kPoint(k,PU.P,EC);
		kQ=kPoint(k,PU.Q,EC);
	} while (0==kQ.x);
	CD.x1=kP.x;
	CD.y1=kP.y;
	CD.c=(m*kQ.x)%EC.p;
	return CD;
}

char DecrpytByte(CipherData CD,EllipseCurve EC,long long d)
{
	char m;
	Point pt1,pt2;
	pt1.x=CD.x1;
	pt1.y=CD.y1;
	pt2=kPoint(d,pt1,EC);
	m=(CD.c*Inverse(pt2.x,EC.p))%EC.p;
	m=m>=0?m:m+EC.p;
	return m;
}

Signature MakeSignature(char m,PublicKey PU,long long d,EllipseCurve EC)
{
	long long k;
	Signature sig;
	do 
	{
		k=rand()%(PU.n-1)+1;
		sig.r=kPoint(k,PU.P,EC).x%PU.n;
		sig.r=sig.r>=0?sig.r:PU.n+sig.r;
		sig.s=(m+sig.r*d)*Inverse(k,PU.n)%PU.n;
		sig.s=sig.s>=0?sig.s:PU.n+sig.s;
	} while (0==sig.r||0==sig.s);
	return sig;
}

bool VerifySignature(char m,Signature sig,PublicKey PU,EllipseCurve EC)
{
	long long u,v,r;
	u=(m*Inverse(sig.s,PU.n))%PU.n;
	v=(sig.r*Inverse(sig.s,PU.n))%PU.n;
	r=PointAdd(kPoint(u,PU.P,EC),kPoint(v,PU.Q,EC),EC).x%PU.n;
	return r==sig.r;
}
long long Quadratic_Congruence(long long a,long long p)		/*解二次同余方程x^2=a(mod p)，其中p是奇素数*/
{
	long long n=p/2;	/*奇素数p=2*n+1*/
	long long b=n%2?(n+1)/2:-n/2;
	if (0==(a-b)%p)
	{
		return n;
	}
	else
	{
		long long unit[3]={0};
		long long i,aSUBb=a-b,m;
		bool flag=0;
		for (i=0;i<10;i++)
		{
			long long temp=(p*i+aSUBb)%10;
			if (0==temp)
			{
				unit[0]=i;
			}
			else if (2==temp)
			{
				unit[1]=i;
			}
			else if (6==temp)
			{
				unit[2]=i;
			}
		}
		for (i=0;!flag;i++)
		{
			for (long long j=0;j<3;j++)
			{
				long long temp=p*(10*i+unit[j])+aSUBb;
				m=(long long)sqrt((float)temp);
				if (m*(m+1)==temp)
				{
					flag=1;
					break;
				}
			}
		}
		return m>n?(m-n)%p:(n-m)%p;
	}
}

