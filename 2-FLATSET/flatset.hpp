#include <set>
#include <vector>
#include <iostream>
#include <limits>

template <typename T, typename Comparator = std::less<T> >
class flat_set {
  private:
    T* m_values = nullptr;
    int m_size = 0;
    int m_capacity = 0;
    Comparator m_comparator;

    class MyIterator: public std::iterator<
                        std::random_access_iterator_tag,   // iterator_category
                        T,                      // value_type
                        T,                      // difference_type
                        const T*,               // pointer
                        T&                      // reference
                                      > {
    private:
      T* m_current = nullptr;
      const flat_set<T, Comparator>* m_set;
      typedef unsigned long pointer_diff;
    public:

      MyIterator() = default;

      MyIterator(const flat_set<T, Comparator>* src, bool is_end = false) {
        this->m_set = src;
        if (is_end && this->m_set->m_values != nullptr) {
            this->m_current = this->m_set->m_values+m_set->m_size;
        } else {
            this->m_current = this->m_set->m_values;
        }
      }

      MyIterator operator++() {
        m_current += 1;
        return *this;
      }

      MyIterator operator++(int) {
        MyIterator result_it = *this;
        this->m_current += 1;
        return result_it;
      }

      MyIterator operator+(pointer_diff add) {
        MyIterator result_it = *this;
        for (int i = add; i > 0; i--) {
          result_it++;
        }
        return result_it;
      }

      MyIterator operator--() {
        this->m_current -= 1;
        return *this;
      }

      MyIterator operator--(int) {
        MyIterator result_it = *this;
        this->m_current -= 1;
        return result_it;
      }

      MyIterator operator-(pointer_diff add) {
        MyIterator result_it = *this;
        for (pointer_diff i = add; i > 0; i--) {
          result_it--;
        }
        return result_it;
      }

      pointer_diff operator-(MyIterator other) {
        return this->m_current - other.m_current;
      }

      T& operator*() {
        return *m_current;
      }

      bool operator!=(MyIterator const& other) const {
        return (this->m_current != other.m_current);
      }

      bool operator==(MyIterator const& other) const {
        return (this->m_current == other.m_current);
      }

      void goTo(T* position) {
        this->m_current = position;
      }

      void goTo(MyIterator& other) {
        this->m_current = other.m_current;
      }

      T* getCurrent() const {
        return this->m_current;
      }

      const flat_set<T, Comparator>* getSet() const {
        return this->m_set;
      }
    };

    class MyConstIterator: public std::iterator<
                        std::random_access_iterator_tag,   // iterator_category
                        const T,                      // value_type
                        const T,                      // difference_type
                        const T*,               // pointer
                        const T                      // reference
                                      > {
    private:
      T* m_current = nullptr;
      const flat_set<T, Comparator>* m_set;
      typedef unsigned long pointer_diff;
    public:

      MyConstIterator() = default;

      MyConstIterator(const flat_set<T, Comparator>* src, bool is_end = false) {
        this->m_set = src;
        if (is_end && this->m_set->m_values != nullptr) {
            this->m_current = this->m_set->m_values+m_set->m_size;
        } else {
            this->m_current = this->m_set->m_values;
        }
      }

      MyConstIterator(const MyIterator& other) {
        this->m_set = other.getSet();
        this->m_current = other.getCurrent();
      }

      MyConstIterator operator++() {
        m_current += 1;
        return *this;
      }

      MyConstIterator operator++(int) {
        MyConstIterator result_it = *this;
        this->m_current += 1;
        return result_it;
      }

      MyConstIterator operator+(pointer_diff add) {
        MyConstIterator result_it = *this;
        for (int i = add; i > 0; i--) {
          result_it++;
        }
        return result_it;
      }

      MyConstIterator operator--() {
        m_current -= 1;
        return *this;
      }

      MyConstIterator operator--(int) {
        MyConstIterator result_it = *this;
        m_current -= 1;
        return result_it;
      }

      MyConstIterator operator-(pointer_diff add) {
        MyConstIterator result_it = *this;
        for (pointer_diff i = add; i > 0; i--) {
          result_it--;
        }
        return result_it;
      }

      pointer_diff operator-(MyConstIterator other) {
        return this->m_current - other.m_current;
      }

      const T operator*() {
        //return static_cast<T>(*m_current);
        return *m_current;
      }

      bool operator!=(MyConstIterator const& other) const {
        return (this->m_current != other.m_current);
      }

      bool operator==(MyConstIterator const& other) const {
        return (this->m_current == other.m_current);
      }

      MyConstIterator& operator=(const MyIterator& other) {
        MyConstIterator it = MyConstIterator(this->m_set);
        it.goTo(other->m_current);
        return it;
      }

      void goTo(T* position) {
        this->m_current = position;
      }

      void goTo(MyConstIterator other) {
        this->m_current = other.m_current;
      }
    };

    typedef MyIterator my_iterator;
    typedef MyConstIterator my_const_iterator;

    static bool values_equal(Comparator cmp, T const& v1, T const& v2) {
      return (!(cmp(v1, v2) || (cmp(v2, v1))));
    }

    static bool values_equal(T const& v1, T const& v2) {
      Comparator cmp;
      return values_equal(cmp, v1, v2);
    }

    bool value_equals(T const& v1, T const& v2) const {
      return values_equal(this->m_comparator, v1, v2);
    }

    my_iterator find_value_iterator(T const& value) {
      my_iterator it = this->begin();
      while (it != this->end() && (this->m_comparator(*it, value))) {
        it++;
      }
      return it;
    }

    my_const_iterator find_value_const_iterator(T const& value) const {
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
      if (this != &rhs) {
        this->clear();
        this->from_flat_set(&rhs);
      }
      return *this;
    }

    flat_set<T, Comparator>& operator=(flat_set<T, Comparator>&& rhs) {
      this->clear();
      this->swap(rhs);
      return *this;
    }

    ~flat_set() {
      this->clear();
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
    std::pair<iterator, bool> insert_internal(T const& v) {

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
        size_type new_size = this->m_size + 1;
        if (this->m_capacity < new_size) {
          this->m_capacity = new_size;
        }
        T* new_arr = new T[this->m_capacity];
        T* new_it = new_arr;
        iterator old_it = this->begin();
        iterator result_it = MyIterator(this);

        while (old_it != value_it) {
          *new_it = *old_it;
          new_it++;
          old_it++;
        }

        *new_it = v;
        result_it.goTo(new_it);
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
        this->m_size = new_size;
        return std::make_pair(result_it, true);
      } else {
        return std::make_pair(value_it, false);
      }

    }

    std::pair<iterator, bool> insert(T const& v) {
      T value = v;
      return insert_internal(value);
    }

    std::pair<iterator, bool> insert(T&& v) {
      T value = std::move(v);
      return insert_internal(value);
    }

    // Inserts [first, last) range of elements
    template <typename InputIterator>
    void insert(InputIterator first, InputIterator last) {
      this->from_iterator(first, last);
    }

    // Iterator member functions
    iterator begin() noexcept {
      return MyIterator(this);
    }

    iterator end() noexcept {
      return MyIterator(this, true);
    }

    const_iterator begin() const noexcept {
      return this->cbegin();
    }

    const_iterator end() const noexcept {
      return this->cend();
    }

    const_iterator cbegin() const noexcept {
      return MyConstIterator(this);
    }

    const_iterator cend() const noexcept {
      return MyConstIterator(this, true);
    }

    bool empty() const {
      return (this->size() == 0);
    }

    size_type size() const {
      return this->m_size;
    }

    size_type capacity() const {
      return this->m_capacity;
    }

    void reserve(size_type c) {
      if (c > this->m_capacity) {
        this->m_capacity = c;
      }
    }

    void clear() {
      if (this->m_values != nullptr) {
        delete [] this->m_values;
      }
      this->m_size = 0;
    }

    // Lookup member functions
    // Returns iterator to element equivalent to v, or an end iterator if such element is not present
    iterator find(T const& v) {
      iterator it = this->find_value_iterator(v);
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

    const_iterator cfind(T const& v) const {
      const_iterator it = this->find_value_const_iterator(v);
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

    const_iterator find(T const& v) const {
      return this->cfind(v);
    }

    // Deletes elements in range [first, last), returns iterator to the next element
    iterator erase(const_iterator first, const_iterator last) {
      if (first != this->cend()) {
        int diff = last - first + 1;
        int new_size = this->m_size - diff;
        T* new_arr;
        iterator result_it = iterator(this);
        if (new_size > 0) {
          new_arr = new T[this->m_capacity];
          T* new_it = new_arr;
          const_iterator old_it = this->cbegin();

          while (old_it != first && old_it != this->cend()) {
            *new_it = *old_it;
            new_it++;
            old_it++;
          }

          while (old_it != last && old_it != this->cend()) {
            old_it++;
          }

          if (old_it != this->cend()) {
            old_it++;
          }
          result_it.goTo(new_it);

          while (old_it != this->cend()) {
            *new_it = *old_it;
            new_it++;
            old_it++;
          }

        } else {
          new_arr = nullptr;
          new_size = 0;
          result_it.goTo(new_arr);
        }

        if (this->m_values != nullptr) {
          delete [] this->m_values;
        }
        this->m_values = new_arr;
        this->m_size = new_size;
        return result_it;
      } else {
        return this->end();
      }
    }

    // Erase overloads
    // Deletes element pointed-to by i, returns iterator to the next element
    iterator erase(const_iterator i) {
      return erase(i, i);
    }

    // Deletes element equal to key if it is present, returns how many elements were deleted
    size_type erase(value_type const& key) {
      const_iterator it = this->cfind(key);
      size_type size = 0;
      if (it != this->cend()) {
        this->erase(it);
        size = 1;
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
      T* values = o.m_values;
      size_type size = o.m_size;
      size_type capacity = o.m_capacity;
      Comparator comparator = o.m_comparator;
      o.m_values = this->m_values;
      o.m_size = this->m_size;
      o.m_capacity = this->m_capacity;
      o.m_comparator = this->m_comparator;
      this->m_values = values;
      this->m_size = size;
      this->m_capacity = capacity;
      this->m_comparator = comparator;
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
