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
  if (node->children[*s] == nullptr) {
    node->children[*s] = create_node(node, *s);
    inserted = true;
  }
  if (*(s+1) == 0) {
    if (!node->children[*s]->is_terminal) {
      node->children[*s]->is_terminal = true;
      inserted = true;
    }
  } else {
    inserted = insert_to_node(node->children[*s], (s+1));
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
      trie.size = 1;
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
    int i;
    while ((*s != 0) && (node != nullptr)) {
      node = node->children[*s];
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

/**
 * Removes given string from the trie
 * Returns true iff string was removed (it was present in the trie).
 */
bool erase(trie& trie, const std::string& str) {
  bool deleted = false;
  const char* s = str.c_str();
  trie_node* node = trie.root;
  while (*s) {
    s++;
  }
  if (node != nullptr) {
    for (int i = 0, max = num_chars; i < num_chars; i++) {
      deallocate_node(node->children[i]);
    }
  }
  return deleted;
}

void deallocate_node(trie_node* node) {
  if (node != nullptr) {
    for (int i = 0; i < num_chars; i++) {
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
