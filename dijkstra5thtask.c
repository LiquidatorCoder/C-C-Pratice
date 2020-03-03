#define F_CPU 14745600
#include <stdlib.h>
#include <stdio.h>
#define inf 0
#define max 15
#define infi 9999

void m_place_lr ()
{
    printf("MPLACE LR\n");
}
void m_place_hr ()
{
    printf("MPLACE HR\n");
}
void s_place_lr ()
{
    printf("SPLACE LR\n");
}
void s_place_hr ()
{
    printf("SPLACE HR\n");
}
void forward_wls(int a, int b)
{
    printf("Forward %d , %d \n",a,b);
}
void lcd_cursor(int a, int b)
{
    //printf("LCD CURSOR %d , %d \n",a,b);
}
void lcd_wr_char(char c)
{
    printf("Direction -- %c\n",c);
}
void right_turn_wls()
{
    printf("Right\n");
}
void right_turn_wls_bwall()
{
    printf("Right before wall\n");
}
void right_turn_inv()
{
    printf("Right inv\n");
}
void left_turn_wls()
{
    printf("Left\n");
}
void left_turn_wls_bwall()
{
    printf("Left before wall\n");
}
void left_turn_inv()
{
    printf("Left inv\n");
}
void back()
{
    printf("Back\n");
}
void _delay_ms(int time)
{
    printf("Delay %d\n",time);
}
void stop()
{
    printf("Stop\n");
}
void init_devices()
{
    //printf("INIT\n");
}
void lcd_print()
{
    //printf("LCD PRINT\n");
}
void lcd_init()
{
    //printf("LCD INIT\n");
}
void m_pick()
{
    printf("MPICK\n");
}
void s_pick()
{
    printf("SPICK\n");
}
int n = 15;							//total node count and initial node
int u = 0;
char face = 'w';					//direction variables which include directions w,n,e,s
char fdir = 'n';
int house_config[5] = {0,1,1,0,0};
int house_req[5] = {2,2,2,2,2};
int which_material[10] = {9,11,5,4,12,7,1,3,2,8};
//int which_material[10] = {-,-,-,-,-,0,-,-,-,-};
int dis[15];
int pre[15];
int b1n = 2;
int b2n = 2;
int b3n = 13;
int b4n = 13;
int b5n = 4;
int b6n = 4;
int b7n = 11;
int b8n = 11;
int b9n = 6;
int b10n = 6;
int b11n = 9;
int b12n = 9;

int h1n = 3;
int h2n = 12;
int h3n = 5;
int h4n = 10;
int h51 = 7;
int h52 = 8;

int block_placed[12] = {0,0,0,0,0,0,0,0,0,0,0,0};

unsigned char ADC_Value, adc_reading;
unsigned char sharp, distance, wall; //ADC Output from Sharp sensor
unsigned int value;
unsigned char base = 230; //base velocity of motor
unsigned char turn = 185; //turn velocity of motor
unsigned char soft = 205; //soft turn velocity of motor
unsigned char ls, ms, rs; //ADC Output from line sensors
unsigned long int ShaftCountLeft = 0; //to keep track of left position encoder
unsigned long int ShaftCountRight = 0; //to keep track of right position encoder
unsigned int Degrees; //to accept angle in degrees for turning

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
int check_block(int block)
{
    int i;
    for(i = 0; i <10; i++)
    {
        if(which_material[i] == block)
            return 1;
    }
    return 0;
}
int G[15][15] = {
	// 0  1	  2   3   4	  5	  6	  7	  8	  9	 10	 11	 12	 13	 14
	{inf,4,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,4},//0
	{4,inf,1,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf},//1
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
	{4,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,inf,1,inf}//14
};

//n,e,s,w
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

/*
*
* Function Name: dijkstra
* Input: adjacency matrix, total nodes, initial node
* Output: void
* Logic: calculates the minimum distance between the initial node and every other node using weights stored in adjacency matrix
* Example Call: dijkstra(G, 32, 4); //calculates minimum distance between the 4th node and every other node based on the weights given in adjacency matrix
*
*/
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

int which_node(int block)
{
	if (block == 1) return b1n;
	else if (block == 2) return b2n;
	else if (block == 3) return b3n;
	else if (block == 4) return b4n;
	else if (block == 5) return b5n;
	else if (block == 6) return b6n;
	else if (block == 7) return b7n;
	else if (block == 8) return b8n;
	else if (block == 9) return b9n;
	else if (block == 10) return b10n;
	else if (block == 11) return b11n;
	else if (block == 12) return b12n;
	return -1;
}

int which_block(int node)
{
	if ((node == b1n) && (face == 'w')) return 1;
	else if ((node == b2n) && (face == 'e')) return 2;
	else if ((node == b3n) && (face == 'w')) return 3;
	else if ((node == b4n) && (face == 'e')) return 4;
	else if ((node == b5n) && (face == 'w')) return 5;
	else if ((node == b6n) && (face == 'e')) return 6;
	else if ((node == b7n) && (face == 'w')) return 7;
	else if ((node == b8n) && (face == 'e')) return 8;
	else if ((node == b9n) && (face == 'w')) return 9;
	else if ((node == b10n) && (face == 'e')) return 10;
	else if ((node == b11n) && (face == 'w')) return 11;
	else if ((node == b12n) && (face == 'e')) return 12;
	return -1;
}

int which_house(int house)
{
	if (house == 1) return h1n;
	else if (house == 2) return h2n;
	else if (house == 3) return h3n;
	else if (house == 4) return h4n;
	return -1;
}

/*
*
* Function Name: traverse
* Input: array, current face direction, initial node
* Output: void
* Logic: uses direction knowledge and the distance array generated by dijkstra to traverse to any node from the current node through shortest path
* Example Call: traverse(path,n,12); //uses direction knowledge and the distance array generated by dijkstra to traverse to any node from the current node through shortest path
*
*/
void traverse(int path[], int u, int *size)
{
	int ps = *size;
	for (int i = 0; i < ps - 1; i++)
	{
		if (((path[i] == 0 && path[i + 1] == 1) || (path[i] == 0 && path[i + 1] == 14)) || ((path[i] == 9 && path[i + 1] == 8) || (path[i] == 6 && path[i + 1] == 7)) || ((path[i] == 13 && path[i + 1] == 14) || (path[i] == 2 && path[i + 1] == 1)) || ((path[i] == 14 && path[i + 1] == 0) || (path[i] == 1 && path[i + 1] == 0)))
		{
			for (int a = 0; a < 4; a++)
			{
				if (movement_array[path[i]][a] == path[i + 1])
				{
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
			    printf("t 1\n");
				forward_wls(2,1);
				face = fdir;
				lcd_cursor(2, 7);
				lcd_wr_char(face);
			}
			else if (face == 'n' && fdir == 'e')
			{
			    printf("t 2\n");
				right_turn_wls();
				forward_wls(2,1);
				face = fdir;
				lcd_cursor(2, 7);
				lcd_wr_char(face);
			}
			else if (face == 'n' && fdir == 's')
			{
			    printf("t 3\n");
				right_turn_wls();
				right_turn_wls();
				forward_wls(2,1);
				face = fdir;
				lcd_cursor(2, 7);
				lcd_wr_char(face);
			}
			else if (face == 'n' && fdir == 'w')
			{
			    printf("t 4\n");
				left_turn_wls();
				forward_wls(2,1);
				face = fdir;
				lcd_cursor(2, 7);
				lcd_wr_char(face);
			}
			else if (face == 'e' && fdir == 'e')
			{
			    printf("t 5\n");
				forward_wls(2,1);
				face = fdir;
				lcd_cursor(2, 7);
				lcd_wr_char(face);
			}
			else if (face == 'e' && fdir == 's')
			{
			    printf("t 6\n");
				right_turn_wls();
				forward_wls(2,1);
				face = fdir;
				lcd_cursor(2, 7);
				lcd_wr_char(face);
			}
			else if (face == 'e' && fdir == 'w')
			{
			    printf("t 7\n");
				right_turn_wls();
				right_turn_wls();
				forward_wls(2,1);
				face = fdir;
				lcd_cursor(2, 7);
				lcd_wr_char(face);
			}
			else if (face == 'e' && fdir == 'n')
			{
			    printf("t 8\n");
				left_turn_wls();
				forward_wls(2,1);
				face = fdir;
				lcd_cursor(2, 7);
				lcd_wr_char(face);
			}
			else if (face == 's' && fdir == 's')
			{
			    printf("t 9\n");
				forward_wls(2,1);
				face = fdir;
				lcd_cursor(2, 7);
				lcd_wr_char(face);
			}
			else if (face == 's' && fdir == 'w')
			{
			    printf("t 10\n");
				right_turn_wls();
				forward_wls(2,1);
				face = fdir;
				lcd_cursor(2, 7);
				lcd_wr_char(face);
			}
			else if (face == 's' && fdir == 'n')
			{
			    printf("t 11\n");
				right_turn_wls();
				right_turn_wls();
				forward_wls(2,1);
				face = fdir;
				lcd_cursor(2, 7);
				lcd_wr_char(face);
			}
			else if (face == 's' && fdir == 'e')
			{
			    printf("t 12\n");
				left_turn_wls();
				forward_wls(2,1);
				face = fdir;
				lcd_cursor(2, 7);
				lcd_wr_char(face);
			}
			else if (face == 'w' && fdir == 'w')
			{
			    printf("t 13\n");
				forward_wls(2,1);
				face = fdir;
				lcd_cursor(2, 7);
				lcd_wr_char(face);
			}
			else if (face == 'w' && fdir == 'n')
			{
			    printf("t 14\n");
				right_turn_wls();
				forward_wls(2,1);
				face = fdir;
				lcd_cursor(2, 7);
				lcd_wr_char(face);
			}
			else if (face == 'w' && fdir == 'e')
			{
			    printf("t 15\n");
				right_turn_wls();
				right_turn_wls();
				forward_wls(2,1);
				face = fdir;
				lcd_cursor(2, 7);
				lcd_wr_char(face);
			}
			else if (face == 'w' && fdir == 's')
			{
			    printf("t 16\n");
				left_turn_wls();
				forward_wls(2,1);
				face = fdir;
				lcd_cursor(2, 7);
				lcd_wr_char(face);
			}
		}
		else if ((path[i] == 3 && path[i + 1] == 12) || (path[i] == 12 && path[i + 1] == 3))
		{
			for (int a = 0; a < 4; a++)
			{
				if (movement_array[path[i]][a] == path[i + 1])
				{
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
			    printf("wf 1\n");
				forward_wls(1,1);
				face = fdir;
				lcd_cursor(2, 7);
				lcd_wr_char(face);
			}
			else if (face == 'n' && fdir == 'e')
			{
			    printf("wf 2\n");
				right_turn_wls();
				forward_wls(1,1);
				face = fdir;
				lcd_cursor(2, 7);
				lcd_wr_char(face);
			}
			else if (face == 'n' && fdir == 's')
			{
			    printf("wf 3\n");
				right_turn_wls();
				right_turn_wls();
				forward_wls(1,1);
				face = fdir;
				lcd_cursor(2, 7);
				lcd_wr_char(face);
			}
			else if (face == 'n' && fdir == 'w')
			{
			    printf("wf 4\n");
				left_turn_wls();
				forward_wls(1,1);
				face = fdir;
				lcd_cursor(2, 7);
				lcd_wr_char(face);
			}
			else if (face == 'e' && fdir == 'e')
			{
			    printf("wf 5\n");
				forward_wls(1,1);
				face = fdir;
				lcd_cursor(2, 7);
				lcd_wr_char(face);
			}
			else if (face == 'e' && fdir == 's')
			{
			    printf("wf 6\n");
				right_turn_wls();
				forward_wls(1,1);
				face = fdir;
				lcd_cursor(2, 7);
				lcd_wr_char(face);
			}
			else if (face == 'e' && fdir == 'w')
			{
			    printf("wf 7\n");
				right_turn_wls();
				right_turn_wls();
				forward_wls(1,1);
				face = fdir;
				lcd_cursor(2, 7);
				lcd_wr_char(face);
			}
			else if (face == 'e' && fdir == 'n')
			{
			    printf("wf 8\n");
				left_turn_wls();
				forward_wls(1,1);
				face = fdir;
				lcd_cursor(2, 7);
				lcd_wr_char(face);
			}
			else if (face == 's' && fdir == 's')
			{
			    printf("wf 9\n");
				forward_wls(1,1);
				face = fdir;
				lcd_cursor(2, 7);
				lcd_wr_char(face);
			}
			else if (face == 's' && fdir == 'w')
			{
			    printf("wf 10\n");
				right_turn_wls();
				forward_wls(1,1);
				face = fdir;
				lcd_cursor(2, 7);
				lcd_wr_char(face);
			}
			else if (face == 's' && fdir == 'n')
			{
			    printf("wf 11\n");
				right_turn_wls();
				right_turn_wls();
				forward_wls(1,1);
				face = fdir;
				lcd_cursor(2, 7);
				lcd_wr_char(face);
			}
			else if (face == 's' && fdir == 'e')
			{
			    printf("wf 12\n");
				left_turn_wls();
				forward_wls(1,1);
				face = fdir;
				lcd_cursor(2, 7);
				lcd_wr_char(face);
			}
			else if (face == 'w' && fdir == 'w')
			{
			    printf("wf 13\n");
				forward_wls(1,1);
				face = fdir;
				lcd_cursor(2, 7);
				lcd_wr_char(face);
			}
			else if (face == 'w' && fdir == 'n')
			{
			    printf("wf 14\n");
				right_turn_wls();
				forward_wls(1,1);
				face = fdir;
				lcd_cursor(2, 7);
				lcd_wr_char(face);
			}
			else if (face == 'w' && fdir == 'e')
			{
			    printf("wf 15\n");
				right_turn_wls();
				right_turn_wls();
				forward_wls(1,1);
				face = fdir;
				lcd_cursor(2, 7);
				lcd_wr_char(face);
			}
			else if (face == 'w' && fdir == 's')
			{
			    printf("wf 16\n");
				left_turn_wls();
				forward_wls(1,1);
				face = fdir;
				lcd_cursor(2, 7);
				lcd_wr_char(face);
			}
		}
		else
		{
			for (int a = 0; a < 4; a++)
			{
				if (movement_array[path[i]][a] == path[i + 1])
				{
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
			    printf("t 1\n");
				forward_wls(0,1);
				face = fdir;
				lcd_cursor(2, 7);
				lcd_wr_char(face);
			}
			else if (face == 'n' && fdir == 'e')
			{
			    printf("t 2\n");
				right_turn_wls();
				forward_wls(0,1);
				face = fdir;
				lcd_cursor(2, 7);
				lcd_wr_char(face);
			}
			else if (face == 'n' && fdir == 's')
			{
			    printf("t 3\n");
				right_turn_wls();
				right_turn_wls();
				forward_wls(0,1);
				face = fdir;
				lcd_cursor(2, 7);
				lcd_wr_char(face);
			}
			else if (face == 'n' && fdir == 'w')
			{
			    printf("t 4\n");
				left_turn_wls();
				forward_wls(0,1);
				face = fdir;
				lcd_cursor(2, 7);
				lcd_wr_char(face);
			}
			else if (face == 'e' && fdir == 'e')
			{
			    printf("t 5\n");
				forward_wls(0,1);
				face = fdir;
				lcd_cursor(2, 7);
				lcd_wr_char(face);
			}
			else if (face == 'e' && fdir == 's')
			{
			    printf("t 6\n");
				right_turn_wls();
				forward_wls(0,1);
				face = fdir;
				lcd_cursor(2, 7);
				lcd_wr_char(face);
			}
			else if (face == 'e' && fdir == 'w')
			{
			    printf("t 7\n");
				right_turn_wls();
				right_turn_wls();
				forward_wls(0,1);
				face = fdir;
				lcd_cursor(2, 7);
				lcd_wr_char(face);
			}
			else if (face == 'e' && fdir == 'n')
			{
			    printf("t 8\n");
				left_turn_wls();
				forward_wls(0,1);
				face = fdir;
				lcd_cursor(2, 7);
				lcd_wr_char(face);
			}
			else if (face == 's' && fdir == 's')
			{
			    printf("t 9\n");
				forward_wls(0,1);
				face = fdir;
				lcd_cursor(2, 7);
				lcd_wr_char(face);
			}
			else if (face == 's' && fdir == 'w')
			{
			    printf("t 10\n");
				right_turn_wls();
				forward_wls(0,1);
				face = fdir;
				lcd_cursor(2, 7);
				lcd_wr_char(face);
			}
			else if (face == 's' && fdir == 'n')
			{
			    printf("t 11\n");
				right_turn_wls();
				right_turn_wls();
				forward_wls(0,1);
				face = fdir;
				lcd_cursor(2, 7);
				lcd_wr_char(face);
			}
			else if (face == 's' && fdir == 'e')
			{
			    printf("t 12\n");
				left_turn_wls();
				forward_wls(0,1);
				face = fdir;
				lcd_cursor(2, 7);
				lcd_wr_char(face);
			}
			else if (face == 'w' && fdir == 'w')
			{
			    printf("t 13\n");
				forward_wls(0,1);
				face = fdir;
				lcd_cursor(2, 7);
				lcd_wr_char(face);
			}
			else if (face == 'w' && fdir == 'n')
			{
			    printf("t 14\n");
				right_turn_wls();
				forward_wls(0,1);
				face = fdir;
				lcd_cursor(2, 7);
				lcd_wr_char(face);
			}
			else if (face == 'w' && fdir == 'e')
			{
			    printf("t 15\n");
				right_turn_wls();
				right_turn_wls();
				forward_wls(0,1);
				face = fdir;
				lcd_cursor(2, 7);
				lcd_wr_char(face);
			}
			else if (face == 'w' && fdir == 's')
			{
			    printf("t 16\n");
				left_turn_wls();
				forward_wls(0,1);
				face = fdir;
				lcd_cursor(2, 7);
				lcd_wr_char(face);
			}

		}
	}
}

void block_traverse()
{
	if (face == 'n' && fdir == 'n')
	{
	    printf("bt 1\n");
		face = fdir;
		lcd_cursor(2, 7);
		lcd_wr_char(face);
	}
	else if (face == 'n' && fdir == 'e')
	{
	    printf("bt 2\n");
		right_turn_wls();
		face = fdir;
		lcd_cursor(2, 7);
		lcd_wr_char(face);
	}
	else if (face == 'n' && fdir == 's')
	{
	    printf("bt 3\n");
		right_turn_wls();
		right_turn_wls_bwall();
		face = fdir;
	}
	else if (face == 'n' && fdir == 'w')
	{
	    printf("bt 4\n");
		left_turn_wls();
		face = fdir;
		lcd_cursor(2, 7);
		lcd_wr_char(face);
	}
	else if (face == 'e' && fdir == 'e')
	{
	    printf("bt 5\n");
		face = fdir;
		lcd_cursor(2, 7);
		lcd_wr_char(face);
	}
	else if (face == 'e' && fdir == 's')
	{
	    printf("bt 6\n");
		right_turn_wls();
		face = fdir;
		lcd_cursor(2, 7);
		lcd_wr_char(face);
	}
	else if (face == 'e' && fdir == 'w')
	{
	    printf("bt 7\n");
		right_turn_wls();
		right_turn_wls_bwall();
		face = fdir;
		lcd_cursor(2, 7);
		lcd_wr_char(face);
	}
	else if (face == 'e' && fdir == 'n')
	{
	    printf("bt 8\n");
		left_turn_wls();
		face = fdir;
		lcd_cursor(2, 7);
		lcd_wr_char(face);
	}
	else if (face == 's' && fdir == 's')
	{
	    printf("bt 9\n");
		face = fdir;
		lcd_cursor(2, 7);
		lcd_wr_char(face);
	}
	else if (face == 's' && fdir == 'w')
	{
	    printf("bt 10\n");
		right_turn_wls();
		face = fdir;
		lcd_cursor(2, 7);
		lcd_wr_char(face);
	}
	else if (face == 's' && fdir == 'n')
	{
	    printf("bt 11\n");
		right_turn_wls();
		right_turn_wls_bwall();
		face = fdir;
		lcd_cursor(2, 7);
		lcd_wr_char(face);
	}
	else if (face == 's' && fdir == 'e')
	{
	    printf("bt 12\n");
		left_turn_wls();
		face = fdir;
		lcd_cursor(2, 7);
		lcd_wr_char(face);
	}
	else if (face == 'w' && fdir == 'w')
	{
	    printf("bt 13\n");
		face = fdir;
		lcd_cursor(2, 7);
		lcd_wr_char(face);
	}
	else if (face == 'w' && fdir == 'n')
	{
	    printf("bt 14\n");
		right_turn_wls();
		face = fdir;
		lcd_cursor(2, 7);
		lcd_wr_char(face);
	}
	else if (face == 'w' && fdir == 'e')
	{
	    printf("bt 15\n");
		right_turn_wls();
		right_turn_wls_bwall();
		face = fdir;
		lcd_cursor(2, 7);
		lcd_wr_char(face);
	}
	else if (face == 'w' && fdir == 's')
	{
	    printf("bt 16\n");
		left_turn_wls();
		face = fdir;
		lcd_cursor(2, 7);
		lcd_wr_char(face);
	}
}

void block_choose(int bnode,int block_placed[])
{
	if (bnode == 2)
	{
		if (block_placed[0] == 0)
		{
			fdir = 'w';
			block_traverse();
			block_placed[0] = 1;
			back();
			_delay_ms(200);
			stop();
		}
		else if (block_placed[1] == 0)
		{
			fdir = 'e';
			block_traverse();
			block_placed[1] = 1;
			back();
			_delay_ms(200);
			stop();
		}
	}
	else if (bnode == 13)
	{
		if (block_placed[2] == 0)
		{
			fdir = 'w';
			block_traverse();
			block_placed[2] = 1;
			back();
			_delay_ms(200);
			stop();
		}
		else if (block_placed[3] == 0)
		{
			fdir = 'e';
			block_traverse();
			block_placed[3] = 1;
			back();
			_delay_ms(200);
			stop();
		}
	}
	else if (bnode == 4)
	{
		if (block_placed[4] == 0)
		{
			fdir = 'w';
			block_traverse();
			block_placed[4] = 1;
			back();
			_delay_ms(200);
			stop();
		}
		else if (block_placed[5] == 0)
		{
			fdir = 'e';
			block_traverse();
			block_placed[5] = 1;
			back();
			_delay_ms(200);
			stop();
		}
	}
	else if (bnode == 11)
	{
		if (block_placed[6] == 0)
		{
			fdir = 'w';
			block_traverse();
			block_placed[6] = 1;
			back();
			_delay_ms(200);
			stop();
		}
		else if (block_placed[7] == 0)
		{
			fdir = 'e';
			block_traverse();
			block_placed[7] = 1;
			back();
			_delay_ms(200);
			stop();
		}
	}
	else if (bnode == 6)
	{
		if (block_placed[8] == 0)
		{
			fdir = 'w';
			block_traverse();
			block_placed[8] = 1;
			back();
			_delay_ms(200);
			stop();
		}
		else if (block_placed[9] == 0)
		{
			fdir = 'e';
			block_traverse();
			block_placed[9] = 1;
			back();
			_delay_ms(200);
			stop();
		}
	}
	else if (bnode == 9)
	{
		if (block_placed[10] == 0)
		{
			fdir = 'w';
			block_traverse();
			block_placed[10] = 1;
			back();
			_delay_ms(200);
			stop();
		}
		else if (block_placed[11] == 0)
		{
			fdir = 'e';
			block_traverse();
			block_placed[11] = 1;
			back();
			_delay_ms(200);
			stop();
		}
	}
}

void block_choose2(int block,int block_placed[])
{
    if (block%2 == 0)
    {
        fdir = 'e';
        block_traverse();
		block_placed[block-1] = 1;
		back();
		_delay_ms(200);
		stop();
    }
    else if (block%2 == 1)
    {
        fdir = 'w';
        block_traverse();
		block_placed[block-1] = 1;
		back();
		_delay_ms(200);
		stop();
    }
}

/* --------------------------------------------------------------MAIN-----------------------------------------------------------*/
/*
int main()
{
  init_devices();
  int house_no = 0;
  int block = 0;
  int bnode;
  int len = 0;
  char apfdir = 'w';
  int *path = (int*)malloc(80);
  u = 0;
  face = 's';

  forward_wls(0,1);

  block = which_material[8];
  if (block==0)
  {
      //int *path = (int*)malloc(80);
      block = which_material[9];
      lcd_init();
      printf("%Block - %d\n",block);
      //lcd_print(2,1,block,3);
      bnode = which_node(block);
      printf("Node - %d\n",bnode);
      //lcd_print(2,14,bnode,3);
      dijkstra(G,n,u);
      printf("Dijkstra Completed\n");
      dist_comp(bnode,bnode,path,&len);
      printf("Dist compare Completed\n");
       for(int p = 0;p<len;p++)
       {
           printf("%d\n",path[p]);
	       //lcd_print(1,2*p,path[p],2);
       }
      traverse(path,u,&len);
      printf("Traverse Completed\n");
      free(path);
      len = 0;
      block_choose2(block,block_placed);
      //block_choose(bnode,block_placed);
      printf("Block Choose Completed\n");
      s_pick();
      lcd_init();
      for(int p = 0;p<=12;p++)
      {
    	  if (path[p] == 1) lcd_print(1,1,p,2);
      }
      u=bnode;

      dijkstra(G,n,u);
      printf("Dijkstra Completed\n");
      dist_comp(h51,h52,path,&len);

      printf("Dist compare Completed\n");
       for(int p = 0;p<len;p++)
       {
           printf("%d\n",path[p]);
	       //lcd_print(1,2*p,path[p],2);
       }
      traverse(path,u,&len);
      printf("Traverse Completed\n");
      u = path[len-1];
      free(path);
      len = 0;
  }

  else
  {
      lcd_init();
      printf("%Block - %d\n",block);
      //lcd_print(2,1,block,3);
      bnode = which_node(block);
      printf("Node - %d\n",bnode);
      //lcd_print(2,14,bnode,3);
      dijkstra(G,n,u);
      printf("Dijkstra Completed\n");
      //int *path = (int*)malloc(80);
      dist_comp(bnode,bnode,path,&len);
      printf("Dist compare Completed\n");
      for(int p = 0;p<len;p++)
      {
          printf("%d\n",path[p]);
	      //lcd_print(1,2*p,path[p],2);
      }
      traverse(path,u,&len);
      printf("Traverse Completed\n");
      free(path);
      len = 0;
      block_choose(bnode,block_placed);
      printf("Block Choose Completed\n");
      m_pick();
      lcd_init();
      u=bnode;

      block = which_material[9];
      lcd_init();
      printf("%Block - %d\n",block);
      //lcd_print(2,1,block,3);
      bnode = which_node(block);
      printf("Node - %d\n",bnode);
      //lcd_print(2,14,bnode,3);
      dijkstra(G,n,u);
      printf("Dijkstra Completed\n");
      dist_comp(bnode,bnode,path,&len);
      printf("Dist compare Completed\n");
       for(int p = 0;p<len;p++)
       {
           printf("%d\n",path[p]);
    	   //lcd_print(1,2*p,path[p],2);
       }
      traverse(path,u,&len);
      printf("Traverse Completed\n");
      free(path);
      len = 0;
      block_choose(bnode,block_placed);
      printf("Block Choose Completed\n");
      s_pick();
      lcd_init();
      for(int p = 0;p<=12;p++)
      {
    	  if (path[p] == 1) lcd_print(1,1,p,2);
      }
      u=bnode;

      dijkstra(G,n,u);
      printf("Dijkstra Completed\n");
      dist_comp(h51,h52,path,&len);

      printf("Dist compare Completed\n");
       for(int p = 0;p<len;p++)
       {
           printf("%d\n",path[p]);
	       //lcd_print(1,2*p,path[p],2);
       }
      traverse(path,u,&len);
      printf("Traverse Completed\n");
      u = path[len-1];
      free(path);
      len = 0;
  }


  if (u==7)
  {
      right_turn_inv();
      forward_wls(4,1);
      face = 'e';
      u = 8;
  }
  else if (u==8)
  {
      left_turn_inv();
      forward_wls(4,1);
      face = 'w';
      u = 7;
  }

  dijkstra(G,n,u);
  printf("Dijkstra Completed\n");
  dist_comp(b9n,b11n,path,&len);
  printf("Dist compare Completed\n");
   for(int p = 0;p<len;p++)
   {
       printf("%d\n",path[p]);
	   //lcd_print(1,2*p,path[p],2);
   }
   bnode = path[len-1];
  traverse(path,u,&len);
  printf("Traverse Completed\n");
  free(path);
  len = 0;
  block_choose(bnode,block_placed);
  printf("Block Choose Completed\n");
  lcd_init();
  u=bnode;
  block = which_block(u);
  for (int i = 0; i < 10; i++)
  {
      if (which_material[i] == block)
      {
          if (i==0) {house_no = 1;break;}
          else if (i==1) {house_no = 1;break;}
          else if (i==2) {house_no = 2;break;}
          else if (i==3) {house_no = 2;break;}
          else if (i==4) {house_no = 3;break;}
          else if (i==5) {house_no = 3;break;}
          else if (i==6) {house_no = 4;break;}
          else if (i==7) {house_no = 4;break;}
      }
      else
      {
          house_no = -1;
      }
  }
  if (house_no == -1)
  {
      if (block == 1) block =2;
      else if (block == 2) block =1;
      else if (block == 3) block =4;
      else if (block == 4) block =3;
      else if (block == 5) block =6;
      else if (block == 6) block =5;
      else if (block == 7) block =8;
      else if (block == 8) block =7;
      else if (block == 9) block =10;
      else if (block == 10) block =9;
      else if (block == 11) block =12;
      else if (block == 12) block =11;
  }
  for (int i = 0; i < 10; i++)
  {
      if (which_material[i] == block)
      {
          if (i==0) {house_no = 1;break;}
          else if (i==1) {house_no = 1;break;}
          else if (i==2) {house_no = 2;break;}
          else if (i==3) {house_no = 2;break;}
          else if (i==4) {house_no = 3;break;}
          else if (i==5) {house_no = 3;break;}
          else if (i==6) {house_no = 4;break;}
          else if (i==7) {house_no = 4;break;}
      }
      else
      {
          house_no = -1;
      }
  }
  if (house_no != -1)
  {
        m_pick();
  }
  //printf("%d\n",block);
  //printf("%d\n",house_no);
  if (block == which_material[2*house_no - 1])
  {
      block = which_material[2*house_no - 2];  }
  else
  {
      block = which_material[2*house_no - 1];
  }
  dijkstra(G,n,u);
  printf("Dijkstra Completed\n");
  bnode = which_node(block);
  dist_comp(bnode,bnode,path,&len);
  printf("Dist compare Completed\n");
   for(int p = 0;p<len;p++)
   {
       printf("%d\n",path[p]);
	   //lcd_print(1,2*p,path[p],2);
   }
   bnode = path[len-1];
  traverse(path,u,&len);
  printf("Traverse Completed\n");
  free(path);
  len = 0;
  block_choose(bnode,block_placed);
  printf("Block Choose Completed\n");
  s_pick();

  dijkstra(G,n,u);
  printf("Dijkstra Completed\n");
  int hnode = 0;
  hnode = which_house(house_no);
  dist_comp(hnode,hnode,path,&len);
  printf("Dist compare Completed\n");
  for(int p = 0;p<len;p++)
   {
       printf("%d\n",path[p]);
	   //lcd_print(1,2*p,path[p],2);
   }
  traverse(path,u,&len);
  printf("Traverse Completed\n");
  free(path);
  len = 0;
  if (house_no == 1)
  {
      fdir = 'w';
      block_traverse();
      back();
      _delay_ms(100);
      stop();
      if (house_config[house_no-1]==0)
      {
          m_place_lr();
          s_place_lr();
      }
      else
      {
          m_place_hr();
          s_place_hr();
      }
  }
  else if (house_no == 2)
  {
      fdir = 'e';
      block_traverse();
      back();
      _delay_ms(100);
      stop();
      if (house_config[house_no-1]==0)
      {
          m_place_lr();
          s_place_lr();
      }
      else
      {
          m_place_hr();
          s_place_hr();
      }
  }
  else if (house_no == 3)
  {
      fdir = 'w';
      block_traverse();
      back();
      _delay_ms(100);
      stop();
      if (house_config[house_no-1]==0)
      {
          m_place_lr();
          s_place_lr();
      }
      else
      {
          m_place_hr();
          s_place_hr();
      }
  }
  else if (house_no == 4)
  {
      fdir = 'e';
      block_traverse();
      back();
      _delay_ms(100);
      stop();
      if (house_config[house_no-1]==0)
      {
          m_place_lr();
          s_place_lr();
      }
      else
      {
          m_place_hr();
          s_place_hr();
      }
  }

  dijkstra(G,n,u);
  printf("Dijkstra Completed\n");
  dist_comp(b5n,b7n,path,&len);
  printf("Dist compare Completed\n");
   for(int p = 0;p<len;p++)
   {
       printf("%d\n",path[p]);
	   //lcd_print(1,2*p,path[p],2);
   }
   bnode = path[len-1];
  traverse(path,u,&len);
  printf("Traverse Completed\n");
  free(path);
  len = 0;
  block_choose(bnode,block_placed);
  printf("Block Choose Completed\n");
  lcd_init();
  u=bnode;
  block = which_block(u);
  for (int i = 0; i < 10; i++)
  {
      if (which_material[i] == block)
      {
          if (i==0) {house_no = 1;break;}
          else if (i==1) {house_no = 1;break;}
          else if (i==2) {house_no = 2;break;}
          else if (i==3) {house_no = 2;break;}
          else if (i==4) {house_no = 3;break;}
          else if (i==5) {house_no = 3;break;}
          else if (i==6) {house_no = 4;break;}
          else if (i==7) {house_no = 4;break;}
      }
      else
      {
          house_no = -1;
      }
  }
  if (house_no == -1)
  {
      if (block == 1) block =2;
      else if (block == 2) block =1;
      else if (block == 3) block =4;
      else if (block == 4) block =3;
      else if (block == 5) block =6;
      else if (block == 6) block =5;
      else if (block == 7) block =8;
      else if (block == 8) block =7;
      else if (block == 9) block =10;
      else if (block == 10) block =9;
      else if (block == 11) block =12;
      else if (block == 12) block =11;
  }
  for (int i = 0; i < 10; i++)
  {
      if (which_material[i] == block)
      {
          if (i==0) {house_no = 1;break;}
          else if (i==1) {house_no = 1;break;}
          else if (i==2) {house_no = 2;break;}
          else if (i==3) {house_no = 2;break;}
          else if (i==4) {house_no = 3;break;}
          else if (i==5) {house_no = 3;break;}
          else if (i==6) {house_no = 4;break;}
          else if (i==7) {house_no = 4;break;}
      }
      else
      {
          house_no = -1;
      }
  }
  if (house_no != -1)
  {
        m_pick();
  }
  //printf("%d\n",block);
  //printf("%d\n",house_no);
  if (block == which_material[2*house_no - 1])
  {
      block = which_material[2*house_no - 2];  }
  else
  {
      block = which_material[2*house_no - 1];
  }
  dijkstra(G,n,u);
  printf("Dijkstra Completed\n");
  bnode = which_node(block);
  dist_comp(bnode,bnode,path,&len);
  printf("Dist compare Completed\n");
   for(int p = 0;p<len;p++)
   {
       printf("%d\n",path[p]);
	   //lcd_print(1,2*p,path[p],2);
   }
   bnode = path[len-1];
  traverse(path,u,&len);
  printf("Traverse Completed\n");
  free(path);
  len = 0;
  block_choose(bnode,block_placed);
  printf("Block Choose Completed\n");
  s_pick();
  printf("u - %d\n",u);
  dijkstra(G,n,u);
  printf("Dijkstra Completed\n");
  printf("House no - %d\n",house_no);
  hnode = which_house(house_no);
  printf("Hnode - %d\n",hnode);
  dist_comp(hnode,hnode,path,&len);
  printf("Dist compare Completed\n");
  for(int p = 0;p<len;p++)
   {
       printf("%d\n",path[p]);
	   //lcd_print(1,2*p,path[p],2);
   }
  traverse(path,u,&len);
  printf("Traverse Completed\n");
  free(path);
  len = 0;
  if (house_no == 1)
  {
      fdir = 'w';
      block_traverse();
      back();
      _delay_ms(100);
      stop();
      if (house_config[house_no-1]==0)
      {
          m_place_lr();
          s_place_lr();
      }
      else
      {
          m_place_hr();
          s_place_hr();
      }
  }
  else if (house_no == 2)
  {
      fdir = 'e';
      block_traverse();
      back();
      _delay_ms(100);
      stop();
      if (house_config[house_no-1]==0)
      {
          m_place_lr();
          s_place_lr();
      }
      else
      {
          m_place_hr();
          s_place_hr();
      }
  }
  else if (house_no == 3)
  {
      fdir = 'w';
      block_traverse();
      back();
      _delay_ms(100);
      stop();
      if (house_config[house_no-1]==0)
      {
          m_place_lr();
          s_place_lr();
      }
      else
      {
          m_place_hr();
          s_place_hr();
      }
  }
  else if (house_no == 4)
  {
      fdir = 'e';
      block_traverse();
      back();
      _delay_ms(100);
      stop();
      if (house_config[house_no-1]==0)
      {
          m_place_lr();
          s_place_lr();
      }
      else
      {
          m_place_hr();
          s_place_hr();
      }
  }

  dijkstra(G,n,u);
  printf("Dijkstra Completed\n");
  dist_comp(b2n,b4n,path,&len);
  printf("Dist compare Completed\n");
   for(int p = 0;p<len;p++)
   {
       printf("%d\n",path[p]);
	   //lcd_print(1,2*p,path[p],2);
   }
   bnode = path[len-1];
  traverse(path,u,&len);
  printf("Traverse Completed\n");
  free(path);
  len = 0;
  block_choose(bnode,block_placed);
  printf("Block Choose Completed\n");
  lcd_init();
  u=bnode;
  block = which_block(u);
  for (int i = 0; i < 10; i++)
  {
      if (which_material[i] == block)
      {
          if (i==0) {house_no = 1;break;}
          else if (i==1) {house_no = 1;break;}
          else if (i==2) {house_no = 2;break;}
          else if (i==3) {house_no = 2;break;}
          else if (i==4) {house_no = 3;break;}
          else if (i==5) {house_no = 3;break;}
          else if (i==6) {house_no = 4;break;}
          else if (i==7) {house_no = 4;break;}
      }
      else
      {
          house_no = -1;
      }
  }
  if (house_no == -1)
  {
      if (block == 1) block =2;
      else if (block == 2) block =1;
      else if (block == 3) block =4;
      else if (block == 4) block =3;
      else if (block == 5) block =6;
      else if (block == 6) block =5;
      else if (block == 7) block =8;
      else if (block == 8) block =7;
      else if (block == 9) block =10;
      else if (block == 10) block =9;
      else if (block == 11) block =12;
      else if (block == 12) block =11;
  }
  for (int i = 0; i < 10; i++)
  {
      if (which_material[i] == block)
      {
          if (i==0) {house_no = 1;break;}
          else if (i==1) {house_no = 1;break;}
          else if (i==2) {house_no = 2;break;}
          else if (i==3) {house_no = 2;break;}
          else if (i==4) {house_no = 3;break;}
          else if (i==5) {house_no = 3;break;}
          else if (i==6) {house_no = 4;break;}
          else if (i==7) {house_no = 4;break;}
      }
      else
      {
          house_no = -1;
      }
  }
  if (house_no != -1)
  {
        m_pick();
  }
  //printf("%d\n",block);
  //printf("%d\n",house_no);
  if (block == which_material[2*house_no - 1])
  {
      block = which_material[2*house_no - 2];  }
  else
  {
      block = which_material[2*house_no - 1];
  }
  dijkstra(G,n,u);
  printf("Dijkstra Completed\n");
  bnode = which_node(block);
  dist_comp(bnode,bnode,path,&len);
  printf("Dist compare Completed\n");
   for(int p = 0;p<len;p++)
   {
       printf("%d\n",path[p]);
	   //lcd_print(1,2*p,path[p],2);
   }
   bnode = path[len-1];
  traverse(path,u,&len);
  printf("Traverse Completed\n");
  free(path);
  len = 0;
  block_choose(bnode,block_placed);
  printf("Block Choose Completed\n");
  s_pick();
  printf("u - %d\n",u);
  dijkstra(G,n,u);
  printf("Dijkstra Completed\n");
  printf("House no - %d\n",house_no);
  hnode = which_house(house_no);
  printf("Hnode - %d\n",hnode);
  dist_comp(hnode,hnode,path,&len);
  printf("Dist compare Completed\n");
  for(int p = 0;p<len;p++)
   {
       printf("%d\n",path[p]);
	   //lcd_print(1,2*p,path[p],2);
   }
  traverse(path,u,&len);
  printf("Traverse Completed\n");
  free(path);
  len = 0;
  if (house_no == 1)
  {
      fdir = 'w';
      block_traverse();
      back();
      _delay_ms(100);
      stop();
      if (house_config[house_no-1]==0)
      {
          m_place_lr();
          s_place_lr();
      }
      else
      {
          m_place_hr();
          s_place_hr();
      }
  }
  else if (house_no == 2)
  {
      fdir = 'e';
      block_traverse();
      back();
      _delay_ms(100);
      stop();
      if (house_config[house_no-1]==0)
      {
          m_place_lr();
          s_place_lr();
      }
      else
      {
          m_place_hr();
          s_place_hr();
      }
  }
  else if (house_no == 3)
  {
      fdir = 'w';
      block_traverse();
      back();
      _delay_ms(100);
      stop();
      if (house_config[house_no-1]==0)
      {
          m_place_lr();
          s_place_lr();
      }
      else
      {
          m_place_hr();
          s_place_hr();
      }
  }
  else if (house_no == 4)
  {
      fdir = 'e';
      block_traverse();
      back();
      _delay_ms(100);
      stop();
      if (house_config[house_no-1]==0)
      {
          m_place_lr();
          s_place_lr();
      }
      else
      {
          m_place_hr();
          s_place_hr();
      }
  }





  for(int p = 0;p<12;p++)
   {
       printf("%d\n",block_placed[p]);
	   //lcd_print(1,2*p,path[p],2);
   }

  //printf("%d\n",hnode);

  //for(int p = 0;p<12;p++)
   //{
       //printf("%d\n",block_placed[p]);
	   //lcd_print(1,2*p,path[p],2);
   //}
  //for (int i = 0; i < 10; i++)
  //{
	  //if (1 == which_material[i])
	  //{
		  //house_no = i;
	  //}
  //}
}

*/

int main()
{
  init_devices();
  int is_block1 = 0;
  int is_block2 = 0;
  int is_block3 = 0;
  int is_block4 = 0;
  int is_block5 = 0;
  int is_block6 = 0;
  int house_no = 0;
  int block = 0;
  int bnode;
  int len = 0;
  char apfdir = 'w';
  int *path = (int*)malloc(80);
  u = 0;
  face = 's';
  forward_wls(0,1);
  block = which_material[8];
  if (block==0)
  {
      block = which_material[9];
      lcd_init();
      printf("Block - %d\n",block);
      //lcd_print(2,1,block,3);
      bnode = which_node(block);
      printf("Node - %d\n",bnode);
      //lcd_print(2,14,bnode,3);
      dijkstra(G,n,u);
      printf("Dijkstra Completed\n");
      dist_comp(bnode,bnode,path,&len);
      printf("Dist compare Completed\n");
       for(int p = 0;p<len;p++)
       {
           printf("%d\n",path[p]);
	       //lcd_print(1,2*p,path[p],2);
       }
      traverse(path,u,&len);
      printf("Traverse Completed\n");
      free(path);
      len = 0;
      block_choose2(block,block_placed);
      //block_choose(bnode,block_placed);
      printf("Block Choose Completed\n");
      s_pick();
      lcd_init();
      for(int p = 0;p<=12;p++)
      {
    	  if (path[p] == 1) lcd_print(1,1,p,2);
      }
      u=bnode;

      dijkstra(G,n,u);
      printf("Dijkstra Completed\n");
      dist_comp(h51,h52,path,&len);

      printf("Dist compare Completed\n");
       for(int p = 0;p<len;p++)
       {
           printf("%d\n",path[p]);
	       //lcd_print(1,2*p,path[p],2);
       }
      traverse(path,u,&len);
      printf("Traverse Completed\n");
      u = path[len-1];
      free(path);
      len = 0;
  }
  else
  {
      lcd_init();
      printf("Block - %d\n",block);
      //lcd_print(2,1,block,3);
      bnode = which_node(block);
      printf("Node - %d\n",bnode);
      //lcd_print(2,14,bnode,3);
      dijkstra(G,n,u);
      printf("Dijkstra Completed\n");
      //int *path = (int*)malloc(80);
      dist_comp(bnode,bnode,path,&len);
      printf("Dist compare Completed\n");
      for(int p = 0;p<len;p++)
      {
          printf("%d\n",path[p]);
	      //lcd_print(1,2*p,path[p],2);
      }
      traverse(path,u,&len);
      printf("Traverse Completed\n");
      free(path);
      len = 0;
      block_choose2(block,block_placed);
      printf("Block Choose Completed\n");
      m_pick();
      lcd_init();
      u=bnode;

      block = which_material[9];
      lcd_init();
      printf("Block - %d\n",block);
      //lcd_print(2,1,block,3);
      bnode = which_node(block);
      printf("Node - %d\n",bnode);
      //lcd_print(2,14,bnode,3);
      dijkstra(G,n,u);
      printf("Dijkstra Completed\n");
      dist_comp(bnode,bnode,path,&len);
      printf("Dist compare Completed\n");
       for(int p = 0;p<len;p++)
       {
           printf("%d\n",path[p]);
    	   //lcd_print(1,2*p,path[p],2);
       }
      traverse(path,u,&len);
      printf("Traverse Completed\n");
      free(path);
      len = 0;
      block_choose2(block,block_placed);
      printf("Block Choose Completed\n");
      s_pick();
      lcd_init();
      for(int p = 0;p<=12;p++)
      {
    	  if (path[p] == 1) lcd_print(1,1,p,2);
      }
      u=bnode;

      dijkstra(G,n,u);
      printf("Dijkstra Completed\n");
      dist_comp(h51,h52,path,&len);

      printf("Dist compare Completed\n");
       for(int p = 0;p<len;p++)
       {
           printf("%d\n",path[p]);
	       //lcd_print(1,2*p,path[p],2);
       }
      traverse(path,u,&len);
      printf("Traverse Completed\n");
      u = path[len-1];
      free(path);
      len = 0;
  }
  if (u==7)
  {
      right_turn_inv();
      forward_wls(3,1);
      face = 'e';
      u = 8;
      is_block1 = check_block(11);
      is_block2 = check_block(12);
      is_block3 = check_block(7);
      is_block4 = check_block(8);
      if (block_placed[10] == 0 && is_block1==1) block = 11;
      else if (block_placed[11] == 0 && is_block2==1) block = 12;
      else if (block_placed[6] == 0 && is_block3==1) block = 7;
      else if (block_placed[7] == 0 && is_block4==1) block = 8;
  }
  else if (u==8)
  {
      left_turn_inv();
      forward_wls(3,1);
      face = 'w';
      u = 7;
      is_block1 = check_block(9);
      is_block2 = check_block(10);
      is_block3 = check_block(5);
      is_block4 = check_block(6);
      if (block_placed[8] == 0 && is_block1==1) block = 9;
      else if (block_placed[9] == 0 && is_block2==1) block = 10;
      else if (block_placed[6] == 0 && is_block3==1) block = 5;
      else if (block_placed[7] == 0 && is_block4==1) block = 6;
  }

  bnode = which_node(block);
  dijkstra(G,n,u);
  printf("Dijkstra Completed\n");
  printf("Block - %d\n",block);
  printf("Node - %d\n",bnode);
  dist_comp(bnode,bnode,path,&len);
  printf("Dist compare Completed\n");
    for(int p = 0;p<len;p++)
       {
           printf("%d\n",path[p]);
	       //lcd_print(1,2*p,path[p],2);
       }
    traverse(path,u,&len);
    printf("Traverse Completed\n");
    free(path);
    len = 0;
    block_choose2(block,block_placed);
    //block_choose(bnode,block_placed);
    printf("Block Choose Completed\n");
    u = bnode;
    for (int i = 0; i < 10; i++)
  {
      if (which_material[i] == block)
      {
          if (i==0) {house_no = 1;break;}
          else if (i==1) {house_no = 1;break;}
          else if (i==2) {house_no = 2;break;}
          else if (i==3) {house_no = 2;break;}
          else if (i==4) {house_no = 3;break;}
          else if (i==5) {house_no = 3;break;}
          else if (i==6) {house_no = 4;break;}
          else if (i==7) {house_no = 4;break;}
      }
      else
      {
          house_no = -1;
      }
  }
  if (house_no != -1)
  {
        m_pick();
  }
  if (block == which_material[2*house_no - 1])
  {
      block = which_material[2*house_no - 2];  }
  else
  {
      block = which_material[2*house_no - 1];
  }
  if (block != 0)
  {
  dijkstra(G,n,u);
  printf("Dijkstra Completed\n");
  bnode = which_node(block);
  dist_comp(bnode,bnode,path,&len);
  printf("Dist compare Completed\n");
  printf("Block - %d\n",block);
  printf("Node - %d\n",bnode);
   for(int p = 0;p<len;p++)
   {
       printf("%d\n",path[p]);
	   //lcd_print(1,2*p,path[p],2);
   }
   bnode = path[len-1];
  traverse(path,u,&len);
  printf("Traverse Completed\n");
  free(path);
  len = 0;
  block_choose2(block,block_placed);
  printf("Block Choose Completed\n");
  s_pick();
  }

  dijkstra(G,n,u);
  printf("Dijkstra Completed\n");
  int hnode = 0;
  hnode = which_house(house_no);
  dist_comp(hnode,hnode,path,&len);
  printf("Dist compare Completed\n");
  for(int p = 0;p<len;p++)
   {
       printf("%d\n",path[p]);
	   //lcd_print(1,2*p,path[p],2);
   }
  traverse(path,u,&len);
  printf("Traverse Completed\n");
  free(path);
  len = 0;
  if (house_no == 1)
  {
      fdir = 'w';
      block_traverse();
      back();
      _delay_ms(100);
      stop();
      if (house_config[house_no-1]==0)
      {
          m_place_lr();
          s_place_lr();
      }
      else
      {
          m_place_hr();
          s_place_hr();
      }
      is_block1 = check_block(1);
      is_block2 = check_block(2);
      is_block3 = check_block(5);
      is_block4 = check_block(6);
      is_block5 = check_block(9);
      is_block6 = check_block(10);
      if (block_placed[0] == 0 && is_block1==1) block = 1;
      else if (block_placed[1] == 0 && is_block2==1) block = 2;
      else if (block_placed[4] == 0 && is_block3==1) block = 5;
      else if (block_placed[5] == 0 && is_block4==1) block = 6;
      else if (block_placed[8] == 0 && is_block5==1) block = 9;
      else if (block_placed[9] == 0 && is_block6==1) block = 10;
  }
  else if (house_no == 2)
  {
      fdir = 'e';
      block_traverse();
      back();
      _delay_ms(100);
      stop();
      if (house_config[house_no-1]==0)
      {
          m_place_lr();
          s_place_lr();
      }
      else
      {
          m_place_hr();
          s_place_hr();
      }
      is_block1 = check_block(3);
      is_block2 = check_block(4);
      is_block3 = check_block(7);
      is_block4 = check_block(8);
      is_block5 = check_block(11);
      is_block6 = check_block(12);
      if (block_placed[2] == 0 && is_block1==1) block = 3;
      else if (block_placed[3] == 0 && is_block2==1) block = 4;
      else if (block_placed[6] == 0 && is_block3==1) block = 7;
      else if (block_placed[7] == 0 && is_block4==1) block = 8;
      else if (block_placed[10] == 0 && is_block5==1) block = 11;
      else if (block_placed[11] == 0 && is_block6==1) block = 12;
  }
  else if (house_no == 3)
  {
      fdir = 'w';
      block_traverse();
      back();
      _delay_ms(100);
      stop();
      if (house_config[house_no-1]==0)
      {
          m_place_lr();
          s_place_lr();
      }
      else
      {
          m_place_hr();
          s_place_hr();
      }
      is_block1 = check_block(5);
      is_block2 = check_block(6);
      is_block3 = check_block(9);
      is_block4 = check_block(10);
      is_block5 = check_block(1);
      is_block6 = check_block(2);
      if (block_placed[4] == 0 && is_block1==1) block = 5;
      else if (block_placed[5] == 0 && is_block2==1) block = 6;
      else if (block_placed[8] == 0 && is_block3==1) block = 9;
      else if (block_placed[9] == 0 && is_block4==1) block = 10;
      else if (block_placed[0] == 0 && is_block5==1) block = 1;
      else if (block_placed[1] == 0 && is_block6==1) block = 2;
  }
  else if (house_no == 4)
  {
      fdir = 'e';
      block_traverse();
      back();
      _delay_ms(100);
      stop();
      if (house_config[house_no-1]==0)
      {
          m_place_lr();
          s_place_lr();
      }
      else
      {
          m_place_hr();
          s_place_hr();
      }
      is_block1 = check_block(7);
      is_block2 = check_block(8);
      is_block3 = check_block(11);
      is_block4 = check_block(12);
      is_block5 = check_block(3);
      is_block6 = check_block(4);
      if (block_placed[6] == 0 && is_block1==1) block = 7;
      else if (block_placed[7] == 0 && is_block2==1) block = 8;
      else if (block_placed[10] == 0 && is_block3==1) block = 11;
      else if (block_placed[11] == 0 && is_block4==1) block = 12;
      else if (block_placed[2] == 0 && is_block5==1) block = 3;
      else if (block_placed[3] == 0 && is_block6==1) block = 4;
  }

  bnode = which_node(block);
  dijkstra(G,n,u);
  printf("Dijkstra Completed\n");
  printf("Block - %d\n",block);
  printf("Node - %d\n",bnode);
  dist_comp(bnode,bnode,path,&len);
  printf("Dist compare Completed\n");
    for(int p = 0;p<len;p++)
       {
           printf("%d\n",path[p]);
	       //lcd_print(1,2*p,path[p],2);
       }
    traverse(path,u,&len);
    printf("Traverse Completed\n");
    free(path);
    len = 0;
    block_choose2(block,block_placed);
    //block_choose(bnode,block_placed);
    printf("Block Choose Completed\n");
    u = bnode;
    for (int i = 0; i < 10; i++)
  {
      if (which_material[i] == block)
      {
          if (i==0) {house_no = 1;break;}
          else if (i==1) {house_no = 1;break;}
          else if (i==2) {house_no = 2;break;}
          else if (i==3) {house_no = 2;break;}
          else if (i==4) {house_no = 3;break;}
          else if (i==5) {house_no = 3;break;}
          else if (i==6) {house_no = 4;break;}
          else if (i==7) {house_no = 4;break;}
      }
      else
      {
          house_no = -1;
      }
  }
  if (house_no != -1)
  {
        m_pick();
  }
  if (block == which_material[2*house_no - 1])
  {
      block = which_material[2*house_no - 2];  }
  else
  {
      block = which_material[2*house_no - 1];
  }
  if (block != 0)
  {
  dijkstra(G,n,u);
  printf("Dijkstra Completed\n");
  bnode = which_node(block);
  dist_comp(bnode,bnode,path,&len);
  printf("Dist compare Completed\n");
  printf("Block - %d\n",block);
  printf("Node - %d\n",bnode);
   for(int p = 0;p<len;p++)
   {
       printf("%d\n",path[p]);
	   //lcd_print(1,2*p,path[p],2);
   }
   bnode = path[len-1];
  traverse(path,u,&len);
  printf("Traverse Completed\n");
  free(path);
  len = 0;
  block_choose2(block,block_placed);
  printf("Block Choose Completed\n");
  s_pick();
  }

  dijkstra(G,n,u);
  printf("Dijkstra Completed\n");
  hnode = 0;
  hnode = which_house(house_no);
  dist_comp(hnode,hnode,path,&len);
  printf("Dist compare Completed\n");
  for(int p = 0;p<len;p++)
   {
       printf("%d\n",path[p]);
	   //lcd_print(1,2*p,path[p],2);
   }
  traverse(path,u,&len);
  printf("Traverse Completed\n");
  free(path);
  len = 0;
  if (house_no == 1)
  {
      fdir = 'w';
      block_traverse();
      back();
      _delay_ms(100);
      stop();
      if (house_config[house_no-1]==0)
      {
          m_place_lr();
          s_place_lr();
      }
      else
      {
          m_place_hr();
          s_place_hr();
      }
      is_block1 = check_block(1);
      is_block2 = check_block(2);
      is_block3 = check_block(5);
      is_block4 = check_block(6);
      is_block5 = check_block(9);
      is_block6 = check_block(10);
      if (block_placed[0] == 0 && is_block1==1) block = 1;
      else if (block_placed[1] == 0 && is_block2==1) block = 2;
      else if (block_placed[4] == 0 && is_block3==1) block = 5;
      else if (block_placed[5] == 0 && is_block4==1) block = 6;
      else if (block_placed[8] == 0 && is_block5==1) block = 9;
      else if (block_placed[9] == 0 && is_block6==1) block = 10;
  }
  else if (house_no == 2)
  {
      fdir = 'e';
      block_traverse();
      back();
      _delay_ms(100);
      stop();
      if (house_config[house_no-1]==0)
      {
          m_place_lr();
          s_place_lr();
      }
      else
      {
          m_place_hr();
          s_place_hr();
      }
      is_block1 = check_block(3);
      is_block2 = check_block(4);
      is_block3 = check_block(7);
      is_block4 = check_block(8);
      is_block5 = check_block(11);
      is_block6 = check_block(12);
      if (block_placed[2] == 0 && is_block1==1) block = 3;
      else if (block_placed[3] == 0 && is_block2==1) block = 4;
      else if (block_placed[6] == 0 && is_block3==1) block = 7;
      else if (block_placed[7] == 0 && is_block4==1) block = 8;
      else if (block_placed[10] == 0 && is_block5==1) block = 11;
      else if (block_placed[11] == 0 && is_block6==1) block = 12;
  }
  else if (house_no == 3)
  {
      fdir = 'w';
      block_traverse();
      back();
      _delay_ms(100);
      stop();
      if (house_config[house_no-1]==0)
      {
          m_place_lr();
          s_place_lr();
      }
      else
      {
          m_place_hr();
          s_place_hr();
      }
      is_block1 = check_block(5);
      is_block2 = check_block(6);
      is_block3 = check_block(9);
      is_block4 = check_block(10);
      is_block5 = check_block(1);
      is_block6 = check_block(2);
      if (block_placed[4] == 0 && is_block1==1) block = 5;
      else if (block_placed[5] == 0 && is_block2==1) block = 6;
      else if (block_placed[8] == 0 && is_block3==1) block = 9;
      else if (block_placed[9] == 0 && is_block4==1) block = 10;
      else if (block_placed[0] == 0 && is_block5==1) block = 1;
      else if (block_placed[1] == 0 && is_block6==1) block = 2;
  }
  else if (house_no == 4)
  {
      fdir = 'e';
      block_traverse();
      back();
      _delay_ms(100);
      stop();
      if (house_config[house_no-1]==0)
      {
          m_place_lr();
          s_place_lr();
      }
      else
      {
          m_place_hr();
          s_place_hr();
      }
      is_block1 = check_block(7);
      is_block2 = check_block(8);
      is_block3 = check_block(11);
      is_block4 = check_block(12);
      is_block5 = check_block(3);
      is_block6 = check_block(4);
      if (block_placed[6] == 0 && is_block1==1) block = 7;
      else if (block_placed[7] == 0 && is_block2==1) block = 8;
      else if (block_placed[10] == 0 && is_block3==1) block = 11;
      else if (block_placed[11] == 0 && is_block4==1) block = 12;
      else if (block_placed[2] == 0 && is_block5==1) block = 3;
      else if (block_placed[3] == 0 && is_block6==1) block = 4;
  }
  free(path);
  len = 0;
  bnode = which_node(block);
  dijkstra(G,n,u);
  printf("Dijkstra Completed\n");
  printf("Block - %d\n", block);
  printf("Node - %d\n", bnode);
  dist_comp(bnode,bnode,path,&len);
  printf("Dist compare Completed\n");
  for(int p = 0;p<len;p++)
       {
           printf("%d\n",path[p]);
	       //lcd_print(1,2*p,path[p],2);
       }
  traverse(path,u,&len);
  printf("Traverse Completed\n");
  free(path);
  len = 0;
  block_choose2(block,block_placed);
  printf("Block Choose Completed\n");
  u = bnode;
  for (int i = 0; i < 10; i++)
  {
      if (which_material[i] == block)
      {
          if (i==0) {house_no = 1;break;}
          else if (i==1) {house_no = 1;break;}
          else if (i==2) {house_no = 2;break;}
          else if (i==3) {house_no = 2;break;}
          else if (i==4) {house_no = 3;break;}
          else if (i==5) {house_no = 3;break;}
          else if (i==6) {house_no = 4;break;}
          else if (i==7) {house_no = 4;break;}
      }
      else
      {
          house_no = -1;
      }
  }
  if (house_no != -1)
  {
        m_pick();
  }
  if (block == which_material[2*house_no - 1])
  {
      block = which_material[2*house_no - 2];  }
  else
  {
      block = which_material[2*house_no - 1];
  }
  if (block != 0)
  {
  dijkstra(G,n,u);
  printf("Dijkstra Completed\n");
  bnode = which_node(block);
  dist_comp(bnode,bnode,path,&len);
  printf("Dist compare Completed\n");
  printf("Block - %d\n",block);
  printf("Node - %d\n",bnode);
   for(int p = 0;p<len;p++)
   {
       printf("%d\n",path[p]);
	   //lcd_print(1,2*p,path[p],2);
   }
   bnode = path[len-1];
  traverse(path,u,&len);
  printf("Traverse Completed\n");
  free(path);
  len = 0;
  block_choose2(block,block_placed);
  printf("Block Choose Completed\n");
  s_pick();
  }
  dijkstra(G,n,u);
  printf("Dijkstra Completed\n");
  hnode = 0;
  hnode = which_house(house_no);
  dist_comp(hnode,hnode,path,&len);
  printf("Dist compare Completed\n");
  for(int p = 0;p<len;p++)
   {
       printf("%d\n",path[p]);
	   //lcd_print(1,2*p,path[p],2);
   }
  traverse(path,u,&len);
  printf("Traverse Completed\n");
  free(path);
  len = 0;
  if (house_no == 1)
  {
      fdir = 'w';
      block_traverse();
      back();
      _delay_ms(100);
      stop();
      if (house_config[house_no-1]==0)
      {
          m_place_lr();
          s_place_lr();
      }
      else
      {
          m_place_hr();
          s_place_hr();
      }
      is_block1 = check_block(1);
      is_block2 = check_block(2);
      is_block3 = check_block(5);
      is_block4 = check_block(6);
      is_block5 = check_block(9);
      is_block6 = check_block(10);
      if (block_placed[0] == 0 && is_block1==1) block = 1;
      else if (block_placed[1] == 0 && is_block2==1) block = 2;
      else if (block_placed[4] == 0 && is_block3==1) block = 5;
      else if (block_placed[5] == 0 && is_block4==1) block = 6;
      else if (block_placed[8] == 0 && is_block5==1) block = 9;
      else if (block_placed[9] == 0 && is_block6==1) block = 10;
  }
  else if (house_no == 2)
  {
      fdir = 'e';
      block_traverse();
      back();
      _delay_ms(100);
      stop();
      if (house_config[house_no-1]==0)
      {
          m_place_lr();
          s_place_lr();
      }
      else
      {
          m_place_hr();
          s_place_hr();
      }
      is_block1 = check_block(3);
      is_block2 = check_block(4);
      is_block3 = check_block(7);
      is_block4 = check_block(8);
      is_block5 = check_block(11);
      is_block6 = check_block(12);
      if (block_placed[2] == 0 && is_block1==1) block = 3;
      else if (block_placed[3] == 0 && is_block2==1) block = 4;
      else if (block_placed[6] == 0 && is_block3==1) block = 7;
      else if (block_placed[7] == 0 && is_block4==1) block = 8;
      else if (block_placed[10] == 0 && is_block5==1) block = 11;
      else if (block_placed[11] == 0 && is_block6==1) block = 12;
  }
  else if (house_no == 3)
  {
      fdir = 'w';
      block_traverse();
      back();
      _delay_ms(100);
      stop();
      if (house_config[house_no-1]==0)
      {
          m_place_lr();
          s_place_lr();
      }
      else
      {
          m_place_hr();
          s_place_hr();
      }
      is_block1 = check_block(5);
      is_block2 = check_block(6);
      is_block3 = check_block(9);
      is_block4 = check_block(10);
      is_block5 = check_block(1);
      is_block6 = check_block(2);
      if (block_placed[4] == 0 && is_block1==1) block = 5;
      else if (block_placed[5] == 0 && is_block2==1) block = 6;
      else if (block_placed[8] == 0 && is_block3==1) block = 9;
      else if (block_placed[9] == 0 && is_block4==1) block = 10;
      else if (block_placed[0] == 0 && is_block5==1) block = 1;
      else if (block_placed[1] == 0 && is_block6==1) block = 2;
  }
  else if (house_no == 4)
  {
      fdir = 'e';
      block_traverse();
      back();
      _delay_ms(100);
      stop();
      if (house_config[house_no-1]==0)
      {
          m_place_lr();
          s_place_lr();
      }
      else
      {
          m_place_hr();
          s_place_hr();
      }
      is_block1 = check_block(7);
      is_block2 = check_block(8);
      is_block3 = check_block(11);
      is_block4 = check_block(12);
      is_block5 = check_block(3);
      is_block6 = check_block(4);
      if (block_placed[6] == 0 && is_block1==1) block = 7;
      else if (block_placed[7] == 0 && is_block2==1) block = 8;
      else if (block_placed[10] == 0 && is_block3==1) block = 11;
      else if (block_placed[11] == 0 && is_block4==1) block = 12;
      else if (block_placed[2] == 0 && is_block5==1) block = 3;
      else if (block_placed[3] == 0 && is_block6==1) block = 4;
  }

  free(path);
  len = 0;
  bnode = which_node(block);
  dijkstra(G,n,u);
  printf("Dijkstra Completed\n");
  printf("Block - %d\n", block);
  printf("Node - %d\n", bnode);
  dist_comp(bnode,bnode,path,&len);
  printf("Dist compare Completed\n");
  for(int p = 0;p<len;p++)
       {
           printf("%d\n",path[p]);
	       //lcd_print(1,2*p,path[p],2);
       }
  traverse(path,u,&len);
  printf("Traverse Completed\n");
  free(path);
  len = 0;
  block_choose2(block,block_placed);
  printf("Block Choose Completed\n");
  u = bnode;
  for (int i = 0; i < 10; i++)
  {
      if (which_material[i] == block)
      {
          if (i==0) {house_no = 1;break;}
          else if (i==1) {house_no = 1;break;}
          else if (i==2) {house_no = 2;break;}
          else if (i==3) {house_no = 2;break;}
          else if (i==4) {house_no = 3;break;}
          else if (i==5) {house_no = 3;break;}
          else if (i==6) {house_no = 4;break;}
          else if (i==7) {house_no = 4;break;}
      }
      else
      {
          house_no = -1;
      }
  }
  if (house_no != -1)
  {
        m_pick();
  }
  if (block == which_material[2*house_no - 1])
  {
      block = which_material[2*house_no - 2];  }
  else
  {
      block = which_material[2*house_no - 1];
  }
  if (block != 0)
  {
  dijkstra(G,n,u);
  printf("Dijkstra Completed\n");
  bnode = which_node(block);
  dist_comp(bnode,bnode,path,&len);
  printf("Dist compare Completed\n");
  printf("Block - %d\n",block);
  printf("Node - %d\n",bnode);
   for(int p = 0;p<len;p++)
   {
       printf("%d\n",path[p]);
	   //lcd_print(1,2*p,path[p],2);
   }
   bnode = path[len-1];
  traverse(path,u,&len);
  printf("Traverse Completed\n");
  free(path);
  len = 0;
  block_choose2(block,block_placed);
  printf("Block Choose Completed\n");
  s_pick();
  }
  dijkstra(G,n,u);
  printf("Dijkstra Completed\n");
  hnode = 0;
  hnode = which_house(house_no);
  dist_comp(hnode,hnode,path,&len);
  printf("Dist compare Completed\n");
  for(int p = 0;p<len;p++)
   {
       printf("%d\n",path[p]);
	   //lcd_print(1,2*p,path[p],2);
   }
  traverse(path,u,&len);
  printf("Traverse Completed\n");
  free(path);
  len = 0;
  if (house_no == 1)
  {
      fdir = 'w';
      block_traverse();
      back();
      _delay_ms(100);
      stop();
      if (house_config[house_no-1]==0)
      {
          m_place_lr();
          s_place_lr();
      }
      else
      {
          m_place_hr();
          s_place_hr();
      }
      is_block1 = check_block(1);
      is_block2 = check_block(2);
      is_block3 = check_block(5);
      is_block4 = check_block(6);
      is_block5 = check_block(9);
      is_block6 = check_block(10);
      if (block_placed[0] == 0 && is_block1==1) block = 1;
      else if (block_placed[1] == 0 && is_block2==1) block = 2;
      else if (block_placed[4] == 0 && is_block3==1) block = 5;
      else if (block_placed[5] == 0 && is_block4==1) block = 6;
      else if (block_placed[8] == 0 && is_block5==1) block = 9;
      else if (block_placed[9] == 0 && is_block6==1) block = 10;
  }
  else if (house_no == 2)
  {
      fdir = 'e';
      block_traverse();
      back();
      _delay_ms(100);
      stop();
      if (house_config[house_no-1]==0)
      {
          m_place_lr();
          s_place_lr();
      }
      else
      {
          m_place_hr();
          s_place_hr();
      }
      is_block1 = check_block(3);
      is_block2 = check_block(4);
      is_block3 = check_block(7);
      is_block4 = check_block(8);
      is_block5 = check_block(11);
      is_block6 = check_block(12);
      if (block_placed[2] == 0 && is_block1==1) block = 3;
      else if (block_placed[3] == 0 && is_block2==1) block = 4;
      else if (block_placed[6] == 0 && is_block3==1) block = 7;
      else if (block_placed[7] == 0 && is_block4==1) block = 8;
      else if (block_placed[10] == 0 && is_block5==1) block = 11;
      else if (block_placed[11] == 0 && is_block6==1) block = 12;
  }
  else if (house_no == 3)
  {
      fdir = 'w';
      block_traverse();
      back();
      _delay_ms(100);
      stop();
      if (house_config[house_no-1]==0)
      {
          m_place_lr();
          s_place_lr();
      }
      else
      {
          m_place_hr();
          s_place_hr();
      }
      is_block1 = check_block(5);
      is_block2 = check_block(6);
      is_block3 = check_block(9);
      is_block4 = check_block(10);
      is_block5 = check_block(1);
      is_block6 = check_block(2);
      if (block_placed[4] == 0 && is_block1==1) block = 5;
      else if (block_placed[5] == 0 && is_block2==1) block = 6;
      else if (block_placed[8] == 0 && is_block3==1) block = 9;
      else if (block_placed[9] == 0 && is_block4==1) block = 10;
      else if (block_placed[0] == 0 && is_block5==1) block = 1;
      else if (block_placed[1] == 0 && is_block6==1) block = 2;
  }
  else if (house_no == 4)
  {
      fdir = 'e';
      block_traverse();
      back();
      _delay_ms(100);
      stop();
      if (house_config[house_no-1]==0)
      {
          m_place_lr();
          s_place_lr();
      }
      else
      {
          m_place_hr();
          s_place_hr();
      }
      is_block1 = check_block(7);
      is_block2 = check_block(8);
      is_block3 = check_block(11);
      is_block4 = check_block(12);
      is_block5 = check_block(3);
      is_block6 = check_block(4);
      if (block_placed[6] == 0 && is_block1==1) block = 7;
      else if (block_placed[7] == 0 && is_block2==1) block = 8;
      else if (block_placed[10] == 0 && is_block3==1) block = 11;
      else if (block_placed[11] == 0 && is_block4==1) block = 12;
      else if (block_placed[2] == 0 && is_block5==1) block = 3;
      else if (block_placed[3] == 0 && is_block6==1) block = 4;
  }
  for(int p = 0;p<12;p++)
   {
       printf("%d -- %d\n",p+1,block_placed[p]);
	   //lcd_print(1,2*p,path[p],2);
   }
   //is_block2 = check_block(8);
   //printf("is block 8 %d\n",is_block2);

}
