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

bool check_count(int c, int seen, int checkpoints[CHECK_S]){
  if (checkpoints[seen]==c){
    return true;
  }
  return false;
}

int main(void){
  char buffer[BUF_S];
  int count =1;
  int x = 1;
  int cycle_val;
  int seen_signals=0;
  //20th, 60th, 100th, 140th, 180th, and 220th
  int checkpoints[CHECK_S]={20, 60, 100, 140, 180, 220};
  int signals[CHECK_S];

  while (fgets(buffer, BUF_S, stdin)){
    if (noop(buffer)){
      if (check_count(count, seen_signals, checkpoints)){
        signals[seen_signals]= count * x;
        seen_signals += 1;
      }
      count += 1;
    }
    else{
      cycle_val = addx(buffer);
      for (int i=0; i<2; i++){
        if (check_count(count, seen_signals, checkpoints)){
          printf("%d: %d (%d, %d)\n", count, x, i, cycle_val);
          signals[seen_signals]= count * x;
          seen_signals += 1;
        }
        count += 1;
      }
      x += cycle_val;
    }
  }
  int res=0;
  for(int i=0; i<CHECK_S; i++){
    res += signals[i];
    printf("%d, ", signals[i]);
  }
  printf("\n");
  printf("%d\n", res);
}
