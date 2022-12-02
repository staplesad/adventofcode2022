#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_new_ranking(int* max, int sum) {
      if (max[0] < sum) {
        max[2] = max[1];
        max[1] = max[0];
        max[0] = sum;
      }
      else if (max[1] < sum) {
        max[2] = max[1];
        max[1] = sum;
      }
      else if (max[2] < sum) {
        max[2] = sum;
      }
}

int main(void) {
  char lineBuffer[80];
  int elf_sum = 0;
  int n = 0;
  int max[3] = {0};
  while (fgets(lineBuffer, 80, stdin)) {
    if (strncmp(lineBuffer, "\n", 80)==0) {
      get_new_ranking(max, elf_sum);
      elf_sum = 0;
    }
    else {
      n = strtol(lineBuffer, NULL, 10);
      elf_sum += n;
    }
  }
  get_new_ranking(max, elf_sum);
  printf("%d\n", max[0]+max[1]+max[2]);
}
