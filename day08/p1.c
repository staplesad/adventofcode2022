#include <stdio.h>
#include <stdbool.h>

#define W 185
#define H 100


int load_line(int *tree_line, char* buffer){
  int i;
  for (i =0; i< W;i++){
    if (buffer[i]=='\n'){
      break;
    }
    tree_line[i] = (buffer[i] - '0');
  }
  return i;
}

void print_matrix(int matrix[H][W], int a_h, int a_w){
  for(int j=0;j<a_h;j++){
    for(int i=0;i<a_w;i++){
      printf("%d", matrix[j][i]);
    }
    printf("\n");
  }
}

void print_max(int matrix[H][W][4], int a_h, int a_w){
  for(int j=0;j<a_h;j++){
    for(int i=0;i<a_w;i++){
      printf("(%d, %d, %d, %d) ", matrix[j][i][0],matrix[j][i][1],matrix[j][i][2],matrix[j][i][3]);
    }
    printf("\n");
  }
}

int count_visable(int matrix[H][W], int a_h, int a_w){
  int count =0;
  int max[H][W][4];
  int tmp;
  // 0: max left
  // 1: max up
  // 2: max right
  // 3: max down
  // max left and max right?
  // max top and max bottom?
  for (int j=0;j<a_h; j++){
    for (int i=0;i<a_w;i++){
      if (i==0){
        max[j][i][0] = matrix[j][i];
      }
      else if(matrix[j][i] < max[j][i-1][0]){
        max[j][i][0] = max[j][i-1][0];
      }
      else if(matrix[j][i] >= max[j][i-1][0]){
        max[j][i][0] = matrix[j][i];
      }

      if (j==0){
        max[j][i][1] = matrix[j][i];
      }
      else if(matrix[j][i] < max[j-1][i][1]){
        max[j][i][1] = max[j-1][i][1];
      }
      else if(matrix[j][i] >= max[j-1][i][1]){
        max[j][i][1] = matrix[j][i];
      }

    }
  }
  //printf("\n");
  //print_max(max, a_h, a_w);
  for (int j=a_h-1;j>=0; j--){
    for (int i=a_w-1;i>=0; i--){
      if (i==a_w-1){
        max[j][i][2] = matrix[j][i];
      }
      else if(matrix[j][i] < max[j][i+1][2]){
        max[j][i][2] = max[j][i+1][2];
      }
      else if(matrix[j][i] >= max[j][i+1][2]){
        max[j][i][2] = matrix[j][i];
      }

      if (j==a_h-1){
        max[j][i][3] = matrix[j][i];
      }
      else if(matrix[j][i] < max[j+1][i][3]){
        max[j][i][3] = max[j+1][i][3];
      }
      else if(matrix[j][i] >= max[j+1][i][3]){
        max[j][i][3] = matrix[j][i];
      }
    }
  }
  //printf("\n");
  //print_max(max, a_h, a_w);
  
  //
  // then count?
  int x;
  int y;
  for (int j=1;j<a_h-1; j++){
    for (int i=1;i<a_w-1;i++){
      for (int k=0;k<4;k++){
        switch(k){
          case 0:
            x = i-1;
            y= j;
            break;
          case 1:
            x = i;
            y=j-1;
            break;
          case 2:
            x=i+1;
            y=j;
            break;
          case 3:
            x=i;
            y= j+1;
            break;
        }
        if (matrix[j][i] > max[y][x][k]){
          count += 1;
          break;
        }
      }
    }
  }
  count += 2*a_h+2*(a_w-2);
  return count;
}
int main(void) {
  int trees[H][W];
  char lineBuffer[W];
  int count = 0;
  int act_w;
  while(fgets(lineBuffer, W, stdin)){
    act_w = load_line(trees[count], lineBuffer);
    count++;
  }
  //print_matrix(trees, count, act_w);
  printf("%d\n",count_visable(trees, count, act_w));
  return 0;
}
