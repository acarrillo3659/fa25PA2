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


    //  Insert a node index to heap, placing it at the end of data array and then restore the minheap order by calling upheap on the insert position
    //  weightArr[] is used for comparisons and ties are broken by the smaller index
    //  If size is full insert is ignored and prints message

    void push(int idx, int weightArr[]) {
        if (size >= 64) {
            cout << "Heap is full. Cannot insert new element." << endl;
            return;
        }
        data[size] = idx;
        upheap(size, weightArr);
        size++;
    }

    //  Removes and returns the smallest index which is stored at the root of the heap
    //  If heap is empty, a message is printed and -1 is returned.
    //  Root is being saved and replaced by the last element.
    //  Size will be decreased and to restore the minheap property downheap() is called.

    int pop(int weightArr[]) {
        if (size == 0) {
            cout << "Heap is empty. Cannot pop element." << endl;
            return -1;
        }

        int p = data[0];
        size--;

        if (size > 0) {
            data[0] = data[size];
            downheap(0, weightArr);
        }
        return p;
    }


    // Restores the minheap property after inserting a new element
    // Starting from given position, function compares itself with its parent
    // If node weight is smaller or if weight is same but index is smaller position is swapped
    // Process continues until it reaches root node or if parent is smaller

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

    //  Restore the minheap property after removing the root and replacing it with the last element.
    //  Starting at the root, we choose the smaller child by the weight, if tie we use smaller index.
    //  We keep swapping with the child until the child nodes are no longer small or the node has no children.

    void downheap(int pos, int weightArr[]) {
        while (true) {
            int left = 2 * pos + 1;
            int right = 2 * pos + 2;

            if (left >= size) {
                break;
            }

            int smallest = left;

            if (right < size) {
                int l = data[left];
                int r = data[right];
                bool smallerByWeight = (weightArr[r] < weightArr[l]);
                bool smallerByIdx = (weightArr[r] == weightArr[l] && r < l);
                if (smallerByWeight || smallerByIdx) {
                    smallest = right;
                }
            }

            int c = data[smallest];
            int p = data[pos];
            bool cSmallerByWeight = (weightArr[c] < weightArr[p]);
            bool pSmallerbyIdx = (weightArr[c] == weightArr[p] && c < p);
            if (cSmallerByWeight || pSmallerbyIdx) {
                int temp = data[pos];
                data[pos] = data[smallest];
                data[smallest] = temp;
                pos = smallest;
            }
            else {
                break;
            }
        }
    }
};

#endif