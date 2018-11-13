#include <set>
#include <vector>
#include <iostream>

template <typename T, typename Comparator = std::less<T> >
class flat_set {
  private:
    std::vector<T> m_values;
    Comparator m_comparator;

    typedef typename std::vector<T>::iterator my_iterator;

    bool value_equals(T v1, T v2) {
      return (!(this->m_comparator(v1, v2) || (this->m_comparator(v2, v1))));
    }

    my_iterator find_value_iterator(T value) {
      my_iterator it = this->begin();
      while (it != this->end() && (this->m_comparator(*it, value))) {
        it++;
      }
      return it;
    }

    typedef typename std::vector<T>::const_iterator my_const_iterator;

    my_const_iterator find_value_const_iterator(T value) {
      my_const_iterator it = this->cbegin();
      while (it != this->cend() && (this->m_comparator(*it, value))) {
        it++;
      }
      return it;
    }

    std::pair<my_iterator, bool> insert_value(T value) {
      my_iterator it = this->find_value_iterator(value);
      bool can_insert = false;

      if (it == this->end()) {
        can_insert = true;
      } else {
        if (!(this->value_equals(*it, value))) {
          can_insert = true;
        }
      }

      if (can_insert) {
        return make_pair(this->m_values.insert(it, value), true);
      } else {
        return make_pair(it, false);
      }
    }

    template <typename InputIterator>
    void from_iterator(InputIterator first, InputIterator last) {
      if (first != last) {
        for (auto it = first; it != last; it++) {
          this->insert_value(*it);
        }
      }
    }

    void from_flat_set(const flat_set<T, Comparator>* fs) {
      this->clear();
      m_comparator = fs->getComparator();
      if (!fs->empty()) {
        this->from_iterator(fs->cbegin(), fs->cend());
      }
    }

  public:
    typedef T value_type;
    typedef typename std::vector<T>::size_type size_type;
    typedef my_iterator iterator;
    typedef my_const_iterator const_iterator;

    flat_set<T, Comparator>() = default;

    flat_set<T, Comparator>(Comparator const& cmp) {
      m_comparator = cmp;
    }

    flat_set<T, Comparator>(flat_set<T, Comparator> const& rhs) {
      this->from_flat_set(&rhs);
    }

    flat_set<T, Comparator>(flat_set<T, Comparator> && rhs) {
      this->from_flat_set(&rhs);
    }

    flat_set<T, Comparator>& operator=(flat_set<T, Comparator> const& rhs) {
      this->clear();
      this->from_flat_set(&rhs);
      return *this;
    }

    flat_set<T, Comparator>& operator=(flat_set<T, Comparator> && rhs) {
      return rhs;
    }

    ~flat_set() {

    }

    Comparator getComparator() const {
      return m_comparator;
    }

    // Constructs flat_set from elements in range [first, last)
    template <typename InputIterator>
    flat_set(InputIterator first, InputIterator last) {
      this->from_iterator(first, last);
    }

    template <typename InputIterator>
    flat_set(InputIterator first, InputIterator last, Comparator const& cmp){
      m_comparator = cmp;
      this->from_iterator(first, last);
    }

    // Insert overloads
    std::pair<iterator, bool> insert(T const& v) {
      return this->insert_value(v);
    }

    std::pair<iterator, bool> insert(T&& v) {
      return this->insert_value(v);
    }

    // Inserts [first, last) range of elements
    template <typename InputIterator>
    void insert(InputIterator first, InputIterator last) {
      this->from_iterator(first, last);
    }

    // Iterator member functions
    iterator begin() noexcept {
      return this->m_values.begin();
    }

    iterator end() noexcept {
      return this->m_values.end();
    }

    const_iterator begin() const noexcept {
      return this->m_values.cbegin();
    }

    const_iterator end() const noexcept {
      return this->m_values.cend();
    }

    const_iterator cbegin() const noexcept {
      return this->m_values.cbegin();
    }

    const_iterator cend() const noexcept {
      return this->m_values.cend();
    }

    bool empty() const {
      return (this->size() == 0);
    }

    size_type size() const {
      return this->m_values.size();
    }

    size_type capacity() const {
      return this->m_values.capacity();
    }

    void reserve(size_type c) {
      this->m_values.reserve(c);
    }

    void clear() {
      this->m_values.clear();
    }

    // Lookup member functions
    // Returns iterator to element equivalent to v, or an end iterator if such element is not present
    iterator find(T const& v) {
      my_iterator it = this->find_value_iterator(v);
      if (it == this->end()) {
        return it;
      } else {
        if (this->value_equals(*it, v)) {
          return it;
        } else {
          return this->end();
        }
      }
    }

    const_iterator find(T const& v) const {
      my_const_iterator it = this->find_value_const_iterator(v);
      if (it == this->cend()) {
        return it;
      } else {
        if (this->value_equals(*it, v)) {
          return it;
        } else {
          return this->cend();
        }
      }
    }

    // Erase overloads
    // Deletes element pointed-to by i, returns iterator to the next element
    iterator erase(const_iterator i) {
      return this->m_values.erase(i);
    }

    // Deletes elements in range [first, last), returns iterator to the next element
    iterator erase(const_iterator first, const_iterator last) {
      return this->m_values.erase(first, last);
    }

    // Deletes element equal to key if it is present, returns how many elements were deleted
    size_type erase(value_type const& key) {
      iterator it = this->find(key);
      size_type size = 0;
      while (it != this->end() && (*it == key)) {
        it = this->erase(it);
        size++;
      }
      return size;
    }

    // Returns iterator to first element that is not less than t, end iterator if no such element is present
    iterator lower_bound(T const& t) {
      return this->find_value_iterator(t);
    }

    const_iterator lower_bound(T const& t) const {
      return this->find_value_const_iterator(t);
    }

    // Returns iterator to first element that is greater than t, end iterator if no such element is present
    iterator upper_bound(T const& t) {
      my_iterator it = this->find_value_iterator(t);
      while (it != this->end() && (*it == t)) {
        ++it;
      }
      return it;
    }

    const_iterator upper_bound(T const& t) const {
      my_const_iterator it = this->find_value_const_iterator(t);
      while (it != this->cend() && (*it == t)) {
        ++it;
      }
      return it;
    }

    void swap(flat_set<T, Comparator>& o) {
      flat_set<T, Comparator> f3 = flat_set<T, Comparator>(o);
      o.from_flat_set(this);
      this->from_flat_set(&f3);
    }

};

template <typename T, typename Comparator>
bool operator==(flat_set<T, Comparator> const& a, flat_set<T, Comparator> const& b) {
  return false;
}

template <typename T, typename Comparator>
bool operator!=(flat_set<T, Comparator> const& a, flat_set<T, Comparator> const& b) {
  return false;
}

template <typename T, typename Comparator>
bool operator<(flat_set<T, Comparator> const& a, flat_set<T, Comparator> const& b) {
  return false;
}

template <typename T, typename Comparator>
bool operator<=(flat_set<T, Comparator> const& a, flat_set<T, Comparator> const& b) {
  return false;
}

template <typename T, typename Comparator>
bool operator>=(flat_set<T, Comparator> const& a, flat_set<T, Comparator> const& b) {
  return false;
}

template <typename T, typename Comparator>
bool operator>(flat_set<T, Comparator> const& a, flat_set<T, Comparator> const& b) {
  return false;
}

template <typename T>
void swap(flat_set<T> const& a, flat_set<T> const& b) {
  a.swap(b);
}
