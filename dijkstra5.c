#include<stdio.h>
#define inf 0
#define max 15
#define infi 9999
/* ----------------------------CHANGE THESE CONFIGURATION----------------------------------*/
int n = 15;							//total node count and initial node
int u = 0;
char face = 'w';					//direction variables which include directions w,n,e,s
char fdir = 'n';
int house_config[5] = {1,0,0,1,0};
int house_req[5] = {2,2,2,1,2};
int which_material[10] = {3,11,9,5,4,7,1,0,2,8};
int block_placed[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
int dis[15];
int pre[15];
int movement_array[15][4] = {
	{inf,14,inf,1},
	{2,0,inf,inf},
	{3,inf,1,inf},
	{4,12,2,inf},
	{5,inf,3,inf},
	{6,10,4,inf},
	{7,inf,5,inf},
	{inf,8,6,inf},
	{inf,inf,9,7},
	{8,inf,10,inf},
	{9,inf,11,5},
	{10,inf,12,inf},
	{11,inf,13,3},
	{12,inf,14,inf},
	{13,inf,inf,0}
};
/* ----------------------------DIJKSTRA----------------------------------*/

#define wf 6
#define zz 6
#define in 8
void reverse(int a[],int n)
{
    int l=n-1;
    int i=0;
    while(i<=l)
    {
        int temp;
        temp=a[i];
        a[i]=a[l];
        a[l]=temp;
        i++;
        l--;
    }
}
int G[15][15] = {
	// 0  1	  2   3   4	  5	  6	  7	  8	  9	 10	 11	 12	 13	 14
	{inf,2,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,2},//0
	{2,inf,1,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf},//1
	{inf,1,inf,1,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf},//2
	{inf,inf,1,inf,1,inf,inf,inf,inf,inf,inf,inf,wf,inf,inf},//3
	{inf,inf,inf,1,inf,1,inf,inf,inf,inf,inf,inf,inf,inf,inf},//4
	{inf,inf,inf,inf,1,inf,1,inf,inf,inf,zz,inf,inf,inf,inf},//5
	{inf,inf,inf,inf,inf,1,inf,1,inf,inf,inf,inf,inf,inf,inf},//6
	{inf,inf,inf,inf,inf,inf,1,inf,in,inf,inf,inf,inf,inf,inf},//7
	{inf,inf,inf,inf,inf,inf,inf,in,inf,1,inf,inf,inf,inf,inf},//8
	{inf,inf,inf,inf,inf,inf,inf,inf,1,inf,1,inf,inf,inf,inf},//9
	{inf,inf,inf,inf,inf,zz,inf,inf,inf,1,inf,1,inf,inf,inf},//10
	{inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,1,inf,1,inf,inf},//11
	{inf,inf,inf,wf,inf,inf,inf,inf,inf,inf,inf,1,inf,1,inf},//12
	{inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,1,inf,1},//13
	{2,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,1,inf}//14
};
void dijkstra(int G[15][15], int n, int startnode) {
	int cost[15][15], distance[15], pred[15];					//initialising cost, distance and perd arrays
	int visited[15], count, mindistance, nextnode, i, j;
	for (i = 0; i < n; i++)										//generating cost matrix
	for (j = 0; j < n; j++)
	if (G[i][j] == 0)
	cost[i][j] = infi;
	else
	cost[i][j] = G[i][j];
	for (i = 0; i < n; i++) {									//for loop to initialise visited array
		distance[i] = cost[startnode][i];
		pred[i] = startnode;
		visited[i] = 0;
	}
	distance[startnode] = 0;
	visited[startnode] = 1;
	count = 1;
	while (count < n - 1) {										//main while loop which calculates the distance using dijkstra algorithm
		mindistance = infi;
		for (i = 0; i < n; i++)
		if (distance[i] < mindistance && !visited[i]) {
			mindistance = distance[i];
			nextnode = i;
		}
		visited[nextnode] = 1;
		for (i = 0; i < n; i++)
		if (!visited[i])
		if (mindistance + cost[nextnode][i] < distance[i]) {
			distance[i] = mindistance + cost[nextnode][i];
			pred[i] = nextnode;
		}
		count++;
	}
	for (i = 0; i < n; i++)									//generating dis and pre arrays from distance and pred
	{
		dis[i] = distance[i];
	}
	for (i = 0; i < n; i++)
	{
		pre[i] = pred[i];
	}
}
void dist_comp(int x, int y, int path[], int *index)
{
	if (dis[x] <= dis[y])
	{
		if (u != x)
		{
			int j = x;
			path[*index] = x;
			*index = *index + 1;
			do {
				j = pre[j];
				path[*index] = j;
				*index = *index + 1;
			} while (j != u);
		}
		reverse(path, *index);
		u = x;

	}
	else
	{
		if (u != y)
		{
			int j = y;
			path[*index] = y;
			*index = *index + 1;
			do {
				j = pre[j];
				path[*index] = j;
				*index = *index + 1;
			} while (j != u);
		}
		reverse(path, *index);
		u = y;

	}
}
void traverse(int path[], int u, int *size)
{
	int ps = *size;
	for (int i = 0; i < ps - 1; i++)
	{
		if ((path[i] == 0 && path[i + 1] == 1) || (path[i] == 0 && path[i + 1] == 14))
		{
			for (int a = 0; a < 4; a++)
			{
				if (movement_array[path[i]][a] == path[i + 1])
				{
				    printf("Forward(2,1)\n");
					if (a == 0)
					{
						fdir = 'n';
					}
					else if (a == 1)
					{
						fdir = 'e';
					}
					else if (a == 2)
					{
						fdir = 's';
					}
					else if (a == 3)
					{
						fdir = 'w';
					}
				}
			}
			if (face == 'n' && fdir == 'n')
			{
				printf("Forward\n");
				face = fdir;

				printf("%c\n",face);
			}
			else if (face == 'n' && fdir == 'e')
			{
				printf("Right\n");
				printf("Forward\n");
				face = fdir;

				printf("%c\n",face);
			}
			else if (face == 'n' && fdir == 's')
			{
				printf("Right\n");
				printf("Right\n");
				printf("Forward\n");
				face = fdir;

				printf("%c\n",face);
			}
			else if (face == 'n' && fdir == 'w')
			{
				printf("Left\n");
				printf("Forward\n");
				face = fdir;

				printf("%c\n",face);
			}
			else if (face == 'e' && fdir == 'e')
			{
				printf("Forward\n");
				face = fdir;

				printf("%c\n",face);
			}
			else if (face == 'e' && fdir == 's')
			{
				printf("Right\n");
				printf("Forward\n");
				face = fdir;

				printf("%c\n",face);
			}
			else if (face == 'e' && fdir == 'w')
			{
				printf("Right\n");
				printf("Right\n");
				printf("Forward\n");
				face = fdir;

				printf("%c\n",face);
			}
			else if (face == 'e' && fdir == 'n')
			{
				printf("Left\n");
				printf("Forward\n");
				face = fdir;

				printf("%c\n",face);
			}
			else if (face == 's' && fdir == 's')
			{
				printf("Forward\n");
				face = fdir;

				printf("%c\n",face);
			}
			else if (face == 's' && fdir == 'w')
			{
				printf("Right\n");
				printf("Forward\n");
				face = fdir;

				printf("%c\n",face);
			}
			else if (face == 's' && fdir == 'n')
			{
				printf("Right\n");
				printf("Right\n");
				printf("Forward\n");
				face = fdir;

				printf("%c\n",face);
			}
			else if (face == 's' && fdir == 'e')
			{
				printf("Left\n");
				printf("Forward\n");
				face = fdir;

				printf("%c\n",face);
			}
			else if (face == 'w' && fdir == 'w')
			{
				printf("Forward\n");
				face = fdir;

				printf("%c\n",face);
			}
			else if (face == 'w' && fdir == 'n')
			{
				printf("Right\n");
				printf("Forward\n");
				face = fdir;

				printf("%c\n",face);
			}
			else if (face == 'w' && fdir == 'e')
			{
				printf("Right\n");
				printf("Right\n");
				printf("Forward\n");
				face = fdir;

				printf("%c\n",face);
			}
			else if (face == 'w' && fdir == 's')
			{
				printf("Left\n");
				printf("Forward\n");
				face = fdir;

				printf("%c\n",face);
			}
		}
		else
		{
			for (int a = 0; a < 4; a++)
			{
				if (movement_array[path[i]][a] == path[i + 1])
				{
				    printf("Else\n");
					if (a == 0)
					{
						fdir = 'n';
					}
					else if (a == 1)
					{
						fdir = 'e';
					}
					else if (a == 2)
					{
						fdir = 's';
					}
					else if (a == 3)
					{
						fdir = 'w';
					}
				}
			}
			if (face == 'n' && fdir == 'n')
			{
				printf("Forward\n");
				face = fdir;

				printf("%c\n",face);
			}
			else if (face == 'n' && fdir == 'e')
			{
				printf("Right\n");
				printf("Forward\n");
				face = fdir;

				printf("%c\n",face);
			}
			else if (face == 'n' && fdir == 's')
			{
				printf("Right\n");
				printf("Right\n");
				printf("Forward\n");
				face = fdir;

				printf("%c\n",face);
			}
			else if (face == 'n' && fdir == 'w')
			{
				printf("Left\n");
				printf("Forward\n");
				face = fdir;

				printf("%c\n",face);
			}
			else if (face == 'e' && fdir == 'e')
			{
				printf("Forward\n");
				face = fdir;

				printf("%c\n",face);
			}
			else if (face == 'e' && fdir == 's')
			{
				printf("Right\n");
				printf("Forward\n");
				face = fdir;

				printf("%c\n",face);
			}
			else if (face == 'e' && fdir == 'w')
			{
				printf("Right\n");
				printf("Right\n");
				printf("Forward\n");
				face = fdir;

				printf("%c\n",face);
			}
			else if (face == 'e' && fdir == 'n')
			{
				printf("Left\n");
				printf("Forward\n");
				face = fdir;

				printf("%c\n",face);
			}
			else if (face == 's' && fdir == 's')
			{
				printf("Forward\n");
				face = fdir;

				printf("%c\n",face);
			}
			else if (face == 's' && fdir == 'w')
			{
				printf("Right\n");
				printf("Forward\n");
				face = fdir;

				printf("%c\n",face);
			}
			else if (face == 's' && fdir == 'n')
			{
				printf("Right\n");
				printf("Right\n");
				printf("Forward\n");
				face = fdir;

				printf("%c\n",face);
			}
			else if (face == 's' && fdir == 'e')
			{
				printf("Left\n");
				printf("Forward\n");
				face = fdir;

				printf("%c\n",face);
			}
			else if (face == 'w' && fdir == 'w')
			{
				printf("Forward\n");
				face = fdir;

				printf("%c\n",face);
			}
			else if (face == 'w' && fdir == 'n')
			{
				printf("Right\n");
				printf("Forward\n");
				face = fdir;

				printf("%c\n",face);
			}
			else if (face == 'w' && fdir == 'e')
			{
				printf("Right\n");
				printf("Right\n");
				printf("Forward\n");
				face = fdir;

				printf("%c\n",face);
			}
			else if (face == 'w' && fdir == 's')
			{
				printf("Left\n");
				printf("Forward\n");
				face = fdir;

				printf("%c\n",face);
			}

		}
	}
}
void block_traverse()
{
    printf("BlockTraverse \n");
	if (face == 'n' && fdir == 'n')
	{
	    printf("1sa\n");
		face = fdir;

		printf("%c\n",face);
	}
	else if (face == 'n' && fdir == 'e')
	{
	    printf("2sa\n");
		printf("Right\n");
		face = fdir;

		printf("%c\n",face);
	}
	else if (face == 'n' && fdir == 's')
	{
	    printf("3sa\n");
		printf("Right\n");
		printf("Rightbwall\n");
		face = fdir;
	}
	else if (face == 'n' && fdir == 'w')
	{
	    printf("4sa\n");
		printf("Left\n");
		face = fdir;

		printf("%c\n",face);
	}
	else if (face == 'e' && fdir == 'e')
	{
	    printf("5sa\n");
		face = fdir;

		printf("%c\n",face);
	}
	else if (face == 'e' && fdir == 's')
	{
	    printf("6sa\n");
		printf("Right\n");
		face = fdir;

		printf("%c\n",face);
	}
	else if (face == 'e' && fdir == 'w')
	{
	    printf("7sa\n");
		printf("Right\n");
		printf("Rightbwall\n");
		face = fdir;

		printf("%c\n",face);
	}
	else if (face == 'e' && fdir == 'n')
	{
	    printf("8sa\n");
		printf("Left\n");
		face = fdir;

		printf("%c\n",face);
	}
	else if (face == 's' && fdir == 's')
	{
	    printf("8sa\n");
		face = fdir;

		printf("%c\n",face);
	}
	else if (face == 's' && fdir == 'w')
	{
	    printf("11sa\n");
		printf("Right\n");
		face = fdir;

		printf("%c\n",face);
	}
	else if (face == 's' && fdir == 'n')
	{
	    printf("8sa\n");
		printf("Right\n");
		printf("Rightbwall\n");
		face = fdir;

		printf("%c\n",face);
	}
	else if (face == 's' && fdir == 'e')
	{
	    printf("8sa\n");
		printf("Left\n");
		face = fdir;

		printf("%c\n",face);
	}
	else if (face == 'w' && fdir == 'w')
	{
	    printf("8sa\n");
		face = fdir;

		printf("%c\n",face);
	}
	else if (face == 'w' && fdir == 'n')
	{
	    printf("22sa\n");
		printf("Right\n");
		face = fdir;

		printf("%c\n",face);
	}
	else if (face == 'w' && fdir == 'e')
	{
	    printf("23sa\n");
		printf("Right\n");
		printf("Rightbwall\n");
		face = fdir;

		printf("%c\n",face);
	}
	else if (face == 'w' && fdir == 's')
	{
	    printf("8sa\n");
		printf("Left\n");
		face = fdir;

		printf("%c\n",face);
	}
}
void block_choose(int bnode,int block_placed[])
{
    printf(" face = %c\n",face);
	if (bnode == 2)
	{
		if (block_placed[0] == 0)
		{
		    printf("Block 1\n");
			fdir = 'w';
			block_traverse();
			block_placed[0] = 1;
			printf("Back\n");

			printf("Stop\n");

		}
		else if (block_placed[1] == 0)
		{
		    printf("Block 2\n");
			fdir = 'e';
			block_traverse(face,fdir);
			block_placed[1] = 1;
			printf("Back\n");

			printf("Stop\n");

		}
	}
	else if (bnode == 13)
	{
		if (block_placed[2] == 0)
		{
		    printf("Block 3\n");
			fdir = 'w';
			block_traverse(face,fdir);
			block_placed[2] = 1;
			printf("Back\n");

			printf("Stop\n");

		}
		else if (block_placed[3] == 0)
		{
		    printf("Block 4\n");
			fdir = 'e';
			block_traverse(face,fdir);
			block_placed[3] = 1;
			printf("Back\n");

			printf("Stop\n");

		}
	}
	else if (bnode == 4)
	{
		if (block_placed[4] == 0)
		{
		    printf("Block 5\n");
			fdir = 'w';
			block_traverse(face,fdir);
			block_placed[4] = 1;
			printf("Back\n");

			printf("Stop\n");

		}
		else if (block_placed[5] == 0)
		{
		    printf("Block 6\n");
			fdir = 'e';
			block_traverse(face,fdir);
			block_placed[5] = 1;
			printf("Back\n");

			printf("Stop\n");

		}
	}
	else if (bnode == 11)
	{
		if (block_placed[6] == 0)
		{
		    printf("Block 7\n");
			fdir = 'w';
			block_traverse(face,fdir);
			block_placed[6] = 1;
			printf("Back\n");

			printf("Stop\n");

		}
		else if (block_placed[7] == 0)
		{
		    printf("Block 8\n");
			fdir = 'e';
			block_traverse(face,fdir);
			block_placed[7] = 1;
			printf("Back\n");

			printf("Stop\n");

		}
	}
	else if (bnode == 6)
	{
		if (block_placed[8] == 0)
		{
		    printf("Block 9\n");
			fdir = 'w';
			block_traverse(face,fdir);
			block_placed[8] = 1;
			printf("Back\n");

			printf("Stop\n");

		}
		else if (block_placed[9] == 0)
		{
		    printf("Block 10\n");
			fdir = 'e';
			block_traverse(face,fdir);
			block_placed[9] = 1;
			printf("Back\n");

			printf("Stop\n");

		}
	}
	else if (bnode == 9)
	{
		if (block_placed[10] == 0)
		{
		    printf("Block 11\n");
			fdir = 'w';
			block_traverse(face,fdir);
			block_placed[10] = 1;
			printf("Back\n");

			printf("Stop\n");

		}
		else if (block_placed[11] == 0)
		{
		    printf("Block 12\n");
			fdir = 'e';
			block_traverse(face,fdir);
			block_placed[11] = 1;
			printf("Back\n");

			printf("Stop\n");

		}
	}
}
int main()
{
    dijkstra(G,n,u);
    int len = 0;
    int *path = (int*)malloc(80);
    dist_comp(2,2,path,&len);
    for(int i = 0;i<len;i++)
    {
        printf("%d \n",path[i]);
    }
    face = 's';
    traverse(path,u,&len);
    int bnode = 2;
    block_choose(bnode,block_placed);
    printf("Pick");
    u=2;
    free(path);
    len=0;
    dijkstra(G,n,u);
    dist_comp(11,11,path,&len);
    for(int i = 0;i<len;i++)
    {
        printf("%d \n",path[i]);
    }
    traverse(path,u,&len);
    return 0;
}
