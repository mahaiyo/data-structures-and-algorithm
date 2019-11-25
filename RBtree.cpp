#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	int val;
	node *left,*right,*parent;
	char color;
}Node;

Node *root = NULL;
Node *insert(Node*,int);
void postorder(Node*);
void preorder(Node *);
Node *Loperations(Node *);
Node *Roperations(Node *);
Node *LLrotate(Node *);
Node *LRrotate(Node *);
Node *RLrotate(Node *);
Node *RRrotate(Node *);
Node *del(Node *, int);
int flag = 0;

int main()
{
	int data;
	int ch;
	while(1)
	{
		printf("\n1.insert\n");
		printf("2.postorder\n");
		printf("3.preorder\n");
		printf("4.deletion\n");
		printf("enter choice\n");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				printf("enter the data\n");
				scanf("%d",&data);
				root = insert(root,data);
				root->color = 'B';
				break;
			case 2:
				postorder(root);
				break;
			case 3:
				preorder(root);
			case 4:
				printf("enter the data to delete\n");
				scanf("%d",&data);
				root = del(root,data);
				break;
				break;
		}
	}
	return 0;
}

Node *insert(Node *root,int data)
{
	if(root == NULL)
	{
		root = (node *)malloc(sizeof(node));
		root->val = data;
		root->color = 'R';
		root->left = NULL;
		root->right = NULL;
		root->parent = NULL;
	}
	else if(data < root->val)
	{
		root->left = insert(root->left,data);
		root->left->parent = root;
		if(root->color == 'R')
		{
			if(root->left != NULL)
			{
				if(root->left->color == 'R')
				{
					if(root->val < root->parent->val)
						root = Loperations(root);
					else
						root = Roperations(root);
				}
			}
			else if(root->right != NULL)
			{
				if(root->right->color == 'R')
				{
					if(root->val < root->parent->val)
						root = Loperations(root);
					else
						root = Roperations(root);
				}
			}
		}

		else if(root->left->left != NULL || root->left->right != NULL)
		{
			if(root->left->left != NULL && root->left->color == 'R' && root->left->left->color == 'R')
				root = LLrotate(root);
			else if(root->left->right != NULL && root->left->color == 'R' && root->left->right->color == 'R')
				root = LRrotate(root);
		}
	}
	else if(data > root->val)
	{
		root->right = insert(root->right,data);
		root->right->parent = root;
		if(root->color == 'R')
		{
			if(root->left != NULL)
			{
				if(root->left->color == 'R')
				{
					if(root->val < root->parent->val)
						root = Loperations(root);
					else
						root = Roperations(root);
				}
			}
			else if(root->right != NULL)
			{
				if(root->right->color == 'R')
				{
					if(root->val < root->parent->val)
						root = Loperations(root);
					else
						root = Roperations(root);
				}
			}
		}
		else if(root->right->left != NULL || root->right->right != NULL)
		{
			if(root->right->left != NULL && root->right->color == 'R' && root->right->left->color == 'R')
				root = RLrotate(root);
			else if(root->right->right != NULL && root->right->color == 'R' && root->right->right->color == 'R')
				root = RRrotate(root);
		}
	}
	return root;
}

void postorder(Node *root)
{
	if(root != NULL)
	{
		postorder(root->left);
		postorder(root->right);
		printf("%d(%c)->",root->val,root->color);
	}
}
void preorder(Node *root)
{
	if(root != NULL)
	{
		printf("%d(%c)->",root->val,root->color);
		preorder(root->left);
		preorder(root->right);
		
	}
}

Node *Loperations(Node *snode)
{
	if(snode->parent->right != NULL && snode->parent->right->color == 'R')
	{
		snode->color = 'B';
		snode->parent->color = 'R';
		snode->parent->right->color = 'B';
		return snode;	
	}
	else
		return snode;
}

Node *Roperations(Node *snode)
{
	if(snode->parent->left != NULL && snode->parent->left->color == 'R')
	{
		snode->color = 'B';
		snode->parent->color = 'R';
		snode->parent->left->color = 'B';
		return snode;	
	}
	else
		return snode;
}

Node *LLrotate(Node * snode)
{
	Node *child = snode->left;
	snode->left = child->right;
	child->parent = NULL;
	if(snode->parent != NULL)
	{
		if(snode->val < snode->parent->val)
			snode->parent->left = child;
		else
			snode->parent->right = child;
		child->parent = snode->parent;
	}
	child->right = snode;
	snode->parent = child;
	child->color = 'B';
	snode->color = 'R';			
	return child; 
}
Node *LRrotate(Node *snode)
{

	Node *child = snode->left;
	Node *Rgrandchild = child->right;
	snode->left = Rgrandchild->right;
	if(snode->parent != NULL)
	{
		if(snode->val < snode->parent->val)
			snode->parent->left = Rgrandchild;
		else
			snode->parent->right = Rgrandchild;
		Rgrandchild->parent = snode->parent;
	}
	Rgrandchild->right = snode;
	snode->parent = Rgrandchild;
	child->right = Rgrandchild->left;
	Rgrandchild->left = child;
	child->parent = Rgrandchild;
	Rgrandchild->color = 'B';
	child->color = 'R';
	snode->color = 'R';
	return Rgrandchild;	
}

Node *RRrotate(Node * snode)
{
	Node *child = snode->right;
	snode->right = child->left;
	child->parent = NULL;
	if(snode->parent != NULL)
	{
		if(snode->val < snode->parent->val)
			snode->parent->left = child;
		else
			snode->parent->right = child;
		child->parent = snode->parent;
	}
	child->left = snode;
	snode->parent = child;
	child->color = 'B';
	snode->color = 'R';			 
	return child;
}

Node *RLrotate(Node *snode)
{
	Node *child = snode->right;
	Node *Rgrandchild = child->left;
	snode->right = Rgrandchild->left;
	if(snode->parent != NULL)
	{
		if(snode->val < snode->parent->val)
			snode->parent->left = Rgrandchild;
		else
			snode->parent->right = Rgrandchild;
		Rgrandchild->parent = snode->parent;
	}
	Rgrandchild->left = snode;
	snode->parent = Rgrandchild;
	child->left = Rgrandchild->right;
	Rgrandchild->right = child;
	child->parent = Rgrandchild;
	Rgrandchild->color = 'B';
	child->color = 'R';		
	snode->color = 'R';
	return Rgrandchild;
}


Node *del(Node *snode,int data)
{
	if(snode == NULL)
		return NULL;
	else if(data < snode->val)
	{
		snode->left = del(snode->left,data);
		if(flag){
		if(snode->right != NULL && snode->right->color == 'B')
		{
			if(snode->right->left != NULL && snode->right->left->color == 'R')
				snode = RLrotate(snode);
			else if(snode->right->right != NULL && snode->right->right->color == 'R')
				snode = RRrotate(snode);
			else if(snode->right->left != NULL && snode->right->right != NULL && snode->right->left->color == 'B' && snode->right->right->color == 'B'){
				snode->right->left->color == 'R';
				snode->right->right->color == 'R';
			}
			else if(snode->right != NULL && snode->right->color == 'R'){
				Node *temp = snode->right;
				snode->right = temp->left;
				temp->left->parent = snode;
				temp->left = snode;
				snode->parent = temp;
				snode = temp;
			}			
		}
		}
		flag = 0;
		return snode;
	}
	else if(data > snode->val)
	{
		snode->right = del(snode->right,data);
		if(flag){
		if(snode->left != NULL && snode->left->color == 'B')
		{
			if(snode->left->left != NULL && snode->left->left->color == 'R')
				snode = LLrotate(snode);
			else if(snode->left->right != NULL && snode->left->right->color == 'R')
				snode = LRrotate(snode);
			else if(snode->left->left != NULL && snode->left->right != NULL && snode->left->left->color == 'B' && snode->left->right->color == 'B'){
				snode->left->left->color == 'R';
				snode->left->right->color == 'R';
			}
			else if(snode->left != NULL && snode->left->color == 'R'){
				Node *temp = snode->left;
				snode->left = temp->right;
				temp->right->parent = snode;
				temp->right = snode;
				snode->parent = temp;
				snode = temp;
			}
		}
		}
		flag = 0;
		return snode;
	}
	else
	{
		if(snode->left == NULL && snode->right == NULL)//no child
		{
			if(data < snode->parent->val)
				snode->parent->left = NULL;
			else
				snode->parent->right = NULL;
			free(snode);
			flag = 1;
			return NULL;
		}
		else if(snode->left == NULL || snode->right == NULL)//one child
		{
			if(snode->left == NULL)
			{	
				Node *temp = snode->right;
				if(data <snode->parent->val){
					snode->parent->left = temp;
					temp->parent = snode->parent;
					if(temp->color == 'B' && snode->color == 'B')
						flag = 1;
					temp->color = 'B';
				}
				else{
					snode->parent->right = temp;
					temp->parent = snode->parent;
					if(temp->color == 'B' && snode->color == 'B')
						flag = 1;
					temp->color = 'B';
				}
				free(snode);
				return temp;
			}
			else
			{
				Node *temp = snode->left;
				if(data < snode->parent->val){
					snode->parent->left = temp;
					temp->parent = snode->parent;
					if(temp->color == 'B' && snode->color == 'B')
						flag = 1;
					temp->color = 'B';
				}
				else{
					snode->parent->right = temp;
					temp->parent = snode->parent;
					if(temp->color == 'B' && snode->color == 'B')
						flag = 1;
					temp->color = 'B';
				}
				free(snode);
				return temp;	
			}
		}
		else if(snode->left != NULL && snode->right != NULL)  //two child
		{
			Node *Rgrandchild = snode->right;
			while(Rgrandchild->left != NULL)
			{
				Rgrandchild = Rgrandchild->left;
			}
			snode->val = Rgrandchild->val;
			snode->right = del(snode->right,Rgrandchild->val);
			if(snode->right == NULL){
			if(snode->left != NULL && snode->left->color == 'B')
			{
				if(snode->left->left != NULL && snode->left->left->color == 'R')
					snode = LLrotate(snode);
				else if(snode->left->right != NULL && snode->left->right->color == 'R')
					snode = LRrotate(snode);
				else if(snode->left->left != NULL && snode->left->right != NULL && snode->left->left->color == 'B' && snode->left->right->color == 'B'){
					snode->left->left->color == 'R';
					snode->left->right->color == 'R';
				}
			}
			else if(snode->left != NULL && snode->left->color == 'R'){
				Node *temp = snode->left;
				snode->left = temp->right;
				temp->right->parent = snode;
				temp->right = snode;
				snode->parent = temp;
				snode = temp;
			}
		}
			return snode;
		}		
	}
}
