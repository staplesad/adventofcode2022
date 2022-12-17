#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

#define T_LEN 10
#define NAME_S 3
#define input_nodes 60

typedef struct {
  char name[3];
  int flow;
  char edge_names[T_LEN][3];
  int edges[T_LEN];
  int n_edges;
  int index;
  int dist_all[input_nodes];
  bool on;
} valve;

valve create_valve(char name[3], int flow, char edge_names[T_LEN][3], int n_edges, int index){
  valve new = {.name="", .flow=flow, .edge_names = {0}, .edges={-1}, .n_edges=n_edges, .index=index, .dist_all={-1}, .on=false};
  strncpy(new.name, name, 3);
  memcpy(new.edge_names, edge_names, sizeof(char)*3*T_LEN);
  return new;
}

void print_valve(valve v, int count){
  printf("(%d) %c%c: %d, [%d]\n", v.index, v.name[0], v.name[1], v.flow, v.n_edges);
  printf("children:\n");
  for (int i=0; i<v.n_edges; i++){
    printf("%d: %c%c,\t", v.edges[i], v.edge_names[i][0], v.edge_names[i][1]);
  }
  printf("\n");
  for (int j=0; j<count; j++){
    printf("%d: %d,\t", j, v.dist_all[j]);
  }
  printf("\n");
}

void print_all_valves(valve nodes[input_nodes], int count){
  for (int i=0; i<count; i++){
    print_valve(nodes[i], count);
    printf("\n");
  }
}

bool int_in_array(int *array, int limit, int search_val){
  for (int i=0; i<limit; i++){
    if (array[i]==search_val){
      return true;
    }
  }
  return false;
}

int is_neighbour(valve nodes[input_nodes], valve cur_node, int count, int check_index, int visited[input_nodes], int visited_count){
  //could make this faster if I can tell is .dist_all has been set or not already
  //bfs would also be better than recursive
  printf("%c%c: checking for %d, visited count %d\n", cur_node.name[0], cur_node.name[1], check_index, visited_count);
  for (int i=0; i< cur_node.n_edges; i++){
    if(cur_node.edges[i]==check_index){
      return 1;
    }
  }
  int min_dist = count;
  int rec_dist = count;
  for (int i=0; i<cur_node.n_edges; i++){
    if (int_in_array(visited, visited_count, cur_node.edges[i])){
      printf("in visited\n");
      continue;
    }
    printf("visited count: %d\n", visited_count);
    visited[visited_count] = i;
    rec_dist = is_neighbour(nodes, nodes[cur_node.edges[i]], count, check_index, visited, visited_count+1);
    if (rec_dist<min_dist){
      min_dist = rec_dist;
    }
    printf("min_dist: %d, rec_dist: %d\n", min_dist, rec_dist);
  }
  return min_dist+1;
}

void set_distances(valve nodes[input_nodes], int count){
  for (int i=0; i<count; i++){
    //for each node set as source
    //set self as zero
    printf("node %d is source\n", i);
    for (int j=0; j<count; j++){
      printf("finding dist to node %d\n", j);
      if (j == i){
        nodes[i].dist_all[i]=0;
      }
      else {
        int visited[input_nodes] = {0};
        visited[0] = i;
        int visited_count =1;
        nodes[i].dist_all[j] = is_neighbour(nodes, nodes[i], count, j, visited, visited_count);
      }
    }
    printf("\n");
  }
  printf("end of set distances\n");
}

int main(void){
  valve nodes[input_nodes];
  int real_line;
  int cur_flow;
  char cur_name[3];
  int count = 0;

  int max_flow = 0;
  while(true){
    real_line = scanf("Valve %s has flow rate=%d; ", cur_name, &cur_flow);
    if (real_line !=2){
      break;
    }
    if (cur_flow > max_flow){
      max_flow = cur_flow;
    }
    int edge_count = 0;
    char cur_edges[T_LEN][3];
    char end_char;
    scanf("tunnel%*c lead%*c to valve%*c");
    while (true) {
      scanf(" %c%c%c", &cur_edges[edge_count][0], &cur_edges[edge_count][1], &end_char);
      cur_edges[edge_count][2] = '\0';
      edge_count++;
      if(end_char=='\n'){
        break;
      }
    }
    valve new_node = create_valve(cur_name, cur_flow, cur_edges, edge_count, count);
    nodes[count] = new_node;
    count++;
  }

  //construct edge lists
  for (int i=0;i<count;i++){
    for(int c=0; c<nodes[i].n_edges;c++){
      for (int j=0; j<count; j++){
        if (nodes[j].name[0]==nodes[i].edge_names[c][0]
        && nodes[j].name[1]==nodes[i].edge_names[c][1]){
          nodes[i].edges[c] = j;
          break;
        }
      }
    }
  }
  set_distances(nodes, count);
  printf("max flow: %d\n", max_flow);
  print_all_valves(nodes, count);

  // how to choose steps?
  // get 'shortest' distance to each point in graph from first point
  // minimum spanning tree?
  //
  //compute problem
  int current_flow = 0;
  int upcoming_flow = 0;
  int countdown = 0;
  int released_pressure = 0;
  for( int i=0; i<30; i++){
    // step through graph and add to upcoming flow (with countdown)
    // |_> when turning on valve
    // add current flow to released_pressure every step
  }
}
