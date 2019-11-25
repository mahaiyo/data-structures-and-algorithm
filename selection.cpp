#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void selection(int *,int,int);
int main()
{
	srand(time(0));
	int n,r;
	printf("enter the number of elements\n");
	scanf("%d",&n);
	int list[n];
	printf("enter the elements\n");
	for(int i = 0;i<n;i++)
	{
		scanf("%d",&list[i]);
	}
	printf("enter the rank\n");
	scanf("%d",&r);
	selection(list,n,r);
	return 0;
}

void selection(int *a,int n,int r)
{
	int i,rdn = rand() % n;
	int *arr1 = (int*)malloc(n*sizeof(int)),count1 = 0,*arr2 = (int*)malloc(n*sizeof(int)),count2 = 0;
	for( i = 0;i<n;i++)
	{
		if(a[i] < a[rdn])
		{
			arr1[count1++] = a[i];
		}
		if(a[i] > a[rdn])
		{
			arr2[count2++] = a[i];
		}
	}
	if(count1 == r-1)
		printf("output:%d",a[rdn]);
	else
	{
		if(count1 >= r)
			selection(arr1,count1,r);
		else
			selection(arr2,count2,r-(count1+1));
	}
	
}
