// Demo / self-test for LinkedList<T>. Build and run: see README.
#include <iostream>
#include <string>
#include "LinkedList.h"

static int failures = 0;
#define CHECK(cond) do { if (!(cond)) { std::cout << "FAIL line " << __LINE__ << ": " #cond "\n"; failures++; } } while (0)

static LinkedList<int> make(std::initializer_list<int> xs) {
    LinkedList<int> l;
    for (int x : xs) l.addLast(x);
    return l;
}

int main() {
    // reverse
    LinkedList<int> a = make({1, 2, 3, 4, 5});
    a.reverse();
    CHECK(a == make({5, 4, 3, 2, 1}));
    LinkedList<int> empty;
    empty.reverse();                       // no-op on empty list
    CHECK(empty.isEmpty());

    // shift: positive, negative, more than size, zero
    LinkedList<int> b = make({1, 2, 3, 4, 5});
    b.shift(2);   CHECK(b == make({4, 5, 1, 2, 3}));
    b.shift(-2);  CHECK(b == make({1, 2, 3, 4, 5}));
    b.shift(7);   CHECK(b == make({4, 5, 1, 2, 3}));   // 7 % 5 == 2
    b.shift(0);   CHECK(b == make({4, 5, 1, 2, 3}));

    // operator==
    CHECK(make({1, 2, 3}) == make({1, 2, 3}));
    CHECK(!(make({1, 2, 3}) == make({1, 2, 4})));
    CHECK(!(make({1, 2, 3}) == make({1, 2})));

    // copy constructor is a deep copy
    LinkedList<int> c = make({1, 2, 3});
    LinkedList<int> d(c);
    d.set(99, 0);
    CHECK(c.get(0) == 1 && d.get(0) == 99);

    // operator= (deep copy, self-assignment safe)
    LinkedList<int> e = make({7, 8});
    e = c;
    CHECK(e == c);
    e = e;
    CHECK(e == c);

    // operator+= (append copy, works with itself)
    LinkedList<int> f = make({1, 2});
    f += make({3, 4});
    CHECK(f == make({1, 2, 3, 4}));
    f += f;
    CHECK(f == make({1, 2, 3, 4, 1, 2, 3, 4}));
    LinkedList<int> g;
    g += make({9});
    CHECK(g == make({9}));

    // works with other types too
    LinkedList<std::string> s;
    s.addLast("b"); s.addFirst("a"); s.addLast("c");
    s.reverse();
    CHECK(s.get(0) == "c" && s.get(2) == "a");

    std::cout << (failures ? "SOME TESTS FAILED\n" : "All tests passed\n");
    return failures ? 1 : 0;
}
