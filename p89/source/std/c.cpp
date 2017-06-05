#include<cstdio>
#include<cstring>
#define MAXL 5100

struct {int l,s[MAXL];}Y,M,R,Ans,Div;

struct {int l,s[16000];}Str;

long long N,Res,X;

int Len,L;

char Chr;

int GetL(long long a)
{	int i;
	for(i=0;a;i++)a/=10;
	for(Res=1;Res<=N;Res*=10);
	Div.l=1;
	Div.s[0]=Res/N;
	Res%=N;
	if(!Res)
	{	Div.s[Div.l-1]--;
		Res=N;
	}
	return i;
}

void reads()
{	for(Y.l=0;(Chr=getchar())<'0';);
	for(Y.s[Y.l++]=Chr-'0';(Chr=getchar())>='0';Y.s[Y.l++]=Chr-'0');
	int i,j;
	for(i=0;2*i<Y.l;i++)
	{	j=Y.s[i];
		Y.s[i]=Y.s[Y.l-i-1];
		Y.s[Y.l-i-1]=j;
	}
}

bool Comp()
{	if(R.l!=M.l)return R.l<M.l;
	for(int i=R.l-1;i>=0;i--)
		if(R.s[i]!=M.s[i])
			return R.s[i]<M.s[i];
	return 1;
}

void Minus()
{	for(int i=0;i<R.l;i++)
	{	R.s[i]-=M.s[i];
		for(;R.s[i]<0;R.s[i+1]--)R.s[i]+=10;
	}
	for(;R.l&&!R.s[R.l-1];R.l--);
}

	void GetDiv()
{	if(Res==N)
	{	Div.s[Div.l-1]++;
		Res=0;
	}
	Div.s[Div.l++]=Res*10/N;
	Res=(Res*10)%N;
	if(!Res)
	{	Div.s[Div.l-1]--;
		Res=N;
	}
}

void Divide()
{	for(int i=R.l-1;i>0;i--)
	{	R.s[i-1]+=(R.s[i]%L)*10;
		R.s[i]/=L;
	}
	Res=R.s[0]%L;
	R.s[0]/=L;
	if(Res)R.s[0]++;
	else Res=L;
}

void Mult()
{	int i;
	for(i=0;i<M.l;i++)M.s[i]*=L;
	for(i=0;i<M.l||M.s[i];i++)
		if(M.s[i]>=10)
		{	M.s[i+1]+=M.s[i]/10;
			M.s[i]%=10;
		}
	M.l=i;
}

bool Get_10_To_Div()
{	int i;
	L++;
	memset(M.s,0,sizeof M.s);
	M.l=Div.l;
	M.s[M.l-1]=1;
	for(i=0;i<M.l;i++)M.s[i]=Div.s[Div.l-i-1]-M.s[i];
	M.s[0]++;
	for(i=0;i<M.l;i++)
	{	for(;M.s[i]<0;M.s[i+1]--)M.s[i]+=10;
		if(M.s[i]>=10)
		{	M.s[i+1]++;
			M.s[i]-=10;
		}
	}
	if(M.s[M.l])M.l++;
	for(;M.l&&!M.s[M.l-1];M.l--);
	Mult();
	if(Comp())
	{	Divide();
		memset(Ans.s,0,sizeof Ans.s);
		Ans.l=Div.l;
		Ans.s[Ans.l-1]=1;
		Ans.s[0]--;
		for(i=0;i<Ans.l;i++)Ans.s[i]=Ans.s[i]+R.s[i];
		for(i=0;i<Ans.l||Ans.s[i];i++)
		{	if(Ans.s[i]<0)
			{	Ans.s[i+1]--;
				Ans.s[i]+=10;
			}
			if(Ans.s[i]>=10)
			{	Ans.s[i+1]+=Ans.s[i]/10;
				Ans.s[i]%=10;
			}
		}
		Ans.l=i;
		return 0;
	}
	Minus();
	return 1;
}

bool Get_Div_To_10()
{	int i;
	L++;
	memset(M.s,0,sizeof M.s);
	M.l=Div.l+1;
	M.s[M.l-1]=1;
	for(i=0;i<M.l;i++)M.s[i]=M.s[i]-(Div.l>=i+1?Div.s[Div.l-i-1]:0);
	M.s[0]--;
	for(i=0;i<M.l;i++)
	{	for(;M.s[i]<0;M.s[i+1]--)M.s[i]+=10;
		if(M.s[i]>=10)
		{	M.s[i+1]++;
			M.s[i]-=10;
		}
	}
	if(M.s[M.l])M.l++;
	for(;M.l&&!M.s[M.l-1];M.l--);
	Mult();
	if(Comp())
	{	Divide();
		memset(Ans.s,0,sizeof Ans.s);
		Ans.l=Div.l;
		for(i=0;i<Ans.l;i++)Ans.s[i]=Div.s[Div.l-i-1];
		for(i=0;i<Ans.l;i++)Ans.s[i]=Ans.s[i]+R.s[i];
		for(i=0;i<Ans.l||Ans.s[i];i++)
			if(Ans.s[i]>=10)
			{	Ans.s[i+1]+=Ans.s[i]/10;
				Ans.s[i]%=10;
			}
		Ans.l=i;
		return 0;
	}
	Minus();
	return 1;
}

void Write(char a){if(Str.l-Res+1<Len)Str.s[Str.l++]=a;}

void Out()
{	long long j(N);
	int i;
	for(i=0;j;i++,j/=10)M.s[i]=j%10;
	M.l=i;
	for(i=0;i<M.l;i++)Write(M.s[M.l-i-1]+'0');
	Write('*');
	for(i=0;i<Ans.l;i++)Write(Ans.s[Ans.l-i-1]+'0');
	Write('=');
	memset(M.s,0,sizeof M.s);
	for(i=0;i<Ans.l;i++)M.s[i]=Ans.s[i]*N;
	M.l=Ans.l;
	for(i=0;i<M.l||M.s[i];i++)
		if(M.s[i]>=10)
		{	M.s[i+1]+=M.s[i]/10;
			M.s[i]%=10;
		}
	M.l=i;
	for(i=0;i<M.l;i++)Write(M.s[M.l-i-1]+'0');
	Write(' ');
	Ans.s[0]++;
	for(i=0;i<Ans.l;i++)
		if(Ans.s[i]>=10)
		{	Ans.s[i+1]+=Ans.s[i]/10;
			Ans.s[i]%=10;
		}
		else break;
	if(Ans.s[Ans.l])Ans.l++;
}

int main()
{
	scanf("%I64d",&X);
	reads();
	scanf("%d",&Len);
	N=2;
	for(N=X;N<X+5;N++)
{	L=2*GetL(N)+3;
	R.l=Y.l;
	memcpy(R.s,Y.s,sizeof Y.s);
	for(;Get_10_To_Div()&&Get_Div_To_10();GetDiv());
	Str.l=0;
	for(;Str.l-Res+1<Len;)Out();
	for(int i=Res-1;i<Res-1+Len;i++)putchar(Str.s[i]);
	printf("\n");
}
return 0;
}
