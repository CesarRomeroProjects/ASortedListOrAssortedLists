#ifndef __SORTED_DOUBLY_LINKED_LIST_HPP
#define __SORTED_DOUBLY_LINKED_LIST_HPP

#include <stdexcept>

class KeyNotFoundException : public std::runtime_error 
{
public:
	explicit KeyNotFoundException(const std::string & err) : std::runtime_error(err) {}
};

template<typename Key, typename Value>
class SortedList
{
private:
	// fill in private member data here
	struct Node {
		Node(const Key& k, const Value& v)
		: key(k), value(v), next(nullptr), prev(nullptr) 
		{}

		Key key;
		Value value;
		Node* next;
		Node* prev;
	};

	Node* head;
	Node* tail;

public:
	SortedList();

	// Note:  copy constructors are required.
	// Be sure to do a "deep copy" -- if I 
	// make a copy and modify one, it should not affect the other. 
	SortedList(const SortedList & st);
	SortedList & operator=(const SortedList & st);
	~SortedList();


	size_t size() const noexcept;
	bool isEmpty() const noexcept;


	// If this key is already present, return false.
	// otherwise, return true after inserting this key/value pair.
	bool insert(const Key &k, const Value &v); 

	// Return true if this SortedList contains a mapping of this key.
	bool contains(const Key &k) const noexcept; 


	// removes the given key (and its associated value) from the list.
	// If that key is not in the list, this will silently do nothing.
	void remove(const Key &k);

	// If this key exists in the list, this function returns how many keys are in the list that are less than it.
	// If this key does not exist in the list, this throws a KeyNotFoundException.
	unsigned getIndex(const Key &k) const;

	// If this key does not exist in the list, this throws a KeyNotFoundException.
	// subscript operator for non-const objects returns modifiable lvalue
	Value & operator[] (const Key &k) ;



	// subscript operator for nonconst objects returns non-modifiable lvalue
	// DON'T FORGET TO TEST THIS FUNCTION EXPLICITLY
	// I omitted it from required test cases on purpose.
	// Write a test case that calls this -- I showed you how in class a few times.
	// In projects like this (which also come up in ICS 46), forgetting to test this
	// is a major cause of lost points, sometimes disproportionate to how easy the fix is.
	// Don't let that happen to you.
	// (I'd rather it doesn't happen to anyone)
	const Value & operator [] (const Key & k) const; 



	// returns the largest key in the list that is < the given key.
	// If no such element exists, this throws a KeyNotFoundException.
	// Hint:  think carefully about the situation where none would exist.
	//		Think also very carefully about how this is different
	//		from the subscript operator functions and the getIndex function.
	// A little bit of thinking ahead of time will make this *much easier* to program.
	const Key & largestLessThan(const Key & k) const;



	// This is similar to the previous one, but has some key (pun intended) differences.
	// I recommend you finish the previous function and *extensively* test it first.
	// (be sure to think about boundary cases!)
	// THEN, think carefully about how this differs from that -- you might want to 
	// approach it slightly differently than you approached that one.
	// The time you spend thinking about this will likely save you even more time
	// 	when you can code this quicker and have fewer bugs.
	// There's no prize for "first to finish this function."  Write the previous one first.
	const Key & smallestGreaterThan(const Key & k) const;

	
	// Two SortedLists are equal if and only if:
	//	* They have the same number of elements
	//	* Each element matches in both key and value.
	// This is only a meaningful operator when key-type and value-type both have
	// an implemented operator==.  As such, we will only test with those.
	bool operator==(const SortedList & l) const noexcept;

	// preincrement every Value (not key) in the list.
	// Unlike a numeric type's ++ operator, this does not return a copy of itself.
	// Note that this is silly and is done explicitly to have overload this operator
	// in this assignment.  
	// Because the syntax of pre-incrementing an element can be weird, although
	// it is what you probably think it is, for purposes of this assignment, I will 
	// only test this with value-types whose pre-increment and post-increment
	// operators have the same end-state.
	void operator++();
};


template<typename Key, typename Value>
SortedList<Key,Value>::SortedList()
{
	head = nullptr;
	tail = nullptr;
}


template<typename Key, typename Value>
SortedList<Key,Value>::SortedList(const SortedList & st)
{
	head = nullptr;
	tail = nullptr;

	Node* currentNode{st.head};
	while ( currentNode != nullptr ) {
		insert(currentNode->key, currentNode->value);
		currentNode = currentNode->next;
	}
}


template<typename Key, typename Value>
SortedList<Key,Value> & SortedList<Key,Value>::operator=(const SortedList & st)
{
	if( this != &st )
	{
		while (!isEmpty()) {
			Node* tmp{head};
			head = head->next;
			delete tmp;
		}

		Node* currentNode{st.head};
		while ( currentNode != nullptr ) {
			insert(currentNode->key, currentNode->value);
			currentNode = currentNode->next;
		}
	}

	return *this;

}
	
template<typename Key, typename Value>
SortedList<Key,Value>::~SortedList()
{
	while(head) 
	{
		Node* tmp{head};
		head = head->next;
		delete tmp;
	}
	tail = nullptr;
}


template<typename Key, typename Value>
size_t SortedList<Key,Value>::size() const noexcept
{
	size_t sortedListCount{0};
	Node* currentNode{head};

	while ( currentNode != nullptr ) 
	{
		sortedListCount++;
		currentNode = currentNode->next;
	}
	return sortedListCount;
}

template<typename Key, typename Value>
bool SortedList<Key,Value>::isEmpty() const noexcept
{
	return head == nullptr;
}


// If this key is already present, return false.
// otherwise, return true after inserting this key/value pair/.
template<typename Key, typename Value>
bool SortedList<Key,Value>::insert(const Key &k, const Value &v)
{
	// CHECK IF KEY IS PRESENT, INSERT RETURNS FALSE IF SO.
	if ( contains(k) )
		return false;

	// SETUP THE DOUBLY LINKED LIST.
	Node* createNode{new Node(k, v)};
	if ( !head )
		head = tail = createNode;
	else {
		Node* currentNode{head};
		while ( currentNode && ( k > currentNode->key ) )
			currentNode = currentNode->next;

		if ( !currentNode ) 
		{
			createNode->prev = tail;
			tail->next = createNode;
			tail = createNode;
		} else {
			if ( currentNode->prev ) 
			{
				currentNode->prev->next = createNode;
				createNode->prev = currentNode->prev;
			} else
				head = createNode;

			createNode->next = currentNode;
			currentNode->prev = createNode;
		}
	}
	return true;
}

template<typename Key, typename Value>
bool SortedList<Key,Value>::contains(const Key &k) const noexcept
{
	// TRAVERSE THROUGH THE DOUBLY LINKED LIST, TO SEE IF KEY EXISTS OR NOT.	
	Node* currentNode{head};
	while ( currentNode ) 
	{
		if ( currentNode->key == k )
			return true;
		currentNode = currentNode->next; // GOES TO THE FOLLOWING NODE, WHICH LINKED LIST SHOULD BE SORTED.
	}
	return false;
}

template<typename Key, typename Value>
void SortedList<Key,Value>::remove(const Key &k) 
{
	Node* currentNode{head};
	while ( currentNode ) 
	{
		if ( currentNode->key == k) 
		{
			if ( currentNode->prev)
				currentNode->prev->next = currentNode->next;
			else
				head = currentNode->next;
			
			if ( currentNode->next )
				currentNode->next->prev = currentNode->prev;
			else
				tail = currentNode->prev;
			
			delete currentNode;
			return;
		}
		currentNode = currentNode->next;
	}
}

// If this key exists in the list, this function returns how many keys are in the list that are less than it.
// If this key does not exist in the list, this throws a KeyNotFoundException.
template<typename Key, typename Value>
unsigned SortedList<Key,Value>::getIndex(const Key &k) const
{
	if ( contains(k) ) 
	{
		unsigned count{0};
		Node* currentNode{head};
		while ( currentNode->key != k ) 
		{
			count++;
			currentNode = currentNode->next;
		}
		return count;
	}
	else
		throw KeyNotFoundException{"Key not found in list"};
}

template<typename Key, typename Value>
Value & SortedList<Key,Value>::operator[] (const Key &k) 
{
	if ( contains(k) ) 
	{
		Node* currentNode{head};
		while ( currentNode->key != k )
			currentNode = currentNode->next;
		return currentNode->value;
	}
	else
		throw KeyNotFoundException{"Key not found in list"};  
}

template<typename Key, typename Value>
const Value & SortedList<Key,Value>::operator[] (const Key &k) const 
{
	if ( contains(k) ) 
	{
		Node* currentNode{head};
		while ( currentNode->key != k )
			currentNode = currentNode->next;
		return currentNode->value;
	}
	else
		throw KeyNotFoundException{"Key not found in list"};  
}

template<typename Key, typename Value>
const Key & SortedList<Key,Value>::largestLessThan(const Key & k) const
{
	// If the list is empty.
	if (isEmpty())
		throw KeyNotFoundException("Key not found in list");
	else 
	{
		Node* currentNode{tail};

		while ( currentNode && !(currentNode->key < k) )
			currentNode = currentNode->prev;

		if ( !currentNode )
			throw KeyNotFoundException{"Key not found in list"};

		return currentNode->key;
	}
}

template<typename Key, typename Value>
const Key & SortedList<Key,Value>::smallestGreaterThan(const Key & k) const
{
	if ( isEmpty() )
		throw KeyNotFoundException("Key not found in list");
	else 
	{
		Node* currentNode{head};
		while ( currentNode && !(currentNode->key > k) )
			currentNode = currentNode->next;

		if ( !currentNode )
			throw KeyNotFoundException("Key not found in list");

		return currentNode->key;
	}
}

template <typename Key, typename Value>
bool SortedList<Key,Value>::operator==(const SortedList & l) const noexcept
{
	// CHECK IF THEY HAVE SAME NUMBER OF ELEMENTS
	if ( size() != l.size() )
		return false;

	// CHECK IF EACH ELEMENTS MATCHES IN KEY-VALUE PAIR
	Node* nodeOne{head};
	Node* nodeTwo{l.head};

	while ( nodeOne ) 
	{
		if ( ( nodeOne->key != nodeTwo->key ) && ( nodeOne->value != nodeTwo->value ) )
			return false;
		nodeOne = nodeOne->next;
		nodeTwo = nodeTwo->next;
	}
	return true;
}

template <typename Key, typename Value>
void SortedList<Key,Value>::operator++()
{
	// CHECK IF THE LIST IS EMPTY.
	if ( isEmpty() )
		return;

	Node* currentNode{head};
	while ( currentNode )
	{
		++currentNode->value;
		currentNode = currentNode->next;
	}
}

#endif 

