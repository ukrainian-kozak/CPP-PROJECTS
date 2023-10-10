#include <iostream>
#include <vector>

void swap (int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void heapify(std::vector<int>& hT, int index)
{
    int size = hT.size();
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    if (left < size && hT[left] > hT[largest])
            largest = left;
    if (right < size && hT[right] > hT[largest])
            largest = right;
    
    if (largest != index) {
        swap(hT[index], hT[largest]);
        heapify(hT, largest);
    }
}

void insert(std::vector<int>& hT, int val)
{
    int size = hT.size();
    if (size == 0) {
        hT.push_back(val);
    } else {
        hT.push_back(val);
        for (int i = size / 2 - 1; i >= 0; --i) {
            heapify(hT, i);
        }
    }
}

void deleteNode(std::vector<int>& hT, int val)
{
    int size = hT.size();
    int i;
    for (i = 0; i < size; ++i) {
        if (hT[i] == val)
            break;
    }

    swap(hT[i], hT[size-1]);
    hT.pop_back();

    for (int i = size / 2 - 1; i >= 0; --i) {
        heapify(hT, i);
    }
}

void printVector(std::vector<int>& hT)
{
    for (int i = 0; i < hT.size(); ++i) {
        std::cout << hT[i] << ' ';
    }
    std::cout << '\n';
}

int main() 
{
    std::vector<int> heapTree;

    insert(heapTree, 3);
    insert(heapTree, 4);
    insert(heapTree, 9);
    insert(heapTree, 5);
    insert(heapTree, 2);

    std::cout << "Max-Heap array: ";
    printVector(heapTree);

    deleteNode(heapTree, 4);

    std::cout << "After deleting an element: ";

    printVector(heapTree);
}
