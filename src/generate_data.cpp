#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <string>

using namespace std;

const int NUM_ELEMENTS = 1000000;
const int NUM_DATASETS = 10;

void generateData() {
    mt19937_64 rng(42); // fixed seed for reproducibility
    uniform_real_distribution<double> dist(-1000000.0, 1000000.0);

    for (int d = 1; d <= NUM_DATASETS; ++d) {
        vector<double> arr(NUM_ELEMENTS);
        for (int i = 0; i < NUM_ELEMENTS; ++i) {
            arr[i] = dist(rng);
        }

        if (d == 1) {
            sort(arr.begin(), arr.end());
            cout << "Dang tao data1.txt (Tang dan)..." << endl;
        } else if (d == 2) {
            sort(arr.begin(), arr.end(), greater<double>());
            cout << "Dang tao data2.txt (Giam dan)..." << endl;
        } else {
            cout << "Dang tao data" << d << ".txt (Ngau nhien)..." << endl;
        }

        string filename = "project/data/data" + to_string(d) + ".txt";
        ofstream fout(filename);
        if (!fout.is_open()) {
            cerr << "Khong the mo file: " << filename << endl;
            return;
        }

        fout << fixed << setprecision(4);
        fout << NUM_ELEMENTS << "\n";
        for (int i = 0; i < NUM_ELEMENTS; ++i) {
            fout << arr[i] << (i == NUM_ELEMENTS - 1 ? "" : " ");
        }
        fout.close();
        cout << "Da ghi: " << filename << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << "=== SINH BO DU LIEU THU NGHIEM (1.000.000 SO THUC / DAY) ===" << endl;
    generateData();
    cout << "Hoan tat tao 10 file tu data1.txt den data10.txt!" << endl;
    return 0;
}
