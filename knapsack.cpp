#include<stdio.h>
#include<math.h>
#include<stdlib.h>
void knapsack(int[],float[],int,int,int,float);
int min(int, int);
float RoundScale(float *,int,float);
float findMax(float [],int);


int main()
{
	int i,n,W,P=0;
	float e;
	printf("enter the number of items\n");
	scanf("%d",&n);
	printf("enter the weight of knapsack\n");
	scanf("%d",&W);
	printf("enter e\n");
	scanf("%f",&e);
	int weight[n];
	float profit[n];
	for(i = 1;i<=n;i++)
	{
		printf("enter weight and profit of item %d\n",i);
		scanf("%d",&weight[i]);
		scanf("%f",&profit[i]);
	}
	float mul = RoundScale(profit,n,e);
	for(i=1;i<=n;i++)
		P = P+profit[i];
	knapsack(weight,profit,W,P,n,mul);
	return 0;
}

void knapsack(int weight[],float profit[],int W,int P,int n,float mul)
{
	int i,newpro[n];
	int p;
	for(i=1;i<=n;i++)
		newpro[i] = (int)profit[i];
	float a[n+1][P+1];
	for(p=1;p<=P;p++)
		a[0][p] = 9999;
	for(i=0;i<=n;i++)
		a[i][0] = 0;
	for(i=1;i<=n;i++)
	{
		for(p=1;p<=P;p++)
		{
			if(newpro[i]<=p)
				a[i][p] = min(a[i-1][p],weight[i]+a[i-1][p-newpro[i]]);
			else
				a[i][p] = a[i-1][p];
		}
	}
	int maxPro = 0;
	for(i=0;i<=n;i++)
	{
		for(p=0;p<=P;p++)
		{
			if(a[i][p]<=W)
			{
				if(p >= maxPro)
					maxPro = p;
			}
		}
	}
	printf("the maximum profit is %f\n",maxPro*mul);
	p = maxPro;
	bool S[n+1];
	for(i=1;i<=n;i++)
		S[i] = false;
	for(i=n;i>=1;i--)
	{
		if(newpro[i]<=p)
		{
			if(weight[i]+a[i-1][p-newpro[i]]<a[i-1][p])
			{
				S[i] = true;
				p = p-profit[i];
			}
		}
	}
	printf("The items are\n");
	for(i=1;i<=n;i++)
	{
		if(S[i])
			printf("%d-",i);
	}
}

int min(int a,int b)
{
	if(a<=b)
		return a;
	else
		return b;
}

float RoundScale(float *profit,int n,float e)
{
	int i;
	float max = 0;
	float LB = findMax(profit,n);
	float mul = (e/n)*LB;
	for(i = 1; i <= n; i++)
		profit[i] = ceil(profit[i]/mul);
	return mul;
}

float findMax(float *a,int n)
{
	int i;
	float max = 0;
	for(i=1;i<=n;i++)
	{
		if(a[i]>=max)
			max = a[i];
	}
	return max;
}
