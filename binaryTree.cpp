#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

typedef struct node
{
	int val;
	struct node *left,*right;
}Node;

Node *root,*newnode;

Node *child();
void inorder(Node*);
void preorder(Node*);
void postorder(Node*);



int main()
{	
	int ch,data;
	while(1)
	{
		printf("\n1. create binary tree\n");
		printf("2. inorder traversal\n");
		printf("3. preorder traversal\n");
		printf("4. postorder traversal\n");
		printf("Enter choice\n");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				root = child();
				break;
			case 2:
				inorder(root);
				break;
			case 3:
				preorder(root);
				break;
			case 4:
				postorder(root);
				break;
			default:
				printf("invalid\n");
		}
	}
	return 0;	
}

Node *child()
{
	Node *temp;
	int data;
	char ans;
	printf("enter the data\n");
	scanf("%d",&data);
	temp = (node *)malloc(sizeof(node));
	temp->val = data;
	temp->left = NULL;
	temp->right = NULL;
	
	printf("does %d have left child(Y/N)?\n",temp->val);
	scanf("%s",&ans);
	if(ans == 'N' || ans == 'n')
	{
		temp->left = NULL;
	}
	else
	{
		temp->left = child();
	}
	
	printf("does %d have right child(Y/N)?\n",temp->val);
	scanf("%s",&ans);
	if(ans == 'N' || ans == 'n')
	{
		temp->right = NULL;
	}
	else
	{
		temp->right = child();
	}
	
	
	return temp;
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

void preorder(Node *root)
{
	
	if(root != NULL)
	{
		printf("%d->",root->val);
		preorder(root->left);
		preorder(root->right);
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

