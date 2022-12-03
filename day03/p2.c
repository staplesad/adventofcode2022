#include <stdio.h>
#include <stdbool.h>

#define LINE_LEN 50


int LOWER_CST = 96;
int UPPER_CST = 38;

int norm(int val) {
  if (val < 97) {
    return val - UPPER_CST;
  }
  return val - LOWER_CST;
}

bool is_in(char val, char* first) {
  for (int i=0; i<LINE_LEN; i++) {
    if (first[i]=='\n' || first[i]=='\0') {
      return false;
    }
    if (first[i]==val) {
      return true;
    }
  }
  return false;
}

void main(void) {
  char lineBuffer[3][LINE_LEN];
  int sep = 0;
  int running_sum = 0;
  while(fgets(lineBuffer[0], LINE_LEN, stdin)) {
    fgets(lineBuffer[1], LINE_LEN, stdin);
    fgets(lineBuffer[2], LINE_LEN, stdin);
    char overlap[LINE_LEN] = {'\0'};
    int count = 0;
    for (int i=0; i<LINE_LEN; i++) {
      if (lineBuffer[1][i] == '\n') {
        break;
      }
      if (is_in(lineBuffer[1][i], lineBuffer[0])){
        overlap[count] = lineBuffer[1][i];
        count++;
      }
    }
    for (int i=0; i<LINE_LEN; i++) {
      if (lineBuffer[2][i] == '\n') {
        break;
      }
      if (is_in(lineBuffer[2][i], overlap)) {
        running_sum += norm(lineBuffer[2][i]);
        break;
      }
    }
  }
  printf("%d\n", running_sum);
}
