#include "shortest_path.h"
int main(int argc, char *argv[]) {
 if (argc != 3) {
    fprintf(stderr, "Insufficient arguments.\n");
    return EXIT_FAILURE;
 }
 FILE * fptr = fopen(argv[1], "r"); //mapping file
 FILE * fptr2 = fopen(argv[2], "r"); //Query file (source->dest)
 if (fptr == NULL) {
     fprintf(stderr, "Can't open input file.\n");
     return EXIT_FAILURE;
  }
 if (fptr2 == NULL) {
     fprintf(stderr, "Can't open input file.\n");
     return EXIT_FAILURE;
  }
  int num_vert = get_verts(fptr);
  int num_q = get_verts(fptr2); //get verts function can be used for number of queries, source and destination
  int ** coord_book = malloc(sizeof(int*) * 2);
  int i,c;
  for (i = 0; i < 3; i++) {
    coord_book[i] = malloc(sizeof(int) * num_vert);
    for (c = 0; c<num_vert; c++) {
      coord_book[i][c] = -1;
    }
  }
  
  //while (fgetc(fptr) != '\n') {}
  int num_edges;
  fscanf(fptr, "%d", &num_edges);
  //printf("num edges = %d\n", num_edges);
  build_coord_book(fptr,coord_book,num_vert);
  
  //printing coord book 
  /*int j;
  for (i = 0; i < 3; i++) {
    for (j=0; j<num_vert; j++) {      
      printf("coord_book[%d][%d] = %d\n", i,j,coord_book[i][j]);      
    }
  }
  */
  /*int n = 0;
  fscanf(fptr, "%d", &n);
  printf("n = %d", n);
  */

  adj_list * adj_array[num_vert]; //array of linked lists each link is a adjacent vertex.
  for (i = 0; i<num_vert; i++) {
     adj_array[i] = List_construct(i); 
  } 
  build_adj_array(fptr,adj_array,num_vert,num_edges);
  q * q_array = malloc(sizeof(q) * num_vert);
   /*
   //printing adjacent array (vertex with its adjacent vals):
   for (i = 0; i<num_vert; i++) { 
     printf("%d: ", adj_array[i]->num); 
     while (adj_array[i]->next != NULL) { 
       adj_array[i] = adj_array[i]->next; 
       printf("%d ",adj_array[i]->num); 
     } 
     printf("\n");
     }*/

   int src,dest; 
   for (i = 0; i < num_q; i++) { 
     fscanf(fptr2, "%d", &src); 
     fscanf(fptr2, "%d", &dest); 
     //printf("source = %d, dest = %d\n", src,dest); 
     dijkstra(num_vert,src,dest,coord_book,adj_array,q_array); 
   } 
  
   //print vertexes with adjacent verticies (milestone 2) *\/ */
  
     
    
 return EXIT_SUCCESS;
 
} 
/* /\* void List_print(adj_list * n) { *\/ */
/* /\*   while (n!=NULL) { *\/ */
/* /\*     printf("num = %d\n", n->num); *\/ */
/* /\*     n = n->next; *\/ */
/* /\*   } *\/ */
/* /\*   return; *\/ */
/* /\* } *\/ */
 adj_list * List_construct(int num) { 
   adj_list * m = malloc(sizeof(adj_list)); 
   m->num = num;
   m->next = NULL; 
   return m; 
 } 
 int get_verts(FILE * fptr) {
  int c = 0;
   fscanf(fptr, "%d", &c); 
   return c; 
 } 

void build_coord_book(FILE * fptr, int ** coord_book, int num_vert) { 
   int vert = 0; 
   int x = 0;
   int y = 0;
   int i; 
   int r = 0; 
   int c = 0; 
   for (i = 0; i<num_vert; i++) { 
    
     fscanf(fptr, "%d", &vert); 
     fscanf(fptr, "%d", &x); 
     fscanf(fptr, "%d", &y);
     coord_book[r][c] = vert; 
     r++; 
     coord_book[r][c] = x; 
     r++; 
     coord_book[r][c] = y; 
     r = 0; 
     c++; 
   } 
   

} 

 void build_adj_array(FILE * fptr, adj_list * adj_array[], int num_vert, int num_edges) {
   int ind = 0; //adj_array index (vertex #) *\/ */
   int vnum = 0; //adj_vertex num to be put into linked list *\/ */
   adj_list * curr;
   adj_list * prev; 
   adj_list * temp; 
  
  int i;
  
  for (i = 0; i < num_edges; i++) {
    fscanf(fptr, "%d", &ind);
    fscanf(fptr, "%d", &vnum);
    curr = List_construct(vnum);
    if (adj_array[ind]->next == NULL) {
      adj_array[ind]->next = curr;
    } else {
      prev = adj_array[ind]->next;
      temp = prev;
      while (prev->next != NULL) {
	prev = prev->next;
      }
      prev->next = curr;
      adj_array[ind]->next = temp;
    }

    curr = List_construct(ind);
    if (adj_array[vnum]->next == NULL) {
      adj_array[vnum]->next = curr;
    } else {
      prev = adj_array[vnum]->next;
      temp = prev;
      while (prev->next != NULL) {
	prev = prev->next;
      }
      prev->next = curr;
      adj_array[vnum]->next = temp;
    }
   
    //printf("After %d iteration:\n", counter);
    //List_print(adj_array[ind]);
  }
}

void dijkstra(int num_vert, int src, int dest, int ** coord_book, adj_list * adj_array[], q * q_array) {
  int * dist = malloc(sizeof(int) * num_vert);
  int * prev = malloc(sizeof(int) * num_vert);
  int * visited = malloc(sizeof(int) * num_vert);
  int i,u,alt,d;
  adj_list * curr; 
  //printf("here\n");
  for (i=0; i<num_vert; i++) {
    prev[i] = -1;
    visited[i] = 0;
    q_array[i].vert = i;
    if (i != src) {
      dist[i] = INT_MAX;
      q_array[i].t_dist = INT_MAX;
    } else {
      dist[i] = 0;
      q_array[i].t_dist = 0;
    }
  }
  /*for (i = 0; i <num_vert; i++) {
    printf("vert = %d, tdist = %d\n", q_array[i].vert,q_array[i].t_dist);
    }*/
  for (i=0; i<num_vert; i++) {
    
    u = find_min(q_array,visited,num_vert);
    if (u == dest) {
      break;
    }
    //printf("%d\n", u);
    //printf("u = %d\n", u);
    visited[u] = 1;
    curr = adj_array[u];
    while (curr->next != NULL) {
      curr = curr->next;
      d = find_dist(u, curr->num, coord_book);      
      alt = dist[u] + d;
      //printf("alt = %d", alt);
      if (alt < dist[curr->num]) {
	dist[curr->num] = alt;
	prev[curr->num] = u;
	
	q_array[curr->num].t_dist = alt;
	
      }
      
    }
  }

  if (src == dest) {
    printf("0\n");
    printf("%d\n",src);
  } else {
    printf("%d\n", dist[dest]);
    int ind = dest;
    //int path;
    //printf("%d ", dest);
    int cnt = 2; //count path array length
    while (prev[ind] != src) {
      cnt++;
      //printf("%d ", prev[ind]);
      ind = prev[ind];
    }
    int path = prev[dest];
    int * path_array = malloc(sizeof(int) * cnt);
    path_array[0] = src;
    path_array[cnt-1] = dest;
    i = cnt-2;
    while (i > 0) {
      path_array[i] = path;
      path = prev[path];
      i--;
    }
    for (i = 0; i < cnt; i++) {
      printf("%d ",path_array[i]);
    }
    printf("\n");
  }
  
}


int find_dist(int u, int v, int ** coord_book) {
  int x1,x2,y1,y2,d;
  x1 = coord_book[1][u];
  x2 = coord_book[1][v];
  y1 = coord_book[2][u];
  y2 = coord_book[2][v];
  d = sqrt(pow((x2-x1),2) + pow((y2-y1),2));
  return d;
}
int find_min(q * q_array, int * visited, int num_vert) {
  int i;
  int min = INT_MAX;
  int u;
  for (i = 0;i<num_vert; i++) {
    if (min > q_array[i].t_dist && visited[i] == 0) {
      min = q_array[i].t_dist;
      u = q_array[i].vert;
    }
  }
  return u;
}
/*void build_graph(int ** graph, adj_list * adj_array[], int ** coord_book, int num_vert) {
  int x1,x2,y1,y2,i, adj_vert,d;
  adj_list * curr;
  printf("got in here!");
  for (i = 0; i < num_vert; i++) {
    curr = adj_array[i]->next;
    while (curr != NULL) {
      adj_vert = curr->num;
      x1 = coord_book[1][i];
      x2 = coord_book[1][adj_vert];
      y1 = coord_book[2][i];
      y2 = coord_book[2][adj_vert];
      d = sqrt(pow((x2-x1),2) + pow((y2-y1),2));      
      graph[i][adj_vert] = d;
      graph[adj_vert][i] = d;
      curr = curr->next;      
    }      
  }
  }*/

/*void build_adj_book(FILE * fptr, int ** adj_book, int column) {
  int j = 0;
  int ch;
  while (j < column + 1) {
    ch = fgetc(fptr);
    if (ch == '\n') {
      j++;
    }
  }
  //int count_array[row];
  int r = 0;
  int c = -1;
  //int ogc = 0; //original column
  int first = 0;
  int second = 0;
  int prev_first = -1;
  int prev_second = -1;
  while (!feof(fptr)) {
    fscanf(fptr, "%d", &first);
    fscanf(fptr, "%d", &second);
        
   
    if (first != prev_first) {
      c++;
      r = 0;
      adj_book[r][c] = first;
      r++;
      adj_book[r][c] = second;
    } else {
      r++;
      adj_book [r][c] = second;
    }
    prev_first = first;
    prev_second = second;
    
  }
    

  }*/


