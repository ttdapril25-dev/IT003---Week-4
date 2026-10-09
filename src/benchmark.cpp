#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;
using namespace std::chrono;

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

void merge(vector<double>& a, int left, int mid, int right, vector<double>& temp) {
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) {
        if (a[i] <= a[j]) temp[k++] = a[i++];
        else temp[k++] = a[j++];
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

bool loadDataset(int d, vector<double>& arr) {
    string filename = "project/data/data" + to_string(d) + ".txt";
    ifstream fin(filename);
    if (!fin.is_open()) return false;
    int n;
    if (!(fin >> n)) return false;
    arr.resize(n);
    for (int i = 0; i < n; ++i) fin >> arr[i];
    fin.close();
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== THUC NGHIEM SO SANH THUAT TOAN SAP XEP (1.000.000 PHAN TU) ===\n";
    vector<vector<double>> results(10, vector<double>(4, 0.0));

    for (int d = 1; d <= 10; ++d) {
        vector<double> original;
        if (!loadDataset(d, original)) {
            cerr << "Loi mo file data" << d << ".txt\n";
            return 1;
        }

        cout << "Dang chay tren data" << d << ".txt... " << flush;

        // QuickSort
        {
            auto arr = original;
            auto start = high_resolution_clock::now();
            quickSort(arr, 0, (int)arr.size() - 1);
            auto stop = high_resolution_clock::now();
            duration<double, milli> ms = stop - start;
            results[d-1][0] = ms.count();
        }

        // HeapSort
        {
            auto arr = original;
            auto start = high_resolution_clock::now();
            heapSort(arr);
            auto stop = high_resolution_clock::now();
            duration<double, milli> ms = stop - start;
            results[d-1][1] = ms.count();
        }

        // MergeSort
        {
            auto arr = original;
            auto start = high_resolution_clock::now();
            mergeSort(arr);
            auto stop = high_resolution_clock::now();
            duration<double, milli> ms = stop - start;
            results[d-1][2] = ms.count();
        }

        // std::sort
        {
            auto arr = original;
            auto start = high_resolution_clock::now();
            sort(arr.begin(), arr.end());
            auto stop = high_resolution_clock::now();
            duration<double, milli> ms = stop - start;
            results[d-1][3] = ms.count();
        }

        cout << "Xong! (QS: " << fixed << setprecision(2) << results[d-1][0] << "ms, "
             << "HS: " << results[d-1][1] << "ms, "
             << "MS: " << results[d-1][2] << "ms, "
             << "std::sort: " << results[d-1][3] << "ms)\n";
    }

    // Tinh trung binh
    vector<double> avg(4, 0.0);
    for (int d = 0; d < 10; ++d)
        for (int a = 0; a < 4; ++a)
            avg[a] += results[d][a];
    for (int a = 0; a < 4; ++a) avg[a] /= 10.0;

    ofstream fout("project/benchmark_results.csv");
    fout << "Dataset,QuickSort,HeapSort,MergeSort,std_sort\n";
    for (int d = 0; d < 10; ++d) {
        fout << (d + 1) << "," << fixed << setprecision(2)
             << results[d][0] << "," << results[d][1] << ","
             << results[d][2] << "," << results[d][3] << "\n";
    }
    fout << "Trung binh," << avg[0] << "," << avg[1] << "," << avg[2] << "," << avg[3] << "\n";
    fout.close();

    cout << "\nDa xuat ket qua ra file project/benchmark_results.csv thanh cong!\n";
    return 0;
}
