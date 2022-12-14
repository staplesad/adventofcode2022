#include <stdbool.h>
#include <stdio.h>

#define BUF_LEN 500
#define W 700
#define H 170
#define SOURCE 500


void print_matrix(int matrix[H][W], int new_start_x, int new_start_y, int new_end_x, int new_end_y){
  int start_X = 0;
  int start_Y = 0;
  int end_X = W;
  int end_Y = H;
  if(new_start_x!=0){
    start_X = new_start_x;
  }
  if(new_start_y!=0){
    start_Y=new_start_y;
  }
  if(new_end_x!=0){
    end_X = new_end_x;
  }
  if(new_end_y!=0){
    end_Y=new_end_y;
  }

  for(int j=start_Y;j<end_Y;j++){
    for(int i=start_X;i<end_X;i++){
      printf("%d", matrix[j][i]);
    }
    printf("\n");
  }
}

bool parse_line(char buffer[BUF_LEN], int matrix[][W], int* max_y){
  int from_x;
  int from_y;
  int to_x;
  int to_y;

  int y_start;
  int y_end;
  int x_start;
  int x_end;

  int eol;
  char temp;
  eol = scanf("%d,%d", &from_x, &from_y);
  if(eol!=2){
    return false;
  }
//  printf("outside loop: %d, %d\n", from_x, from_y);
  while (true){
    scanf("%c-%*c", &temp);
    if (temp==10){
      return true;
    }
//    printf("c: %d\n", temp);
    scanf("%d,%d", &to_x, &to_y);
//    printf("from: %d, %d\nto: %d, %d\n", from_x, from_y, to_x, to_y);
    if (from_y <= to_y){
      y_start = from_y;
      y_end = to_y;
    }
    else {
      y_start = to_y;
      y_end = from_y;
    }
    if (from_x <= to_x){
      x_start = from_x;
      x_end = to_x;
    }
    else {
      x_start = to_x;
      x_end = from_x;
    }
    if (x_start==x_end && y_start ==y_end){
      return false;
    }
    if (y_end > *max_y){
      *max_y = y_end;
    }
    for (int j=y_start; j<y_end+1; j++){
      for(int i=x_start; i<x_end+1; i++){
//        printf("%d, %d\n", i, j);
        matrix[j][i]=1;
      }
    }
    from_x = to_x;
    from_y = to_y;
  }
  return true;
}

int simulate_sand(int matrix[H][W]){
  int sand_x = SOURCE;
  int sand_y = -1;

  while(true){
    //printf("%d, %d\n", sand_x, sand_y);
    if (matrix[sand_y+1][sand_x]!=0){
      if (matrix[sand_y+1][sand_x-1]!=0){
        if (sand_x+1>=W){
          printf("Warning sand falling outside matrix bounds\n");
          return -1;
        }
        if(matrix[sand_y+1][sand_x+1]!=0){
          matrix[sand_y][sand_x]=2;
          return sand_y;
        }
        else {
          sand_x++;
        }
      }
      else{
        sand_x--;
      }
    }
    sand_y++;
  }
}

int main(void){
  int matrix[H][W] = {0};
  char buffer[BUF_LEN];

  int max_depth = 0;
  while(parse_line(buffer, matrix, &max_depth)){
    continue;
  }
  printf("%d\n", max_depth);
  max_depth += 2;
  for (int i=0;i<W;i++){
    matrix[max_depth][i]=1;
  }

  int count = 0;
  int last_hor_pos;
  while(true){
    last_hor_pos = simulate_sand(matrix);
    count++;
    if (last_hor_pos==0){
      break;
    }
  }
  printf("count: %d\n", count);
}
