#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;

// QuickSort su dung phan hoach Hoare voi phan tu chot (pivot) o giua
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
    quickSort(a, 0, n - 1);
    auto stop = high_resolution_clock::now();

    duration<double, milli> ms = stop - start;
    cout << "QuickSort tren " << filename << " (" << n << " phan tu): " << ms.count() << " ms\n";
    cout << "Kiem tra tinh dung dan: " << (is_sorted(a.begin(), a.end()) ? "DUNG" : "SAI") << "\n";
    return 0;
}
