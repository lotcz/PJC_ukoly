#include <set>
#include <vector>
#include <iostream>
#include <limits>

template <typename T, typename Comparator = std::less<T> >
class flat_set {
  private:
    T* m_values = nullptr;
    int m_length = 0;
    Comparator m_comparator;

    typedef T* my_iterator;
    typedef my_iterator my_const_iterator;

    static bool values_equal(Comparator cmp, T const& v1, T const& v2) {
      return (!(cmp(v1, v2) || (cmp(v2, v1))));
    }

    static bool values_equal(T const& v1, T const& v2) {
      Comparator cmp;
      return values_equal(cmp, v1, v2);
    }

    bool value_equals(T const& v1, T const& v2) {
      return values_equal(this->m_comparator, v1, v2);
    }

    my_iterator find_value_iterator(T const& value) {
      my_iterator it = this->begin();
      while (it != this->end() && (this->m_comparator(*it, value))) {
        it++;
      }
      return it;
    }

    my_const_iterator find_value_const_iterator(T const& value) {
      my_const_iterator it = this->cbegin();
      while (it != this->cend() && (this->m_comparator(*it, value))) {
        it++;
      }
      return it;
    }

    template <typename InputIterator>
    void from_iterator(InputIterator first, InputIterator last) {
      if (first != last) {
        for (auto it = first; it != last; it++) {
          this->insert(*it);
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
    typedef int size_type;
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

      iterator value_it = this->find_value_iterator(v);
      bool can_insert = false;

      if (value_it == this->end()) {
        can_insert = true;
      } else {
        if (!(this->value_equals(*value_it, v))) {
          can_insert = true;
        }
      }

      if (can_insert) {
        T* new_arr = new T[this->m_length+1];
        iterator new_it = new_arr;
        iterator old_it = this->begin();
        iterator result_it;

        while (old_it != value_it) {
          *new_it = *old_it;
          new_it++;
          old_it++;
        }

        *new_it = v;
        result_it = new_it;
        new_it++;

        while (old_it != this->end()) {
          *new_it = *old_it;
          new_it++;
          old_it++;
        }

        if (this->m_values != nullptr) {
          delete [] this->m_values;
        }
        this->m_values = new_arr;
        this->m_length++;
        return std::make_pair(result_it, true);
      } else {
        return std::make_pair(value_it, false);
      }

    }

    std::pair<iterator, bool> insert(T&& v) {
      return insert(v);
    }

    // Inserts [first, last) range of elements
    template <typename InputIterator>
    void insert(InputIterator first, InputIterator last) {
      this->from_iterator(first, last);
    }

    // Iterator member functions
    iterator begin() noexcept {
      return this->m_values;
    }

    iterator end() noexcept {
      return this->m_values + this->m_length;
    }

    const_iterator begin() const noexcept {
      return this->cbegin();
    }

    const_iterator end() const noexcept {
      return this->cend();
    }

    const_iterator cbegin() const noexcept {
      return this->m_values;
    }

    const_iterator cend() const noexcept {
      return this->m_values + this->m_length;
    }

    bool empty() const {
      return (this->size() == 0);
    }

    size_type size() const {
      return this->m_length;
    }

    size_type capacity() const {
      return std::numeric_limits<int>::max();
    }

    void reserve(size_type c) {
      //this->m_values.reserve(c);
    }

    void clear() {
      if (this->m_values != nullptr) {
        delete [] this->m_values;
      }
      this->m_length = 0;
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

    // Deletes elements in range [first, last), returns iterator to the next element
    iterator erase(const_iterator first, const_iterator last) {
      if (first != this->cend()) {
        int diff = last - first + 1;
        T* new_arr = new T[this->m_length-diff];
        iterator new_it = new_arr;
        iterator old_it = this->begin();
        iterator result_it;

        while (old_it != first) {
          *new_it = *old_it;
          new_it++;
          old_it++;
        }

        while (old_it != last) {
          old_it++;
        }

        old_it++;
        result_it = old_it;
        
        while (old_it != this->end()) {
          *new_it = *old_it;
          new_it++;
          old_it++;
        }

        if (this->m_values != nullptr) {
          delete [] this->m_values;
        }
        this->m_values = new_arr;
        this->m_length -= diff;
        return result_it;
      } else {
        return first;
      }
    }

    // Erase overloads
    // Deletes element pointed-to by i, returns iterator to the next element
    iterator erase(const_iterator i) {
      return erase(i, i);
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

/**
* 0 - equal, 1 = a > b, -1 = a < b
*/
template <typename T, typename Comparator>
char elements_equal(flat_set<T, Comparator> const& a, flat_set<T, Comparator> const& b) {
  Comparator cmp;
  typename flat_set<T, Comparator>::const_iterator ita = a.cbegin();
  typename flat_set<T, Comparator>::const_iterator itb = b.cbegin();
  while (ita != a.cend() && itb != b.cend()) {
    if (cmp(*ita, *itb)) {
      return -1;
    } else if (cmp(*itb, *ita)) {
      return 1;
    } else {
      ita++;
      itb++;
    }
  }
  if (ita != a.cend()) {
    return 1;
  } else if (itb != b.cend()) {
    return -1;
  } else {
    return 0;
  }
}

template <typename T, typename Comparator>
bool operator==(flat_set<T, Comparator> const& a, flat_set<T, Comparator> const& b) {
  if (a.size() != b.size()) {
    return false;
  } else {
    return (elements_equal(a, b) == 0);
  }
}

template <typename T, typename Comparator>
bool operator!=(flat_set<T, Comparator> const& a, flat_set<T, Comparator> const& b) {
  if (a.size() != b.size()) {
    return true;
  } else {
    return (elements_equal(a, b) != 0);
  }
}

template <typename T, typename Comparator>
bool operator<(flat_set<T, Comparator> const& a, flat_set<T, Comparator> const& b) {
  return (elements_equal(a, b) == -1);
}

template <typename T, typename Comparator>
bool operator<=(flat_set<T, Comparator> const& a, flat_set<T, Comparator> const& b) {
  return (elements_equal(a, b) <= 0);
}

template <typename T, typename Comparator>
bool operator>=(flat_set<T, Comparator> const& a, flat_set<T, Comparator> const& b) {
  return (elements_equal(a, b) >= 0);
}

template <typename T, typename Comparator>
bool operator>(flat_set<T, Comparator> const& a, flat_set<T, Comparator> const& b) {
  return (elements_equal(a, b) == 1);
}

template <typename T>
void swap(flat_set<T> const& a, flat_set<T> const& b) {
  a.swap(b);
}
