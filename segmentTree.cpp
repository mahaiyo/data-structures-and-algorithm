
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int getsum(int *,int,int,int,int,int);
int constructTree(int[],int*,int,int,int);
void updateValue(int *,int,int,int,int,int,int);

int main()
{
	int i,j,newVal,ch;
	int a[] = {1,5,3,4,10,12};
	int n = sizeof(a)/sizeof(a[0]);
	int height = (int)ceil(log2(n));
	int size = 2*(int)pow(2,height)-1;
	int *st = (int*)malloc(size*sizeof(int));
	constructTree(a,st,n-1,0,0);
	while(1)
	{
		printf("\n1.get sum\n2.update\n");
		printf("enter choice\n");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				printf("enter the indexes to sum\n");
				scanf("%d",&i);
				scanf("%d",&j);
				if(i<0 || j>n-1 || i>j)
					printf("invalid");
				else
				{
					int sum = getsum(st,i,j,n-1,0,0);
					printf("%d",sum);
				}
				break;
			case 2:
				printf("enter the array index and value to update\n");
				scanf("%d",&i);
				scanf("%d",&newVal);
				if(i<0 || i>n-1)
					printf("invalid index");
				else
				{
					int d =  newVal-a[i];
					a[i] = newVal;
					updateValue(st,n-1,i,newVal,d,0,0);
				}
				break;
		}
	}
	return 0;
}

int constructTree(int a[],int *st,int end,int start,int si)
{
	if(start == end)
	{
		st[si] = a[start];
		return a[start];
	}
	else
	{
		int mid = (start+end)/2;
		st[si] = constructTree(a,st,mid,start,2*si+1)+constructTree(a,st,end,mid+1,2*si+2);
		return st[si];
	}
}

int getsum(int *st,int i,int j,int end,int start,int si)
{
	if (end < i || start > j) 
        return 0; 
	if(i<=start && j >= end)
		return st[si];
	int mid = (start+end)/2; 
    return getsum(st, i,j, mid,start, 2*si+1) + 
           getsum(st, i,j,end,mid+1, 2*si+2); 
}

void updateValue(int *st,int end,int i,int newValue,int d,int start,int si)
{
    st[si] = st[si] + d; 
    if (end != start) 
    { 
        int mid = (start+end)/2;
        updateValue(st, mid, i,newValue, d,start, 2*si + 1); 
        updateValue(st, end,i,newValue, d,mid+1, 2*si + 2); 
    } 
}
