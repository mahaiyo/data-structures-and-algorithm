#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	int val;
	node *right,*left,*parent;
}Node;



Node *insert(Node*,int);
void inorder(Node*);
void postorder(Node *);
Node *del(Node*,int);
void levelOrder(Node *);

int main()
{
	Node *root = NULL;
	int data,ch;
	while(1)
	{
		printf("\n1.insert\n");
		printf("2.inorder traversal\n");
		printf("3.postorder traversal\n");
		printf("4. level order\n");
		printf("5. deletion\n");
		printf("Enter choice\n");
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
				inorder(root);
				break;
			case 3:
				postorder(root);
				break;
			case 4:
				levelOrder(root);
				break;	
			case 5:
				printf("enter element to delete\n");
				scanf("%d",&data);
				root = del(root,data);
				break;
		}
	
	}
	return 0;
}

Node *insert(Node *root,int data)
{
	if(root == NULL)
	{
		root = (node*)malloc(sizeof(node));
		root->val = data;
		root->left = NULL;
		root->right = NULL;
		root->parent = NULL;
	}
	
	if(data < root->val)
	{
		Node *lchild = insert(root->left,data);
		root->left = lchild;
		lchild->parent = root;
	}
	else if(data > root->val)
	{
		Node *rchild = insert(root->right,data);
		root->right = rchild;
		rchild->parent = root;
	}
	
	return root;
}

void inorder(Node *root)
{
	if(root != NULL)
	{
		inorder(root->left);
		printf("%d->",root->val);
		inorder(root->right);
	}
}
void postorder(Node *root)
{
	if(root != NULL)
	{
		postorder(root->left);
		postorder(root->right);
		printf("%d->",root->val);
	}
}

Node *del(Node *node,int data)
{
	Node *temp = node->parent;
	if(node == NULL)
		printf("empty BST");
	if(data < node->val)
		node->left = del(node->left,data);
	else if(data > node->val)
		node->right = del(node->right,data);
	else
	{
		if(node->left == NULL && node->right == NULL)
		{
			if(data < temp->val)
			{
				temp->left = NULL;
				free(node);
			}
			else if(data > temp->val)
			{
				temp->right =NULL;
				free(node);
			}
			return NULL;
		}
		else if(node->left == NULL || node->right == NULL)
		{
		if(node->left == NULL)
		{
			if(data < temp->val)
			{
				temp->left = node->right;
				node->right->parent = temp;
				free(node);
				return temp->left;
			}
			else if(data > temp->val)
			{
				temp->right = node->right;
				node->right->parent = temp;
				free(node);
				return temp->right;
			}
		}
		else if(node->right == NULL)
		{
			if(data < temp->val)
			{
				temp->left = node->left;
				node->left->parent = temp;
				free(node);
				return temp->left;
			}
			else if(data > temp->val)
			{
				temp->right = node->left;
				node->left->parent = temp;
				free(node);
				return temp->right;
			}
		}
		}
		else
		{
			Node *Lchild = node->left;
			Node *Rchild = node->right;
			while(Rchild->left != NULL)
			{
				Rchild = Rchild->left;
			}
			node->val = Rchild->val;
			node->right = del(node->right,Rchild->val);
			return node;
		}
	}
}

void levelOrder(Node *snode)
{
	Node *a[99999];
	int front = 0;
	int rear = 0;
	a[rear++] = snode;
	Node *dummy = (node*)malloc(sizeof(node));
	dummy->left = dummy->right = NULL;
	dummy->val = 99999;
	a[rear++] = dummy;
	while(front+1 != rear)
	{
		if(a[front]->val != 99999)
		{
			printf("%d-",a[front]->val);
			if(a[front]->left)
			{
				a[rear++] = a[front]->left;
			}
			if(a[front]->right)
			{
				a[rear++] = a[front]->right;
			}
		}
		else
		{
			a[rear++] = dummy;
			printf("\n");
		}
		front++;
	}
}
