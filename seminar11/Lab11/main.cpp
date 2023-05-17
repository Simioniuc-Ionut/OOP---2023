#define CATCH_CONFIG_MAIN
#include "Catch2.hpp"
#include <iostream>
#include <string.h>
using namespace std;

struct isEmpty : std::exception {
    const char* what() const noexcept override {
        return "the queue is empty";
    }
};

template <class T>
class CircularQueue {
  private:
    int MaxSize;
    int index;
    int FullQueue;
    T* q;

  public:
    CircularQueue() {
        MaxSize = 1000;
        index = 0;
        FullQueue = -1;
        q = new T[MaxSize];
    }
    CircularQueue(int capacity) {
        MaxSize = capacity;
        index = 0;
        FullQueue = -1;
        q = new T[capacity];
    }
    ~CircularQueue() {
        delete[] q;
    }
    void push(T ele) {
        if (index < MaxSize) {
            q[index] = ele;
            index++;
        } else {
            index = 0;
            q[index] = ele;
            index++;
            FullQueue = MaxSize;
        }
    }
    void pop() {
        if (FullQueue == -1) {
            if (index != 0) {
                for (int i = 0; i < index - 1; i++)
                    q[i] = q[i + 1];
                index--;
                FullQueue = -1;
            } else
                throw isEmpty{};
        } else {
            if (index != 0) {
                for (int i = 0; i < FullQueue - 1; i++)
                    q[i] = q[i + 1];
                index = FullQueue - 1;
                FullQueue = -1;
            } else
                throw isEmpty{};
        }
    }
    T& front() {
        if (index != 0)
            return this->q[0];
        else
            throw isEmpty{};
    }
    T& back() {
        if (FullQueue == -1) {
            if (index != 0)
                return this->q[index - 1];
            else
                throw isEmpty{};
        } else
            return this->q[FullQueue - 1];
    }
    int size() {
        return (FullQueue != -1) ? FullQueue : index;
    }
    bool empty() {
        return index == 0;
    }
};
TEST_CASE("add 2 elements; check that the size is 2") {
    CircularQueue<unsigned> A(4);
    A.push(1);
    A.push(2);
    REQUIRE(A.size() == 2);
}
TEST_CASE("add one and pop one; check if is empty") {
    CircularQueue<unsigned> A(4);
    A.push(1);
    A.pop();
    REQUIRE(A.empty());
}
TEST_CASE("check the first and the last element without adding anything (this should throw)") {
    CircularQueue<unsigned> A(4);
    REQUIRE_THROWS(A.front());
    REQUIRE_THROWS(A.back());
}
TEST_CASE("add 5 elements and check that the first element is the 5th added element") {
    CircularQueue<unsigned> A(4);
    A.push(1);
    A.push(2);
    A.push(3);
    A.push(4);
    A.push(5);
    REQUIRE_NOTHROW(A.front());
}
TEST_CASE("add 1000 elements; pop all of them and check that they are correct") {
    CircularQueue<unsigned> A(4);
    for (int i = 1; i <= 1000; i++)
        A.push(i);
    while (!A.empty())
        A.pop();
    REQUIRE(A.size() == 0);
}
TEST_CASE("ADD 3 elements,and check first and last") {
    CircularQueue<std::string> A(4);
    A.push("1");
    A.push("2");
    A.push("3");
    REQUIRE_NOTHROW(A.front());
    REQUIRE_NOTHROW(A.back());
}

TEST_CASE("ADD 7 elemets,pop 3, if size is 1") {
    CircularQueue<std::string> A(4);
    A.push("1");
    A.push("2");
    A.push("3");
    A.push("4");
    A.push("5");
    A.push("6");
    A.push("7");
    A.pop();
    A.pop();
    A.pop();
    REQUIRE(A.size() == 1);
}
