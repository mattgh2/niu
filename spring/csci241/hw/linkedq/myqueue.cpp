#include <iostream>
#include "myqueue.h"

using std::ostream;

/**
 * Constructs a myqueue with a copy of the elements of another myqueue.
 *
 * @param x Another myqueue object whose contents are copied.
 */
myqueue::myqueue(const myqueue& x)
{
    q_front = q_back = nullptr;
    q_size = 0;
    clone(x);
}

/**
 * Destroys the myqueue object.
 */
myqueue::~myqueue()
{
    clear();
}

/**
 * Assigns new contents to a myqueue.
 *
 * @param x A myqueue object whose contents are copied.
 *
 * @return The value of the modified left operand.
 */
myqueue& myqueue::operator=(const myqueue& x)
{
    if (this != &x)
    {
        clear();
        clone(x);
    }
    
    return *this;
}

/**
 * Sets a myqueue back to empty, without deleting its dynamic storage.
 */
void myqueue::clear()
{
    q_size = 0;
    q_front = 0;
    q_back = 0;
}

/**
 * Returns whether the myqueue is empty: i.e., whether its size is 0.
 *
 * @return true if the size is 0, false otherwise.
 */
bool myqueue::empty() const
{
    return (q_size == 0);
}

/**
 * Returns the size of the myqueue.
 *
 * @return The number of values stored in the myqueue.
 */
size_t myqueue::size() const
{
    return (q_size);
}

/**
 * Inserts a value at the back of the myqueue.
 *
 * @param value An integer value to insert.
 */
void myqueue::push(int value)
{
    node* new_node = new node(value);

    if (empty()) {
        q_front = new_node;
    } else {
        q_back->next = new_node;
    }
    q_back = new_node;
    q_size++;

}

/**
 * Removes the value at the front of the myqueue.
 */
void myqueue::pop()
{
    node *delete_node = new node(0);
    delete_node = q_front;

    q_front = q_front-> next;

    if (q_front == nullptr) {
        q_back = nullptr;
    }
    delete delete_node;
    q_size--;

}

/**
 * Returns the value at the front of the myqueue.
 *
 * @return The value of the front item in the myqueue's array.
 */
int myqueue::front() const
{
    return q_front->value;
}

/**
 * Returns the value at the back of the myqueue.
 *
 * @return The value of the back item in the myqueue's array.
 */
int myqueue::back() const
{
    return q_back->value;
}

/**
 * Makes a copy of a myqueue object's linked list.
 *
 * @param x Another myqueue object whose linked list is copied.
 */
void myqueue::clone(const myqueue& x)
{
  node* ptr = x.q_front;
  
  // Loops that copies over nodes
    while (ptr != nullptr) {
        push(ptr->value);
        ptr = ptr->next;
    }
}

/**
 * Inserts the elements of the myqueue into an output stream.
 *
 * @param os The output stream.
 * @param obj A myqueue object to insert into the stream.
 *
 * @return The output stream.
 */
ostream& operator<<(ostream& os, const myqueue& obj)
{
    node* ptr;

    os << '(';
    for (ptr = obj.q_front; ptr; ptr = ptr->next)
    {
        os << ptr->value;
        
        // If this is not the last node in the list
        if (ptr->next)
            os << ", ";
    }
    os << ')';
    
    return os;
}
