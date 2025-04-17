#include <cstring>
#include <iostream>

// Template function for swapping two elements
template <typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

// Template function for partitioning the array
template <typename T>
int partition(T arr[], int low, int high) {
    T pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Template function for quicksort
template <typename T>
void quickSort(T arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Specialization of partition for char*
template <>
int partition<char*>(char* arr[], int low, int high) {
    char* pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (std::strcmp(arr[j], pivot) <= 0) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Specialization of quickSort for char*
template <>
void quickSort<char*>(char* arr[], int low, int high) {
    if (low < high) {
        int pi = partition<char*>(arr, low, high);
        quickSort<char*>(arr, low, pi - 1);
        quickSort<char*>(arr, pi + 1, high);
    }
}

int main() {
    // Example with integers
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    std::cout << "Original integer array: ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    quickSort(arr, 0, n - 1);

    std::cout << "Sorted integer array: ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    // Example with strings
    char* strArr[] = {"apple", "zebra", "banana", "cat"};
    int m = sizeof(strArr) / sizeof(strArr[0]);
    std::cout << "Original string array: ";
    for (int i = 0; i < m; i++) {
        std::cout << strArr[i] << " ";
    }
    std::cout << std::endl;

    quickSort(strArr, 0, m - 1);

    std::cout << "Sorted string array: ";
    for (int i = 0; i < m; i++) {
        std::cout << strArr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
