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

  int h_x = 0;
  int h_y = 0;

  int t_x = 0;
  int t_y = 0;

  while(fgets(lineBuffer, BUF_S, stdin)){
    printf("%s", lineBuffer);
    sscanf(lineBuffer, "%c %d\n", &dir, &steps);
    printf("indexes: %d, %d, %d, %d\n", h_x, h_y, t_x, t_y);
    printf("dir: %c, steps: %d\n", dir, steps);
    printf("current count:%d\n", count);
    for (int s=0; s< steps; s++){
      switch(dir){
        case 'R':
          h_x= h_x+1;
          break;
        case 'L':
          h_x = h_x-1;
          break;
        case 'U':
          h_y = h_y+1;
          break;
        case 'D':
          h_y = h_y-1;
          break;
      }
      if (get_max_dist(h_x, h_y, t_x, t_y)> 1){
        //get directions for horizontal + vertical
        t_x += get_directional_change(h_x, t_x);
        t_y += get_directional_change(h_y, t_y);
        if (!pos_in_array(t_x, t_y, visited, count)){
          visited[count][0] = t_x;
          visited[count][1] = t_y;
          count+=1;
        }
      }
    }
  }
  printf("%d\n", count);
}
