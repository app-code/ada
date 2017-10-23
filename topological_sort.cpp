/*
 * Topological Sorting 
 * @author :: Bimal Kumar Sah
 */


#include <stdio.h>
#include <stack>

using namespace std;

/*
 * Adjacency list Node
 * For each node we  maintain a list
 * al is an array of all these list
 */

struct vertex
{
	int x;
	struct vertex *next;
}* al[6] = {NULL};

struct vertex* addAtEnd(struct vertex *root,int v)
{
	struct vertex *ptr = root;
	struct vertex *vert = new vertex();
	vert->x = v;
	vert->next = NULL;
	if(!root)
		return vert;
	while(ptr->next)
		ptr = ptr->next;
	ptr->next = vert;
	return root;
}

void traverse(struct vertex *root)
{
	if(!root)
	{
		printf("NIL\n");
		return;
	}
	struct vertex *ptr = root;
	while(ptr->next)
	{
		printf("%d-->",ptr->x );
		ptr = ptr->next;
	}
	printf("%d",ptr->x );
	printf("\n");
}

void topo_Util(int i,bool visited[],stack<int> &S)
{
	visited[i] = true;
	struct vertex *vv = al[i];

	/*
	 * While we traverse the entire list for that node,
	 * we keep on calling recursively topo_Util
	 */

	while(vv)
	{
		if(visited[vv->x]==false)
			topo_Util(vv->x,visited,S);
		vv = vv->next;
	}

	/* 
	 * After traversing all its adjacent nodes
	 * ( and adjacent nodes of adjacent nodes )
	 * We push into the stack
	 */
	S.push(i);
}

void topologicalSort()
{
	/* 
	 * First We create a boolean array to keep track of visited nodes
	 * If we get a unvisited node we call topo_Util recurcively such that
	 * all its adjacent nodes and their adjacent are visited.
	 * then we push that node into the stack
	 */
	bool visited[6];
	for (int i = 0; i < 6; ++i)
	{
		visited[i] = false;
	}

	stack <int> S;

	for(int i=0;i<6;i++)
	{
		if(visited[i] == false)
			topo_Util(i,visited,S);
	}

	while(!S.empty())
	{
		printf("%d  ", S.top());
		S.pop();
	}
}

int main()
{

	int cost[][6] = {
						{0,0,0,0,0,0},
						{0,0,0,0,0,0},
						{0,0,0,1,0,0},
						{0,1,0,0,0,0},
						{1,1,0,0,0,0},
						{1,0,1,0,0,0}
	};


	/* 
	 * For each vertex, its all adjacent vertices are entered into the list
	 */

	for(int i=0;i<6;i++)
	{
		for(int j=0;j<6;j++)
		{
			
			if(cost[i][j]==1)
			{
				al[i] = addAtEnd(al[i],j);
			}
			
		}
	}
	/*
	 * For traversing the list of each vertex
	 */

	for(int i=0;i<6;i++)
	{
		traverse(al[i]);
	}

	printf("Topological sorting\n");
	topologicalSort();

	return 0;
}

