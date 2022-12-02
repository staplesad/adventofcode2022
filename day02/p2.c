#include<stdio.h>

int match_score(char outcome){
  switch(outcome) {
    case 'X':
      return 0;
    case 'Y':
      return 3;
    case 'Z':
      return 6;
  }
}

int get_play(char opp, char outcome) {
  switch(outcome) {
    case 'X':
      if (opp=='A') {return 3;}
      if (opp=='B') {return 1;}
      if (opp=='C') {return 2;}
    case 'Y':
      if (opp=='A') {return 1;}
      if (opp=='B') {return 2;}
      if (opp=='C') {return 3;}
    case 'Z':
      if (opp=='A') {return 2;}
      if (opp=='B') {return 3;}
      if (opp=='C') {return 1;}
  }
}

int main(void) {
  char lineBuffer[5];
  char opp;
  char outcome;
  int score = 0;
  int count = 0;
  while (fgets(lineBuffer, 5, stdin)) {
    count += 1;
    opp = lineBuffer[0];
    outcome = lineBuffer[2];
    score += (get_play(opp, outcome) + match_score(outcome));
  }
  printf("%d\n", score);
}
