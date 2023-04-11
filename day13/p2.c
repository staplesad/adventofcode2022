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

bool eq_tree(tree_node a, tree_node b){
  if (a.leaf && b.leaf){
    if (a.val == b.val){
      return true;
    }
  }
  if (!a.leaf && !b.leaf){
    if (a.n_children!=b.n_children){
      return false;
    }
    for (int i=0; i< a.n_children; i++){
      if(!eq_tree(*a.children[i], *b.children[i])){
        return false;
      }
    }
    return true;
  }
  return false;
}
int find_trees(tree_node * all_nodes, tree_node a, tree_node b, int count){
  int prod = 1;
  for (int i=0;i<count;i++){
    if (eq_tree(all_nodes[i], a) || eq_tree(all_nodes[i], b)){
      printf("%d\n", i+1);
      prod *= (i+1);
    }
  }
  return prod;
}

void print_tree(tree_node n){
  if (n.leaf) {
    putchar(n.val+'0');
  } else {
    putchar('[');
    for (int i =0;i<n.n_children;i++){
      print_tree(*n.children[i]);
      if (i!=(n.n_children-1)){
        putchar(',');
      }
    }
    putchar(']');
  }
}

int rev_comp(const void * left, const void * right){
  int res;
  res = rec_comp(*(tree_node*)left, *(tree_node*)right);
  if (res == 0){
    return 1;
  }
  else{
    return -1;
  }
}

int main(void){
  char first[BUF_LEN];
  char second[BUF_LEN];

  int count = 2;
  parse_object res;
  res = parse_node("[[2]]", 0);
  tree_node a = *res.node;
  res = parse_node("[[6]]", 0);
  tree_node b = *res.node;
  tree_node * all_nodes = malloc(sizeof(tree_node)*500);
  all_nodes[0] = a;
  all_nodes[1] = b;

  while(fgets(first, BUF_LEN, stdin)){
    fgets(second, BUF_LEN, stdin);
    scanf(" ", stdin);
    res = parse_node(first, 0);
    all_nodes[count] = *res.node;
    count++;
    res = parse_node(second, 0);
    all_nodes[count] = *res.node;
    count++;
    printf("count: %d\n", count);
  }
  //add a tree print func?
  qsort(all_nodes, count, sizeof(tree_node), rev_comp);
  for (int i=0;i<count;i++){
    print_tree(all_nodes[i]);
    putchar('\n');
  }
  int prod;
  prod = find_trees(all_nodes, a, b, count);
  printf("%d\n", prod);
}
