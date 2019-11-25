#include<stdio.h>
void loadBal(int[],int,int);
int findMinLoad(int[],int m);
int main()
{
	int m,i,n;
	printf("enter the number of jobs\n");
	scanf("%d",&n);
	int jobs[n];
	for(i=1;i<=n;i++)
	{
		printf("enter the time to finish job %d\n",i);
		scanf("%d",&jobs[i]);
	}
	printf("enter the number of machines\n");
	scanf("%d",&m);
	loadBal(jobs,n,m);
	return 0;

}

void loadBal(int jobs[],int n,int m)
{
	int T[m],i,min,makespan = 0;
	for(i=1;i<=n;i++)
		T[i] = 0;
	for(i=1;i<=n;i++)
	{
		min = findMinLoad(T,m);
		T[min] = T[min]+jobs[i];
	}
	for(i=1;i<=n;i++)
	{
		if(T[i]>=makespan)
			makespan = T[i];
	}
	printf("the minimum time to finish all the jobs is %d",makespan);
}
int findMinLoad(int a[],int m)
{
	int i,j,min=999999;
	for(i=1;i<=m;i++)
	{
		if(a[i]<=min)
		{
			min = a[i];
			j = i;
		}
	}
	return j;
}
