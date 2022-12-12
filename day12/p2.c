#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

enum {
  width = 80,
  height = 41,
};

typedef struct {
  int x;
  int y;
} pos;

typedef struct {
  pos c_pos;
  int cur_len;
} explore_state;

int possible_steps(char map[height][width], int h, int w, pos cur, pos * next_steps){
  int count=0;
  pos new_pos[4]= {{cur.x, cur.y-1}, {cur.x, cur.y+1},{cur.x-1, cur.y},{cur.x+1, cur.y}};
  for (int i=0; i<4; i++){
    if (new_pos[i].x <0 || new_pos[i].y <0|| new_pos[i].x >=w|| new_pos[i].y >=h){
      continue;
    }
    else if (map[cur.y][cur.x]+1 >= (map[new_pos[i].y][new_pos[i].x])) {
      next_steps[count] = new_pos[i];
      count++;
    }
  }
  return count;
}


int main(void){
  char map[height][width];
  int h=0;
  int w=0;
  char buffer[width+2];
  char c;

  pos start_positions[3000];
  int n_start = 0;
  pos end_pos;

  printf("before input\n");
  while(fgets(buffer, width+2, stdin)){
    c = buffer[0];
    if (c=='\n'){
      break;
    }
    w = 0;
    while(c!='\n'){
      if (c=='S'){
        map[h][w]='a';
        start_positions[n_start].y = h;
        start_positions[n_start].x = w;
        n_start++;
      }
      else if(c=='a'){
        map[h][w]='a';
        start_positions[n_start].y = h;
        start_positions[n_start].x = w;
        n_start++;
      }
      else if (c=='E'){
        map[h][w]='z';
        end_pos.y = h;
        end_pos.x = w;
      }
      else{
        map[h][w] = c;
      }
      //printf("%c", c);
      w++;
      c=buffer[w];
    }
    //printf("\n");
    h++;
  }
  printf("before init min_path\n");
  uint16_t min_path[h][w];
  for (int i = 0; i< h; i++){
    for (int j= 0; j<w; j++){
        min_path[i][j] = w*h;
      }
    }
  printf("%d, %d, %d\n", h, w, n_start);
  pos next_steps[4];
  int step_amt;
  int stack_len = 100000;
  explore_state stack[stack_len];
  int stack_count=0;
  for (int i=0; i<n_start; i++){
    stack_count++;
    //printf("init stack at %d with (%d, %d)\n", stack_len-stack_count, start_positions[i].x, start_positions[i].y);
    min_path[start_positions[i].y][start_positions[i].x]=0;
    explore_state popped_state = {start_positions[i], 0};
    stack[stack_len-stack_count] = popped_state;
  }
  int current_len;
  explore_state popped_state;

  while (stack_count!=0) {
    popped_state = stack[stack_len-stack_count];
    stack_count--;
    //printf("popped state (%d, %d) len: %d start_pos:%d\n", popped_state.c_pos.x, popped_state.c_pos.y, popped_state.cur_len, popped_state.cur_star_pos);
    step_amt = possible_steps(map, h, w, popped_state.c_pos, next_steps);
    current_len = popped_state.cur_len+1;
    for (int i = 0; i < step_amt; i++) {
      pos next_pos = next_steps[i];
      if (min_path[next_pos.y][next_pos.x] > current_len){
        min_path[next_pos.y][next_pos.x] = current_len;
        if (next_pos.x == end_pos.x && next_pos.y==end_pos.y){
          continue;
        }
        else {
          stack_count++;
          explore_state next = {next_pos, current_len};
          stack[stack_len-stack_count] = next;
        }
      }
    }
  }
  printf("%d\n", min_path[end_pos.y][end_pos.x]);



}
