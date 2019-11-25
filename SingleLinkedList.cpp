#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

struct node
{
	int val;
	struct node *next;	
}*start = NULL,*newnode,*current,*temp;


int size = 0;
void create();
void display();
void findMax();
void insert();
void del();
void reverse();
void sizeoflist();


int main()
{
	int ch;
	while(1)
	{
	printf("\n1.Creating a list\n");
	printf("2.Displaying the list\n");
	printf("3.Find max\n");
	printf("4.Insert a node\n");
	printf("5.Delete a node\n");
	printf("6.Reverse the list\n");
	printf("7.Size of list\n");
	printf("enter choice\n");
	scanf("%d",&ch);
	switch(ch)
	{
		case 1:
			create();
			break;
		case 2:
			display();
			break;
		case 3:
			findMax();
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
		case 7:
			sizeoflist();
			break;
		default: printf("wrong choice\n");
	}
	}
	return 0;
}

void create()
{
	int data;
	while(1)
	{
	
	printf("insert the data\n");
	scanf("%d",&data);
	if(data != -1)
	{
		newnode = (struct node*)malloc(sizeof(struct node));
		newnode->val = data;
		if(start == NULL)
		{
			newnode->next = NULL;
			start = newnode;
			size++;
		}
		else
		{
			newnode->next = start;
			start = newnode;
			size++;
		}
	}
	else
	{
		break;
	}
	}
}

void sizeoflist()
{
	printf("size of the list is %d",size);
}

void display()
{
	if(start == NULL)
	{
		printf("list is empty\n");
	}
	else
	{
		current = start;
		printf("the list is \n");
		while(current != NULL)
		{
			printf("%d->",current->val);
			current = current->next;
		}
	}
}

void findMax()
{
	int max = 0;
	current = start;
	if(start == NULL)
	{
		printf("list is empty\n");
	}
	else
	{
		
		while(current->next != NULL)
		{
			if(max<current->val)
			{
				max = current->val;
				current = current->next;
				}
			else
			{
				current = current->next;
				}	
		}
	}
	
	printf("max is : %d",max);
}
void insert()
{
	int data,pos,i;
	current = start;
	printf("enter the data to be inserted\n");
	scanf("%d",&data);
	printf("enter the position to be inserted\n");
	scanf("%d",&pos);
	if(start == NULL)
	{
		newnode = (struct node*)malloc(sizeof(struct node));
		newnode->val = data;
		start = newnode;
		start->next = NULL;
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
	if(pos == 1)
	{
		newnode->next = start;
		start = newnode;
		size++;
	}
	else if(pos == size+1)
	{
		for(i = 1;i<pos;i++)
		{
			if(i == pos-1)
			{
				current->next = newnode;
				current = newnode;
				current->next = NULL;
				size++;
			}
			else
			{
				current = current->next;
			}
		}
	}
	else
	{
		for(i=1;i<pos;i++)
		{
			if(i == pos-1)
			{
				newnode->next = current->next;
				current->next = newnode;
				current = newnode;
				size++;
			}
			else
			{
				current = current->next;
			}
		}
	}
	}
	}
}
 void del()
 {
 	int pos,i;
	current = start;
	printf("enter the position to be deleted\n");
	scanf("%d",&pos);
	newnode = (struct node*)malloc(sizeof(struct node));

	if(pos < 1 || pos >size)
	{
		printf("invalid position\n");
	}
	else
	{
		if(pos == 1)
		{
			newnode = start;
			start = start->next;
			free(newnode);
			size--;
		}
		else if(pos == size)
		{
			for(i=1;i<size;i++)
			{
				if(i != size-1)
				{
					current = current->next;
				}
				else
				{
					newnode = current->next;
					current->next = NULL;
					free(newnode);
					size--;
				}
			}
		}
		else
		{
			for(i=1;i<pos;i++)
			{
				if(i != pos-1)
				{
					current = current->next;
				}
				else
				{
					newnode = current->next;
					current->next = newnode->next;
					newnode->next = NULL;
					free(newnode);
					size--;
				}
			}
		}
	}
 }
 
 void reverse()
 {
 	
 	struct node *prev = NULL,*next = NULL;
 	current = start;
 	if(size == 0)
 	{
 		printf("list is empty\n");
	 }
	 else
	 {
		while(current != NULL)
		{
			next = current->next;
			current->next = prev;
			prev = current;
			current = next;
		}
		start = prev;
	 }
 }

