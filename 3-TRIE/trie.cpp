#include "trie.hpp"
#include "trie-nodes.hpp"
#include <string>
#include <vector>

/**
 * Initialize trie to default state. Will always be called before further manipulation
 */
void init(trie& trie) {
  deallocate(trie);
  trie.root = nullptr;
  trie.size = 0;
}

/**
* create new node, return pointer to it
*/
trie_node* create_node(trie_node* parent, const char payload) {
  trie_node* node = new trie_node();
  node->parent = parent;
  node->payload = payload;
  return node;
}

/**
* insert string to node, return true if inserted (it was not present before).
*/
bool insert_to_node(trie_node* node, const char* s) {
  bool inserted = false;
  size_t index = *s;
  if (node->children[index] == nullptr) {
    node->children[index] = create_node(node, *s);
    inserted = true;
  }
  if (*(s+1) == 0) {
    if (!node->children[index]->is_terminal) {
      node->children[index]->is_terminal = true;
      inserted = true;
    }
  } else {
    inserted = insert_to_node(node->children[index], (s+1));
  }
  return inserted;
}

/**
 * Inserts given string to the trie.
 * Returns true iff string was successfully inserted (it was not present before).
 */
bool insert(trie& trie, const std::string& str) {
  bool inserted = false;
  const char* s = str.c_str();
  if (trie.root == nullptr) {
    trie.root = create_node(nullptr, 0);
    if (*s == 0) {
      inserted = true;
      trie.root->is_terminal = true;
    }
  }
  if (!inserted) {
    if (*s == 0) {
      if (!trie.root->is_terminal) {
        trie.root->is_terminal = true;
        inserted = true;
      }
    } else {
      inserted = insert_to_node(trie.root, s);
    }
  }
  if (inserted) {
    trie.size++;
  }
  return inserted;
}

/**
 * Inserts all strings from vector to the trie
 */
void insert_all(trie& trie, const std::vector<std::string>& items) {
  for (std::string item: items) {
    insert(trie, item);
  }
}

/**
 * Returns true iff given string is in the trie
 */
bool contains(const trie& trie, const std::string& str) {
  if (trie.root == nullptr) {
    return false;
  } else {
    const char* s = str.c_str();
    trie_node* node = trie.root;
    size_t index;
    while ((*s != 0) && (node != nullptr)) {
      index = *s;
      node = node->children[index];
      s++;
    }
    return (*s == 0 && node->is_terminal);
  }
}

/**
 * Returns how many unique strings are in the trie
 */
size_t size(const trie& trie) {
  return trie.size;
}

/**
 * Returns whether given trie is empty (contains no strings)
 */
bool empty(const trie& trie) {
  return (trie.size == 0);
}

bool node_has_children(trie_node* node) {
  size_t i = 0;
  while (i < num_chars && node->children[i] == nullptr) {
    i++;
  }
  return (i < num_chars);
}

void delete_node(trie_node* node) {
  trie_node* parent = node->parent;
  size_t index = node->payload;
  deallocate_node(node);
  if (parent != nullptr) {
    parent->children[index] = nullptr;
  }
}

/**
 * Removes given string from the trie
 * Returns true iff string was removed (it was present in the trie).
 */
bool erase(trie& trie, const std::string& str) {
  bool found = false;

  trie_node* node = trie.root;
  if (node != nullptr) {
    const char* s = str.c_str();
    size_t index;
    while ((*s != 0) && (node != nullptr)) {
      index = *s;
      node = node->children[index];
      s++;
    }
    found = (*s == 0 && node->is_terminal);
  }

  if (found) {
    if (trie.size == 1) {
      deallocate(trie);
    } else {
      if (node_has_children(node)) {
        node->is_terminal = false;
      } else {
        trie_node* node_to_delete = node;
        node = node->parent;
        delete_node(node_to_delete);
        while (!node->is_terminal && !node_has_children(node)) {
          node_to_delete = node;
          node = node->parent;
          delete_node(node_to_delete);
        }
      }
      trie.size--;
    }
  }

  return found;
}

void deallocate_node(trie_node* node) {
  if (node != nullptr) {
    for (size_t i = 0; i < num_chars; i++) {
      deallocate_node(node->children[i]);
    }
    delete node;
  }
}

/**
 * Deallocates all nodes of given trie.
 * The trie will not be used again afterwards and can be left in an arbitrary state
 */
void deallocate(trie& trie) {
  deallocate_node(trie.root);
  trie.root = nullptr;
  trie.size = 0;
}
