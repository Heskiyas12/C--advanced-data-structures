#include <iostream>
#include <vector>
#include <chrono>
#include <random>

class SortingComparison {
public:
    // insrtion sort
    void insertionSort(std::vector<int>& arr) {
        for (size_t i = 1; i < arr.size(); i++) {
            int key = arr[i];
            int position = i;

            // Move elements greater than 'key' one step to the right
            while (position > 0 && arr[position - 1] > key) {
                arr[position] = arr[position - 1];
                position--;
            }

            if (position != i) {
                arr[position] = key;
            }
        }
    }


    // quick sort
    void quickSort(std::vector<int>& arr, int left, int right) {
        if (left >= right) {
            return; // Base case: no sorting needed
        }

        int pivotIndex = divide(arr, left, right);

        // Sort the subarrays around the pivot
        quickSort(arr, left, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, right);
    }


    // merge sort
    void mergeSort(std::vector<int>& arr, int start, int end) {
        if (start >= end) {
            return; // Base case: single element or invalid range
        }

        int middle = start + (end - start) / 2;

        // Divide and conquer: sort each half
        mergeSort(arr, start, middle);
        mergeSort(arr, middle + 1, end);

        // Combine the sorted halves
        merge(arr, start, middle, end);
    }


    // generate random integers
    std::vector<int> generateRandomArray(int size) {
    std::vector<int> randomArray(size);
    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());
    std::uniform_int_distribution<int> distribution(1, 100000);

    // Fill the array with random integers
    for (int& element : randomArray) {
        element = distribution(generator);
    }

    return randomArray;
}


    // test sorted
    bool isSorted(const std::vector<int>& arr) {
        for (size_t i = 0; i + 1 < arr.size(); i++) {
            if (arr[i] > arr[i + 1]) {
                return false; // Array is not sorted
            }
        }
        return true; // Array is sorted
    }


    // comparison run time for three sorting algorithms
    void compareSortingAlgorithms() {
        std::vector<int> testSizes = { 1000, 10000, 100000 }; // Array sizes for testing

        for (const int currentSize : testSizes) {
            // Generate a random array of the current size
            std::vector<int> originalArray = generateRandomArray(currentSize);
            std::cout << "Data size: " << currentSize << "\n";

            // Insertion Sort
            {
                std::vector<int> tempArray = originalArray;
                auto startTime = std::chrono::high_resolution_clock::now();
                insertionSort(tempArray);
                auto endTime = std::chrono::high_resolution_clock::now();
                double elapsedTime = std::chrono::duration<double>(endTime - startTime).count();
                std::cout << "Insertion Sort: " << elapsedTime << " seconds\n";
                std::cout << "Is Sorted: " << (isSorted(tempArray) ? "Yes" : "No") << "\n";
            }

            // Quick Sort
            {
                std::vector<int> tempArray = originalArray;
                auto startTime = std::chrono::high_resolution_clock::now();
                quickSort(tempArray, 0, static_cast<int>(tempArray.size() - 1));
                auto endTime = std::chrono::high_resolution_clock::now();
                double elapsedTime = std::chrono::duration<double>(endTime - startTime).count();
                std::cout << "Quick Sort: " << elapsedTime << " seconds\n";
                std::cout << "Is Sorted: " << (isSorted(tempArray) ? "Yes" : "No") << "\n";
            }

            // Merge Sort
            {
                std::vector<int> tempArray = originalArray;
                auto startTime = std::chrono::high_resolution_clock::now();
                mergeSort(tempArray, 0, static_cast<int>(tempArray.size() - 1));
                auto endTime = std::chrono::high_resolution_clock::now();
                double elapsedTime = std::chrono::duration<double>(endTime - startTime).count();
                std::cout << "Merge Sort: " << elapsedTime << " seconds\n";
                std::cout << "Is Sorted: " << (isSorted(tempArray) ? "Yes" : "No") << "\n";
            }

            // Separate test results
            std::cout << "---------------------------------------\n";
        }
    }


private:
    // Some internal helper functions
    int divide(std::vector<int>& arr, int left, int right) {
        int pivotValue = arr[right];
        int partitionIndex = left - 1;

        for (int currentIndex = left; currentIndex < right; ++currentIndex) {
            if (arr[currentIndex] <= pivotValue) {
                ++partitionIndex;
                std::swap(arr[partitionIndex], arr[currentIndex]);
            }
        }

        // Place the pivot in its correct position
        std::swap(arr[partitionIndex + 1], arr[right]);
        return partitionIndex + 1;
    }

    void merge(std::vector<int>& arr, int left, int mid, int right) {
        int leftSize = mid - left + 1;
        int rightSize = right - mid;

        // Create temporary arrays for left and right partitions
        std::vector<int> leftArray(leftSize), rightArray(rightSize);

        for (int index = 0; index < leftSize; ++index) {
            leftArray[index] = arr[left + index];
        }

        for (int index = 0; index < rightSize; ++index) {
            rightArray[index] = arr[mid + 1 + index];
        }

        int leftIndex = 0, rightIndex = 0, mainIndex = left;

        // Merge left and right arrays back into the main array
        while (leftIndex < leftSize && rightIndex < rightSize) {
            if (leftArray[leftIndex] <= rightArray[rightIndex]) {
                arr[mainIndex++] = leftArray[leftIndex++];
            }
            else {
                arr[mainIndex++] = rightArray[rightIndex++];
            }
        }

        // Copy remaining elements, if any
        while (leftIndex < leftSize) {
            arr[mainIndex++] = leftArray[leftIndex++];
        }

        while (rightIndex < rightSize) {
            arr[mainIndex++] = rightArray[rightIndex++];
        }
    }

};

int main() {
    SortingComparison sorter;
    sorter.compareSortingAlgorithms();
    return 0;
}
