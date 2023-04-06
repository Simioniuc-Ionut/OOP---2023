/*
Implement a class template for a Vector of elements that has the following methods:
- insert(index, element): inserts the element at the specified index (must be between 0 and size)
- remove(index): removes an element at the specified index
- sort(cmp): sorts the vector by using a comparison function; add an overload that takes no parameters and uses
operator< instead
- print: prints the vector elements
The vector should also have a copy/move constructor, along with an operator[] defined, which returns the element at the
given index.
You MUST have the implementation in the header.
*/

using namespace std;
#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
class Vector {
  private:
    std::vector<T> data_;

  public:
   
    Vector() : data_() {
    }
    Vector(const Vector& other) : data_(other.data_) {
    }
    Vector(Vector&& other) : data_(std::move(other.data_)) {
    }

    
    void insert(size_t index, const T& element) {
        if (index > size()) {
            throw std::out_of_range("Index out of range.");
        }
        data_.insert(data_.begin() + index, element);
    }

    void remove(size_t index) {
        if (index >= size()) {
            throw std::out_of_range("Index out of range.");
        }
        data_.erase(data_.begin() + index);
    }

    void sort() {
        std::sort(data_.begin(), data_.end());
    }

    void sort(int (*cmp)(const T&, const T&)) {
        std::sort(data_.begin(), data_.end(), cmp);
    }

    void print() const {
        for (const auto& element : data_) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }

   
    T& operator[](size_t index) {
        if (index >= size()) {
            throw std::out_of_range("Index out of range.");
        }
        return data_[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size()) {
            throw std::out_of_range("Index out of range.");
        }
        return data_[index];
    }


    size_t size() const {
        return data_.size();
    }
};
//int compare_ints(int x, int y) {
  //  if (x < y)
    //    return -1;
    //if (x > y)
     //   return 1;
    //if (x == y)
     //   return 0;
//}

int main() {
    Vector<int> v;

    // index, element
    v.insert(0, 10);
    v.insert(1, 5);
    v.insert(2, 20);

    Vector<int> w = v;

    // index
    v.remove(0);
    //v.sort(compare_ints);
    printf("%d\n", w[0]);

    v.print();
}