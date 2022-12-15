#include <stdbool.h>
#include <stdio.h>

#define BUF_LEN 1000

bool valid_pair(char first[BUF_LEN], char second[BUF_LEN]){
  int j=0;
  printf("first: %s\nsecond: %s\n", first, second);
  int promote_first = 0;
  int promote_second = 0;
  for (int i = 0; i<BUF_LEN; i++){
    printf("i, j: %d, %d\n", i, j);
    if (first[i] == ','){
      if (second[j]==']'){
        nested_end_skip:
          if (promote_first>0){
            promote_first--;
            j++;
            if (j==']'){
              goto nested_end_skip;
            }
            else{
              j++;
            }
          }
          else{
            printf("second ends early\n");
            return false;
          }
      }
      else{
      j++;
      }
    }
    else if (first[i] =='['){
      if (second[j]=='['){
        j++;
      }
      else if(second[j]==']'){
        printf("second ends early\n");
        return false;
      }
      else {
        promote_second++;
      }
    }
    else if (first[i]==']'){
      if (second[j]==']'){
        j++;
      }
      else if(promote_second>0){
        j++;
        promote_second--;
      }
      else{
        printf("first ends early\n");
        return true;
      }
    }
    else{
      if (second[j]=='['){
        nested_start:
          promote_first++;
          j++;
          if(second[j]=='['){
            goto nested_start;
          }
      }
      else if (second[j]==']'){
        nested_end:
          if (promote_first>0){
            promote_first--;
            j++;
            if (j==']'){
              goto nested_end;
            }
            else{
              j++;
            }
          }
          else{
            printf("second ends early\n");
            return false;
          }
      }
      if (first[i] < second[j]){
        printf(" %c value is less than %c\n", first[i], second[j]);
        return true;
      }
      else if(first[i]>second[j]){
        printf(" %c value is greater than %c\n", first[i], second[j]);
        return false;
      }
      else{
        j++;
      }
    }
  }
}

int main(void){
  char first[BUF_LEN];
  char second[BUF_LEN];

  int count = 0;
  int sum = 0;
  while(fgets(first, BUF_LEN, stdin)){
    count++;
    fgets(second, BUF_LEN, stdin);
    scanf(" ", stdin);
    if (valid_pair(first, second)){
      printf("true\n");
      sum += count;
    }
    else{
      printf("false\n");
    }
    printf("\n");

  }
  printf("%d\n", sum);
}
