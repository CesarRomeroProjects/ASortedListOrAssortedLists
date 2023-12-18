# Project 6: A Sorted List or Assorted Lists?

# Overview
This project involves implementing a Sorted Linked List in C++, combining various concepts covered during the quarter. The list is doubly linked, and each node contains both a key and a value, maintaining order based on keys. The primary goal is to create a functional and efficient implementation of the specified functions.

# Main Idea
The project focuses on implementing a Sorted Linked List, akin to an ordered map. The list is doubly linked, and each node stores a key-value pair.

# Functions to Implement
1. Constructor: Default constructor for an empty list.
2. Destructor: Properly frees memory.
3. Copy constructor and assignment operator: Deep copies.
4. size_t size() const noexcept: Returns the number of elements in the list.
5. bool isEmpty() const noexcept: Checks if the list is empty.
6. bool insert(const Key &k, const Value &v): Inserts a key-value pair; returns true if successful, false if the key is already present.
7. bool contains(const Key &k) const noexcept: Checks if the list contains a mapping for the given key.
8. void remove(const Key &k): Removes the key and its associated value from the list.
9. unsigned getIndex(const Key &k) const: Returns the number of keys smaller than the given key or throws a KeyNotFoundException.
10. Value & operator[](const Key &k): Returns a modifiable value for the given key or throws a KeyNotFoundException.
11. const Value & operator[](const Key &k) const: Returns a non-modifiable value for the given key or throws a KeyNotFoundException.
12. const Key & largestLessThan(const Key &k) const: Returns the largest key in the list that is less than the given key.
13. const Key & smallestGreaterThan(const Key &k) const: Returns the smallest key in the list that is greater than the given key.
14. bool operator==(const SortedList & l) const noexcept: Checks if two SortedLists are equal.
15. void operator++(): Pre-increment operator for every value in the list.

# Restrictions
- Implementation must be a doubly linked list.
- No additional #include directives without permission.
- No use of container classes like std::map.
- Proper memory management is crucial for grading.