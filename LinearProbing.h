#ifndef LINEAR_PROBING_H
#define LINEAR_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <iostream>
#include "Employee.h"
#include "utils.h"

using namespace std;

// this inplementation follows Figure 5.14 in textbook for quadratic probing
template <typename HashedObj>
class ProbingHash
{
public:
    explicit ProbingHash(int size = 101) : array(nextPrime(size)), currentSize{ 0 }
    {
        makeEmpty();
    }

    bool contains(const HashedObj& x) const
    {
        // Find the position of x in the table using quadratic probing
        int position = findPos(x);

        // Check if the position is active (i.e., the element exists at that position)
        return position >= 0 && isActive(position);
    }


    void makeEmpty()
    {
        // Set all elements' status to EMPTY in the array
        for (auto& item : array) {
            item.info = EMPTY;
        }

        // Clear the current size to indicate the table is empty
        currentSize = 0;

    }

    bool insert(const HashedObj& x)
    {
        // Calculate the index where the object should go
        int idx = findPos(x);

        // If the object is already present, return early
        if (isActive(idx)) {
            return false;  // No insertion needed, item exists
        }

        // Place the item into the array at the calculated index
        array[idx] = HashEntry(x, ACTIVE);
        ++currentSize;

        // If the load factor exceeds a set threshold, resize the table
        if (currentSize > array.size() / 2) {
            rehash();
        }

        return true;  // Insertion was successful
    }

    bool insert(HashedObj&& x)
    {
        // Find the appropriate position for the new object
        int idx = findPos(x);

        // If the object is already active at this position, exit early
        if (isActive(idx)) {
            return false;  // Item already exists, no need to insert
        }

        // Move the object into the array to avoid unnecessary copies
        array[idx] = HashEntry(std::move(x), ACTIVE);
        ++currentSize;

        // Rehash if the current load factor surpasses 50%
        if (currentSize > array.size() / 2) {
            rehash();
        }

        return true;  // Successfully inserted the object
    }


    bool remove(const HashedObj& x)
    {
        // Find the position of the object using quadratic probing
        int index = findPos(x);

        // Check if the object is marked as active; if not, it cannot be removed
        if (isActive(index)) {
            // Mark the object as deleted and adjust the current size
            array[index].info = DELETED;
            --currentSize;
            return true;  // Object successfully removed
        }

        // Return false if the object isn't active (either doesn't exist or already deleted)
        return false;
    }


    double readLoadFactor()
    {
        return loadFactor();
    }

    double readCurrentSize()
    {
        return currentSize;
    }

    double readArraySize()
    {
        return array.size();
    }

    enum EntryType { ACTIVE, EMPTY, DELETED };

private:
    struct HashEntry
    {
        HashedObj element;
        EntryType info;

        HashEntry(const HashedObj& e = HashedObj{ }, EntryType i = EMPTY)
            : element{ e }, info{ i } { }

        HashEntry(HashedObj&& e, EntryType i = EMPTY)
            : element{ std::move(e) }, info{ i } { }
    };

    vector<HashEntry> array;
    int currentSize;

    bool isActive(int currentPos) const
    {
        return array[currentPos].info == ACTIVE;
    }

    int findPos(const HashedObj& x) const
    {
        // Calculate the initial position based on the hash value
        int currentPos = myhash(x);
        int initialPos = currentPos;
        int step = 1;  // Step size for linear probing

       
        while (array[currentPos].info != EMPTY) {
            if (array[currentPos].element == x) {
                // Element found, return its position
                return currentPos;
            }

            // Move to the next position using linear probing
            currentPos = (currentPos + step) % array.size();

            
            if (currentPos == initialPos) {
                break;  // Full cycle completed, element not found
            }
        }

        
        return currentPos;
    }


    void rehash()
    {
        
        size_t newSize = nextPrime(2 * array.size());

       
        vector<HashEntry> oldArray = std::move(array);
        array.resize(newSize);

       
        for (size_t i = 0; i < array.size(); ++i) {
            array[i].info = EMPTY;
        }

        currentSize = 0;  

       
        for (auto& entry : oldArray) {
            if (entry.info == ACTIVE) {
                
                insert(std::move(entry.element));
            }
        }
    }


    size_t myhash(const HashedObj& x) const
    {
        static hash<HashedObj> hf;
        return hf(x) % array.size();
    }


    double loadFactor()
    {
        // TODO: compute the load factor of hash table, defined on Page 198 of textbook
        //return 0.0;
        return static_cast<double>(currentSize) / array.size();

    }
};

#endif