#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INF 99999999


int visited[7] = {0};

struct vertex
{
	int x;
	//int cost;
	struct vertex *next;
}* al[7]={NULL};

struct vertex *addAtEnd(struct vertex *root,int v)
{
	struct vertex *ptr = root;
	struct vertex *new = (struct vertex *)malloc(sizeof(struct vertex));
	new->x = v;
	//new->cost = cost;
	new->next = NULL;
	if(!root)
		return new;
	while(ptr->next)
		ptr = ptr->next;
	ptr->next = new;
	return root;
}

void traverse(struct vertex *root)
{
	struct vertex *ptr = root;
	while(ptr->next)
	{
		printf("%d-->",ptr->x );
		ptr = ptr->next;
	}
	printf("%d",ptr->x );
	printf("\n");
}

void DFS(int v)
{
	visited[v] = 1;
	printf("%d\n", v);
	
	struct vertex *ptr = al[v];
	while(ptr)
	{
		int w = ptr->x;
		if(visited[w]==0)
			DFS(w);
		ptr = ptr->next;
	}
}

int main()
{

	int cost[][7] = {{0,28,INF,INF,INF,10,INF},
					{28,0,16,INF,INF,INF,14},
					{INF,16,0,12,INF,INF,INF},
					{INF,INF,12,0,22,INF,18},
					{INF,INF,INF,22,0,25,24},
					{10,INF,INF,INF,25,0,INF},
					{INF,14,INF,18,24,INF,0}};

	for(int i=0;i<7;i++)
	{
		for(int j=0;j<7;j++)
		{
			if(cost[i][j]!=INF && cost[i][j])
			{
				al[i] = addAtEnd(al[i],j);
			}
		}
	}
	//traverse(al[3]);
	/*

	for(int i=0;i<7;i++)
	{
		traverse(al[i]);
	}
	*/

	/*
	int v;
	printf("Enter the  no of vertices\n");
	scanf("%d",&v);

	int i=0;
	for(i=0;i<v;i++)
	{
		int n;
		printf("Enter no of vetices connect to %d vertex\n",i+1);
		scanf("%d",&n);
		printf("Enter the vertex \n");
		for(int j=0;j<n;j++)
		{
			int u,cost;
			scanf("%d",&u);
			al[i] = addAtEnd(al[i],u);
		}
	}
	*/
	printf("\n\n\n");

	DFS(0);

	return 0;
}