#include <iostream>
#include <string>
using namespace std;

struct Node {
    string judul;
    int tahun;
    int rating;
    Node* next;
};

Node* head = NULL;

void tambahBelakang(string j, int t, int r) {
    Node* newnode = new Node;
    newnode->judul = j;
    newnode->tahun = t;
    newnode->rating = r;
    newnode->next = NULL;

    if (head == NULL) {
        head = newnode;
    } else {
        Node* p = head;
        while (p->next != NULL) p = p->next;
        p->next = newnode;
    }
}

void hapusBerdasarkanJudul(string target) {
    if (head == NULL) return;
    Node* p = head;
    Node* prev = NULL;

    if (head->judul == target) {
        head = head->next;
        delete p;
        return;
    }

    while (p != NULL && p->judul != target) {
        prev = p;
        p = p->next;
    }

    if (p == NULL) {
        cout << "Film tidak ditemukan.\n";
    } else {
        prev->next = p->next;
        delete p;
    }
}

void tampilkanDanHitung() {
    Node* p = head;
    int count = 0;
    while (p != NULL) {
        cout << p->judul << " (" << p->tahun << ") - " << p->rating << endl;
        count++;
        p = p->next;
    }
    cout << "\nTotal film tersisa: " << count << endl;
}

int main() {
    int n;
    cout << "Masukkan jumlah film awal: ";
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; i++) {
        string judul;
        int tahun;
        int rating;
        cout << "\nFilm " << i + 1 << ":\n";
        cout << "Judul: ";
        getline(cin, judul);
        cout << "Tahun: ";
        cin >> tahun;
        cout << "Rating: ";
        cin >> rating;
        cin.ignore();
        tambahBelakang(judul, tahun, rating);
    }

    char pilih;
    cout << "\nApakah ingin menghapus film? (y/n): ";
    cin >> pilih;
    cin.ignore();
    if (pilih == 'y' || pilih == 'Y') {
        string target;
        cout << "Masukkan judul film yang sudah ditonton: ";
        getline(cin, target);
        hapusBerdasarkanJudul(target);
    }

    Node* p = head;
    while (p != NULL) {
        cout << p->judul << " (" << p->tahun << ") - " << p->rating << endl;
        p = p->next;
    }

    int total = 0;
    p = head;
    while (p != NULL) { total++; p = p->next; }
    cout << "\nTotal film tersisa: " << total << endl;

    while (head != NULL) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }

    return 0;
}
