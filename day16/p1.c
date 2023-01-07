#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>

#define T_LEN 10
#define NAME_S 3
#define max_nodes 60
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

typedef struct {
  char name[3];
  int flow;
  char edge_names[T_LEN][3];
  int edges[T_LEN];
  int n_edges;
  int dist_all[max_nodes];
  bool on;
} valve;

typedef struct {
  valve nodes[max_nodes];
  int n_nodes;
  int best;
} graph;


void print_valve(valve v, int count){
  printf("%c%c: %d, [%d]\n",  v.name[0], v.name[1], v.flow, v.n_edges);
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

void print_all_valves(valve nodes[max_nodes], int count){
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

int is_neighbour(valve nodes[max_nodes], valve cur_node, int count, int check_index, int visited[max_nodes], int visited_count){
  //could make this faster if I can tell if .dist_all has been set or not already
  //bfs would also be better than recursive
  //printf("%s: checking for %d, visited count %d\n",  cur_node.name, check_index, visited_count);
  for (int i=0; i< cur_node.n_edges; i++){
    if(cur_node.edges[i]==check_index){
      return 1;
    }
  }
  int min_dist = count;
  int rec_dist = count;
  for (int i=0; i<cur_node.n_edges; i++){
    if (int_in_array(visited, visited_count, cur_node.edges[i])){
      //printf("in visited\n");
      continue;
    }
    //printf("visited count: %d\n", visited_count);
    visited[visited_count] = cur_node.edges[i];
    rec_dist = is_neighbour(nodes, nodes[cur_node.edges[i]], count, check_index, visited, visited_count+1);
    if (rec_dist<min_dist){
      min_dist = rec_dist;
    }
    //printf("min_dist: %d, rec_dist: %d\n", min_dist, rec_dist);
  }
  return min_dist+1;
}

void set_distances(valve nodes[max_nodes], int count){
  for (int i=0; i<count; i++){
    //for each node set as source
    //printf("node %d is source\n", i);
    for (int j=0; j<count; j++){
      //printf("finding dist to node %d\n", j);
      //set self as zero
      if (j == i){
        nodes[i].dist_all[i]=0;
      }
      else {
        int visited[max_nodes] = {0};
        visited[0] = i;
        int visited_count =1;
        nodes[i].dist_all[j] = is_neighbour(nodes, nodes[i], count, j, visited, visited_count);
      }
    }
    //printf("\n");
  }
  //printf("end of set distances\n");
}

void read_input(graph * input){
  int real_line;
  int cur_flow;
  char cur_name[3];
  while(true){
    real_line = scanf("Valve %s has flow rate=%d; ", input->nodes[input->n_nodes].name, &input->nodes[input->n_nodes].flow);
    if (real_line !=2){
      break;
    }
    input->nodes[input->n_nodes].on = false;
    char end_char;
    int edge_count=0;
    scanf("tunnel%*c lead%*c to valve%*c");
    while (true) {
      scanf(" %c%c%c", &input->nodes[input->n_nodes].edge_names[edge_count][0],&input->nodes[input->n_nodes].edge_names[edge_count][1], &end_char);
      input->nodes[input->n_nodes].edge_names[edge_count][2] = '\0';
      edge_count++;
      if(end_char=='\n'){
        break;
      }
    }
    input->nodes[input->n_nodes].n_edges = edge_count;
    input->n_nodes++;
  }
}

int solve(graph * input, int cur_idx, int steps_left, int acc, int potential){
  valve *node_p = &input->nodes[cur_idx];
  valve node = *node_p;
  static long long total = 0;
  total++;
  if (steps_left <=1){
    if (acc > input->best){
      printf("%lld: %d, (%d)\n", total, acc, input->best);
      input->best = acc;
    }
    return acc;
  }

  int tmp_acc = acc;
  if (input->nodes[cur_idx].flow!=0 && !input->nodes[cur_idx].on){
    input->nodes[cur_idx].on=true;
    for (int i=0; i<input->n_nodes; i++){
      tmp_acc = MAX(tmp_acc, solve(input, i,  steps_left-1-input->nodes[cur_idx].dist_all[i],
                  acc+input->nodes[cur_idx].flow * (steps_left-1),
                  potential-input->nodes[cur_idx].flow));
    }
    input->nodes[cur_idx].on=false;
  }
  return tmp_acc;
}

int main(void){
  graph input;
  read_input(&input);
  //construct edge lists
  for (int i=0;i<input.n_nodes;i++){
    for(int c=0; c<input.nodes[i].n_edges;c++){
      for (int j=0; j<input.n_nodes; j++){
        if (input.nodes[j].name[0]==input.nodes[i].edge_names[c][0]
        && input.nodes[j].name[1]==input.nodes[i].edge_names[c][1]){
          input.nodes[i].edges[c] = j;
          break;
        }
      }
    }
  }
  set_distances(input.nodes, input.n_nodes);
  print_all_valves(input.nodes, input.n_nodes);
  int potential = 0;
  for (int i=0; i<input.n_nodes; i++){
    potential+=input.nodes[i].flow;
  }
  for (int i=0; i< input.nodes[0].n_edges; i++){
    solve(&input, input.nodes[0].edges[i], 29, 0, potential);
  }
  printf("%d\n", input.best);

  // how to choose steps?
  // get 'shortest' distance to each point in graph from first point
  // - need dist from every point
  //
  // - should i sort based on some combo of dist + flow
  // - should I just try searching (dfs?)
  // - n. poss combinatons is n_nodes! --> minus 0 nodes...
  // 6! for test=set i.e. 720 combinations
  // 15! for input i.e. 1.3e12
  // - can I find breakoff points e.g. if a path is already behind an already found path
  // and it's got less pressure after a certain number of steps
  // I should obviously cut it off?
  //
  // fully connected graph ---- can i break it down into sub problems?
  //
  //compute problem
  // -----
  // recursive solution
  // **use distance to compute possible flows (only plot paths to >0 flow nodes)
  // tree prune on potential flow + accumlated flow > best flow
  // 
  // step through graph and add to upcoming flow (with countdown)
  // |_> when turning on valve
  // add current flow to released_pressure every step
}
