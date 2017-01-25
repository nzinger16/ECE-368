#include "unhuff.h"

int main(int argc, char *argv[])
{
 
  if (argc < 2)
  {
    fprintf(stderr, "Insufficient arguments.\n");
    return EXIT_FAILURE;
  }
  FILE * fptr = fopen(argv[1], "r");
  if (fptr == NULL)
  {
     fprintf(stderr, "Can't open input file.\n");
     return EXIT_FAILURE;
  }
  FILE * fptr2 = fopen(argv[2], "w");
  if (fptr2 == NULL)
  {
     fprintf(stderr, "Can't open input file.\n");
     return EXIT_FAILURE;
  }
  bit * bit_read = NULL;
  bit_read = malloc(sizeof(bit));
  Tnode * tree = NULL;
  tree = tree_build(fptr);
  if (tree == NULL)
  {
    fprintf(stderr, "Error building Tree.\n");
    return EXIT_FAILURE;
  }
  int depth = 0;
  int buffer[256];
  Tree_print(tree,depth,buffer);
  print_binary_directions(bit_read,fptr,tree,fptr2);
  fclose(fptr);
  fclose(fptr2);
  //free(bit_read);
  Tree_destruct(tree);
  return EXIT_SUCCESS;
}
