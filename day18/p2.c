#include <stdio.h>
#include <stdbool.h>

#define MAX_CUBES 2765
#define MAX_AXIS 22
#define BUF_LEN 10
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

typedef struct {
  int x;
  int y;
  int z;
} cube;

typedef struct {
  cube items[MAX_CUBES];
  cube max_vals;
  int n_items;
} grid;

void read_input(grid *input){
  char buffer[BUF_LEN];
  input->n_items=0;
  while (fgets(buffer, BUF_LEN, stdin)){
    sscanf(buffer, "%d,%d,%d",
           &input->items[input->n_items].x,
           &input->items[input->n_items].y,
           &input->items[input->n_items].z);
    if (input->items[input->n_items].x > input->max_vals.x){
      input->max_vals.x = input->items[input->n_items].x;
    }
    if (input->items[input->n_items].y > input->max_vals.y){
      input->max_vals.y = input->items[input->n_items].y;
    }
    if (input->items[input->n_items].z > input->max_vals.z){
      input->max_vals.z = input->items[input->n_items].z;
    }
   input->n_items++;
  }
}

void print_items(grid *input){
  for (int i=0;i<input->n_items; i++){
    printf("%d, %d, %d\n", input->items[i].x, input->items[i].y, input->items[i].z);
  }
  printf("Maxes:\n");
  printf("%d, %d, %d\n", input->max_vals.x, input->max_vals.y, input->max_vals.z);
}

enum Side {
  X = 1,
  Y = 2,
  Z = 3,
  None = 0
};

enum Side any_two_match(cube a, cube b){
  if(a.x==b.x && a.y==b.y){
    return Z;
  }
  if(a.x==b.x && a.z==b.z){
    return Y;
  }
  if(a.y==b.y && a.z==b.z){
    return X;
  }
  return None;
}

int n_uncovered_side(int current, grid * input){
  int left;
  int right;
  int val=6;
  for (int i=0; i<input->n_items; i++){
    if (i==current){
      continue;
    }
    enum Side match = any_two_match(input->items[current], input->items[i]);
    bool touching = false;
    switch (match){
      case X:
        left = input->items[current].x-1;
        right = input->items[current].x+1;
        if(input->items[i].x==left || input->items[i].x==right){
          touching = true;
        }
        break;
      case Y:
        left = input->items[current].y-1;
        right = input->items[current].y+1;
        if(input->items[i].y==left || input->items[i].y==right){
          touching = true;
        }
        break;
      case Z:
        left = input->items[current].z-1;
        right = input->items[current].z+1;
        if(input->items[i].z==left || input->items[i].z==right){
          touching = true;
        }
        break;
      case None:
        break;
    }
    if (touching) {
      //printf("%d, item(%d), current(%d)\n", match, i, current);
      val--;
    }
    if (val==0){
      break;
    }
  }
  return val;
}

int check_side(bool full_grid[][MAX_AXIS][MAX_AXIS], cube current, enum Side side, cube max){
  int left;
  int right;
  int n_neighbours = 0;
  //printf("curr_point: %d\n", full_grid[current.z][current.y][current.x]);
  switch(side){
    case X:
      left = current.x - 1;
      right = current.x + 1;
      if (current.x==0){
        if (full_grid[current.z][current.y][right]){
          return 1;
        }
      }
      else if(current.x==max.x){
        if (full_grid[current.z][current.y][left]){
          return 1;
        }
      }
      else {
        if (full_grid[current.z][current.y][right]){
          n_neighbours++;
        }
        if (full_grid[current.z][current.y][left]){
          n_neighbours++;
        }
        return n_neighbours;
      }
      break;
    case Y:
      left = current.y - 1;
      right = current.y + 1;
      if (current.y==0){
        if (full_grid[current.z][right][current.x]){
          return 1;
        }
      }
      else if(current.y==max.y){
        if (full_grid[current.z][left][current.x]){
          return 1;
        }
      }
      else {
        if (full_grid[current.z][left][current.x]){
          n_neighbours++;
        }
        if (full_grid[current.z][right][current.x]){
          n_neighbours++;
        }
        return n_neighbours;
      }
      break;
    case Z:
      left = current.z - 1;
      right = current.z + 1;
      if (current.z==0){
        if (full_grid[right][current.y][current.x]){
          return 1;
        }
      }
      else if(current.z==max.y){
        if (full_grid[left][current.y][current.x]){
          return 1;
        }
      }
      else {
        if (full_grid[left][current.y][current.x]){
          n_neighbours++;
        }
        if (full_grid[right][current.y][current.x]){
          n_neighbours++;
        }
        return n_neighbours;
      }
      break;
    case None:
      return 0;
      break;
  }
  return n_neighbours;
}

int has_direct_neighbour(bool full_grid[][MAX_AXIS][MAX_AXIS], cube current, cube max_vals){
  int n_neighbours = 0;
  n_neighbours = n_neighbours + check_side(full_grid, current, X, max_vals);
  n_neighbours = n_neighbours + check_side(full_grid, current, Y, max_vals);
  n_neighbours = n_neighbours + check_side(full_grid, current, Z, max_vals);
  return n_neighbours;
}

bool is_in_pocket(bool full_grid[][MAX_AXIS][MAX_AXIS], cube current, cube max_vals){
  //follow all 6 directions and check if I encounter the edge or another cube;
  //TODO flood fill b/c path out might not be straight 
  int m;
  bool reached_edge=true;
  for (m = current.x; m>=0; m--){
    if (full_grid[current.z][current.y][m]){
      reached_edge=false;
      break;
    }
  }
  if (reached_edge){
    return false;
  }
  //
  reached_edge=true;
  for (m = current.x; m<=max_vals.x; m++){
    if (full_grid[current.z][current.y][m]){
      reached_edge=false;
      break;
    }
  }
  if (reached_edge){
    return false;
  }
  // y axis
  reached_edge=true;
  for (m = current.y; m>=0; m--){
    if (full_grid[current.z][m][current.x]){
      reached_edge=false;
      break;
    }
  }
  if (reached_edge){
    return false;
  }
  //
  reached_edge=true;
  for (m = current.y; m<=max_vals.y; m++){
    if (full_grid[current.z][m][current.x]){
      reached_edge=false;
      break;
    }
  }
  if (reached_edge){
    return false;
  }
  // z axis
  reached_edge=true;
  for (m = current.z; m>=0; m--){
    if (full_grid[m][current.y][current.x]){
      reached_edge=false;
      break;
    }
  }
  if (reached_edge){
    return false;
  }
  //
  reached_edge=true;
  for (m = current.z; m<=max_vals.z; m++){
    if (full_grid[m][current.y][current.x]){
      reached_edge=false;
      break;
    }
  }
  if (reached_edge){
    return false;
  }
  return true;
}

int solve(grid *input){
  int running_sum=0;
  bool full[MAX_AXIS][MAX_AXIS][MAX_AXIS];
  for (int k=0;k<input->max_vals.z+1;k++){
    for (int j=0;j<input->max_vals.y+1;j++){
      for (int i=0;i<input->max_vals.x+1;i++){
        full[k][j][i] = 0;
      }
    }
  }
  for(int i=0; i<input->n_items;i++){
    full[input->items[i].z][input->items[i].y][input->items[i].x] =1;
    int open_sides = n_uncovered_side(i, input);
    running_sum = running_sum+open_sides;
    //printf("opensides: %d, running_sum:%d\n", open_sides, running_sum);
    //printf("\n");
  }
  for (int k=0;k<input->max_vals.z+1;k++){
    for (int j=0;j<input->max_vals.y+1;j++){
      for (int i=0;i<input->max_vals.x+1;i++){
        if(!full[k][j][i]){
          cube empty = {i, j, k};
          //printf("%d, %d, %d\n", i, j, k);
          int n_neighbours = has_direct_neighbour(full, empty, input->max_vals);
          if(n_neighbours>0){
            //printf("n_neighbours: %d\n", n_neighbours);
            if (is_in_pocket(full, empty, input->max_vals)){
                running_sum = running_sum - n_neighbours;
            }
          }
        }
      }
    }
  }
  return running_sum;
}


int main(void){
  grid input;
  int answer=-1;
  read_input(&input);
  print_items(&input);
  answer = solve(&input);
  printf("Ans: %d\n", answer);
}
