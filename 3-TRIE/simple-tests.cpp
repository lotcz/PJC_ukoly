#include "trie.hpp"
#include "tests-helpers.hpp"
#include "catch.hpp"

TEST_CASE("Basics: erase") {
    trie trie;
    init(trie);
    scope_guard sg([&] () { deallocate(trie); });

    SECTION("My") {
        REQUIRE(size(trie) == 0);
        insert(trie, "");
        REQUIRE(size(trie) == 1);
        insert(trie, "a");
        REQUIRE(size(trie) == 2);
        insert(trie, "ab");
        REQUIRE(size(trie) == 3);
    }

    SECTION("Erase in the middle") {
        insert_all(trie, {"", "a", "ab", "abc", "abcd"});
        REQUIRE(size(trie) == 5);
        REQUIRE(erase(trie, "ab"));
        REQUIRE(size(trie) == 4);
        REQUIRE_FALSE(contains(trie, "ab"));

        REQUIRE(erase(trie, "abc"));
        REQUIRE(size(trie) == 3);
        REQUIRE_FALSE(contains(trie, "abc"));

        REQUIRE(contains(trie, "abcd"));
    }
}
