#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

void median1(int [],int,float);
int main()
{
	srand(time(0));
	int n;
	printf("enter the number of element in the set\n");
	scanf("%d",&n);
	int a[n] = {1,3,5,8,10};
	float s;
	printf("enter s(0 <= s <= 1/2)\n");
	scanf("%f",&s);
	median1(a,n,s);
	return 0;
}

void median1(int a[],int n,float s)
{
	int j=1, c = 20;
	while(j<=c)
	{
	int r = rand() % n;
	int x = a[r],k=1;
	for(int i = 0;i<n;i++)
	{
		if(x < a[i])
			k= k+1;
	}
	if((0.5-s)*(n+1) <= k && k<=(0.5+s)*(n+1))
		printf("%d\n",x);
	else
		printf("error\n");
	j+=1;
	}
}
