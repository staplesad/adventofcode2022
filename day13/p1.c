#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUF_LEN 1000
#define N_CHILD 66

typedef struct tree_node {
  bool leaf;
  union {
    int val;
    struct tree_node **children;
  };
  int n_children;
} tree_node;

typedef struct {
  int index;
  tree_node *node;
  bool valid;
} parse_object;

parse_object parse_node(char * input, int cur_pos){
  //printf("strlen: %d, pos: %d\n", strlen(input), cur_pos);
  switch (input[cur_pos]) {
    case '\0': {
                parse_object res = {.valid=false};
                return res;
               }
    case 'a':
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9': {
      tree_node *node = malloc(sizeof(tree_node));
      node->leaf = true;
      node->val = input[cur_pos] - '0';
      parse_object res= {.node=node, .index=cur_pos+1, .valid=true};
      return res;
    }
    case '[': {
      tree_node **children = malloc(sizeof(tree_node*)*N_CHILD);
      int count = 0;
      cur_pos++;
      while (input[cur_pos] != ']'){
        if (input[cur_pos]==','){
          cur_pos++;
          continue;
        }
        parse_object c = parse_node(input, cur_pos);
        if (!c.valid){
          break;
        }
        children[count] = c.node;
        count++;
        cur_pos = c.index;
      }
      tree_node * node = malloc(sizeof(tree_node));
      node->leaf=false;
      node->children=children;
      node->n_children=count;
      parse_object res = {.node=node, .index=cur_pos+1, .valid=true};
      return res;
    }
    default: {
      //printf("Reached default case in parsing switch. %d: %c", cur_pos, input[cur_pos]);
      parse_object res;
      return res;
    }
  }
}

int rec_comp(tree_node left, tree_node right){
  if (left.leaf && right.leaf) {
    if (left.val > right.val){
      return 0;
    }
    if (left.val < right.val){
      return 1;
    }
    return 2;
  } else if (!left.leaf && !right.leaf){
    int n_c = (left.n_children >= right.n_children) ? right.n_children : left.n_children;
    int res;
    for (int i=0;i<n_c;i++){
      res = rec_comp(*left.children[i], *right.children[i]);
      if (res != 2){
        return res;
      }
    }
    if (left.n_children > right.n_children){
      return 0;
    }
    if (left.n_children < right.n_children){
      return 1;
    }
    return 2;
  } else {
    tree_node ** children = malloc(sizeof(tree_node*));
    tree_node new_node = {.leaf=false, .children=children, .n_children=1};
    new_node.children[0] = malloc(sizeof(tree_node));
    if (left.leaf){
      *(new_node.children[0]) = left;
      return rec_comp(new_node, right);
    }
    *(new_node.children[0]) = right;
    return rec_comp(left, new_node);
  }
}

bool comp_vals(char * left, char * right){
  // parse trees
  parse_object res;
  res = parse_node(left, 0);
  tree_node left_root = *res.node;
  res = parse_node(right, 0);
  tree_node right_root = *res.node;
  //comp vals
  int r = rec_comp(left_root, right_root);
  //printf("res: %d", r);
  return (bool)r;
}


int main(void){
  char first[BUF_LEN];
  char second[BUF_LEN];

  int count = 0;
  int sum = 0;
  while(fgets(first, BUF_LEN, stdin)){
    count++;
    printf("count: %d\n", count);
    fgets(second, BUF_LEN, stdin);
    scanf(" ", stdin);
    if (comp_vals(first, second)){
      printf("true\n");
      sum += count;
    }
    else{
      printf("false\n");
    }
    //printf("\n");

  }
  printf("%d\n", sum);
}
