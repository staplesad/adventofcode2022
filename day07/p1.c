#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define BASE_S 15
#define NAME_S 20
#define IN_S 60

struct node {
  int size;
  bool is_dir;
  char dir_name[NAME_S];
  struct node * parent;
  struct node * children;
  size_t space;
  int num_children;
};

struct node init_node(int size, bool is_dir, char dir_name[NAME_S], struct node* parent) {
  struct node * children;
  size_t base_size = BASE_S * sizeof *children;
  children = malloc(base_size);
  struct node n = {.size=size, .is_dir=is_dir, .dir_name="",
    .parent=parent, .children=children,
    .space=base_size, .num_children=0};
  strncpy(n.dir_name, dir_name, NAME_S);
  return n;
}

bool is_full(size_t space, int num_used) {
  if (space == (num_used * sizeof(struct node))){
    return true;
  }
  return false;
}

void add_child(struct node *n, int size, bool is_dir, char dir_name[NAME_S]) {
  struct node new_node = init_node(size, is_dir, dir_name, n);
  if (is_full(n->space, n->num_children)) {
    printf("children of %s is full alloc more\n", n->dir_name);
    struct node * tmp = realloc(n->children, (3/2)* n->num_children*sizeof(struct node));
    if (tmp!=NULL){
      n->children = tmp;
    }
    else {
      printf("error! couldn't allocate memory");
    }
  }
  n->children[n->num_children] = new_node;
  n->num_children += 1;
}

struct node* find_dir(struct node* n, char name[NAME_S]){
  //need to traverse children of n and return correct child;
  struct node nn;
  for (int i =0; i<n->num_children; i++){
    nn = n->children[i];
    if (nn.is_dir){
      if (strcmp(nn.dir_name, name)==0){
        return &n->children[i];
      }
    }
  }
  printf("Didn't find dir %s in dir %s\n", name, n->dir_name);
  return NULL;
}

void print_tree(struct node n){
  struct node nn;
  printf("tree: %s\n", n.dir_name);
  for (int i=0; i< n.num_children; i++){
    nn = n.children[i];
    printf("size: %d, is_dir: %d, dirname: %s, n_children: %d\n", nn.size, nn.is_dir, nn.dir_name, nn.num_children);
    if (nn.is_dir) {
      printf("|_\n");
      print_tree(nn);
    }
  }
}

enum line_type {cd, ls, file};

enum line_type cd_command(char * buffer){
  if (strncmp(buffer, "$ cd", 4)==0) {
    return cd;
  }
  if (strncmp(buffer, "$ ls", 4)==0) {
    return ls;
  }
  return file;
}

int get_size(char * buffer){
  if (strncmp(buffer, "dir", 3)==0) {
    return -1;
  }
  int size;
  sscanf(buffer, "%d ", &size);
  return size;
}

void get_name(char * buffer, char*name){
  if (strncmp(buffer, "dir", 3)==0) {
    sscanf(buffer, "dir %s\n", name);
    return;
  }
  name = "";
  return;
}

void get_dir(char * buffer, char * name) {
  if (strncmp(buffer, "$ cd", 3)==0) {
    sscanf(buffer, "$ cd %s\n", name);
    return;
  }
  name = "";
  return;
}

int rec_size(struct node * n){
  if (n->num_children==0){
    return n->size;
  }
  int acc=n->size;
  for (int i=0; i<n->num_children; i++){
    acc+=rec_size(&n->children[i]);
  }
  n->size=acc;
  return acc;
}

int count_dirs(struct node n){
  int count = 0;
  if (n.is_dir) {
    printf("dir %s\n", n.dir_name);
    count += 1;
    for (int i=0; i< n.num_children; i++){
      count+=count_dirs(n.children[i]);
    }
    return count;
  }
  return 0;
}

int partial_sum(struct node n){
  int acc = 0;
  int count = 0;
  if (n.is_dir) {
    count += 1;
    if (n.size<=100000){
      acc+=n.size;
    }
    for (int i=0; i< n.num_children; i++){
      acc+=partial_sum(n.children[i]);
    }
    return acc;
  }
  return 0;
}

int main(void) {
  struct node tree = init_node(0, true, "/", NULL);
  struct node *current_dir = &tree;

  char buffer[IN_S];
  char new_dir[NAME_S];
  int size;
  enum line_type type;
  fgets(buffer, IN_S, stdin);// skip first cd;

  while(fgets(buffer, IN_S, stdin)){
    printf("BUF: %s\n", buffer);
    type = cd_command(buffer);
    switch(type){
      case cd:
        printf("case cd\n");
        get_dir(buffer, new_dir);
        if (strcmp(new_dir, "..")==0) {
          current_dir = current_dir->parent;
        }
        else {
          current_dir = find_dir(current_dir, new_dir);
        }
        printf("%p\n", current_dir);
        printf("%s\n", current_dir->dir_name);
        break;
      case ls:
        printf("case ls\n");
        break;
      case file:
        printf("case file\n");
        size = get_size(buffer);
        printf("size: %d\n", size);
        if (size==-1){
          printf("getting dir child\n");
          get_name(buffer, new_dir);
          printf("%s", buffer);
          printf("%s\n", new_dir);
          add_child(current_dir, 0, true, new_dir);
        }
        else {
          printf("getting child\n");
          add_child(current_dir, size, false, "");
          printf("added child\n");
        }
        break;
    }
  }
  int total_size = rec_size(&tree);
  print_tree(tree);
  int ans = partial_sum(tree);
  count_dirs(tree);
  printf("total: %d\n", total_size);
  printf("%d\n", count_dirs(tree));
  printf("%d\n", ans);
  return 0;
}
