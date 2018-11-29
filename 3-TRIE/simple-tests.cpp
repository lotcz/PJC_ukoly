#include "trie.hpp"
#include "tests-helpers.hpp"
#include "catch.hpp"

TEST_CASE("Basics: inserts") {
    trie trie;
    init(trie);

    SECTION("Empty trie") {
        REQUIRE_FALSE(contains(trie, ""));
        REQUIRE(size(trie) == 0);
        REQUIRE(empty(trie));
    }

    SECTION("Trivial inserts") {
        REQUIRE(insert(trie, "abcd"));
        REQUIRE(contains(trie, "abcd"));
        REQUIRE_FALSE(contains(trie, ""));
        REQUIRE_FALSE(contains(trie, "a"));
        REQUIRE_FALSE(contains(trie, "ab"));
        REQUIRE_FALSE(contains(trie, "abc"));
        REQUIRE(size(trie) == 1);

        REQUIRE(insert(trie, "abc"));
        REQUIRE(contains(trie, "abc"));
        REQUIRE(size(trie) == 2);

        REQUIRE_FALSE(empty(trie));
    }

    SECTION("Insert all") {
        insert_all(trie, {"abc", "bc", "a", "bc", "d", "", "d", "abcd", "abc"});
        REQUIRE(size(trie) == 6);
        REQUIRE(contains(trie, ""));
        REQUIRE(contains(trie, "a"));
        REQUIRE(contains(trie, "d"));
        REQUIRE_FALSE(contains(trie, "b"));
        REQUIRE(contains(trie, "bc"));
        REQUIRE_FALSE(contains(trie, "ab"));
        REQUIRE(contains(trie, "abc"));
        REQUIRE(contains(trie, "abcd"));
    }
}
