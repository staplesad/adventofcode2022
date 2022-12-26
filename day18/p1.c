#include <stdio.h>
#include <stdbool.h>

#define MAX_CUBES 2765
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
      printf("%d, item(%d), current(%d)\n", match, i, current);
      val--;
    }
    if (val==0){
      break;
    }
  }
  return val;
}

int solve(grid *input){
  int max;
  int running_sum=0;
  for(int i=0; i<input->n_items;i++){
    int open_sides = n_uncovered_side(i, input);
    running_sum = running_sum+open_sides;
    printf("opensides: %d, running_sum:%d\n", open_sides, running_sum);
    printf("\n");
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
