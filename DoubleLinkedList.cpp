#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

struct node
{
	int val;
	struct node *prev,*next;
}*head,*tail,*newnode,*temp;

int size;

void create();
void trafor();
void traback();
void insert();
void del();
void reverse();

int main()
{
	int ch;
	while(1)
	{
		printf("\n1.Create list\n");
		printf("2.Traverse the list forward\n");
		printf("3.Traverse the list backward\n");
		printf("4.Insert at a position\n");
		printf("5.Delete from a position\n");
		printf("6.Reverse the list\n");
		printf("Enter choice\n");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				create();
				break;
			case 2:
				trafor();
				break;
			case 3:
				traback();
				break;
			case 4:
				insert();
				break;
			case 5:
				del();
				break;
			case 6:
				reverse();
				break;
			default:
				printf("invalid choice\n");
				
		}
		
	}
}

void create()
{
	int data;
	while(1)
	{
		printf("Enter the data\n");
		scanf("%d",&data);
		if(data != -1)
		{
			newnode = (struct node*)malloc(sizeof(struct node));
			newnode->val = data;
			if(head == NULL)
			{
				head = newnode;
				head->next = NULL;
				head->prev = NULL;
				tail = head;
				size++;
			}
			else
			{
				newnode->next = head;
				newnode->prev = NULL;
				head->prev = newnode;
				head = newnode;
				size++;
			}
		}
		else
		{
			break;
		}
	}
}

void trafor()
{
	temp = head;
	if(size ==0)
	{
		printf("list is empty\n");
	}
	else
	{
		while(temp != NULL)
		{
			printf("<-%d->",temp->val);
			temp = temp->next;
		}
	}
}

void traback()
{
	temp = tail;
	if(size == 0)
	{
		printf("list is empty\n");
	}
	else
	{
		while(temp != NULL)
		{
			printf("<-%d->",temp->val);
			temp = temp->prev;
		}
	}
}

void insert()
{
	int data,pos,i;
	temp = head;
	printf("enter the data to be inserted\n");
	scanf("%d",&data);
	printf("enter where position to be inserted\n");
	scanf("%d",&pos);
	if(size == 0)
	{
		newnode = (struct node*)malloc(sizeof(struct node));
		newnode->val = data;
		head = newnode;
		head->next = NULL;
		head->prev = NULL;
		tail = head;
		size++;
		
	}
	else
	{
	if(pos < 1 || pos >size+1)
	{
		printf("invalid position\n");
	}
	else
	{
	newnode = (struct node*)malloc(sizeof(struct node));
	newnode->val = data;
	newnode->next = NULL;
	newnode->prev = NULL;
	if(pos == 1)
	{
		newnode->next = head;
		head = newnode;
		size++;
	}
	else if(pos == size+1)
	{
		newnode->prev = tail;
		tail->next = newnode;
		tail = newnode;
		size++;
	}
	else
	{
		for(i=1;i<pos;i++)
		{
			if(i == pos-1)
			{
				newnode->next = temp->next;
				newnode->prev = temp;
				(temp->next)->prev = newnode;
				temp->next = newnode;
				temp = newnode;
				size++;
			}
			else
			{
				temp = temp->next;
			}
		}
	}
	}
	}
}

void del()
{
	int pos,i;
	temp = head;
	if(size == 0)
	{
		printf("list is empty\n");
	}
	else
	{
		printf("Enter the position to be deleted\n");
		scanf("%d",&pos);
		if(pos<1 || pos>size)
		{
			printf("invalid position\n");
		}
		else
		{
			if(pos == 1)
			{
				newnode = head;
				head = head->next;
				newnode->next = NULL;
				free(newnode);
				size--;
			}
			else if(pos == size)
			{
				newnode = tail;
				tail = tail->prev;
				tail->next = NULL;
				newnode->prev = NULL;
				free(newnode);
				size--;
			}
			else
			{
			for(i=1;i<pos;i++)
			{
				if(i != pos-1)
				{
					temp = temp->next;
				}
				else
				{
					newnode = temp->next;
					temp->next = newnode->next;
					(newnode->next)->prev = temp;
					newnode->next = NULL;
					newnode->prev = NULL;
					free(newnode);
					size--;
				}
			}
			}
		}
	}
}

void reverse()
{
	temp = head;
	while(temp != NULL)
	{
		newnode = temp->next;
		temp->next = temp->prev;
		temp->prev = newnode;
		temp = newnode;
	}
	newnode = head;
	head = tail;
	tail = newnode;
}



