#pragma once
#include "trie.hpp"

bool insert_to_node(trie_node* node, const char* s);
void deallocate_node(trie_node* node);
trie_node* create_node(trie_node* parent, const char payload);
