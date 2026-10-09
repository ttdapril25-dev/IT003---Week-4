#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;

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

int main(int argc, char* argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string filename = (argc > 1) ? argv[1] : "data/data1.txt";
    ifstream fin(filename);
    if (!fin.is_open()) {
        cerr << "Khong the mo file: " << filename << endl;
        return 1;
    }

    int n;
    if (!(fin >> n)) return 1;
    vector<double> a(n);
    for (int i = 0; i < n; ++i) fin >> a[i];
    fin.close();

    auto start = high_resolution_clock::now();
    mergeSort(a);
    auto stop = high_resolution_clock::now();

    duration<double, milli> ms = stop - start;
    cout << "MergeSort tren " << filename << " (" << n << " phan tu): " << ms.count() << " ms\n";
    cout << "Kiem tra tinh dung dan: " << (is_sorted(a.begin(), a.end()) ? "DUNG" : "SAI") << "\n";
    return 0;
}
