//
//Torbert, March 2013
//Jake Shankman 3/11/2013
// gcc -fopenmp filename
#include <stdio.h>
#include <omp.h>
//
#define N 8
#define logN 3
//
int main(void)
{
  int temp1, temp2;
  //
  int rank, size=N, j;
  //
  int data[N] = {4,5,3,7,8,2,1,6};//{3, 1, 4, 1, 5, 9, 2, 6};
  //
  int tree[logN + 1][N];	    //wastes memory
  //
  omp_set_num_threads(size);
  printf("%d\n", size);
  //
  #pragma omp parallel private(rank) // time O(1)
  {
    rank = omp_get_thread_num();
    printf("%d ", rank);
    //
    tree[logN][rank] = data[rank];  // work O(N)
  }
  printf("\n\n");
  //
  for(j = logN - 1; j >= 0; --j)    // time O(logN)
  {
    size /= 2;
    //
    omp_set_num_threads(size);
    printf("%d %d\n", size, j);
    //
    #pragma omp parallel private(rank)
    {
      rank = omp_get_thread_num();
      printf("%d ", rank);
      //
      //pairwise independent sums... work O(N)
      //
      temp1 = tree[j+1][2*rank];
      temp2 = tree[j+1][2*rank+1];
      if(temp1 > temp2)
      {
	tree[j][rank] = temp2;
      }
      else
      {
	tree[j][rank] = temp1;
      }
      
    }
    printf("\n\n");
  }
  printf("%d\n", tree[0][0]);
  //
  printf("\nPrefix calculations...\n");
  //
  int prefix[logN + 1][N];
  //
  prefix[0][0] = tree[0][0];
  for(j = 1; j <= logN; ++j)
  {
    size *= 2;
    //
    omp_set_num_threads(size);
    printf("%d %d\n", size, j);
    //
    #pragma omp parallel private(rank)
    {
      rank = omp_get_thread_num();
      printf("%d ", rank);
      //
      //
      if(rank == 0)
      {
	prefix[j][rank] = tree[j][rank]; 
      }
      else if(rank %2 == 1)
      {
	prefix[j][rank] = prefix[j - 1][rank/2];
      }
      else
      {
	temp1 = prefix[j - 1][rank/2 - 1];
	temp2 = tree[j][rank];
	if(temp1 > temp2)
	{
	  prefix[j][rank] = temp2;
	}
	else
	{
	  prefix[j][rank] = temp1;
	}
      }
      //
      //DO SOMETHING!!!!
    }
    printf("\n\n");
  }
  int x;
  for(x = 0; x < N; ++x)
  {
    printf("%d ", prefix[logN][x]);
  }
  printf("\n\n");
  //
  return 0;
}