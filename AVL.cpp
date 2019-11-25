#include<stdio.h>
#include<stdlib.h>

int bal = 1;
typedef struct node
{
	int val;
	node *left,*right,*parent;
	int bf;
}Node;

Node *root;
Node *insert(Node*,int,int *bal);
Node *Rrotate(Node *,int *bal);
Node *Lrotate(Node *,int *bal);
Node *del(Node *,int,int *bal);
void inorder(Node *);
void postorder(Node *);
Node *minValue(Node*);

int main()
{
	int data;
	int ch;
	while(1)
	{
		printf("\n1.insert\n");
		printf("2.inorder\n");
		printf("3.postorder\n");
		printf("4.deletion\n");
		printf("enter choice\n");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				printf("enter the data\n");
				scanf("%d",&data);
				root = insert(root,data,&bal);
				break;
			case 2:
				inorder(root);
				break;
			case 3:
				postorder(root);
				break;
			case 4:
				printf("enter the element to delete\n");
				scanf("%d",&data,&bal);
				root = del(root,data,&bal);
				break;
		}
	}
	return 0;
}

Node *insert(Node *root,int data,int *bal)
{
	if(root == NULL)
	{
		*bal = 0;
		root = (node *)malloc(sizeof(node));
		root->val = data;
		root->bf = 0;
		root->left = NULL;
		root->right = NULL;
		root->parent = NULL;
	}
	else if(data < root->val)
	{
		root->left = insert(root->left,data,bal);
		root->left->parent = root;
		if(*bal!=1)
		{
			if(root->bf == 0)
			{
				root->bf = 1;
			}
			else if(root->bf == 1)
			{
				root = Lrotate(root,bal);
			}
			else if(root->bf == -1)
			{
				root->bf =0;
				*bal = 1;
			}
		}
			
	}
	else if(data > root->val)
	{
		root->right = insert(root->right,data,bal);
		root->right->parent = root;
		if(*bal!=1)
		{
			if(root->bf == 0)
			{
				root->bf =-1;
			}
			else if(root->bf == 1)
			{
				root->bf = 0;
				*bal=1;
			}
			else if(root->bf == -1)
			{
				root = Rrotate(root,bal);
			}
				
		}	
	}
	return root;
}

Node *Lrotate(Node *root,int *bal)
{
	Node *temp = root->left;
	if(temp->bf == 1)// LL rotation
	{
		root->left = temp->right;
		temp->right = root;
		root->bf = 0;
		root = temp;
	}
	else //LR rotation
	{
		Node *grandchild = temp->right;
		temp->right = grandchild->left;
		root->left = grandchild->right;
		grandchild->right = root;
		grandchild->left = temp;
		if(grandchild->bf == 0)
		{
			temp->bf = 0;
			root->bf = 0;
		}
		else if(grandchild->bf == 1)
		{
			temp->bf = 0;
			root->bf = -1;
		}
		else if(grandchild->bf == -1)
		{
			temp->bf = 1;
			root->bf = 0;
		}
		root = grandchild;
	}
	root->bf =0;
	*bal = 1;
	return root;
}

Node *Rrotate(Node *root,int *bal)
{
	Node *temp = root->right;
	if(temp->bf == -1)// RR rotation
	{
		root->right = temp->left;
		temp->left = root;
		root->bf = 0;
		root = temp;
	}
	else //RL rotation
	{
		Node *grandchild = temp->left;
		root->right = grandchild->left;
		temp->left = grandchild->right;
		grandchild->left = root;
		grandchild->right = temp;
		root = grandchild;
		if(root->bf == 0)
		{
			temp->bf = 0;
			root->left->bf = 0;
		}
		else if(root->bf == 1)
		{
			temp->bf = -1;
			root->left->bf = 0;
		}
		else if(root->bf == -1)
		{
			temp->bf = 0;
			root->left->bf = 1;
		}
	}
	root->bf =0;
	*bal = 1;
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

Node *del(Node *root, int data,int *bal)
{
	if(root == NULL)
	{
		printf("data not found\n");//empty tree
		return root;
	}
	else if(data < root->val)
	{
		root->left = del(root->left,data,bal);
		if(*bal==0){
		if(root->bf == 0){
			root->bf = -1;
		}
		else if(root->bf == 1){
			root->bf = 0;
		}
		else if(root->bf == -1){
			if(root->left == NULL || root->left->bf ==0)
					root = Rrotate(root,bal);
			else
				root->bf = -1;
		}
		}
		return root;
	}
	else if(data > root->val)
	{
		root->right = del(root->right,data,bal);
		if(*bal==0){
			if(root->bf == 0){
				root->bf = 1;
			}
			else if(root->bf == 1)
			{
				if(root->right == NULL || root->right->bf ==0)
					root = Lrotate(root,bal);
				else
					root->bf = 1;
			}
			else if(root->bf == -1)
			{
				root->bf = 0;
			}
		}
		return root;	
	}
	else
	{
		Node *pre = root->parent;
		if(root->left == NULL && root->right == NULL)//node has no child
		{
			if(pre == NULL){
				free(root);
				*bal = 0;	
			}
			else if(root->val < pre->val)
			{
				pre->left = NULL;
				free(root);
				*bal = 0;
			}
			else if(root->val > pre->val)
			{
				pre->right = NULL;
				free(root);
				*bal = 0;
			}
			return NULL;
		}
		else if(root->left == NULL || root->right == NULL)//node has one child
		{
			if(root->left == NULL)
			{
				if(data < pre->val)
				{
					pre->left = root->right;
					root->right->parent = pre;
					free(root);
					*bal = 0;
					return pre->left;
				}
				else
				{
					pre->right = root->right;
					root->right->parent = pre;
					free(root);
					*bal = 0;
					return pre->right;
				
				}	
			}
			
			else if(root->right == NULL)
			{
				if(data > pre->val)
				{
					pre->right = root->left;
					root->left->parent = pre;
					free(root);
					*bal = 0;
					return pre->right;
				
				}	
				else
				{
					pre->left = root->left;
					root->left->parent = pre;
					free(root);
					*bal = 0;
					return pre->left;
				}
			}
		}
		else if(root->left != NULL && root->right != NULL)//node has two child
		{
			Node *lchild = root->left;
			Node *rchild = root->right;
			Node *temp = minValue(rchild);
			root->val = temp->val;
			root->right = del(root->right,temp->val,bal);
			if(root->bf == 0)
			{
				if(rchild->bf == 0){
					root->bf = 1;
					*bal = 1;
				}
				else
					root->bf = 0;	
			}
			else if(root->bf == 1)
			{
				if(rchild == NULL || rchild->bf == 0)
					root = Lrotate(root,bal);
				else
					root->bf = 1;
			}
			else if(root->bf == -1)
			{
				if(rchild->bf == 0)
					root->bf =0;
				else
					root->bf = -1;
			}
			return root;
		}
	}
}

Node *minValue(Node *node){
	while(node->left != NULL)
	{
		node = node->left;
	}
	return node;
}
