#include <iostream>
#include "mylist.h"

using std::ostream;

/**
 * Constructs a myqueue with a copy of the elements of another myqueue.
 *
 * @param ar An array of values to insert into the list.
 * @param n Size of the array.
 */
mylist::mylist(int ar[], size_t n)
{
    node* new_node;
    l_front = nullptr;
    l_size = 0;
    
    for (int i = n - 1; i >= 0; i--)
    {
        new_node = new node(ar[i], l_front);
        l_front = new_node;
        l_size++;
    }
}

/**
 * Destroys the mylist object.
 */
mylist::~mylist()
{
    node* del_node;
    
    while (l_front)
    {
        del_node = l_front;
        l_front = l_front->next;
        delete del_node;
    }
}

/**
 * Returns whether the mylist is empty: i.e., whether its size is 0.
 *
 * @return true if the size is 0, false otherwise.
 */
bool mylist::empty() const
{
    return (l_size == 0);
}

/**
 * Returns the size of the myqueue.
 *
 * @return The number of values stored in the myqueue.
 */
size_t mylist::size() const
{
    return l_size;
}

/**
 * Inserts the elements of the myqueue into an output stream.
 *
 * @param os The output stream.
 * @param obj A myqueue object to insert into the stream.
 *
 * @return The output stream.
 */
ostream& operator<<(ostream& os, const mylist& obj)
{
    node* ptr;

    os << '(';
    for (ptr = obj.l_front; ptr; ptr = ptr->next)
    {
        os << ptr->value;
        
        // If this is not the last node in the list
        if (ptr->next)
            os << ", ";
    }
    os << ')';
    
    return os;
}

/**
 * Reverses the order of the elements of the mylist. Ideally, this should not
 * require allocating or deallocating any nodes.
 */
void mylist::reverse()
{
    if (l_size == 0)
        return;
    if (l_size == 1) {
        return;
    }
    node *p_left = l_front;
    node *p_right = l_front;
    node *tmp = l_front;

    // Traverse to the back
    while (p_left->next != nullptr) {
        p_left = p_left->next;
    }
    for (;;) {
        if (p_left->next == p_right) {
            return;
        }
        int temp_value = p_right->value;
        p_right->value = p_left->value;
        p_left->value = temp_value;
        
        p_right = p_right->next;
        while (tmp->next != p_left) {
            tmp = tmp->next;
        }
        p_left = tmp;
        tmp = l_front; 
    }
}

