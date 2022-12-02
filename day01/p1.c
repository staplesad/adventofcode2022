#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  char lineBuffer[80];
  int elf_sum = 0;
  int n = 0;
  int max = 0;
  while (fgets(lineBuffer, 80, stdin)) {
    if (strncmp(lineBuffer, "\n", 80)==0) {
      if (max < elf_sum) {
        max = elf_sum;
      }
      elf_sum = 0;
    }
    else {
      n = strtol(lineBuffer, NULL, 10);
      elf_sum += n;
    }
  }
  printf("%d\n", max);
}
