#pragma once
#include "trie.hpp"

bool insert_to_node(trie_node* node, const char* s);
bool node_has_children(trie_node* node);
void deallocate_node(trie_node* node);
trie_node* create_node(trie_node* parent, const char payload);
void delete_node(trie_node* node);
