#include "huff.h"

int main(int argc, char *argv[])
{
  if (argc < 3) {
    fprintf(stderr, "No input/output file given\n");
    return EXIT_FAILURE;
  }
  else if (argc > 3) {
    fprintf(stderr, "Too many input arguments\n");
    return EXIT_FAILURE;
  }
  else {
    FILE * fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
      fprintf(stderr, "can't open input file\n");
      return EXIT_FAILURE;
    }
    FILE * fptr2 = fopen(argv[2], "wb");
    if (fptr2 == NULL) {
      fprintf(stderr, "can't read output file\n");
      return EXIT_FAILURE;
    }
    int size;
    int * ascii_array = Ascii_Array(fptr, &size);
    //int i;
    /*for (i = 0; i < 256; i++) {
      printf("Ascii_Array[%d] = %d\n", i, ascii_array[i]);
      }*/
    Lnode * sorted_list = List_build(ascii_array);
    //Lnode_print(sorted_list);
    Tnode * huff_tree = tree_build(sorted_list);
    
    int depth = 0;
    int buffer[256];          
    int column = get_column(huff_tree);
    int row = get_row(huff_tree);
    column++;
    tree_print(huff_tree,depth,buffer);
    
     	     
    int ** code_book = malloc(sizeof(int*) * row);
    int r;
    int c;
    for (r = 0; r<row; r++) {
      code_book[r] = malloc(sizeof(int) * column);
      for (c = 0; c < column; c++) {
	code_book[r][c] = -1;
      }
    }
    build_book(huff_tree,code_book);
    //Testing code_book
    /*for (r = 0; r<row; r++) {
      for (c = 0; c < column; c++) {
	printf("code_book[%d][%d] = %d\n", r,c,code_book[r][c]);
      }
      }*/
    //int bit_offset = 0;
    //unsigned char byte = 0;
    write_huff_header(huff_tree, fptr2);//,byte,bit_offset);
    write_huff_paths(code_book, fptr,fptr2,size, row);
    //printf("size = %d", size);
    /*while (sorted_list->next!=NULL) {
      printf("frequency = %d, charachter index = %d\n", sorted_list->freq, sorted_list->index);
      sorted_list = sorted_list->next;
      }*/
    //Lnode_print(sorted_list);
    return EXIT_SUCCESS;
  }
}
      
  
