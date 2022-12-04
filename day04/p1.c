#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pair {
  int a_min;
  int a_max;
  int b_min;
  int b_max;
};

int* parse_section(char* line, int* array) {
  array[0] = strtol(strtok(line, "-"), NULL, 10);
  array[1] = strtol(strtok(NULL, ""), NULL, 10);
}

struct pair parse_pairs(char* buffer) {
  char * a = strtok(buffer, ",");
  char * b = strtok(NULL, ",");
  int range_a[2];
  int range_b[2];
  parse_section(a, range_a);
  parse_section(b, range_b);
  struct pair elves = {.a_min=range_a[0], .a_max=range_a[1],
                       .b_min=range_b[0], .b_max=range_b[1]};
  return elves;
}

void main(void) {
  char lineBuffer[50];
  int count = 0;
  while(fgets(lineBuffer, 50, stdin)){
    struct pair e = parse_pairs(lineBuffer);
    if (e.a_min <= e.b_min && e.a_max >= e.b_max) {
      count++;
    }
    else if (e.b_min <= e.a_min && e.b_max >= e.a_max) {
      count++;
    }
  }
  printf("%d\n", count);
}
