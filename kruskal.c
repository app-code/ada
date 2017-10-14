#include <stdio.h>
#include <stdlib.h>

struct Edge
{
	int src,dest,wt;
};

struct Graph
{
	int V,E;
	struct Edge *edge;
};

struct Graph* createGraph(int V,int E)
{
	struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
	graph->V = V;
	graph->E = E;

	graph->edge = (struct Edge *)malloc(sizeof(struct Edge) * graph->E);

	return graph;
}

struct subset
{
	int parent;
	int rank;
};

// Utility function to find the set of element i
int find(struct subset ss[],int i)
{
	if(ss[i].parent != i)
		ss[i].parent = find(ss,ss[i].parent);
	return ss[i].parent;
}

void Union(struct subset ss[],int x,int y)
{
	int xroot = find(ss,x);
	int yroot = find(ss,y);

	if(ss[xroot].rank < ss[yroot].rank)
		ss[xroot].parent = yroot;
	else if(ss[xroot].rank > ss[yroot].rank)
		ss[yroot].parent = xroot;
	else
	{
		ss[yroot].parent = xroot;
		ss[xroot].rank++;
	}
}

int my_comp(const void* a,const void* b)
{
	struct Edge* al = (struct Edge*)a;
	struct Edge* bl = (struct Edge*)b;

	return al->wt > bl->wt;
}

void MST_KRUSKAL(struct Graph* graph)
{
	int V = graph->V;
	struct Edge result[V];
	int e = 0;
	int i = 0;


	qsort(graph->edge,graph->E,sizeof(graph->edge[0]),my_comp);
	struct subset *ss = (struct subset *)malloc(sizeof(struct subset));

	for(int v = 0;v<V;++v)
	{
		ss[v].parent = v;
		ss[v].rank = 0;
	}

	while(e < V-1)
	{
		struct Edge next_edge = graph->edge[i++];
		int x = find(ss,next_edge.src);
		int y = find(ss,next_edge.dest);

		if(x != y)
		{
			result[e++] = next_edge;
			Union(ss,x,y);
		}
	}

	printf("******Printing the Minimum Spanning Tree*********\n");
	for(int i=0;i<e;i++)
		printf("* (%d, %d) --- %d\t\t\t\t\t*\n", result[i].src,result[i].dest,result[i].wt);
	printf("*************************************************\n");

	return;
}

int main()
{
	int E[][9] = {{1,2},{2,3},{2,7},{3,4},{4,5},{4,7},{5,6},{5,7},{6,1}};
	int cost[9] = {28,16,14,12,22,18,25,24,10};

	int V = 7;
	int N = 9;

	struct Graph *graph = createGraph(V,N);

	for(int i=0;i<N;i++)
	{
		graph->edge[i].src = E[i][0];
		graph->edge[i].dest = E[i][1];
		graph->edge[i].wt = cost[i];
	}

	MST_KRUSKAL(graph);

	return 0;
}