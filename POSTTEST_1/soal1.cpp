#include <iostream>
using namespace std;

void tampilkanArray(const int* arr, int ukuran) {
    for (int i = 0; i < ukuran; ++i) {
        cout << *(arr + i) << " ";
    }
    cout << endl;
}

int main() {
    const int ukuran = 7;
    int data[ukuran];

    for (int i = 0; i < ukuran; ++i) {
        data[i] = (i + 1) * 3;
    }

    cout << "Array: ";
    tampilkanArray(data, ukuran);

    return 0;
}