# linked-list-cpp

A generic singly linked list in C++ (templates), written for a Data Structures course at Tecnológico de Monterrey.

## What it implements

`LinkedList<T>` with a destructor, copy constructor and deep-copy assignment, plus:

| Operation | Description | Time |
|---|---|---|
| `reverse()` | Reverses the list in place by flipping links | O(n) |
| `shift(n)` | Rotates the list by `n` positions (negative and `n > size` handled with modulo) | O(n) |
| `operator==` | Element-wise equality | O(n) |
| `LinkedList(const LinkedList&)` | Deep copy | O(n) |
| `operator=` | Deep copy, safe against self-assignment | O(n + m) |
| `operator+=` | Appends a copy of another list, safe when appending a list to itself | O(n + m) |

It also has the usual `addFirst`, `addLast`, `add`, `get`, `set`, `change`, `deleteFirst`, `deleteLast`, `del`, `deleteAll`, `getSize` and `print`.

## Build and run the tests

```bash
g++ -std=c++17 -Wall -Wextra -fsanitize=address,undefined -g main.cpp -o ll_test
./ll_test        # prints "All tests passed"
```

`main.cpp` covers reverse, shift (positive, negative, larger than size, zero), equality, deep copy independence, self-assignment, `+=` with itself, and a `LinkedList<std::string>`. It passes under AddressSanitizer and UBSan.

A CMake build is also provided: `cmake -S . -B build && cmake --build build`.

## Notes

- `Node.h` is the node class provided by the course instructor (Santiago Conant); `LinkedList.h` is my implementation.
- `add(data, pos)` expects `1 <= pos <= size`; use `addFirst` to insert at the head.
