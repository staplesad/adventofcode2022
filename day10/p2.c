#include <stdbool.h>
#include <stdio.h>
#include <string.h>


#define BUF_S 20
#define CHECK_S 6

bool noop(char buffer[BUF_S]){
  if (strcmp(buffer, "noop\n")==0){
    return 1;
  }
  return 0;
}

int addx(char buffer[BUF_S]){
  int val;
  sscanf(buffer, "addx %d\n", &val);
  return val;
}

bool check_count(int c){
  if (c>=20 && c%40==0){
    return true;
  }
  return false;
}

bool check_overlap(int centre, int cycle){
  for (int i = -1; i<2; i++){
    if (centre+i == cycle) {
      return true;
    }
  }
  return false;
}

void draw_pixel(int count, int x){
  if (check_overlap(x, (count-1)%40)){
    printf("#");
  }
  else {
    printf(".");
  }
  if (check_count(count)){
    printf("\n");
  }
};

int main(void){
  char buffer[BUF_S];
  int count =1;
  int x = 1;
  int cycle_val;

  while (fgets(buffer, BUF_S, stdin)){
    if (noop(buffer)){
      draw_pixel(count, x);
      count += 1;
    }
    else{
      cycle_val = addx(buffer);
      for (int i=0; i<2; i++){
        draw_pixel(count, x);
        count += 1;
      }
      x += cycle_val;
    }
  }
}
