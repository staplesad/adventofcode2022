#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>

#define HOLD_LEN 50

int parse_monkey(uint64_t monkey[HOLD_LEN], char * optype, int * opval, int * testval,int *true_idx, int *false_idx){
  int count = 0;
  int op;
  scanf(" Starting items: %d", &monkey[count]);
  count++;
  while (scanf(" , %d",  &monkey[count])!=0){
    count++;
  }
  op = scanf(" Operation: new = old %c %d", optype, opval);
  if (op < 2) {
    scanf("old");
    optype[0] = 'p';
    opval[0] = 2;
  }
  scanf(" Test: divisible by %d", testval);
  scanf(" If true: throw to monkey %d", true_idx);
  scanf(" If false: throw to monkey %d\n", false_idx);
  return count;
}

int main(void){
  uint64_t monkeys[8][HOLD_LEN] = {0};
  int opvals[8] = {0};
  char optypes[8];
  int testvals[8];
  int trueidx[8];
  int falseidx[8];
  int current_holding[8] = {0};
  char buffer[20];
  int count = 0;
  uint64_t total_held[8] = {0};

  while (!feof(stdin)){
    fgets(buffer, 20, stdin);
    current_holding[count] = parse_monkey(monkeys[count], &optypes[count], &opvals[count], &testvals[count], &trueidx[count], &falseidx[count]);
    count++;
  }

  uint64_t product_modulo = 1;
  for (int i=0;i<count; i++){
      product_modulo *= testvals[i];
  };

  int n_rounds=10000;
  for (int i =0; i<n_rounds; i++) {
    for (int m =0; m<count;m++) {
      for (int k=0; k< current_holding[m]; k++){
        total_held[m] += 1;
        switch(optypes[m]){
          case '+':
            monkeys[m][k] += opvals[m];
            break;
          case '*':
            monkeys[m][k] *= opvals[m];
            break;
          case 'p':
            monkeys[m][k] *= monkeys[m][k];
            break;
        }
        monkeys[m][k] = monkeys[m][k] % product_modulo;
        if (monkeys[m][k] % testvals[m] == 0){
          monkeys[trueidx[m]][current_holding[trueidx[m]]]= monkeys[m][k];
          current_holding[trueidx[m]]++;
        }
        else {
          monkeys[falseidx[m]][current_holding[falseidx[m]]]= monkeys[m][k];
          current_holding[falseidx[m]]++;
        }
        monkeys[m][k]=0;
      }
      current_holding[m] = 0;
    }
  }
  uint64_t maxes[2]={0};
  for (int i=0;i<count; i++){
    if (total_held[i] > maxes[0]){
      maxes[1] = maxes[0];
      maxes[0] = total_held[i];
    }
    else if (total_held[i] > maxes[1]){
      maxes[1] = total_held[i];
    }
  }
  printf("%"SCNu64"\n", maxes[0]*maxes[1]);
}
