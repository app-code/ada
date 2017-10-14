/*
 * Implemented using Queue
 */


#include <iostream>
#include <stdio.h>
#include <queue>

using namespace std;
#define INF 99999999


int visited[7] = {0};

struct vertex
{
	int x;
	int cost;
	vertex *next;
}* al[7]={NULL};

vertex *addAtEnd(vertex *root,int v,int cost)
{
	vertex *ptr = root;
	vertex *temp = new vertex;
	temp->x = v;
	temp->cost = cost;
	temp->next = NULL;
	if(!root)
		return temp;
	while(ptr->next)
		ptr = ptr->next;
	ptr->next = temp;
	return root;
}

void traverse(struct vertex *root)
{
	struct vertex *ptr = root;
	while(ptr->next)
	{
		printf("(%d, %d)-->",ptr->x,ptr->cost );
		ptr = ptr->next;
	}
	printf("(%d, %d)",ptr->x,ptr->cost );
	printf("\n");
}

void BFS(int v)
{
	visited[v] = 1;
	printf("%d\n",v);
	int u = v;
	vertex *ptr;// = al[v];

	queue <int> Q;
	while(1)
	{
		ptr = al[u];
		while(ptr)
		{
			int w = ptr->x;
			if(visited[w]==0)
			{
				Q.push(w);
				visited[w] = 1;
				printf("%d  ",w );
			}
			ptr = ptr->next;
			
		}
		printf("\n");
		if(Q.empty())
			return;
		u = Q.front();
		Q.pop();
	}
}

int main()
{
	int E[][9] = {{1,2},{2,3},{2,7},{3,4},{4,5},{4,7},{5,6},{5,7},{6,1}};

	int V[7];
	
	//memset(al,NULL,sizeof(al));
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
				al[i] = addAtEnd(al[i],j,cost[i][j]);
			}
		}
	}
	//traverse(al[3]);


	for(int i=0;i<7;i++)
	{
		traverse(al[i]);
	}
	BFS(0);
}