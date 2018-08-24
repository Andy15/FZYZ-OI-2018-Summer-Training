#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<ctime>
#include<cstdlib>
#include<cassert>
namespace io
{
	int F()
	{
		int n=0,F=1;
		char ch;
		while((ch=getchar())!='-'&&(ch<'0'||ch>'9'));
		ch=='-'?F=0:n=ch-'0';
		while((ch=getchar())>='0'&&ch<='9')n=(n<<1)+(n<<3)+ch-'0';
		return F?n:-n;
	}
	long long G()
	{
		long long n=0,F=1;
		char ch;
		while((ch=getchar())!='-'&&(ch<'0'||ch>'9'));
		ch=='-'?F=0:n=ch-'0';
		while((ch=getchar())>='0'&&ch<='9')n=(n<<1)+(n<<3)+ch-'0';
		return F?n:-n;
	}
}
namespace Code
{
	int A[1111],B[1111];
	int a[1111],b[1111];
	int n; 
	int now; 
}
void Inc(int i)
{
	assert(i>=0);
	assert(Code::now);
	assert(i<Code::n);
	int t=Code::a[i];
	Code::a[t]--;
	if(Code::a[t]<0)Code::a[t]+=Code::n;
	if(Code::a[t]>=Code::n)Code::a[t]-=Code::n;
	Code::a[i]++;
	if(Code::a[i]<0)Code::a[i]+=Code::n;
	if(Code::a[i]>=Code::n)Code::a[i]-=Code::n;
}
void Dec(int i)
{
	assert(i>=0);
	assert(Code::now);
	assert(i<Code::n);
	int t=Code::a[i];
	Code::a[t]++;
	if(Code::a[t]<0)Code::a[t]+=Code::n;
	if(Code::a[t]>=Code::n)Code::a[t]-=Code::n;
	Code::a[i]--;
	if(Code::a[i]<0)Code::a[i]+=Code::n;
	if(Code::a[i]>=Code::n)Code::a[i]-=Code::n;
}
int check(int N,const int* A,const int* B);
void work(int N,const int* A,const int* B);
//Your Solution 
int main()
{
	Code::n=io::F();
	if(Code::n==0){puts("Code");return 0;}
	for(register int i=0;i<Code::n;++i)Code::a[i]=Code::A[i]=io::F();
	for(register int i=0;i<Code::n;++i)Code::b[i]=Code::B[i]=io::F();
	int tmp=check(Code::n,Code::A,Code::B);
	if(tmp==-1)return puts("NoSolutionCode"),0;
	Code::now=1;
	work(Code::n,Code::A,Code::B);
	for(register int i=0;i<Code::n;++i)
		if(Code::a[i]!=Code::b[i])return 0;
	puts("Code");
	return 0;
}


