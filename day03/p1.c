#include <stdio.h>
#include <stdbool.h>

int LOWER_CST = 96;
int UPPER_CST = 38;

int norm(int val) {
  if (val < 97) {
    return val - UPPER_CST;
  }
  return val - LOWER_CST;
}

bool is_in_half(int val, int* half, int half_len) {
  for (int i=0; i<half_len; i++) {
    if (val==half[i]) {
      return true;
    }
  }
  return false;
}

void main(void) {
  char lineBuffer[100];
  int values[100] = {0};
  int sep = 0;
  int running_sum = 0;
  while(fgets(lineBuffer, sizeof(lineBuffer), stdin)) {
    int count = 0;
    for (int i=0; i<sizeof(lineBuffer); i++) {
      if (lineBuffer[i] == '\n') {
        break;
      }
      count+=1;
      values[i] = norm(lineBuffer[i]);
     }
    sep = (count / 2);
    for (int i = sep; i<=count; i++) {
      if (is_in_half(values[i], values, sep)) {
          running_sum += values[i];
          break;
      }
    }
  }
  printf("%d\n", running_sum);
}
