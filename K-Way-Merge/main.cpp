/*
 * main.cpp
 *
 * Includes the main() function for the sorting project. 
 *
 * This code is included in the build target "run-main"
*/

#include <iostream>
#include <vector>
#include <chrono>
#include "sorter.h" 

using namespace std;

#include <iostream>
#include <vector>
#include "sorter.h"

using namespace std;

template <class T>
void printVector(const vector<T>& vec) {
    for (const T& val : vec) {
        cout << val << " ";
    }
    cout << endl;
}

void testSorter() {
    // Test 1: Simple test with integers
    vector<int> vec1 = {38, 27, 43, 3, 9, 82, 10};
    int k1 = 3;
    cout << "Original array: ";
    printVector(vec1);

    sorter(vec1, k1);
    cout << "Sorted array: ";
    printVector(vec1);

    // Test 2: Already sorted array
    vector<int> vec2 = {1, 2, 3, 4, 5};
    int k2 = 2;
    cout << "\nOriginal array: ";
    printVector(vec2);

    sorter(vec2, k2);
    cout << "Sorted array: ";
    printVector(vec2);

    // Test 3: Single element array
    vector<int> vec3 = {42};
    int k3 = 2;
    cout << "\nOriginal array: ";
    printVector(vec3);

    sorter(vec3, k3);
    cout << "Sorted array: ";
    printVector(vec3);

    // Test 4: Empty array
    vector<int> vec4;
    int k4 = 2;
    cout << "\nOriginal array: ";
    printVector(vec4);

    sorter(vec4, k4);
    cout << "Sorted array: ";
    printVector(vec4);

    // Test 5: Large array with repeated elements
    vector<int> vec5 = {5, 1, 4, 2, 8, 5, 9, 6, 5, 5, 2};
    int k5 = 4;
    cout << "\nOriginal array: ";
    printVector(vec5);

    sorter(vec5, k5);
    cout << "Sorted array: ";
    printVector(vec5);

    // Test 6: Test with floating-point numbers
    vector<float> vec6 = {2.5, 1.1, 4.8, 3.3, 0.9};
    int k6 = 2;
    cout << "\nOriginal array: ";
    printVector(vec6);

    sorter(vec6, k6);
    cout << "Sorted array: ";
    printVector(vec6);
}

int main() {
    testSorter();
    return 0;
}


