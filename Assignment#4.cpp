#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

const int SWITCH_THRESHOLD = 16;
const int MAX_DEPTH_THRESHOLD = 20;

void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> leftArr(n1);
    std::vector<int> rightArr(n2);

    for (int i = 0; i < n1; ++i)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        rightArr[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j])
            arr[k++] = leftArr[i++];
        else
            arr[k++] = rightArr[j++];
    }

    while (i < n1) arr[k++] = leftArr[i++];
    while (j < n2) arr[k++] = rightArr[j++];
}

void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left >= right) return;
    
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}


void hybridQuickSort(std::vector<int>& arr, int low, int high, int depth) {
    if (low < high) {
       
        if (depth > MAX_DEPTH_THRESHOLD) {
            mergeSort(arr, low, high);
            return;
        }

              if (high - low + 1 > SWITCH_THRESHOLD) {
            int pivotIndex = partition(arr, low, high);
            hybridQuickSort(arr, low, pivotIndex - 1, depth + 1);
            hybridQuickSort(arr, pivotIndex + 1, high, depth + 1);
        }
      
        else {
            mergeSort(arr, low, high);
        }
    }
}


void hybridSort(std::vector<int>& arr) {
    hybridQuickSort(arr, 0, arr.size() - 1, 0);
}

int main() {
    std::vector<int> arr = {34, 7, 23, 32, 5, 62, 32, 7, 45, 29, 1};
    std::cout << "Original Array: ";
    for (int num : arr) std::cout << num << " ";
    std::cout << "\n";

    hybridSort(arr);

    std::cout << "Sorted Array: ";
    for (int num : arr) std::cout << num << " ";
    std::cout << "\n";

    return 0;
}

