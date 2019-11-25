#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	int key,degree;
	node *parent,*left,*right,*child;
	bool mark;
}Node;

typedef struct fibo_heap
{
	Node *min;
	int n;
}heap;

heap *insert(heap*,int);
heap *create_heap();
Node *concatenate(Node *,Node *);
heap *extractMin(heap*);
Node *consolidate(heap *);
Node *link(Node *,Node*);
heap *decreaseKey(heap*,int,int);
Node *search(Node *,int);
heap *cut(heap *,Node *,Node *);
heap *cascadingCut(heap*,Node*);
heap *deleteKey(heap *,int);
void levelorder(Node *);

int main()
{
	int data,key,ch,n = 0;
	heap *H = create_heap();
	while(1)
	{
		printf("\n1.Insertion\n");
		printf("2. level order\n");
		printf("3. extract min\n");
		printf("4. decrease key\n");
		printf("5. delete a key\n");
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
					H = insert(H,data);
				}
				break;
			case 2:
				levelorder(H->min);
				break;
			case 3:
				H = extractMin(H);
				break;
			case 4:
				printf("enter old key\n");
				scanf("%d",&key);
				printf("enter the new key\n");
				scanf("%d",&data);
				H = decreaseKey(H,key,data);
				break;
			case 5:
				printf("enter the key to delete\n");
				scanf("%d",&data);
				H = deleteKey(H,data);
				break;
		}
	}
	return 0;
}
heap *create_heap()
{
	heap *H = (heap*)malloc(sizeof(heap));
	H->min = NULL;
	H->n = 0;
}

heap *insert(heap *H,int data)
{
	Node *temp = (node*)malloc(sizeof(node));
	temp->key = data;
	temp->parent = NULL;
	temp->child = NULL;
	temp->left = temp->right = temp;
	temp->degree = 0;
	temp->mark = false;
	if(!H->min)
		H->min = temp;
	else
		H->min = concatenate(H->min,temp);
	H->n+=1;
	return H;
}
Node *concatenate(Node *snode1,Node *snode2)
{
	Node *temp = snode1->left;
	temp->right = snode2;
	snode2->left = temp;
	snode2->right = snode1;
	snode1->left = snode2;
	if(snode1->key < snode2->key)
		return snode1;
	else
		return snode2;		
}

void levelorder(Node *min)
{
	node *(queue[100]);
	int f=-1,r=-1;
	node *dmy=NULL;
	dmy=(node*)malloc(sizeof(node));
	dmy->child = dmy->left = dmy->right = dmy->parent = NULL;
	dmy->degree = 0;
	dmy->mark = false;
	dmy->key=-99999;
	node *ptr=min;
	do
	{
		queue[++r]=ptr;
		ptr=ptr->right;
	}while(ptr->key != min->key);
	queue[++r]=dmy;
	while((f+1) != r)
	{
		node *tmp=queue[++f];
		if(tmp->key != -99999)
		{
			printf("%d-",tmp->key);
			ptr=tmp->child;
			if(ptr)
			{
				do
				{
					queue[++r]=ptr;
					ptr=ptr->right;
				}while(ptr != tmp->child);
			}
		}
		else
		{
			queue[++r]=dmy;
			printf("\n");
		}
	}
}

heap *extractMin(heap *H)
{
	Node *z = H->min;	
	if(z)
	{
		if(z->child)// making children root
		{
			Node *y =NULL;
			Node *ptr = z->child;
			do
			{
				y = ptr->right;
				ptr->parent = NULL;
				H->min = concatenate(H->min,ptr); 
				ptr = y;
			}while(y != z->child);
		}
		H->min->right->left = H->min->left;//removing the min
		H->min->left->right = H->min->right;
		if(z == z->right)
			H->min = NULL;
		else
		{
			H->min = z->right;
			H->min = consolidate(H);
		}
		H->n-=1;
	}
	return H;
}

Node *consolidate(heap *H)
{
	int i;
	Node *a[H->n];
	for(i = 0;i<=H->n;i++)
		a[i] = NULL;
	Node *x = H->min;
	Node *w = x;
	do
	{
		w = w->right;
		int d = x->degree;
		while(a[d] != NULL)
		{
			Node *y = a[d];
			if(y->key != x->key)
			{
				if(x->key > y->key)// swaping nodes
				{
					int temp = x->key;
					x->key = y->key;
					y->key = temp;
					Node *ptr = x->child;
					Node *ptr2 = y->child;
					x->child = y->child;
					if(y->child)
					{
						do
						{
							ptr2->parent = x;
							ptr2 = ptr2->right;
						}while(ptr2 != y->child);
					}
					y->child = ptr;
					if(ptr)
					{
						do
						{
							ptr->parent = y;
							ptr = ptr->right;
						}while(ptr != y->child);
					}
				}
				if(H->min == y)
					H->min = x;
				x = link(y,x);
				a[d] = NULL;
				d+=1;	
			}
			else
				break;
		}
		if(!a[d])
			a[d] = x;
		x= x->right;
	}while(x != H->min);
	H->min = NULL;
	for(i=0;i<=H->n;i++)
	{
		if(a[i])
		{
			if(!H->min)
				H->min = a[i];
			else
			{
				if(a[i]->key < H->min->key)
					H->min = a[i];
			}
		}
	}
	return H->min;
}

Node *link(Node *y,Node *x)
{
	y->parent = x;
	if(x->right == y && x->left == y)
		x->right = x;
	if(x->left == y)
	{
		x->left = y->left;
		x->left->right = x;
	}
	else
	{
		y->left->right = y->right;
		y->right->left  = y->left;
	}
	if(!x->child)
	{
		y->left = y->right = y;
		x->child = y;
	}
	else
		x->child = concatenate(x->child,y);
	y->mark = false;
	x->degree+=1;
}
heap *decreaseKey(heap *H,int x,int y)
{
	if(y > x)
	{
		printf("old key is less than new key");
		return H;
	}
	Node *temp = search(H->min,x);
	temp->key = y;
	Node *pre = temp->parent;
	if(pre && temp->key < pre->key)
	{
		H = cut(H,temp,pre);
		//levelorder(H->min);
		H = cascadingCut(H,pre);
	}
	return H;
}
Node *search(Node *min,int x)
 {
 	Node *y = NULL;
 	if(min->key == x)
 	{
 		y = min;
 		return y;
	}
	if(min->child && y == NULL)
	 	y = search(min->child,x);
	if(min->right->key != min->key && y == NULL)
		y = search(min->right,x);
	return y;
 }
 
heap *cut(heap *H,Node *x,Node *y)
{
 	if(y->degree == 1)
 	{
 		y->child = NULL;
 		H->min = concatenate(H->min,x);
	}
	else
	{
		if(y->child == x)
			y->child =  x->right;
		x->left->right = x->right;
		x->right->left = x->left;
		H->min = concatenate(H->min,x);
	}
	y->degree-=1;
	x->parent = NULL;
	x->mark = false;
	return H;
}
 heap *cascadingCut(heap *H,Node *y)
 {
 	Node *z = y->parent;
 	if(z)
 	{
 		if(y->mark == false)
 			y->mark = true;
 		else
 		{
 			H = cut(H,y,z);
 			H = cascadingCut(H,z);
		 }
	 }
	 return H;
 }
 heap *deleteKey(heap *H,int data)
 {
 	H = decreaseKey(H,data,-10000);
 	H = extractMin(H);
 	return H;
 }
