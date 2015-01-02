#include "stdafx.h"
#include "EllipseCurve.h"
int main()
{
	printf("\t\t\t����������Բ�����ϵ����롪������\n\n");
	char OpNum=0;
	EllipseCurve EC;
	FILE *fin,*fout,*fout1;
	char FileName[256]={0};
	printf("��ѡ��1-�������߲��� 2-�����������\n\n");
	do 
	{
		OpNum=_getch();
	} while (OpNum<'1'||OpNum>'2');
	if ('1'==OpNum)
	{
		while(1)
		{
			printf("\n������p=");
			scanf("%lld",&EC.p);
			if (!IsPrime(EC.p))
			{
				printf("\np�������������������룡\n\n");
				continue;
			}
			printf("\n���߲���a=");
			scanf("%lld",&EC.a);
			printf("\n���߲���b=");
			scanf("%lld",&EC.b);
			if (0==(4*PowerMod(EC.a,3,EC.p)+27*EC.b*EC.b%EC.p)%EC.p)
			{
				printf("4a^3+27b^2=0��������Ҫ�����������룡\n");
				continue;
			}
			break;
		}
	}
	else
	{
		printf("������������У����Ժ򡭡�\n\n");
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
		printf("\n���߷���Ϊ������%lld�ϵ����ߣ�y^2=x^3+%lldx+%lld\n\n",EC.p,EC.a,EC.b);
	}
	while(1)
	{
		printf("\n����������ţ�\n\n");
		printf("1-��ѡ���߷���\n\n");
		printf("2-���������ϵ�ĸ���\n\n");
		printf("3-�����ϵ������\n\n");
		printf("4-��Բ�����ϵ�Elgmal����\n\n");
		printf("5-��Բ�����ϵ�Elgmalǩ��\n\n");
		printf("6-�˳�\n\n");
		do 
		{
			OpNum=_getch();
		} while (OpNum<'1'||OpNum>'7');
		switch(OpNum)
		{
		case '1':
			printf("��ѡ��1-�������߲��� 2-����������� 3-����\n\n");
			do 
			{
				OpNum=_getch();
			} while (OpNum<'1'||OpNum>'3');
			if ('3'==OpNum) break;
			if ('1'==OpNum)
			{
				while(1)
				{
					printf("\n������p=");
					scanf("%lld",&EC.p);
					if (!IsPrime(EC.p))
					{
						printf("p�������������������룡\n\n");
						continue;
					}
					printf("\n���߲���a=");
					scanf("%lld",&EC.a);
					printf("\n���߲���b=");
					scanf("%lld",&EC.b);
					if (0==(4*PowerMod(EC.a,3,EC.p)+27*EC.b*EC.b%EC.p)%EC.p)
					{
						printf("4a^3+27b^2=0��������Ҫ�����������룡\n");
						continue;
					}
					break;
				}
			}
			else
			{
				printf("������������У����Ժ򡭡�\n\n");
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
				printf("\n���߷���Ϊ������%lld�ϵ����ߣ�y^2=x^3+%lldx+%lld\n\n",EC.p,EC.a,EC.b);
			}
			system("pause");
			break;
		case '2':
			printf("���ڼ��������ϵ�ĸ��������Ժ򡭡�\n\n");
			long long PointCount,i;
			fout=fopen("point.txt","w");
			fout1=fopen("primepoint.txt","w");
			for(i=0,PointCount=0;i<EC.p;i++)
			{
				long long y_2=(PowerMod(i,3,EC.p)+EC.a*i+EC.b)%EC.p;	/*y^2=(x^3+a^x+b) mod p*/
				long long legendre=Legendre(y_2,EC.p);	/*�������õ·���(y^2/p)*/
				if (1==legendre||0==legendre)
				{
					PointCount+=(legendre+1);
				}
			}
			PointCount++;	/*��������Զ��*/
			for (i=0;i<EC.p;i++)
			{
				long long y_2=(PowerMod(i,3,EC.p)+EC.a*i+EC.b)%EC.p;	/*y^2=(x^3+a^x+b) mod p*/
				long long legendre=Legendre(y_2,EC.p);	/*�������õ·���(y^2/p)*/
				if (1==legendre||0==legendre)
				{
					long long y=Quadratic_Congruence(y_2,EC.p);	/*�����ͬ��ʽ*/
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
							fprintf(fout1,"(%lld,%lld) (%lld,%lld) ��Ϊ%lld\n",i,y,i,EC.p-y,j);
						}
					}
				}
			}
			printf("��������Զ�㣬�����Ϲ���%lld���㣬ȫ�����������point.txt�ļ��У���Ϊ�����ĵ��������primepoint.txt�ļ���\n\n",PointCount);
			fclose(fout);
			fclose(fout1);
			system("pause");
			break;
		case '3':
			while (1)
			{
				printf("��ѡ��:1-����P+Q 2-����2P 3-����kP 4-����\n\n");
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
					printf("��P���꣺\nXp=");
					scanf("%lld",&P.x);
					printf("Yp=");
					scanf("%lld",&P.y);
					printf("\n��Q���꣺\nXq=");
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
					printf("��P���꣺\nXp=");
					scanf("%lld",&P.x);
					printf("Yp=");
					scanf("%lld",&P.y);
					R=DoublePoint(P,EC);
					printf("\n2P(%lld,%lld)=R(%lld,%lld)\n\n",P.x,P.y,R.x,R.y);
					break;
				case '3':
					long long k;
					printf("������k=");
					scanf("%lld",&k);
					printf("\n��P���꣺\nXp=");
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
				printf("��ѡ��:1-��Կ���� 2-���� 3-���� 4-����\n\n");
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
						printf("����ѡ���߷��̣����������ģ��p����256\n");
						printf("\n������p=");
						scanf("%lld",&EC.p);
						printf("\n���߲���a=");
						scanf("%lld",&EC.a);
						printf("\n���߲���b=");
						scanf("%lld",&EC.b);
					}
					PublicKey PU;
					Point temp;
					long long d;
					srand((unsigned long long)time(NULL));
					while(1)
					{
						printf("������ѡ���P�����꣺\nXp=");
						scanf("%lld",&PU.P.x);
						PU.P.x%=EC.p;
						printf("Yp=");
						scanf("%lld",&PU.P.y);
						PU.P.y%=EC.p;
						long long legendre=Legendre((PowerMod(PU.P.x,3,EC.p)+EC.a*PU.P.x+EC.b)%EC.p,EC.p);
						if (!(1==legendre||0==legendre))
						{
							printf("����ĵ㲻�������ϣ�������\n\n");
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
					printf("���ɵĹ�ԿΪPU={E(Fq),P,n,Q}={E(F%lld),P(%lld,%lld),%lld,Q(%lld,%lld)\n\n",EC.p,PU.P.x,PU.P.y,PU.n,PU.Q.x,PU.Q.y);
					printf("˽ԿΪd=%lld\n\n",d);
					break;
				case '2':
					srand((unsigned long long)time(NULL));
					while(1)
					{
						printf("������ѡ���P�����꣺\nXp=");
						scanf("%lld",&PU.P.x);
						printf("Yp=");
						scanf("%lld",&PU.P.y);
						long long legendre=Legendre((PowerMod(PU.P.x,3,EC.p)+EC.a*PU.P.x+EC.b)%EC.p,EC.p);
						if (!(1==legendre||0==legendre))
						{
							printf("����ĵ㲻�������ϣ�������\n\n");
							continue;
						}
						break;
					}
					printf("�������P������n=");
					scanf("%lld",&PU.n);
					printf("\n������Q�����꣺\nXq=");
					scanf("%lld",&PU.Q.x);
					printf("Yq=");
					scanf("%lld",&PU.Q.y);
					while(1)
					{
						printf("���������������ļ����ļ�����");
						scanf("%s",FileName);
						if (NULL==(fin=fopen(FileName,"r")))
						{
							printf("���ļ�ʧ�ܣ������ԣ�\n\n");
							continue;
						}
						break;
					}
					while(1)
					{
						printf("������Ҫ������ļ�����");
						scanf("%s",FileName);
						if (NULL==(fout=fopen(FileName,"w")))
						{
							printf("���ļ�ʧ�ܣ������ԣ�\n\n");
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
					printf("���ܺ�Ľ���������%s�ļ���\n\n",FileName);
					fclose(fin);
					fclose(fout);
					break;
				case '3':
					char FileName[256];
					FILE *fin;
					printf("������˽Կd=");
					scanf("%lld",&d);
					printf("\n���������������ļ�����");
					fflush(stdin);
					scanf("%s",FileName);
					while(NULL==(fin=fopen(FileName,"r")))
					{
						printf("���ļ�ʧ�ܣ������ԣ�\n\n");
						printf("���������������ļ�����");
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
					printf("���ܽ���������plaintext.txt�ļ���\n\n");
					break;
				default:
					break;
				}
			}
			break;
		case '5':
			while(1)
			{
				printf("��ѡ��:1-������Կ 2-����ǩ�� 3-��֤ǩ�� 4-����\n\n");
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
						printf("������ѡ���P�����꣺\nXp=");
						scanf("%lld",&PU.P.x);
						PU.P.x%=EC.p;
						printf("Yp=");
						scanf("%lld",&PU.P.y);
						PU.P.y%=EC.p;
						long long legendre=Legendre((PowerMod(PU.P.x,3,EC.p)+EC.a*PU.P.x+EC.b)%EC.p,EC.p);
						if (!(1==legendre||0==legendre))
						{
							printf("����ĵ㲻�������ϣ�������\n\n");
							continue;
						}
						for (PU.n=1,temp=PU.P;!(INFINITE==temp.x&&INFINITE==temp.y);PU.n++)
						{
							temp=PointAdd(temp,PU.P,EC);
						}
						if (!IsPrime(PU.n))
						{
							printf("��P�Ľײ������������������룡\n\n");
							continue;
						}
						break;
					}
					d=rand()%(PU.n-1)+1;
					PU.Q=kPoint(d,PU.P,EC);
					printf("���ɵĹ�ԿΪPU={E(Fq),P,n,Q}={E(F%lld),P(%lld,%lld),%lld,Q(%lld,%lld)\n\n",EC.p,PU.P.x,PU.P.y,PU.n,PU.Q.x,PU.Q.y);
					printf("˽ԿΪd=%lld\n\n",d);
					break;
				case '2':
					Signature sig;
					long long k;
					char h1;
					srand((unsigned long long)time(NULL));
					while(1)
					{
						printf("������ѡ���P�����꣺\nXp=");
						scanf("%lld",&PU.P.x);
						printf("Yp=");
						scanf("%lld",&PU.P.y);
						long long legendre=Legendre((PowerMod(PU.P.x,3,EC.p)+EC.a*PU.P.x+EC.b)%EC.p,EC.p);
						if (!(1==legendre||0==legendre))
						{
							printf("����ĵ㲻�������ϣ�������\n\n");
							continue;
						}
						printf("�������P������n=");
						scanf("%lld",&PU.n);
						if (!IsPrime(PU.n))
						{
							printf("P�����ڲ���������������\n\n");
							continue;
						}
						break;
					}
					printf("������˽Կd=");
					scanf("%lld",&d);
					printf("������Ҫ����ǩ������Ϣ��\n");
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
					printf("���ɵ�ǩ��Ϊ(%lld,%lld)\n\n",sig.r,sig.s);
					break;
				case '3':
					while(1)
					{
						printf("������ѡ���P�����꣺\nXp=");
						scanf("%lld",&PU.P.x);
						printf("Yp=");
						scanf("%lld",&PU.P.y);
						long long legendre=Legendre((PowerMod(PU.P.x,3,EC.p)+EC.a*PU.P.x+EC.b)%EC.p,EC.p);
						if (!(1==legendre||0==legendre))
						{
							printf("����ĵ㲻�������ϣ�������\n\n");
							continue;
						}
						break;
					}
					printf("�������P������n=");
					scanf("%lld",&PU.n);
					printf("\n������Q�����꣺\nXq=");
					scanf("%lld",&PU.Q.x);
					printf("Yq=");
					scanf("%lld",&PU.Q.y);
					printf("������ǩ������Ϣ��\n");
					fflush(stdin);
					h1=0;
					while(1)
					{
						char m;
						m=getchar();
						if ('\n'==m)	break;
						h1=h1^m;
					}
					printf("������ǩ����\n");
					printf("r=");
					scanf("%lld",&sig.r);
					printf("s=");
					scanf("%lld",&sig.s);
					VerifySignature(h1,sig,PU,EC)?printf("����֤��ǩ����Ч��\n\n"):printf("����֤��ǩ����Ч��\n\n");
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

bool IsPrime(unsigned long long Num)		/*Miller-Rabin���Բ���*/
{
	if (Num<=1||(Num>2&&0==Num%2))		/*С�ڵ���1�����ʹ���2��ż������������*/
	{
		return false;
	}
	if (2==Num||3==Num)		/*2��3������������Ĳ���Ҫ�������EC.a����1<EC.a<n-1��2��3������*/
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
		a=rand()%(Num-3)+2;			/*�����EC.a��1<a<n-1*/
		if (1==PowerMod(a,q,Num))	
		{
			continue;		/*���β��Խ����ȷ���������´β���*/
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
			continue;	/*���β��Խ����ȷ���������´β���*/
		}
		return false;	/*�������������ʶ������㣬���غ���*/
	}
	return true;
}

unsigned long long PowerMod(unsigned long long BaseNum,unsigned long long Exponent,unsigned long long Modulus)	/*ģ������*/
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

long long Legendre(unsigned long long n,unsigned long long p)	/*�������õ·���(n/p)*/
{
	return (long long)PowerMod(n,(p-1)/2,p);
}

long long Inverse(long long Num,long long Modulus)	/*����ModulusΪģ��Num����*/
{
	long long t,InverseNum;
	Extend_Euclid(Modulus,Num,&t,&InverseNum);
	InverseNum=InverseNum>0?InverseNum:InverseNum+Modulus;
	return InverseNum;
}

long long Extend_Euclid(long long a,long long b,long long* x,long long* y)//��չŷ������㷨
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

Point PointAdd(Point P,Point Q,EllipseCurve EC)		/*����P+Q=R*/
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

Point kPoint(long long k,Point P,EllipseCurve EC)		/*����kP=R*/
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
long long Quadratic_Congruence(long long a,long long p)		/*�����ͬ�෽��x^2=a(mod p)������p��������*/
{
	long long n=p/2;	/*������p=2*n+1*/
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

