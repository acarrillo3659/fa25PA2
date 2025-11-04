//
//  Created by Manju Muralidharan on 10/19/25.
//
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;

//  Global arrays for node information
const int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

//  Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

int main() {
    int freq[26] = {0};

    //  Step 1: Read file and count letter frequencies
    buildFrequencyTable(freq, "input.txt");

    //  Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    //  Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

    //  Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    //  Step 5: Encode the message and print output
    encodeMessage("input.txt", codes);

    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

//  Step 1: Read file and count frequencies
void buildFrequencyTable(int freq[], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;
    while (file.get(ch)) {
        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }
    file.close();

    cout << "Frequency table built successfully.\n";
}

//  Step 2: Create leaf nodes for each character
int createLeafNodes(int freq[]) {
    int nextFree = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            charArr[nextFree] = 'a' + i;
            weightArr[nextFree] = freq[i];
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;
}

//  Step 3: Build the encoding tree using heap operations
//  This function builds the encoding tree by combining the two smallest weight nodes until only one root remains
//  Leaf nodes are push first into the min heap.
//  Each time it removes the two smallest nodes from the heap, then creates a parent node above them who has the weight of those two
//  It then links the parent to the two child nodes created as left and right, which is then pushed into the index as new parent into the heap
//  This repeats until there is only one node remains in the heap, which becomes the root of the tree
int buildEncodingTree(int nextFree) {
    //  1. Create a MinHeap object.
    MinHeap heap;

    //  2. Push all leaf node indices into the heap.
    for (int i = 0; i < nextFree; ++i) {
        heap.push(i, weightArr);
    }
    if (heap.size == 0) {
        return -1;
    }

    //  3. While the heap size is greater than 1:
    //    - Pop two smallest nodes
    //    - Create a new parent node with combined weight
    //    - Set left/right pointers
    //    - Push new parent index back into the heap
    //  Move to the next free slot for the next parent node
    int curr = nextFree;
    while (heap.size > 1) {
        int left = heap.pop(weightArr);
        int right = heap.pop(weightArr);

        if (curr >= MAX_NODES) {
            cerr << "Error: too many nodes\n";
            return -1;
        }
        weightArr[curr] = weightArr[left] + weightArr[right];
        leftArr[curr] = left;
        rightArr[curr] = right;

        heap.push(curr, weightArr);
        curr++;
    }


    //  4. Return the index of the last remaining node (root)
    int root = heap.pop(weightArr);
    return root;
}

//  Step 4: Use an STL stack to generate codes
//  This function does a depth first search.
//  stack<int> holds the node it wants to visit and
//  Each time we pop the path is extended from the node to its children
//  When we reach a leaf mode the final code path is stored in codes[]
void generateCodes(int root, string codes[]) {
    if (root == -1) return;

    //  Local array for each node’s path string (potential debug point later).
    string path[MAX_NODES];

    //  Stack for node indices to simulate DFS traversal.
    stack<int> stk;
    stk.push(root);
    path[root] = "";

    //  Process nodes until all have been visited.
    while (!stk.empty()) {
        int node = stk.top();
        stk.pop();

        bool isLeaf = (leftArr[node] == -1 && rightArr[node] == -1);

        //  Record code when a leaf node is reached.
        if (isLeaf) {
            if (charArr[node] >= 'a' && charArr[node] <= 'z') {
                if (path[node].empty()) {
                    codes[charArr[node] - 'a'] = "0";
                } else {
                    codes[charArr[node] - 'a'] = path[node];
                }

                //  Trim leading zeros until only one zero or a 1 is reached
                string &code = codes[charArr[node] - 'a'];
                int pos = code.find('1');
                if (pos != string::npos) {
                    code = code.substr(pos);
                } else if (!code.empty()) {
                    code = "0";
                }
            }
        } else {
            //  Push right child and extend the path with '1'.
            if (rightArr[node] != -1) {
                stk.push(rightArr[node]);
                path[rightArr[node]] = path[node] + "1";
            }

            //  Push left child and extend the path with '0'.
            if (leftArr[node] != -1) {
                stk.push(leftArr[node]);
                path[leftArr[node]] = path[node] + "0";
            }
        }
    }
}

//  Step 5: Print table and encoded message
void encodeMessage(const string& filename, string codes[]) {
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";
    }

    cout << "\nEncoded message:\n";

    ifstream file(filename);
    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
    }
    cout << "\n";
    file.close();
}