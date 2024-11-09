#pragma once
// OpenMP header
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>
#include <numeric>

void hello_world() {
    std::cout << "(0) Test OpenMP" << std::endl;

     omp_set_num_threads(8);  

#pragma omp parallel
    {
            int tid = omp_get_thread_num();
        if (tid == 0) {
            int nthreads = omp_get_num_threads();
            printf("Expected threads = 8, Actual threads = %d\n", nthreads);
        }
        printf("Welcome from thread = %d\n", tid);
    }

    std::cout << "OpenMP test finished" << std::endl << std::endl;
}



void calSum()
{
    std::cout << "(1) Test calSum()" << std::endl;

    int sum = 0;
    int data_size = 100000000;
    int num_threads = 8;
    int* data = new int[data_size];
    for (int i = 0; i < data_size; ++i)
    {
        data[i] = 1;
    }

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();


    omp_set_num_threads(num_threads);
#pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < data_size; ++i)
    {
        sum += data[i];
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Elapsed time of calSum() by OpenMP = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()
        << "[milliseconds]" << std::endl;

    std::vector<int> vect(data, data + data_size);
    begin = std::chrono::steady_clock::now();
    int sumSTL = std::accumulate(vect.begin(), vect.end(), 0);
    end = std::chrono::steady_clock::now();
    std::cout << "Elapsed time of calSum() by STL accumulate() = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()
        << "[milliseconds]" << std::endl;

    assert(sum == data_size);
    assert(sum == sumSTL);
    std::cout << "calSum() assert pass!" << std::endl << std::endl;
}



void calMax()
{
    std::cout << "(2) Test calMax()" << std::endl;

    int max = 0;
    int data_size = 100000000;
    int num_threads = 8;
    int* data = new int[data_size];
    for (int i = 0; i < data_size; ++i)
    {
        data[i] = rand() % data_size;
    }

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();


    omp_set_num_threads(num_threads);
#pragma omp parallel for reduction(max:max)
    for (int i = 0; i < data_size; ++i)
    {
        if (data[i] > max)
        {
            max = data[i];
        }
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Elapsed time of calMax() by OpenMP = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()
        << "[milliseconds]" << std::endl;

    std::vector<int> vect(data, data + data_size);
    begin = std::chrono::steady_clock::now();
    int maxSTL = *std::max_element(vect.begin(), vect.end());
    end = std::chrono::steady_clock::time_point();
    std::cout << "Elapsed time of calMax() by STL max_element() = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()
        << "[milliseconds]" << std::endl;

    assert(max == maxSTL);
    std::cout << "calMax() assert pass!" << std::endl << std::endl;
}

