#include <iostream>
#include <string>
using namespace std;

struct Pasien {
    string nama;
    string jenis;
    int umur;
    int tingkatDarurat;
    int urutan;
};

void ubahKapital(string &s) {
    for (int i = 0; i < (int)s.length(); i++) {
        if (s[i] >= 'a' && s[i] <= 'z') s[i] = s[i] - 32;
    }
}

int main() {
    int n;
    cout << "Masukkan jumlah pasien: ";
    if (!(cin >> n)) return 0;
    cin.ignore(); 

    Pasien *data = new Pasien[n];

    for (int i = 0; i < n; i++) {
        cout << "\nPasien " << i + 1 << ":\n";
        cout << "Nama hewan: ";
        getline(cin, data[i].nama);
        cout << "Jenis hewan: ";
        getline(cin, data[i].jenis);
        cout << "Umur: ";
        cin >> data[i].umur;
        cout << "Tingkat darurat (1-5): ";
        cin >> data[i].tingkatDarurat;
        data[i].urutan = i;
        cin.ignore(); 
    }

    for (int i = 0; i < n - 1; i++) {
        int idxMax = i;
        for (int j = i + 1; j < n; j++) {
            if (data[j].tingkatDarurat > data[idxMax].tingkatDarurat) {
                idxMax = j;
            } else if (data[j].tingkatDarurat == data[idxMax].tingkatDarurat) {
                if (data[j].urutan < data[idxMax].urutan) idxMax = j;
            }
        }
        if (idxMax != i) {
            Pasien tmp = data[i];
            data[i] = data[idxMax];
            data[idxMax] = tmp;
        }
    }

    for (int i = 0; i < n; i++) {
        ubahKapital(data[i].nama);
        cout << i + 1 << ". " << data[i].nama << " (" << data[i].umur << " tahun) - Darurat " << data[i].tingkatDarurat << endl;
    }

    delete[] data;
    return 0;
} 