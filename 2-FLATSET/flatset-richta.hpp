#include <algorithm>
#include <vector>
#include <iterator>
#include <functional>
#include <set>
#include <memory>
#include <iostream>
#include <unordered_set>

template <typename T, typename Comparator = std::less<T>>
class flat_set {
public:
    std::vector<T> vec;
    Comparator comp;

    typedef typename std::vector<T>::value_type value_type;
    typedef typename std::vector<T>::size_type size_type;
    typedef typename std::vector<T>::iterator iterator;
    typedef typename std::vector<T>::const_iterator const_iterator;

    // These types need to be accesible from the outside:
    // iterator
    // const_iterator
    // size_type
    // value_type

    // Special member functions
    flat_set() {
    }
    flat_set(Comparator const& cmp) {
        comp = cmp;
    }
    flat_set(flat_set const& rhs) {
        vec = rhs.vec;
        comp = rhs.comp;
    }
    flat_set(flat_set && rhs) {
        swap(rhs);
    }
    flat_set& operator=(flat_set const& rhs) {
        flat_set fs(rhs);
        swap(fs);
        return *this;
    }
    flat_set& operator=(flat_set && rhs) {
        swap(rhs);
        return *this;
    }
    ~flat_set() {

    }

    // Constructs flat_set from elements in range [first, last)
    template <typename InputIterator>
    flat_set(InputIterator first, InputIterator last) {
        insert(first, last);
    }
    template <typename InputIterator>
    flat_set(InputIterator first, InputIterator last, Comparator const& cmp) {
        comp = cmp;
        bool contains;
        while (first != last) {
            if (vec.empty()) {
                vec.insert(vec.begin(), *first);
                first++;
                continue;
            }

            contains = false;
            for (iterator it = vec.begin(); it != vec.end(); it++)
            {
                if (!cmp(*it,*first) && !cmp(*first,*it)) {
                    contains = true;
                    break;
                }
            }
            if (contains) {
                first++;
                continue;
            }
            vec.push_back(*first);
            std::sort(vec.begin(), vec.end(), comp);
            first++;

        }

    }


    // Insert overloads
    std::pair<iterator, bool> insert(T const& v) {
        bool b = false;
        auto it = std::find_if(vec.begin(), vec.end(), [&v, this](T& f) { return !comp(v, f) && !comp(f, v); });
        if (it == vec.end()) {
            it = vec.insert(it, std::move(v));
            b = true;
        }
        std::sort(vec.begin(), vec.end(), comp);
        return std::pair<iterator, bool>(it, b);
    }
    std::pair<iterator, bool> insert(T&& v) {
        bool b = false;
        auto it = std::find_if(vec.begin(), vec.end(), [&v, this](T& f) { return !comp(v, f) && !comp(f, v); });
        if (it == vec.end()) {
            it = vec.insert(it, std::move(v));
            b = true;
        }
        std::sort(vec.begin(), vec.end(), comp);
        return std::pair<iterator, bool>(it,b);


    }
    // Inserts [first, last) range of elements
    template <typename InputIterator>
    void insert(InputIterator first, InputIterator last) {
        vec.insert(vec.begin(), first, last);
        std::sort(vec.begin(), vec.end(), comp);
        auto dupe = std::unique(vec.begin(), vec.end(),[this](T& a, T& b) {
            return !comp(a, b) && !comp(b, a);
        });
        vec.erase(dupe, vec.end());
    };

    // Erase overloads
    // Deletes element pointed-to by i, returns iterator to the next element
    iterator erase(const_iterator i) {
        return vec.erase(i);
    }
    // Deletes elements in range [first, last), returns iterator to the next element
    iterator erase(const_iterator first, const_iterator last) {
        return vec.erase(first, last);
    }
    // Deletes element equal to key if it is present, returns how many elements were deleted
    size_type erase(value_type const& key) {
        int val = 0;
        for (size_t i = 0; i < vec.size(); i++)
        {
            if (vec[i] == key) {
                vec.erase(vec.begin() + i);
                val++;
            }
        }
        return val;
    }

    // Iterator member functions

    iterator begin() noexcept {
        return iterator(vec.begin());
    }
    iterator end() noexcept {
        return iterator(vec.end());
    }
    const_iterator begin() const noexcept { return const_iterator(vec.begin()); }
    const_iterator end() const noexcept { return const_iterator(vec.end()); }
    const_iterator cbegin() const noexcept { return const_iterator(vec.cbegin()); }
    const_iterator cend() const noexcept { return const_iterator(vec.cend()); }

    // The usual queries
    bool empty() const { return vec.empty(); }
    size_type size() const { return vec.size(); }
    size_type capacity() const { return vec.capacity(); }

    void reserve(size_type c) { vec.reserve(c); }
    void clear() { vec.clear(); }

    // Lookup member functions
    // Returns iterator to element equivalent to v, or an end iterator if such element is not present
    iterator find(T const& v) {
        iterator iter = vec.begin();
        for (size_t i = 0; i < vec.size(); i++) {
            if (!comp(*iter,v) && !comp(v,*iter)) {
                return iter;
            }
            else {
                iter++;
            }
        }
        return vec.end();
    }
    const_iterator find(T const& v) const {
        const_iterator iter = vec.cbegin();
        for (size_t i = 0; i < vec.size(); i++) {
            if (*iter == v) {
                return iter;
            }
            else {
                iter++;
            }
        }
        return vec.cend();
    }

    // Returns iterator to first element that is not less than t, end iterator if no such element is present
    iterator lower_bound(T const& t) {
        iterator iter = vec.begin();
        for (size_t i = 0; i < vec.size(); i++) {
            if (*iter >= t) {
                return iter;
            }
            else {
                iter++;
            }
        }
        return vec.end();
    };
    const_iterator lower_bound(T const& t) const {
        const_iterator iter = vec.cbegin();
        for (size_t i = 0; i < vec.size(); i++) {
            if (*iter >= t) {
                return iter;
            }
            else {
                iter++;
            }
        }
        return vec.cend();
    }

    // Returns iterator to first element that is greater than t, end iterator if no such element is present
    iterator upper_bound(T const& t) {
        iterator iter = vec.begin();
        for (size_t i = 0; i < vec.size(); i++) {
            if (*iter > t) {
                return iter;
            }
            else {
                iter++;
            }
        }
        return vec.end();
    }
    const_iterator upper_bound(T const& t) const {
        const_iterator iter = vec.cbegin();
        for (size_t i = 0; i < vec.size(); i++) {
            if (*iter > t) {
                return iter;
            }
            else {
                iter++;
            }
        }
        return vec.cend();
    }

    void swap(flat_set& o) {
        std::swap(vec, o.vec);
        std::swap(comp, o.comp);
    }

    // Lexicographical comparisons
    friend bool operator==(flat_set const& a, flat_set const& b) {
        if (a.vec.size() != b.vec.size()) {
            return false;
        }
        for (size_t i = 0; i < a.size(); i++)
        {
            if (!(!a.comp(a.vec[i], b.vec[i]) && !a.comp(b.vec[i], a.vec[i]))) {
                return false;
            }
        }
        return true;
    }
    friend bool operator!=(flat_set const& a, flat_set const& b) {
        if (a.vec.size() != b.vec.size()) {
            return true;
        }
        for (size_t i = 0; i < a.size(); i++)
        {
            if ((!a.comp(a.vec[i], b.vec[i]) && !a.comp(b.vec[i], a.vec[i]))) {
                return false;
            }
        }
        return true;
    }
    friend bool operator<(flat_set const& a, flat_set const& b) {
        return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
    }
    friend bool operator<=(flat_set const& a, flat_set const& b) {
        return a == b || a < b;
    }
    friend bool operator>=(flat_set const& a, flat_set const& b) {
        return a == b || a > b;
    }
    friend bool operator>(flat_set const& a, flat_set const& b) {
        return !std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
    }
};
