#include "flatset.hpp"
#include "tests-helpers.hpp"
#include "catch.hpp"

#include <forward_list>
#include <type_traits>
#include <algorithm>
#include <vector>
#include <set>
#include <iterator>
#include <random>
#include <chrono>
#include <climits>
#include <type_traits>
#include <cmath>
#include <iostream>
#include <functional>
#include <numeric>

namespace {
    template <typename T> struct is_flat_set : std::false_type {};
    template <typename T> struct is_flat_set<flat_set<T>> : std::true_type {};

    template <typename T, typename = is_flat_set<T>>
    bool reports_as_empty(const T& s) {
        return s.empty() && (s.size() == 0);
    }
    template <typename T, typename = is_flat_set<T>>
    bool set_equal(const T &a, const std::set<typename T::value_type> &b) {
        return std::equal(a.begin(), a.end(), b.begin(), b.end());
    }
    template <typename T, typename = is_flat_set<T>>
    bool set_equal(const T &a, std::initializer_list<typename T::value_type> &&b) {
        return set_equal(a, std::set<typename T::value_type>(std::move(b)));
    }
    template <typename T, typename = is_flat_set<T>>
    bool set_equal(const T &a, const std::vector<typename T::value_type> &vb) {
        std::set<typename T::value_type> b(vb.begin(), vb.end());
        return std::equal(a.begin(), a.end(), b.begin(), b.end());
    }
    template <typename T>
    flat_set<T> make_flat_set(std::vector<T> const &v) {
        return flat_set<T>(v.begin(), v.end());
    }
    class MyKey {
        friend struct MyKeyComparator;
        int i;
        static unsigned s_nconstructs;
        operator int() const {return i;}
    public:
        static unsigned nconstructs() {return s_nconstructs;}

        explicit MyKey(int i = 0) : i(i) {s_nconstructs++;}
        MyKey(const MyKey &o) : i(o.i) {s_nconstructs++;}
        MyKey& operator=(const MyKey &o) {i = o.i; s_nconstructs++; return *this;}
        MyKey(MyKey &&o) = default;
        MyKey& operator=(MyKey &&o) = default;
    };
    struct MyKeyComparator {
        bool operator()(MyKey const &a, MyKey const &b) const {
            return a.i < b.i;
        }
    };
    template <typename C, typename T, typename U>
    bool equals(T &&a, U &&b, C &&cmp = C()) {
        return !cmp(a, b) && !cmp(b, a);
    }

    unsigned MyKey::s_nconstructs = 0;

    std::mt19937 mt{ std::random_device{}() };
    std::uniform_int_distribution<> dist(INT_MIN, INT_MAX);

    std::vector<int> generate(size_t N) {
        std::vector<int> res;
        res.reserve(N);

        for (size_t i=0; i<N; ++i) {
            res.push_back(dist(mt));
        }
        return res;
    }
    static int randint() {
        return dist(mt);
    }
}

TEST_CASE("Copy operations") {
    SECTION("Move insert moves") {
        flat_set<tracker> fs;
        tracker t(1);
        auto start = tracker::cnt;
        fs.insert(std::move(t));
        auto t1 = tracker::cnt;
        t1.move_constructors = start.move_constructors;
        t1.move_assignments = start.move_assignments;
        REQUIRE(start == t1);
    }

}
