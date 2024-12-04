#include <iostream>
#include "DisjointSets.h"
using namespace std;
// Test main; all finds on same output line should be identical

int main()
{
    int numElements = 128;
    int numInSameSet = 16;
    DisjointSets ds{ numElements };

    // Perform unions to group elements into sets of size `numInSameSet`
    for (int i = 0; i < numElements; i += numInSameSet) {
        for (int j = 1; j < numInSameSet; ++j) {
            int set1 = ds.find(i);
            int set2 = ds.find(i + j);
            ds.unionSets(set1, set2);
        }
    }

    // Print the results
    for (int i = 0; i < numElements; ++i) {
        cout << ds.find(i) - 1 << "*"; // Adjust to make output 0-based
        if (i % numInSameSet == numInSameSet - 1)
            cout << endl;
    }
    cout << endl;
    return 0;
}

