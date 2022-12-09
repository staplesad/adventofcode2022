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
  int left;
  int right;
  int up;
  int down;
  int max = 0;
  for (int j=1;j<a_h-1; j++){
    for(int i=1;i<a_w-1;i++){
      //looking left
      for (int k=1;k<=i;k++){
        if (matrix[j][i-k] >= matrix[j][i]){
          left = k;
          break;
        }
        else if(k==i){
          left=k;
        }
      }
      for (int k=1;k<(a_w-i);k++){
        if (matrix[j][i+k] >= matrix[j][i]){
          right = k;
          break;
        }
        else if(k==(a_w-i-1)){
          right=k;
        }
      }
      for (int k=1;k<=j;k++){
        if (matrix[j-k][i] >= matrix[j][i]){
          up = k;
          break;
        }
        else if(k==j){
          up=k;
        }
      }
      for (int k=1;k<(a_h-j);k++){
        if (matrix[j+k][i] >= matrix[j][i]){
          down = k;
          break;
        }
        else if(k==(a_h-j-1)){
          down=k;
        }
      }
      if (left*right*up*down > max){
        max = left*right*up*down;
      }
      //printf("(%d,%d,%d,%d) ", left,right,up,down);
    }
    //printf("\n");
  }
  return max;
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
