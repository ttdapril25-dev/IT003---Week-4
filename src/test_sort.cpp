#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;

// 1. QUICKSORT (Hoare partition, middle pivot)
void quickSort(vector<double>& a, int left, int right) {
    double pivot = a[left + (right - left) / 2];
    int i = left, j = right;
    while (i <= j) {
        while (a[i] < pivot) i++;
        while (a[j] > pivot) j--;
        if (i <= j) {
            std::swap(a[i], a[j]);
            i++;
            j--;
        }
    }
    if (left < j) quickSort(a, left, j);
    if (i < right) quickSort(a, i, right);
}

// 2. HEAPSORT
void heapify(vector<double>& a, int n, int i) {
    int largest = i;
    while (true) {
        int left = 2 * largest + 1;
        int right = 2 * largest + 2;
        int next_largest = largest;

        if (left < n && a[left] > a[next_largest])
            next_largest = left;
        if (right < n && a[right] > a[next_largest])
            next_largest = right;

        if (next_largest != largest) {
            std::swap(a[largest], a[next_largest]);
            largest = next_largest;
        } else {
            break;
        }
    }
}

void heapSort(vector<double>& a) {
    int n = a.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);
    for (int i = n - 1; i > 0; i--) {
        std::swap(a[0], a[i]);
        heapify(a, i, 0);
    }
}

// 3. MERGESORT
void merge(vector<double>& a, int left, int mid, int right, vector<double>& temp) {
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) {
        if (a[i] <= a[j]) {
            temp[k++] = a[i++];
        } else {
            temp[k++] = a[j++];
        }
    }
    while (i <= mid) temp[k++] = a[i++];
    while (j <= right) temp[k++] = a[j++];
    for (i = left; i <= right; ++i) a[i] = temp[i];
}

void mergeSortInternal(vector<double>& a, int left, int right, vector<double>& temp) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSortInternal(a, left, mid, temp);
    mergeSortInternal(a, mid + 1, right, temp);
    merge(a, left, mid, right, temp);
}

void mergeSort(vector<double>& a) {
    vector<double> temp(a.size());
    mergeSortInternal(a, 0, (int)a.size() - 1, temp);
}

// 4. STD::SORT
void stdSort(vector<double>& a) {
    sort(a.begin(), a.end());
}

int main() {
    cout << "Testing algorithms on 100k numbers..." << endl;
    vector<double> test(100000);
    for (int i = 0; i < 100000; i++) test[i] = 100000 - i;

    auto a1 = test, a2 = test, a3 = test, a4 = test;
    quickSort(a1, 0, a1.size() - 1);
    heapSort(a2);
    mergeSort(a3);
    stdSort(a4);

    cout << "Is QS sorted: " << is_sorted(a1.begin(), a1.end()) << endl;
    cout << "Is HS sorted: " << is_sorted(a2.begin(), a2.end()) << endl;
    cout << "Is MS sorted: " << is_sorted(a3.begin(), a3.end()) << endl;
    cout << "Is SS sorted: " << is_sorted(a4.begin(), a4.end()) << endl;
    return 0;
}
