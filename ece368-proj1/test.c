#include<stdio.h>
#include<stdlib.h>


void seq_1(int Size);

int main()
{
  

  seq_1(10);

  return 0;
}





void seq_1(int Size)
{
  int *array;
  int n = Size;
  array = malloc(sizeof(int) * n);
  array[0] = 1;
  int p2 = 0;
  int p3 = 0;
  int i=1;
  int u2,u3;
  
  while (array[i] < n) 
  {
    if (array[p2] * 2 == array[i-1])
    {
      p2++;
    }
    if (array[p3] * 3 == array[i-1])
    {
      p3++;
    }
    u2 = array[p2] * 2;
    u3 = array[p3] * 3;
    if (u2<u3)
    { 
      p2++;
      array[i] = u2;
    }
    else 
    {
      p3++;
      array[i] = u3;
    }
    printf("array[%d] = %d", i, array[i]);
    i++;
  }
  
}
