//
// Created by Manju Muralidharan on 10/19/25.
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64];
    int size;

    MinHeap() { size = 0; }

    void push(int idx, int weightArr[]) {
        // TODO: insert index at end of heap, restore order using upheap()
    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        // Replace root with last element, then call downheap()
        return -1; // placeholder
    }
    // Restores the minheap property after inserting a new element

    void upheap(int pos, int weightArr[]) {
        while (pos > 0) {
            int parent = (pos - 1) / 2;
            int a = data[pos];
            int b = data[parent];

            bool smallerByWeight = (weightArr[a] < weightArr[b]);
            bool tieAndSmallerIdx = (weightArr[a] == weightArr[b] && a < b);

            if (smallerByWeight || tieAndSmallerIdx) {
                int temp = data[pos];
                data[pos] = data[parent];
                data[parent] = temp;
                pos = parent;
            } else {
                break;
            }
        }
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
    }
};

#endif