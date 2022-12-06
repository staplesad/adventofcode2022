#include <stdio.h>
#include <stdbool.h>

#define NCHARS 4500

bool check_count(int count[26]){
  for(int i=0; i<26; i++){
    if (count[i]>1){
      return false;
    }
  }
  return true;
}

int c_to_i(char c){
  return ((int)c)-97;
}

void main(void) {
  char lineBuffer[NCHARS];
  fgets(lineBuffer, NCHARS, stdin);
  char running[4];
  int count[26]={0};

  for (int i=0; i<4;i++){
    count[c_to_i(lineBuffer[i])] += 1;
    running[i]=lineBuffer[i];
  }

  for (int i=4;i<NCHARS;i++){
    if (check_count(count)) {
      printf("%d\n", i);
      return;
    }
    count[c_to_i(running[i%4])] -=1;
    count[c_to_i(lineBuffer[i])] += 1;
    running[i%4]=lineBuffer[i];
  }
}
