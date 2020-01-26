#include<iostream>
#include<stdio.h>
using namespace std;
#define INFINITY 9999
#define max 32
#define inf 0
void dijkstra(int G[max][max],int n,int startnode);
int main() {
    int G[max][max] = {
//	  0   1	  2	  3	  4	  5	  6	  7	  8	  9	 10	 11	 12	 13	 14	 15	 16	 17	 18	 19	 20	 21	 22	 23	 24	 25	 26	 27	 28	 29	 30	 31
    {inf,5,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,5},//0
	{5,inf,3,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf},//1
	{inf,3,inf,1,1,3,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf},//2
	{inf,inf,1,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf},//3
	{inf,inf,1,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf},//4
	{inf,inf,3,inf,inf,inf,1,3,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,12,inf,inf,inf,inf,inf},//5
	{inf,inf,inf,inf,inf,1,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf},//6
	{inf,inf,inf,inf,inf,3,inf,inf,1,1,3,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf},//7
	{inf,inf,inf,inf,inf,inf,inf,1,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf},//8
	{inf,inf,inf,inf,inf,inf,inf,1,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf},//9
	{inf,inf,inf,inf,inf,inf,inf,3,inf,inf,inf,1,3,inf,inf,inf,inf,inf,inf,inf,inf,15,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf},//10
	{inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,1,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf},//11
	{inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,3,inf,inf,1,1,3,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf},//12
	{inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,1,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf},//13
	{inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,1,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf},//14
	{inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,3,inf,inf,inf,10,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf},//15
	{inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,10,inf,10,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf},//16
	{inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,10,inf,3,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf},//17
	{inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,3,inf,1,1,3,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf},//18
	{inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,1,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf},//19
	{inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,1,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf},//20
	{inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,15,inf,inf,inf,inf,inf,inf,inf,3,inf,inf,inf,1,3,inf,inf,inf,inf,inf,inf,inf,inf},//21
	{inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,1,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf},//22
	{inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,3,inf,inf,1,1,3,inf,inf,inf,inf,inf},//23
	{inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,1,inf,inf,inf,inf,inf,inf,inf,inf},//24
	{inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,1,inf,inf,inf,inf,inf,inf,inf,inf},//25
	{inf,inf,inf,inf,inf,12,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,3,inf,inf,inf,1,3,inf,inf,inf},//26
	{inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,1,inf,inf,inf,inf,inf},//27
	{inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,3,inf,inf,1,1,3},//28
	{inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,1,inf,inf,inf},//29
	{inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,1,inf,inf,inf},//30
	{5,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,3,inf,inf,inf}};//31
   int n=32;
   int u=0;
   dijkstra(G,n,u);
   return 0;
}
void dijkstra(int G[max][max],int n,int startnode) {
   int cost[max][max],distance[max],pred[max];
   int visited[max],count,mindistance,nextnode,i,j;
   for(i=0;i<n;i++)
      for(j=0;j<n;j++)
   if(G[i][j]==0)
      cost[i][j]=INFINITY;
   else
      cost[i][j]=G[i][j];
   for(i=0;i<n;i++) {
      distance[i]=cost[startnode][i];
      pred[i]=startnode;
      visited[i]=0;
   }
   distance[startnode]=0;
   visited[startnode]=1;
   count=1;
   while(count<n-1) {
      mindistance=INFINITY;
      for(i=0;i<n;i++)
         if(distance[i]<mindistance&&!visited[i]) {
         mindistance=distance[i];
         nextnode=i;
      }
      visited[nextnode]=1;
      for(i=0;i<n;i++)
         if(!visited[i])
      if(mindistance+cost[nextnode][i]<distance[i]) {
         distance[i]=mindistance+cost[nextnode][i];
         pred[i]=nextnode;
      }
      count++;
   }
   for(i=0;i<n;i++)
   if(i!=startnode) {
      cout<<"\nDistance of node"<<i<<"="<<distance[i];
      cout<<"\nPath="<<i;
      j=i;
      do {
         j=pred[j];
         cout<<"<-"<<j;
      }while(j!=startnode);
   }
}
