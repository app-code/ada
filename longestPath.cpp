/*
 * Longest Path Algorithm 
 * @author :: Bimal Kumar Sah
 */


#include <stdio.h>
#include <stack>
#define INF   999999999
#define NINF -999999999

using namespace std;

/*
 * Adjacency list Node
 * For each node we  maintain a list
 * al is an array of all these list
 */

struct vertex
{
	int x;
	int cost;
	struct vertex *next;
}* al[6] = {NULL};

struct vertex* addAtEnd(struct vertex *root,int v,int cost)
{
	struct vertex *ptr = root;
	struct vertex *vert = new vertex();
	vert->x = v;
	vert->cost = cost;
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

int * topologicalSort()
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

	int *sorted = new int[S.size()];
	int i=0;
	while(!S.empty())
	{
		//printf("%d  ", S.top());
		sorted[i++] = S.top();
		S.pop();
	}

	return sorted;
}

void longestPath()
{

	/*
	 * First Topologically sort the graph
	 * then,for each vertex from sorted graph,
	 -- choose all its neighbor (i.e adjacent) vertex
	 -- and find the maximum dist from source
	 */

	int *sorted = topologicalSort();

	printf("Sorted graph is\n");
	for(int i=0;i<6;i++)
		printf("%d ", sorted[i]);
	printf("\n");


	int dist[6] ;
	for(int i=0;i<6;i++)
		dist[i] = NINF;
	/*
	 * Making source to be reachable in 0
	 * Here source is "1"
	 */
	dist[1] = 0;

	for(int u=0;i<6;u++)
	{
		struct vertex *v = al[i];

		/*
		 * Do following for every adjacent vertex v of u
			-- if (dist[v] < dist[u] + weight(u, v))
			-- dist[v] = dist[u] + weight(u, v)
		 * we will traverse through the list of vertex v
		 */

		while(v)
		{
			if(dist[v->x] < dist[u] + v->cost)
				dist[v->x] = dist[u] + v->cost;
			v = v->next;
		}
	}
	
	for(int i=0;i<6;i++)
		printf("%d\n", dist[i]);
}

int main()
{

	int cost[][6] = {
						{0,5,3,INF,INF,INF},
						{INF,0,2,6,INF,INF},
						{INF,INF,0,7,4,2},
						{INF,INF,INF,0,-1,1},
						{INF,INF,INF,INF,0,-2},
						{INF,INF,INF,INF,INF,0}
	};


	/* 
	 * For each vertex, its all adjacent vertices are entered into the list
	 */

	for(int i=0;i<6;i++)
	{
		for(int j=0;j<6;j++)
		{
			
			if(cost[i][j]!= INF && cost[i][j]!=0)
			{
				al[i] = addAtEnd(al[i],j,cost[i][j]);
			}
			
		}
	}
	/*
	 * For traversing the list of each vertex
	 */
	
	longestPath();
	return 0;
}

