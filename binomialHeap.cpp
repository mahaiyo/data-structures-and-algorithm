#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	int key;
	node *parent,*child,*sibling;
	int degree;
}Node;


Node *insert(Node *,int);
Node *unionHeap(Node *,Node *);
Node *binomialLink(Node*,Node*);
Node *findMin(Node *);
Node *extractMin(Node *);
Node *decreaseKey(Node *,int, int);
Node *search(Node *,int);
Node *del(Node *,int);
void levelTraverse(Node *);
void preOrder(Node *);

int main()
{
	int data,ch,newVal;
	Node *head = NULL;
	while(1)
	{
		printf("\n 1. insert\n");
		printf("2. preorder\n");
		printf("3. Find the minimum\n");
		printf("4. Extract minimum\n");
		printf("5. Decrease key\n");
		printf("6. delete\n");
		printf("7. Level order traversal\n");
		printf("enter choice\n");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				while(1)
				{
					printf("\nenter data\n");
					scanf("%d",&data);
					if(data == 0)
						break;
					head = insert(head,data);
				}
				break;
			case 2:
				preOrder(head);
				break;
			case 3:
				Node *y;
				y = findMin(head);
				printf("Minimum is %d",y->key);
				break;
			case 4:
				head = extractMin(head);
				break;
			case 5:
				printf("enter old key\n");
				scanf("%d",&data);
				printf("enter new key\n");
				scanf("%d",&newVal);
				head = decreaseKey(head,data,newVal);
				break;
			case 6:
				printf("enter key to delete\n");
				scanf("%d",&data);
				head = del(head,data);
				break;
			case 7:
				levelTraverse(head);
				break;
		}
	}
	return 0;
}

Node *insert(Node *H,int data)
{
	Node *temp = (node *)malloc(sizeof(node));
	temp->key = data;
	temp->degree = 0;
	temp->parent = temp->child = temp->sibling = NULL;
	H = unionHeap(H,temp);
	return H;
}
Node *mergeHeap(Node *H1,Node *H2)
{
	if(H1 == NULL)
		return H2;
	else if(H2 == NULL)
		return H1;
	if(H1->degree <= H2->degree)
	{
		H1->sibling = mergeHeap(H1->sibling,H2);
		return H1;
	}
	else
	{
		H2->sibling = mergeHeap(H1,H2->sibling);
		return H2;
	}
}
Node *binomialLink(Node *h1,Node *h2)
{
	h1->parent = h2;
	h1->sibling = h2->child;
	h2->child = h1;
	h2->degree+=1;
	return h2;
}		


Node *unionHeap(Node *H1,Node *H2)
{
	Node *temp = mergeHeap(H1,H2);
	Node *prev_x=NULL;
	Node *x = temp;
	Node *next_x=x->sibling;
	while(next_x != NULL)
	{
		if((x->degree != next_x->degree) || (next_x->sibling != NULL && next_x->sibling->degree == x->degree))//case 1 and 2
		{
			prev_x = x;
			x = next_x;
		}
		else if(x->key <= next_x->key) //case 3
		{
			x->sibling = next_x->sibling;
			x = binomialLink(next_x,x);
		}
		else //case 4
		{
			if(!prev_x)
				temp = next_x;
			else
				prev_x->sibling = next_x;
			next_x = binomialLink(x,next_x);
			x = next_x;
		}
		next_x = x->sibling;
	}
	
	return temp;	
}

void preOrder(Node *snode)
{
	if(snode)
	{
		printf("%d-",snode->key);
		if(snode->child)
			preOrder(snode->child);
		snode = snode->sibling;
		preOrder(snode);
	}
		
		
}
 Node * findMin(Node * snode)
 {
 	Node *min = snode;
 	while(snode)
 	{
 		if(snode->key <= min->key)
 		{
 			min = snode;
 			
 		}
 		snode = snode->sibling;
	 }
	 return min;
 }
 
 Node *extractMin(Node *snode)
 {
 	Node *min = snode,*prev = NULL,*H1 = snode;//find min and separate from heap
 	while(snode->sibling)
 	{
 		if(snode->sibling->key < min->key)
 		{
 			prev = snode;
 			min = snode->sibling;
 		}
 		snode = snode->sibling;
	 }
	 if(!prev)
	 	H1 = min->sibling;
	 else if(prev && min->sibling)
		prev->sibling = min->sibling;
	 else if(prev && min->sibling == NULL)
		prev->sibling = NULL;
	min->sibling = NULL;
	if(min->child) //remove minimum and reversing the heap
	{
		Node *c = min->child,*l= NULL,*n;
		while(c)
		{
			n = c->sibling;
			c->sibling = l;
			l = c;
			c = n;
		}
		min = l;
		min->parent = NULL;
	}
	Node *temp = unionHeap(H1,min); // union of the two heaps
	return temp;
 }
 
 Node *decreaseKey(Node *snode,int old,int newVal)
 {
 	int n;
 	if(newVal>=old)
 	{
 		printf("cannot decrease");
	 }
	 Node *temp = search(snode,old);
	 temp->key = newVal;
	 Node *y = temp;
	 Node *z = y->parent;
	 while(z && y->key < z->key)
	 {
		n = y->key;
		y->key = z->key;
		z->key = n;
		y = z;
		z = y->parent;	 	
	 }
	 return snode;
	
 }
 Node *search(Node *snode,int key)
 {
 	Node *y = NULL;
 	if(snode->key == key)
 	{
 		y = snode;
 		return y;
	 }
	 if(snode->child && y == NULL)
	 	y = search(snode->child,key);
	if(snode->sibling && y == NULL)
		y = search(snode->sibling,key);
	return y;
 }
 Node *del(Node *snode,int data)
 {
 	snode = decreaseKey(snode,data,-10000);
 	snode = extractMin(snode);
 	return snode;
 }
 
void levelTraverse(Node *h)
{
	node *(queue[100]);
	int f=-1,r=-1;
	node *dmy=NULL;
	dmy=(node*)malloc(sizeof(node));
	dmy->child=dmy->sibling=NULL;
	dmy->key=-99999;
	node *ptr=h;
	while(ptr!=NULL)
	{
		queue[++r]=ptr;
		ptr=ptr->sibling;
	}
	queue[++r]=dmy;
	while((f+1) != r)
	{
		node *tmp=queue[++f];
		if(tmp->key != -99999)
		{
			printf("%d-",tmp->key);
			//if(tmp->sibling==NULL)
			//{
				//printf("\t");
			//}
			ptr=tmp->child;
			while(ptr)
			{
				queue[++r]=ptr;
				ptr=ptr->sibling;
			}
			
		}
		else
		{
			queue[++r]=dmy;
			printf("\n");
		}
	}
}

