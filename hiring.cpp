#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void permutation(int *,int);
void hiredCandidate(int [],int);
int main()
{
	srand(time(0));
	int n;
	printf("enter the number of candidates\n");
	scanf("%d",&n);
	int list[n];
	printf("enter the rank of each candidates\n");
	for(int i = 1;i<=n;i++)
	{
		scanf("%d",&list[i]);
	}
	hiredCandidate(list,n);
	return 0;
}

void hiredCandidate(int list[],int n)
{
	int i;
	permutation(list,n);
	for(i=1;i<=n;i++)
		printf("%d-",list[i]);
	int cost = 0;
	int current = 0;
	for( i =1;i<=n;i++)
	{
		int r = rand() % n;
		if(current == 0 || list[i] > list[r])
		{
			current = list[i];
			cost+=1;
		}
	}
	printf("the hired candidate is %d with total cost of %d",current,cost);
}

void permutation(int *a,int n)
{
	int temp;
	for(int i =1;i<=n;i++)
	{
		int r = (rand() % (n-i + 1))+i;
		if(a[r] != a[i])
		{
			temp = a[i];
			a[i] = a[r];
			a[r] = a[i];
		}
	}
}
