#ifndef SEPARATE_CHAINING_H
#define SEPARATE_CHAINING_H

#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <functional>
#include <iostream>
#include "Employee.h"
#include "utils.h"

using namespace std;

template <typename HashedObj>
class ChainingHash
{
public:
    explicit ChainingHash(int size = 101) : currentSize{ 0 }
    {
        theLists.resize(101);
    }

    bool contains(const HashedObj& x) const
    {
        // Locate the appropriate list based on the hash value of x
        const auto& targetList = theLists[myhash(x)];

        // Check if x is present in the list using std::find
        return std::find(targetList.begin(), targetList.end(), x) != targetList.end();
    }


    void makeEmpty()
    {
        // TODO: refer to Figure 5.9 in textbook
        for (auto& thisList : theLists) {
            thisList.clear();
        }
        currentSize = 0;
    }

    bool insert(const HashedObj& x)
    {
        // Calculate hash index for x and retrieve the corresponding bucket
        size_t index = myhash(x);
        auto& bucket = theLists[index];

        // Check if x already exists in the bucket and return false if it does
        if (std::any_of(bucket.begin(), bucket.end(), [&x](const HashedObj& obj) { return obj == x; })) {
            return false;
        }

        // Add x to the bucket and increment the size
        bucket.push_back(x);
        ++currentSize;

        // Trigger rehash if the size exceeds the threshold
        if (currentSize > theLists.size()) {
            rehash();
        }

        return true;  // Successfully inserted x
    }


    bool insert(HashedObj&& x)
    {
        // Determine the hash index for the given object
        const size_t bucketIndex = myhash(x);
        auto& bucket = theLists[bucketIndex];

        // Use a lambda to check for the presence of x in the bucket
        if (std::any_of(bucket.begin(), bucket.end(), [&x](const HashedObj& obj) { return obj == x; })) {
            return false;  // If x is already in the bucket, don't insert
        }

        // Move the object into the bucket to avoid copying
        bucket.emplace_back(std::move(x));
        ++currentSize;

        // Trigger a rehash if the number of elements exceeds the bucket size
        if (currentSize > theLists.size()) {
            rehash();
        }

        return true;  // Successfully inserted the object
    }


    bool remove(const HashedObj& x)
    {
        // Get the corresponding bucket for the hash value of x
        auto& bucket = theLists[myhash(x)];

        // Use an iterator to search for the object in the bucket
        auto iterator = std::find(bucket.begin(), bucket.end(), x);

        // If the element is not found, return false
        if (iterator == bucket.end()) {
            return false;
        }

        // Remove the element from the bucket and decrease the size
        bucket.erase(iterator);
        --currentSize;

        return true;  // Successfully removed the element
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
        return theLists.size();
    }

private:
    vector<list<HashedObj>> theLists;   // The array of Lists
    int currentSize;

    void rehash()
    {
        // Store the old list of buckets before resizing
        std::vector<std::list<HashedObj>> previousBuckets = theLists;

        // Resize the list of buckets to the next prime number
        size_t newBucketCount = nextPrime(2 * theLists.size());
        theLists.resize(newBucketCount);

        // Clear all the lists in the newly resized hash table
        for (auto& bucket : theLists) {
            bucket.clear();
        }

        // Reset the current size counter
        currentSize = 0;

        // Rehash and insert each element from the old lists into the new table
        for (auto& bucket : previousBuckets) {
            for (auto& obj : bucket) {
                insert(std::move(obj));
            }
        }
    }


    size_t myhash(const HashedObj& x) const
    {
        static hash<HashedObj> hf;
        return hf(x) % theLists.size();
    }

    double loadFactor()
    {
       
        return static_cast<double>(currentSize) / theLists.size();

    }
};

#endif
