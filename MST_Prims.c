#include<stdio.h>
#include<stdlib.h>

# define INF 99999

void MST_PRIMS(int (*E)[9],int (*cost)[7],int n,int (*t)[2])
{

	// E is the set of edges present in the graph.
	// cost is the nxn adjacency matrix.
	// MST is computed and stored in array 't'.

	int minCost=INF,k,l,i,j,near[n],index,min,p;

	// Selecting min-cost edge among all edges.
	for(i=0;i<=8;i++)
	{
		k = E[i][0];
		l = E[i][1];
		if(cost[k-1][l-1] < minCost)
			minCost = cost[k-1][l-1];

	}

	i=0;
	
	// Storing first edge in array 't'.
	t[i][0] = k;
	t[i][1] = l;


	// Calculating near for all vertices. i.e. closest vertex to each vertices among 'k' and 'l'.
	for(j=0;j<n;j++)
	{
		if(cost[j][l-1] < cost[j][k-1])
			near[j] = l;
		else
			near[j] = k;
	}


	// zero for those who are included in 't'.
	near[k-1] = 0;
	near[l-1] = 0;


	// For remaining edges of MST
	for(i=1;i<=n-2;i++)
	{

		// Finding minimum in 'near' array.
		min = INF;
		for(j=0;j<n;j++)
		{
			if(near[j]==0)
				continue;
			if(cost[j][near[j]-1] < min)
			{
				min = cost[j][near[j]-1];
				index = j+1;
			}
		}

		// store the edge that has minimum weight.
		t[i][0] = index;
		t[i][1] = near[index-1];

		minCost += min;

		// newly included vertex in MST is set to zero.
		near[index-1] = 0;

		//for(z=0;z<n;z++)
		//	printf("%d\t",near[z]);
		//printf("\n\n\n");

		//update the 'near' array because newly added vertex may be closer to remaining vertices
		for(p=0;p<n;p++)
		{
			if((near[p]!=0) && (cost[p][near[p]-1] > cost[p][index-1]))
				near[p] = index;
		}
	}

	printf("\nPrinting the edges of MST\n");
	
	for(i=0;i<n-1;i++)
	{
		printf("(%d , %d)\n",t[i][0],t[i][1]);
	}

	printf("\n%d is the Minimum cost of MST using Prim's Algo\n",minCost);
	
}

int main()
{
	printf("%d\n\n\n",size);
	int E[][9] = {{1,2},{2,3},{2,7},{3,4},{4,5},{4,7},{5,6},{5,7},{6,1}};
	int cost[][7] = {{0,28,INF,INF,INF,10,INF},
					{28,0,16,INF,INF,INF,14},
					{INF,16,0,12,INF,INF,INF},
					{INF,INF,12,0,22,INF,18},
					{INF,INF,INF,22,0,25,24},
					{10,INF,INF,INF,25,0,INF},
					{INF,14,INF,18,24,INF,0}};

	int n = 7,t[n-1][2],minCost;
	MST_PRIMS(E,cost,n,t);
}
