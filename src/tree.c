#include "tree.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
Tree* create_tree() {
  Tree* instance = malloc(sizeof(Tree));
  memset(instance, 0, sizeof(Tree));
  return instance;
}

Node* tree_insert(Tree* tree, char* name, size_t name_len, void* data) {
  if(name_len == 0)
    return NULL;
  Node* target = NULL;
  for(size_t i = 0; i < name_len; i++) {
    uint8_t target_char = (uint8_t)name[i];
    Node* next;
    if(i == 0) {
      next = tree->root_nodes[target_char];
    } else {
      next = target->children[target_char];
    }
    if(next == NULL) {
      next = malloc(sizeof(Node));
      memset(next, 0, sizeof(Node));
      next->value = target_char;
      next->used = 1;
      if(i == 0) {
        tree->root_nodes[target_char] = next;
      } else {
        target->children[target_char] = next;
    }

    } else {
      next->used++;
    }
    target = next;

  }
  assert(target != NULL);
  target->data = data;
  tree->size++;
  return target;
}
Node* tree_get(Tree* tree, char* name, size_t name_len) {
 if(name_len == 0)
    return NULL;
  Node* target = NULL;
  for(size_t i = 0; i < name_len; i++) {
    uint8_t target_char = (uint8_t)name[i];
    if(i == 0) {
      target = tree->root_nodes[target_char];
    } else {
      target = target->children[target_char];
    }
    if(target == NULL) {
      return NULL;
    }

  }
  return target;
}
void tree_remove(Tree* tree, char* name, size_t name_len) {
 if(name_len == 0)
   return;
 Node* maybe_free[name_len];
  Node* target = NULL;
  for(size_t i = 0; i < name_len; i++) {
    uint8_t target_char = (uint8_t)name[i];
    if(i == 0) {
      target = tree->root_nodes[target_char];
    } else {
      target = target->children[target_char];
    }
    if(target == NULL) {
      return;
    }
    maybe_free[i] = target;

  }
  for(int i = name_len-1; i > -1; i--) {
    Node* current = maybe_free[i];
    uint8_t target_char = name[i];
    if(i == 0) {

      if(current->used == 1) {
        printf("freeing %c\n", (char) target_char);
        free(current);
        tree->root_nodes[target_char] = NULL;
      }
    } else {
      if(current->used == 1) {
        printf("freeing %c\n", (char) target_char);
        free(current);
      } else {
        current->used--;
      }
      maybe_free[i-1]->children[target_char] = NULL;
    }
  }
  tree->size--;
}
void recursive_free(Node* node) {
    for(size_t i = 0; i < 256; i++) {
      if(node->children[i] != NULL) {
        recursive_free(node->children[i]);
        node->children[i] = NULL;
      }
    }
    free(node);
}
void tree_free(Tree* tree) {
  for(size_t i = 0; i < 256; i++) {
    if(tree->root_nodes[i] != NULL) {
      recursive_free(tree->root_nodes[i]);
      tree->root_nodes[i] = NULL;
    }
  }
  free(tree);
}
void recursive_search(SearchResult* resultPtr, Node* node) {
    for(size_t i = 0; i < 256; i++) {
      Node* current = node->children[i];
      if(current != NULL) {
        if(current->data != NULL) {
          resultPtr->size++;
          if(resultPtr->result == NULL)
            resultPtr->result = malloc(sizeof(Node*));
          else
            resultPtr->result = realloc(resultPtr->result, sizeof(Node*) * resultPtr->size);
          resultPtr->result[resultPtr->size - 1] = current;
        }
        recursive_search(resultPtr, current);
      }
    }
}
SearchResult tree_search(Tree* t, char* start, size_t search_len) {
  SearchResult result ={NULL, 0};
  Node* target = tree_get(t, start, search_len);
  if(target != NULL) {
    if (target->data != NULL) {
      result.size = 1;
      result.result = malloc(sizeof(Node*));
      result.result[0] = target;
    }
    recursive_search(&result, target);
  }
  return result;
}
