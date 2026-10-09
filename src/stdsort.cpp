#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;

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
    sort(a.begin(), a.end());
    auto stop = high_resolution_clock::now();

    duration<double, milli> ms = stop - start;
    cout << "std::sort tren " << filename << " (" << n << " phan tu): " << ms.count() << " ms\n";
    cout << "Kiem tra tinh dung dan: " << (is_sorted(a.begin(), a.end()) ? "DUNG" : "SAI") << "\n";
    return 0;
}
