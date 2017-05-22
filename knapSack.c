#include<stdio.h>
#include<stdlib.h>


void swap(int *a,int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

int partition(float arr[],int pro[],int w[], int start, int end)
{
	int x,i,j,p,q;
	float temp;
	x = arr[end];
	i = start - 1;
	for(j=start;j<=end-1;j++)
	{
		if(arr[j] <= x)
		{
			i = i+1;
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;

			swap(&pro[i],&pro[j]);
			swap(&w[i],&w[j]);
		}
	}
	
	temp = arr[i+1];
	arr[i+1] = arr[j];
	arr[j] = temp;

	swap(&pro[i+1],&pro[j]);
	swap(&w[i+1],&w[j]);

	return i+1;

}
void quickSort_knapSack(float p_to_w[],int p[],int w[],int start,int end)
{
	int q;
	if(start < end)
	{
		q = partition(p_to_w,p,w,start,end);
		quickSort_knapSack(p_to_w,p,w,start,q-1);
		quickSort_knapSack(p_to_w,p,w,q+1,end);
	}
}

void greedy_knapSack(int profit[],int weight[],int size,int cap)
{
	int i,j;
	float prof_to_wt[size+1],totalP;
	for(i=0;i<=size;i++)
		prof_to_wt[i] = (float)profit[i]/weight[i];

	for(i=0;i<=size;i++)
	{
		printf("%d\t%d\t%.2f\n",profit[i],weight[i],prof_to_wt[i]);
	}
	printf("\n");
	quickSort_knapSack(prof_to_wt,profit,weight,0,size);
	for(i=0;i<=size;i++)
	{
		printf("%d\t%d\t%.2f\n",profit[i],weight[i],prof_to_wt[i]);
	}

	for(j = size;j>=0;j--)
	{
		if(cap > 0 && weight[j] <= cap)
		{
			cap = cap - weight[j];
			totalP += profit[j];
		}
		else
			break;
	}

	if(cap > 0)
		totalP += profit[j]*((float)cap/weight[j]);

	printf("\n%.2f\n",totalP);
	
}

int main()
{
	//int profit[7] = {10,5,15,7,6,18,3};
	//int weight[7] = {2,3,5,7,1,4,1};

	int profit[5] = {2,28,25,18,9};
	int weight[5] = {1,4,5,3,3};
	int capacity = 15;
	greedy_knapSack(profit,weight,4,capacity);
	return 0;
}
