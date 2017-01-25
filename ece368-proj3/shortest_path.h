#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>
//Structs:
typedef struct adjacent_list {
  int num; //vertex num
  struct adjacent_list * next;
} adj_list;

typedef struct queue {
  int vert;
  int t_dist;
} q;
 



//List functions
adj_list * List_construct(int num);
void List_print(adj_list * n);

int get_verts(FILE * fptr); //#of "cities" (verteces)
void build_coord_book(FILE * fptr, int ** coord_book, int num_vert); //builds codebook for verticies and their coordinates
void build_adj_array(FILE * fptr, adj_list * adj_array[], int num_vert, int num_edges);
//void build_graph(int ** graph, adj_list * adj_array, int ** coord_book, int num_vert);

void dijkstra(int num_vert, int src, int dest, int ** coord_book, adj_list * adj_array[], q * q_array);
//void build_adj_book(FILE * fptr, int ** adj_book, int column); //builds codebook for all adjacent verticies

int find_dist(int u, int v, int ** coord_book);
int find_min(q * q_array, int * visited, int num_vert);
