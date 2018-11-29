#include "trie.hpp"

/**
 * Initialize trie to default state. Will always be called before further manipulation
 */
void init(trie& trie) {

}

/**
 * Inserts given string to the trie.
 * Returns true iff string was successfully inserted (it was not present before).
 */
bool insert(trie& trie, const std::string& str) {
    return true;
}

/**
 * Inserts all strings from vector to the trie
 */
void insert_all(trie& trie, const std::vector<std::string>& items) {

}

/**
 * Returns true if given string is in the trie
 */
bool contains(const trie& trie, const std::string& str) {
    return true;
}

/**
 * Returns how many unique strings are in the trie
 */
size_t size(const trie& trie) {
    return 0;
}

/**
 * Returns whether given trie is empty (contains no strings)
 */
bool empty(const trie& trie) {
    return true;
}

/**
 * Removes given string from the trie
 * Returns true iff string was removed (it was present in the trie).
 */
bool erase(trie& trie, const std::string& str) {
    return true;
}

/**
 * Deallocates all nodes of given trie.
 * The trie will not be used again afterwards and can be left in an arbitrary state
 */
void deallocate(trie& trie) {

}
