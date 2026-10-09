#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;

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
    heapSort(a);
    auto stop = high_resolution_clock::now();

    duration<double, milli> ms = stop - start;
    cout << "HeapSort tren " << filename << " (" << n << " phan tu): " << ms.count() << " ms\n";
    cout << "Kiem tra tinh dung dan: " << (is_sorted(a.begin(), a.end()) ? "DUNG" : "SAI") << "\n";
    return 0;
}
