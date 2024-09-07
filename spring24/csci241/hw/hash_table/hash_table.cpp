#include <iomanip>
#include <iostream>
#include <string>
#include "hash_table.h"

using std::endl;
using std::left;
using std::ostream;
using std::right;
using std::setfill;
using std::setw;
using std::string;

/**
 Hashes an integer key to produce a hash value.
 
 @param key - The integer key to hash.
 
 @return - Returns the integer hash value, an array subscript between 0 and
           TABLE_SIZE - 1.
 */
int hash_table::hash(int key) const
{
    return key % TABLE_SIZE;
}

/**
 Attempts to insert a key and value into the hash table.

 @param key - The integer key to insert.

 @param value - The string value to insert.

 @return - Returns true if successful; otherwise, false.
*/
bool hash_table::insert(int key, const string& value)
{
    int index = hash(key);
    for (int i = index; i < TABLE_SIZE; i++)
    {
        if (table[i].state == EMPTY || table[i].state == DELETED) {
            table[i].key = key;
            table[i].value = value;
            table[i].state = FILLED;
            return true;
        }
    }
    for (int i = 0; i < index; i++) {
        if (table[i].state == EMPTY || table[i].state == DELETED) {
            table[i].key = key;
            table[i].value = value;
            table[i].state = FILLED;
            return true;
        }
    }
    return false;
}

/**
 Attempts to find a key in the hash table.

 @param key - The integer key to find.

 @return - Returns the index of the table element that contains
           the key if successful; otherwise, returns -1.
*/
int hash_table::find(int key) const
{
    int index = hash(key);
    for (int i = index; i < TABLE_SIZE; i++) {
        if (table[i].state == EMPTY)
            return -1;
        else if (table[i].key == key) {
            return i;
        }
    }
    for (int i = 0; i < index; i++) {
        if (table[i].state == EMPTY)
            return -1;
        else if (table[i].key == key) {
            return i;
        }
    }
    return -1;
}

/**
 Attempts to update the value of the record with the specified
 key.

 @param key - The integer key of the record to update.

 @param value - The new value to be used to update the record.

 @return - Returns true if successful; otherwise, false.
*/
bool hash_table::update(int key, const string& value)
{
    int index = find(key);
    if (index == -1)
        return false;
    table[index].value = value;
    return true;
    // for (int i = index; i < TABLE_SIZE; i++) {
    //     if (index == TABLE_SIZE - 1) {
    //         index = (index + 1) % TABLE_SIZE;
    //     }
    //
    //     if (table[i].state == EMPTY) {
    //         return false;
    //     }
    //
    //     else if (table[i].key == key) {
    //         table[i].value = value;
    //         return true;
    //     }
    // }
}

/**
 Attempts to delete the record with the specified key from the 
 hash table.

 @param key - The integer key for the record to delete.

 @return - Returns true if successful; otherwise, false.
*/
bool hash_table::erase(int key)
{
    int index = find(key);
    if (index == -1)
        return false;
    table[index].state = DELETED;
    return true;
}

/**
 Prints the hash table in a formatted fashion on the specified
 output stream.

 @param os - The output stream on which to print the table.

 @param obj - The hash_table object to print.

 @return - The updated output stream.
*/
ostream& operator<<(ostream& os, const hash_table& obj)
{
    os << "Index  Key    Value\n";
    os << "===========================================================\n";

    for (int i = 0; i < obj.TABLE_SIZE; i++)
    {
        os << setfill(' ') << '[' << setw(2) << right << i << "]   ";
        
        if (obj.table[i].state == EMPTY)
            os << "EMPTY";
        else if (obj.table[i].state == DELETED)
            os << "DELETED";
        else
            os << setfill('0') << right << setw(4) << obj.table[i].key
               << "   " << setfill(' ') << left << obj.table[i].value;
        
        os << endl;
    }
    
    return os;
}
