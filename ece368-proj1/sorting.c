#include "sorting.h"
#include <string.h>

int *seq_1(int Size, int *seq_size);
int *seq_2(int Size, int *seq_size);
long *Load_File(char *Filename, int *Size)
{
  
  long *array;
  FILE * fptr = fopen(Filename, "r");
  int n;
  long ln; //long integer to be scanned from file
  int i = 0;
  
  fscanf(fptr,"%d", &n);
  *Size = n;
  array = malloc(sizeof(long) * n);
  while (!feof(fptr))
  {
    fscanf(fptr, "%ld", &ln);
    array[i] = ln;
    i++;
  }
  fclose(fptr);


  /*printf("size of array = %d\n", seq_size);
  for (i = 0; i<seq_size; i++) {
    printf("array[%d] = %ld\n", i, array[i]);
    }*/
  
  return array;
}    
    
int Save_File(char *Filename, long *Array, int Size)   
{
  FILE * fptr = fopen(Filename, "w");
  int count = 0;
  int i;
  fprintf(fptr, "%d\n", Size);
  for (i=0; i<Size; i++)
  {
    fprintf(fptr, "%ld\n", Array[i]);
    
    count++;
  }
  fclose(fptr);
  return count;
}

void Shell_Insertion_Sort(long *Array, int Size, double *N_Comp, double *N_Move)
{
  int seq_size;
  int *seq_array = seq_1(Size, &seq_size);
  printf("sequence array size is: %d\n", seq_size);
  int i;
  int j;
  int k;
  int l;
  int *rev_array = malloc(sizeof(int) * seq_size);
  int count = 0;
  long temp_r;
  *N_Comp = 0;
  *N_Move = 0;
  
 
  for (i=seq_size-1; i>=0; i--) {
    rev_array[count] = seq_array[i];
    count++;
  }

  
  for (j=0; j<seq_size; j++) {
    for (k=rev_array[j]; k<Size; k++) {
      temp_r = Array[k];
      *N_Comp+=1;
      l = k;
      while ((l>=rev_array[j]) && (Array[l - rev_array[j]] > temp_r)) {
	*N_Comp += 1;
	Array[l] = Array[l - rev_array[j]];
	*N_Move+=3;
	l = l - rev_array[j];
      }
      
      Array[l] = temp_r;
     
    }
  }
  free(rev_array);
  free(seq_array);
 
    
}


void Improved_Bubble_Sort(long *Array, int Size, double *N_Comp, double *N_Move)
{
  int seq_size;
  int *seq_array = seq_2(Size, &seq_size);
  int i,j,last_swap;
  int max_i;
  long temp;
  *N_Comp = 0;
  *N_Move = 0;
  for (j=0; j<seq_size; j++) {
    max_i = Size - seq_array[j];
    do {
      last_swap = -1;
      for (i=0; i<max_i; i++) {
	*N_Comp+=1;
	if (Array[i] > Array[i+seq_array[j]]) {
	  temp = Array[i];
	  Array[i] = Array[i+seq_array[j]];
	  Array[i+seq_array[j]] = temp;
	  last_swap = i;
	  *N_Move+=3;
	}
      }
      max_i = last_swap - 1;
    } while (last_swap >= 0);
    
  }
  free(seq_array);
}

int *seq_1(int Size, int *seq_size)
{
  int *array;
  int n = Size;
  array = malloc(sizeof(int) * n);
  array[0] = 1;
  int p2 = 0;
  int p3 = 0;
  int i;
  int u2,u3;
  int count = 0;
  
  for (i=1; i<Size; i++) 
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
    count++;
    if (array[i] > Size) {
      break;
    }
    
  }
  *seq_size = count;
  return array;
}

int *seq_2(int Size, int *seq_size)
{
  int *array = malloc(sizeof(int) * Size);
  int num = Size;
  int i = 0;
  int j = 1;
  //int div_num;
  while (num != 1) {
    num /= 1.3;
    array[i] = num;
    if (array[i] == 9 || array[i] == 10) {
      array[i] = 11;
    }
    i++;
    j++;
  }

  *seq_size = i;
  return array;
    

}
  
