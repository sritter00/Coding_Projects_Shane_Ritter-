/*
 * sorter.h
 *
 * Declares a template function:
 *    
 *   sorter() : k-way merge sort.
 * 
 * 
 * 
 * Author: Shane Ritter
 */

#ifndef _SORTER_H
#define _SORTER_H

#include <string>
#include <vector>
using namespace std;

template <class T>
vector<T> mergeArrays(vector<T>& arr1, vector<T>& arr2) {
    vector<T> result;
    size_t i = 0, j = 0;
    while (i < arr1.size() && j < arr2.size()) {
        if (arr1[i] < arr2[j]) {
            result.push_back(arr1[i++]);
        } else {
            result.push_back(arr2[j++]);
        }
    }
    while (i < arr1.size()) {
        result.push_back(arr1[i++]);
    }
    while (j < arr2.size()) {
        result.push_back(arr2[j++]);
    }
    return result;
}

template <class T>
vector<T> kWayMerge(vector<vector<T>>& arrays) {
    if (arrays.empty()) return {};
    while (arrays.size() > 1) {
        vector<vector<T>> merged;
        for (size_t i = 0; i < arrays.size(); i += 2) {
            if (i + 1 < arrays.size()) {
                merged.push_back(mergeArrays(arrays[i], arrays[i + 1]));
            } else {
                merged.push_back(arrays[i]);
            }
        }
        arrays = merged;
    }
    return arrays[0];
}

template <class T>
void sorter(vector<T>& vec, int k) {
    if (vec.size() <= 1) return;

    vector<vector<T>> subarrays(k);
    size_t size = vec.size() / k;
    size_t remainder = vec.size() % k;
    size_t index = 0;
    for (int i = 0; i < k; ++i) {
        size_t subarraySize = size + ( static_cast<size_t> (i) < remainder ? 1 : 0);
        subarrays[i].insert(subarrays[i].end(), vec.begin() + index, vec.begin() + index + subarraySize);
        index += subarraySize;
    }

    for (int i = 0; i < k; ++i) {
        sorter(subarrays[i], k);
    }

    vec = kWayMerge(subarrays);
}
#endif
