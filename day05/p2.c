#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define STACKS 9
#define CRATES 50
#define NMOVES 520

bool read_line(char* buffer, char crates[STACKS][CRATES], int current_line) {
  int count = 0;
  char c;
  for (int i=0;i<50;i++){
    c = buffer[i];
    if (c==' ') {
      count +=1;
      if (isdigit(buffer[i+1])){
        return true;
      }
      i+=3;
      continue;
    }
    else if(c=='\0'||c=='\n') {
      return false;
    }
    else if (c=='[') {
      for (int j=CRATES-1; j>=0; j--){
        if (!isalpha(crates[count][j])){
          crates[count][j] = buffer[i+1];
          break;
        }
      }
      count += 1;
      i += 3;
    }
  }
  return false;
}

bool sisdigit(char* str) {
  int i = 0;
  while(true) {
    if (isdigit(str[i])) {
      i += 1;
    }
    else if (str[i]=='\0'||str[i]=='\n') {
      return true;
    }
    else if (i>50) {
    }
    else {
      return false;
    }
  }
}

void get_move(char* buffer, int moves[NMOVES][3], int current_line) {
  int move_n = 0;
  bool loop = true;
  char* section;
  int num;
  section = strtok(buffer, " ");
  while(loop){
    if (move_n>2){
      return;
    }
    else if (section==NULL) {
      return;
    }
    else if (sisdigit(section)) {
      num = strtol(section, NULL, 10);
      if (move_n!=0){
        moves[current_line][move_n] = num-1;
      }
      else {
        moves[current_line][move_n] = num;
      }
      move_n += 1;
    }
    section = strtok(NULL, " ");
  }
}

void print_crates(char boxes[STACKS][CRATES]){
  for (int i=0; i< CRATES; i++){
    for (int j=0; j< STACKS; j++){
      if (isalpha(boxes[j][i])){
        printf("[%c] ", boxes[j][i]);
      }
      else {
        printf("    ");
      }
    }
    printf("\n");
  }
}

void move_box(char boxes[STACKS][CRATES], int from, int to, int move_n) {
  char replace[CRATES]="";
  char tmp;
  int count=0;
  for (int i=CRATES-1; i>=0; i--){
    if (!isalpha(boxes[from][i])){
      break;
    }
    if (count!=move_n){
      replace[count] = boxes[from][i];
      count++;
    }
    boxes[from][i] = boxes[from][i-move_n];
  }
  count=0;
  for (int i=CRATES-1; i>=0; i--) {
    tmp = boxes[to][i];
    boxes[to][i] = replace[count];
    replace[count]=tmp;
    if (count<move_n-1){
      count++;
    }
    else {
      count=0;
    }
  }
//  print_crates(boxes);
}

void main(void) {
  char crates[STACKS][CRATES] ={""};
  char lineBuffer[50];
  int moves[NMOVES][3] = {0};
  bool end_of_state=false;
  int line_count = 0;
  int move_line_s;

  while(fgets(lineBuffer, 50, stdin)) {
    line_count += 1;
    if (end_of_state) {
      if (line_count < move_line_s){
        continue;
      }
      get_move(lineBuffer, moves, line_count-move_line_s);
    }
    else {
      end_of_state = read_line(lineBuffer, crates, line_count);
      move_line_s = line_count + 2;
    }
  }

  print_crates(crates);
  for (int i=0; i<NMOVES; i++){
    if (moves[i][0] == 0){
      break;
    }
    move_box(crates, moves[i][1], moves[i][2], moves[i][0]);
  }
  char concat[STACKS+1];
  int str_cnt = 0;
  for (int i=0; i<STACKS; i++){
    if (isalpha(crates[i][CRATES-1])) {
      concat[str_cnt] = crates[i][CRATES-1];
      str_cnt++;
    }
  }
  concat[str_cnt]='\0';
  printf("%s\n", concat);
}
