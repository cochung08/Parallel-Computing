//Jake Shankman
//Period 2
//Perlocate
//9/28/2012

#include <stdlib.h>
#include <stdio.h>

#define maxR 400
#define maxC 400
int row, col;
float prob;
int span(int matrix[maxR][maxC],int group)
{
  int s1, s2, s3, s4;
  s1 = s2 = s3 = s4 = 0;
  int i, j;
  for(i = 0; i < row; i++)
  {
    if(matrix[i][0] == group)
      s1 = 1;
    if(matrix[i][col - 1] == group)
      s2 = 1;
  }
  for(j = 0; j < col; j++)
  {
   if(matrix[0][j] == group)
     s3 = 1;
   if(matrix[row - 1][j] == group)
     s4 = 1;
  }
  if(s1 == 1 && s2 == 1 && s3 == 1 && s4 == 1)
    return 1;
  else
    return 0;
}
void floodFill(int matrix[maxR][maxC], int r, int c, int group)
{
 if(matrix[r][c] == 0 || matrix[r][c] == group)
   return;
 matrix[r][c] = group;
 if(r > 0)
   floodFill(matrix, r - 1, c, group);
 if(c > 0)
   floodFill(matrix, r, c-1, group);
 if(r < row - 1)
   floodFill(matrix, r + 1, c, group);
 if(c < col - 1)
   floodFill(matrix, r, c + 1, group);
}
int main(int arr,char* array[])
{
  //Initial setup
  int matrix[maxR][maxC];
  //printf("Enter probability\n");
  //scanf("%f", &prob);
  prob = 0.0;
  //printf("Enter rows <= 400\n");
  //scanf("%i", &row);
  //printf("Enter cols <= 400\n");
  //scanf("%i", &col);
  row = 30;
  col = 30;
  int seed = time(NULL);
  srand(seed);
  //Open File
  FILE* out = fopen("lab03.txt", "w");
  fprintf(out, "#Row=%i Col=%i\n", row, col);
  fprintf(out, "#Probability\tPercent_Spanning\n");
  while(prob < 1.0)
  {
  int spann = 0;
  int trial = 0;
  while( trial < 1000)
  {
  int i, j;
  int occupy = 0;
  for(i = 0; i < row; i++)
  {
    for(j= 0; j < col; j++)
    {
     if((rand()%1000)/1000.0 < prob)
     {
       matrix[i][j] = 1;
       occupy++;
       
    }
    else
       matrix[i][j] = 0;// 0 or 1
    }
  }
  printf("\n");
  int group = 2;
  for(i = 0; i < row; i++)
  {
    for(j = 0; j < col; j++)
      if(matrix[i][j] == 1)
      {
	floodFill(matrix, i, j, group);
	group++;
      } 
  }
  //Check spanning
  printf("\n# Occupied=%i\n# groups=%i\n", occupy, group - 1);
  int count = 2;
  int b = 0;
  while(count < group)
  {
   int bool = span(matrix, count);
   if(bool == 1)
   {
     printf("YES! Group=%i\n", count);
     b = 1;
     spann++;
     break;
   }
   count++;
  } 
  if(b == 0)
    printf("NO!\n");
  trial++;
  }
  double percent = 1.0 * spann/trial;
  fprintf(out, "%f\t", prob);
  fprintf(out, "%f\n", percent);
  prob += 0.01;
    
  } 
  return 0;
}