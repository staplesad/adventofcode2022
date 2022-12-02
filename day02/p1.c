#include<stdio.h>

int choice_score(char me){
  switch(me) {
    case 'X':
      return 1;
    case 'Y':
      return 2;
    case 'Z':
      return 3;
  }
}

char transform(char opp) {
  switch(opp) {
    case 'A':
      return 'X';
    case 'B':
      return 'Y';
    case 'C':
      return 'Z';
  }
}

int match_score(char opp, char me) {
  if (me == transform(opp)) {
    return 3;
  }
  switch(opp) {
    case 'A':
      if (me=='Y') {return 6;}
      if (me=='Z') {return 0;}
    case 'B':
      if (me=='Z') {return 6;}
      if (me=='X') {return 0;}
    case 'C':
      if (me=='X') {return 6;}
      if (me=='Y') {return 0;}
  }
}

int main(void) {
  char lineBuffer[5];
  char opp;
  char me;
  int score = 0;
  int count = 0;
  while (fgets(lineBuffer, 5, stdin)) {
    count += 1;
    opp = lineBuffer[0];
    me = lineBuffer[2];
    score += (choice_score(me) + match_score(opp, me));
  }
  printf("%d\n", score);
}
