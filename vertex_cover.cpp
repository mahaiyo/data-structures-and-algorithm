#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	int v;
	node *link;
}Node;

void printGraph(Node *[],int);
void vertex_cover(Node *[],int);
int main()
{	
	int V,i,dest;
	printf("enter the number of vertexes in graph\n");
	scanf("%d",&V);
	Node *adj_list[V];
	for(i = 0;i<V;i++)
	{
		Node *last;
		adj_list[i] = (node *)malloc(sizeof(node));
		adj_list[i] = NULL;
		printf("enter edges from  %d(enter -1 for no edges)\n",i);
		while(1)
		{
			scanf("%d",&dest);
			if(dest == -1)
				break;
			Node *temp = (node *)malloc(sizeof(node));
			temp->v = dest;
			temp->link = NULL;
			if(!adj_list[i])
				adj_list[i] = temp;
			else
				last->link = temp;
			last = temp;
		}
	}
	printGraph(adj_list,V);
	printf("vertex cover set\n");
	vertex_cover(adj_list,V);
	return 0;
}

void printGraph(Node *list[],int V)
{
	int i;
	for(i=0;i<V;i++)
	{
		Node *temp = list[i];
		printf("%d-",i);
		while(temp)
		{
			printf("%d-",temp->v);
			temp = temp->link;
		}
		printf("\n");
	}
	
}

void vertex_cover(Node *list[],int V)
{
	int i;
	bool visited[V];
	for(i = 0;i<V;i++)
		visited[i] = false;
	for(i=0;i<V;i++)
	{
		if(!visited[i])
		{
			Node *j = list[i];
			while(j)
			{
				if(!visited[j->v])
				{
					visited[i] = true;
					visited[j->v] = true;
					break;
				}
				j = j->link;
			}
		}
	}
	
	for(i = 0;i<V;i++)
	{
		if(visited[i])
			printf("%d-",i);
	}
}
