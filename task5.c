#include <stdio.h>
#include <stdlib.h>
int main()
{
   int which_material[10] = {3,11,9,5,4,7,1,0,2,8};
   int block = 0;
   block = which_material[8];
   //printf("%d\n" , block);
   int *path = (int*)malloc(80);
   int len = 20;
   path[0] = 2;
   path[1] = 4;
   free(path);
   path[0] = 6;
   path[1] = 9;
   for(int p = 0;p<len;p++)
  {
	  printf("%d\n" , path[p]);
  }
   return 0;
}
