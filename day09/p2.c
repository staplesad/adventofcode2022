#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define BUF_S 5
#define L 10000

bool pos_in_array(int val_x, int val_y, int array[L][2], int current_size){
  for (int i=0; i<current_size; i++){
    if (array[i][0]==val_x && array[i][1]==val_y){
      return true;
    }
  }
  return false;
}
int get_max_dist(int h_x, int h_y, int t_x, int t_y){
  int hor_dist = abs(h_x-t_x);
  int ver_dist = abs(h_y-t_y);
  if (hor_dist > 2 || ver_dist > 2){
    printf("somehow the head got too far away");
  }
  if (hor_dist >= ver_dist){
    return hor_dist;
  }
  return ver_dist;
}

int get_directional_change(int h, int t){
  if (h-t<0){
    return -1;
  }
  else if (h-t>0){
    return 1;
  }
  else{
    return 0;
  }
}

int main(void){
  int visited[L][2];
  visited[0][0] = 0;
  visited[0][1] = 0;
  char lineBuffer[BUF_S];
  int count = 1;

  char dir;
  int steps;
  
  int knot_pos[10][2]={0};
  int tail_idx = 9;
  while(fgets(lineBuffer, BUF_S, stdin)){
    printf("%s", lineBuffer);
    sscanf(lineBuffer, "%c %d\n", &dir, &steps);
    printf("indexes: %d, %d, %d, %d\n", knot_pos[0][0], knot_pos[0][1], knot_pos[tail_idx][0], knot_pos[tail_idx][1]);
    printf("dir: %c, steps: %d\n", dir, steps);
    printf("current count:%d\n", count);
    for (int s=0; s< steps; s++){
      switch(dir){
        case 'R':
          knot_pos[0][0]= knot_pos[0][0]+1;
          break;
        case 'L':
          knot_pos[0][0] = knot_pos[0][0]-1;
          break;
        case 'U':
          knot_pos[0][1] = knot_pos[0][1]+1;
          break;
        case 'D':
          knot_pos[0][1] = knot_pos[0][1]-1;
          break;
      }
      for (int i=1; i< tail_idx+1; i++){
        if (get_max_dist(knot_pos[i-1][0], knot_pos[i-1][1], knot_pos[i][0], knot_pos[i][1])> 1){
          knot_pos[i][0] += get_directional_change(knot_pos[i-1][0], knot_pos[i][0]);
          knot_pos[i][1] += get_directional_change(knot_pos[i-1][1], knot_pos[i][1]);
          if (i==tail_idx){
            if (!pos_in_array(knot_pos[i][0], knot_pos[i][1], visited, count)){
              visited[count][0] = knot_pos[i][0];
              visited[count][1] = knot_pos[i][1];
              count+=1;
            }
          }
        }
      }
    }
  }
  printf("%d\n", count);
}
