#include "../src/tree.h"
#include <string.h>
#include <stdio.h>

int main() {
  Tree* t = create_tree();
  char* data = "this is my test data which i will insert";
  tree_insert(t, "Liz3", 4, (void*) data);
  tree_insert(t, "Liz34", 5, (void*) data);
  tree_insert(t, "Liz355555", strlen("Liz355555"), (void*) data);

  SearchResult search_res = tree_search(t, "Liz", 3);

  printf("%d %d\n", search_res.size, search_res.result[0]->data == data);
  tree_remove(t, "Liz3", 4);
  tree_free(t);
  return 0;
}
