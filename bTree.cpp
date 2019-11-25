#include<stdio.h>
#include<stdlib.h>
#define t 3

typedef struct node
{
	int n;
	int a[2*t-1];
	node *ptr[2*t];
	bool leaf;
}Node;


void postorder(Node *);
Node  *insert(Node* ,int);
Node *split(Node *,Node *,int);
Node *insertNonFull(Node *,int);
Node *del(Node *,int);
int findInd(Node *snode,int);
Node * merge(Node*,int);
int findPred(Node *);
int findSucc(Node *);

int main()
{
	Node *root=NULL;
	int data,ch,i;
	while(1)
	{
		printf("\n1. insert\n");
		printf("2. postorder\n");
		printf("3. deletion\n");
		printf("enter choice\n");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				while(1)
				{
					printf("enter the data\n");
					scanf("%d",&data);
					if(data == -1)
						break;
					root = insert(root,data);
				}	
				break;
			case 2:
				postorder(root);
				break;
			case 3:
				printf("Enter the data to delete\n");
				scanf("%d",&data);
				root = del(root,data);
				break;
		}
	}
	return 0;
}

Node *insert(Node *snode,int data)
{
	if(snode == NULL)
	{
		snode = (node *)malloc(sizeof(node));
		snode->n = 0;
		snode->leaf = true;
		int i = snode->n;
		snode->a[i] = data;
		snode->ptr[i] = NULL;
		i++;
		snode->n = i;
		snode->ptr[i] = NULL;
		return snode;			
	}
	else
	{
		int i = snode->n;
		if(i == 2*t-1)
		{
			Node *pre = (node *)malloc(sizeof(node));
			pre->n = 0;
			pre->leaf = false;
			pre->ptr[0] = snode;
			pre = split(pre,snode,0);
			pre = insertNonFull(pre,data);
			return pre;
		}
		else{
			snode = insertNonFull(snode,data);
			return snode;
		}
	}
}

void postorder(Node *snode)
{
	int i,j;
	if(snode != NULL)
	{
		for(i = 0;i<=snode->n;i++)
		{
			postorder(snode->ptr[i]);
		}
		for(j = 0;j<snode->n;j++)
		{
			printf("%d-",snode->a[j]);
		}
		printf("\n");
	}
}

Node *insertNonFull(Node *snode,int data)
{
	int i = snode->n;
	if(snode->leaf)
	{
		while(i>0 && data < snode->a[i-1])
		{
			snode->a[i] = snode->a[i-1];
			i--;
		}
		snode->a[i] = data;
		snode->n+=1;
		snode->ptr[snode->n] = NULL;
		return snode;
	}
	else if(!snode->leaf)
	{
		while(i>0 && data < snode->a[i-1])
		{
			i--;
		}
		if(snode->ptr[i]->n == 2*t-1)
		{
			snode = split(snode,snode->ptr[i],i);
			if(data > snode->a[i])
				i+=1;
		}
		snode->ptr[i] = insertNonFull(snode->ptr[i],data);
		return snode;
	}
	
}
Node *split(Node *pre,Node *snode,int k)
{
	int i;
	Node *child = (node *)malloc(sizeof(node));
	child->n = 0;
	child->leaf = snode->leaf;
	child->n = t-1;
	for(i = 0;i<child->n;i++)
	{
		child->a[i] = snode->a[child->n+1+i];
		child->ptr[i] = child->ptr[i+1] = NULL;
	}
	
	if(snode->leaf == false)
	{
		for(i = 0;i<=child->n;i++)
			child->ptr[i] = snode->ptr[child->n+1+i];
	}
	snode->n = t-1;
	for(i = pre->n;i>k;i--)
	{
		pre->ptr[i+1] = pre->ptr[i];
	}
	pre->ptr[k+1] = child;
	for(i = pre->n-1;i>=k;i--)
	{
		pre->a[i+1] = pre->a[i];
	}
	pre->a[k] = snode->a[snode->n];
	pre->n+=1;
	return pre;
}

Node *merge(Node *snode,int i)
{
	int j;
	snode->ptr[i]->a[snode->ptr[i]->n] = snode->a[i];
	snode->ptr[i]->n+=1;
	for(j = 0;j<snode->ptr[i+1]->n;j++)
	{
		snode->ptr[i]->ptr[snode->ptr[i]->n] = snode->ptr[i+1]->ptr[j];
		snode->ptr[i]->a[snode->ptr[i]->n] = snode->ptr[i+1]->a[j];
		snode->ptr[i]->n+=1;
	}
	snode->ptr[i]->ptr[snode->ptr[i]->n] = snode->ptr[i+1]->ptr[snode->ptr[i+1]->n];
	if(snode->n == 1)
		snode = snode->ptr[i];
	else
	{
		j = i+1;
		while(j < snode->n)
		{
			snode->a[j-1] = snode->a[j];
			snode->ptr[j] = snode->ptr[j+1];
			j++;
		}
		snode->n-=1;
	}
	return snode;
}

int findPred(Node *snode)
{
	int pre = snode->a[snode->n-1];
	if(snode->ptr[snode->n] != NULL)
		pre = findPred(snode->ptr[snode->n]);
	return pre;
}
int findSucc(Node *snode)
{
	int succ = snode->a[0];
	if(snode->ptr[0] != NULL)
		succ = findSucc(snode->ptr[0]);
	return succ;
}

Node *del(Node *snode,int key)
{
	int ind = 0,j;
	ind = findInd(snode,key);
	if(ind < snode->n && snode->a[ind] == key)
	{
		if(snode->leaf)// case 1
		{
			if(snode->n > t-1)
			{
				for(j=ind;j<snode->n-1;j++)
				{
					snode->a[j] = snode->a[j+1];
				}
				snode->n-=1;
			}
		}
		else
		{
			if(snode->ptr[ind]->n > t-1)// case 2a
			{
				snode->a[ind] = findPred(snode->ptr[ind]);
				snode->ptr[ind] = del(snode->ptr[ind],snode->a[ind]);
			}
			else if(snode->ptr[ind+1]->n > t-1)//  case 2b
			{
				snode->a[ind] = findSucc(snode->ptr[ind+1]);
				snode->ptr[ind+1] = del(snode->ptr[ind+1],snode->a[ind]);
			}
			else //  case 2c
			{
				snode = merge(snode,ind);
				snode = del(snode,key);
			}
		}
	}
	else
	{
		if(snode->ptr[ind]->n == t-1)
		{
			if(ind != snode->n && snode->ptr[ind+1]->n > t-1)// case 3a
			{
				snode->ptr[ind]->a[snode->ptr[ind]->n] = snode->a[ind];
				snode->ptr[ind]->n+=1;
				snode->ptr[ind]->ptr[snode->ptr[ind]->n] = snode->ptr[ind+1]->ptr[0];
				snode->a[ind] = snode->ptr[ind+1]->a[0];
				for(j = 0;j<snode->ptr[ind+1]->n-1;j++)
				{
					snode->ptr[ind+1]->ptr[j] = snode->ptr[ind+1]->ptr[j+1];
					snode->ptr[ind+1]->a[j] = snode->ptr[ind+1]->a[j+1];
				}
				snode->ptr[ind+1]->ptr[j] = snode->ptr[ind+1]->ptr[snode->ptr[ind+1]->n];
				snode->ptr[ind+1]->n-=1;
				snode->ptr[ind] = del(snode->ptr[ind],key);	
			}
			else if(ind != 0 && snode->ptr[ind-1]->n > t-1)
			{
				snode->ptr[ind]->n+=1;
				for(j = snode->ptr[ind]->n;j>0;j--)
				{
					snode->ptr[ind]->ptr[j+1] = snode->ptr[ind]->ptr[j];
					snode->ptr[ind]->a[j] = snode->ptr[ind]->a[j-1];
				}
				snode->ptr[ind]->ptr[j+1] = snode->ptr[ind]->ptr[j];			
				snode->ptr[ind]->a[0] = snode->a[ind-1];
				snode->ptr[ind]->ptr[0] = snode->ptr[ind-1]->ptr[snode->ptr[ind-1]->n];	
				snode->a[ind-1] = snode->ptr[ind-1]->a[snode->ptr[ind-1]->n-1];
				snode->ptr[ind-1]->n-=1;
				snode->ptr[ind] = del(snode->ptr[ind],key);	
			}
			else // case 3b
			{
				if(ind == snode->n)
					snode = merge(snode,ind-1);
				else
					snode = merge(snode,ind);
				snode = del(snode,key);
			}	
		}
		else
		{
			snode->ptr[ind] = del(snode->ptr[ind],key);
		}
	}
	return snode;
}

int findInd(Node *snode,int key)
{
	int i = 0;
	while(i<snode->n && snode->a[i] < key)
	{
		++i;
	}
	return i;
}

