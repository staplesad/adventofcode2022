#include <stdbool.h>
#include <stdio.h>

#define BUF_LEN 1000
//actually implement a tree?

bool valid_pair(char first[BUF_LEN], char second[BUF_LEN]){
  int i=0;
  int j=0;
  printf("first: %s\nsecond: %s\n", first, second);
  int promote_first = 0;
  int promote_second = 0;
  int first_indent = 0;
  int second_indent = 0;
  while(i<BUF_LEN && j<BUF_LEN){
    printf("loop i, j:\t%d, %d\nvals:\t%c, %c\n", i, j, first[i], second[j]);
    if (first[i]==second[j]){
      if (first[i] == '['){
        first_indent++;
      }
      else if(first[i] == ']'){
        first_indent--;
      }
      if (second[j] == '['){
        second_indent++;
      }
      else if(second[j] == ']'){
        second_indent--;
      }
      i++;
      j++;
    }
    else{
      if (first[i]=='\n'){
        return true;
      }
      else if (second[j]=='\n'){
        return false;
      }
      else if(first[i]=='['||second[j]=='['){
        if(first[i]=='['){
          promote_second++;
          i++;
        }
        else{
          promote_first++;
          j++;
        }
      }
      else if(first[i]==']'||second[j]==']'){
        if(first[i]==']'){
          if(promote_second+second_indent==first_indent && promote_second>0){
            promote_second--;
            i++;
            j++;
          }
          else{
            //first finishes early
            return true;
          }
        }
        else{
          if(promote_first>0){
            promote_first--;
            i++;
            j++;
          }
          else{
            //second finishes early
            return false;
          }
        }
      }
      else if(first[i]==','){
        i++;
      }
      else if(second[j]==','){
        j++;
      }
      else{
        if(first[i]<second[j]){
          return true;
        }
        else if(first[i]>second[j]){
          return false;
        }
        else{
          printf("not sure what other cases exist?\n");
          i++;
          j++;
        }
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
