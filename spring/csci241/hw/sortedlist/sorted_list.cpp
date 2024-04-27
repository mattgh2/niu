#include <iostream>
#include "sorted_list.h"

using std::ostream;

/*
 * Copy constructor
 *
 * @param x List to copy.
 */
sorted_list::sorted_list(const sorted_list& x)
{
    l_front = nullptr;
    l_size = 0;
    clone(x);
}

/*
 * Destructor.
 */
sorted_list::~sorted_list()
{
    clear();
}

/*
 * Copy assignment operator.
 *
 * @param x List to copy.
 *
 * @return The value of the copied list.
 */
sorted_list& sorted_list::operator=(const sorted_list& x)
{
    if (this != &x)
    {
        clear();
        clone(x);
    }
         
    return *this;
}

/*
 * Removes all elements from the list.
 */
void sorted_list::clear()
{
    while (!empty())
    {
        pop_front();
    }
}

/*
 * Returns the number of elements in the list.
 *
 * @return The list size.
 */
size_t sorted_list::size() const
{
    return l_size;
}

/*
 * Tests whether the list is empty.
 *
 * @return Returns true if the list size is 0; otherwise, false.
 */
bool sorted_list::empty() const
{
    return (l_size == 0);
}

/*
 * Access first element.
 *
 * @return The value of the first element in the list.
 */
int sorted_list::front() const
{
    return l_front->value;
}

/*
 * Adds a new element with the specified value at the front of the list.
 *
 * @param value The value to add to the list.
 */
void sorted_list::push_front(int value)
{
    node* new_node = new node(value, l_front);
    l_front = new_node;
    l_size++;
}

/*
 * Removes the first element from the list.
 */
void sorted_list::pop_front()
{
    node* del_node;
    
    del_node = l_front;
    l_front = l_front->next;
    delete del_node;
    l_size--;
}

/*
 * Makes a copy of a list object's elements.
 *
 * @param x List to copy.
 */
void sorted_list::clone(const sorted_list& x)
{
    node* ptr;
    node* new_node;
    node* last = nullptr;

    for (ptr = x.l_front; ptr != nullptr; ptr = ptr->next)
    {
        new_node = new node(ptr->value);
        if (last == nullptr)
            l_front = new_node;
        else
            last->next = new_node;
        last = new_node;
        l_size++;
    }
}

/*
 * Prints the elements of a list from front to back.
 *
 * @param os The output stream on which to print the list.
 * @param obj The list object to print.
 *
 * @return Returns the output stream.
 */
ostream& operator<<(ostream& os, const sorted_list& obj)
{
    node* ptr;
    int i;

    os << '(';
    for (i = 0, ptr = obj.l_front; i < (int) obj.l_size - 1; i++, ptr = ptr->next)
    {
        os << ptr->value << ", ";
    }

    if (ptr)
        os << ptr->value;

    os << ')';

    return os;
}

/*
 * Inserts the specified value into the list, maintaining
 * sorted order.
 *
 * @param value Value to insert into the list.
 */
void sorted_list::insert(int value)
{
    node *new_node = new node(value);
    node *ptr = l_front;
    node *trail = nullptr;

    while (ptr != nullptr && value > ptr->value) {
        trail = ptr;
        ptr = ptr->next;
    }
    if (trail == nullptr) {
        new_node->next = l_front;
        l_front = new_node;
    
    }
    else {
        new_node->next = trail->next;
        trail->next = new_node;
    }
    l_size++;
}

/*
 * Removes all occurrences of the specified value
 * from the list.
 */
void sorted_list::remove(int value)
{
    node *ptr = l_front;
    node *trail = nullptr;

    while (ptr != nullptr) {
        if (ptr->value == value) {
            if (trail == nullptr) {
                ptr = ptr->next;
                pop_front();
            } else {
                node *tmp = ptr->next;
                delete ptr;
                ptr = tmp;
                trail->next = ptr;
                l_size--;
            }
        } else {
            trail = ptr;
            ptr = ptr->next;
        }
                
    }
}
        
