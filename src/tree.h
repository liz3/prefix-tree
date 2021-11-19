#ifndef PREFIX_TREE_H
#define PREFIX_TREE_H

#include <stdint.h>
#include <stddef.h>


struct Node {
  uint8_t value;
  void* data;
  struct Node* children[256];
  size_t used;

};
typedef struct Node Node;
typedef struct {
  Node* root_nodes[256];
  size_t size;
} Tree;
typedef struct {
  Node** result;
  size_t size;
} SearchResult;
Tree* create_tree();

Node* tree_insert(Tree* tree, char* name, size_t name_len, void* data);
Node* tree_get(Tree* tree, char* name, size_t name_len);
void tree_remove(Tree* tree, char* name, size_t name_len);
void tree_free(Tree* tree);
void recursive_free(Node* n);

SearchResult tree_search(Tree* t, char* start, size_t search_len);
void recursive_search(SearchResult* resultPtr, Node* node);

#endif
