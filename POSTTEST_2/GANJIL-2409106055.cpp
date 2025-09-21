#include <iostream>
#include <string>
using namespace std;

struct Node {
    string nama;
    int jumlah;
    Node* next;
};

// Only keep the necessary function
int ubahNilai(int *nilai, int perubahan) {
    *nilai = *nilai + perubahan;
    return *nilai;
}

bool isEmpty(Node *header) {
    return header == NULL;
}

void transversal(Node *header) {
    if (header == NULL) {
        cout << "List kosong!" << endl;
        return;
    }
    
    Node *temp = header;
    int hitung = 1;
    
    while (temp != NULL) {
        cout << "Node ke-" << hitung << ": ";
        cout << "Item: " << temp->nama << " (Jumlah: " << temp->jumlah << ")" << endl;
        temp = temp->next;
        hitung++;
    }
}

void display(Node *header) {
    if (header == NULL) {
        cout << ">> LinkedList kosong <<" << endl;
        return;
    }
    
    Node *temp = header;
    cout << "Isi Inventory: ";
    while (temp != NULL) {
        cout << "[" << temp->nama << ":" << temp->jumlah << "] -> ";
        temp = temp->next;
    }
    cout << "NULL" << endl;
    
    cout << "\n=================================================" << endl;
    cout << "|                 INVENTORY ANDA                |" << endl;
    cout << "=================================================" << endl;
    cout << "| No | Nama Item                    | Jumlah   |" << endl;
    cout << "=================================================" << endl;
    
    Node* saat = header;
    int nomor = 1;
    while (saat != NULL) {
        cout << "| " << nomor << "  | " << saat->nama;
        for (int i = saat->nama.length(); i < 25; i++) {
            cout << " ";
        }
        cout << " | " << saat->jumlah;
        for (int i = to_string(saat->jumlah).length(); i < 8; i++) {
            cout << " ";
        }
        cout << " |" << endl;
        saat = saat->next;
        nomor++;
    }
    cout << "+===============================================+" << endl;
}

void addFirst(Node *&header, int dataBaru) {
    string namaItem;
    cout << "Nama item: ";
    cin.ignore();
    getline(cin, namaItem);
    
    Node* nodeBaru = new Node;
    nodeBaru->nama = namaItem;
    nodeBaru->jumlah = dataBaru;
    nodeBaru->next = header;
    header = nodeBaru;
    
    cout << "Item '" << namaItem << "' ditambahkan dengan jumlah " << dataBaru << "!" << endl;
}

void addMiddle(Node *&header, int dataBaru, int posisi) {
    if (posisi <= 1) {
        addFirst(header, dataBaru);
        return;
    }
    
    string namaItem;
    cout << "Nama item: ";
    cin.ignore();
    getline(cin, namaItem);
    
    Node *temp = header;
    int hitung = 1;
    
    while (temp != NULL && hitung < posisi - 1) {
        temp = temp->next;
        hitung++;
    }
    
    if (temp == NULL) {
        cout << "Posisi melebihi panjang list!" << endl;
        return;
    }
    
    Node* nodeBaru = new Node;
    nodeBaru->nama = namaItem;
    nodeBaru->jumlah = dataBaru;
    nodeBaru->next = temp->next;
    temp->next = nodeBaru;
    
    cout << "Item '" << namaItem << "' disisipkan di posisi " << posisi << "!" << endl;
}

void deleteFirst(Node *&header) {
    if (isEmpty(header)) {
        cout << "Inventory kosong!" << endl;
        return;
    }
    
    Node* temp = header;
    cout << "Item '" << header->nama << "' dihapus!" << endl;
    header = header->next;
    delete temp;
}

void deleteMiddle(Node *&header, int posisi) {
    if (isEmpty(header)) {
        cout << "Inventory kosong!" << endl;
        return;
    }
    
    if (posisi <= 1) {
        deleteFirst(header);
        return;
    }
    
    Node* saat = header;
    int posisiSaat = 1;
    
    while (saat->next != NULL && posisiSaat < posisi - 1) {
        saat = saat->next;
        posisiSaat++;
    }
    
    if (saat->next == NULL) {
        cout << "Posisi tidak ditemukan!" << endl;
        return;
    }
    
    Node* temp = saat->next;
    cout << "Item '" << temp->nama << "' dihapus!" << endl;
    saat->next = saat->next->next;
    delete temp;
}

void deleteLast(Node *&header) {
    if (isEmpty(header)) {
        cout << "Inventory kosong!" << endl;
        return;
    }
    
    if (header->next == NULL) {
        cout << "Item '" << header->nama << "' dihapus!" << endl;
        delete header;
        header = NULL;
    } else {
        Node* saat = header;
        while (saat->next->next != NULL) {
            saat = saat->next;
        }
        
        cout << "Item '" << saat->next->nama << "' dihapus!" << endl;
        delete saat->next;
        saat->next = NULL;
    }
}

void editData(Node *&header, int posisi, int dataBaru) {
    if (header == NULL) {
        cout << ">> LinkedList masih kosong <<" << endl;
        return;
    }
    
    Node *temp = header;
    int hitung = 1;
    
    while (temp != NULL && hitung < posisi) {
        temp = temp->next;
        hitung++;
    }
    
    if (temp == NULL) {
        cout << ">> Posisi tidak valid <<" << endl;
    } else {
        cout << "Data lama: " << temp->jumlah << endl;
        temp->jumlah = dataBaru;
        cout << "Data baru: " << temp->jumlah << endl;
    }
}

Node* cariItem(Node* header, string nama) {
    Node* saat = header;
    while (saat != NULL) {
        if (saat->nama == nama) {
            return saat;
        }
        saat = saat->next;
    }
    return NULL;
}

void hapusItemDariList(Node *&header, string nama) {
    if (isEmpty(header)) return;
    
    if (header->nama == nama) {
        Node* temp = header;
        header = header->next;
        delete temp;
        return;
    }
    
    Node* saat = header;
    while (saat->next != NULL) {
        if (saat->next->nama == nama) {
            Node* temp = saat->next;
            saat->next = saat->next->next;
            delete temp;
            return;
        }
        saat = saat->next;
    }
}

void gunakanItem(Node *&header) {
    if (isEmpty(header)) {
        cout << "Inventory kosong! Tidak ada item untuk digunakan." << endl;
        return;
    }
    
    string namaItem;
    cout << "Masukkan nama item yang ingin digunakan: ";
    cin.ignore();
    getline(cin, namaItem);
    
    Node* itemToUse = cariItem(header, namaItem);
    if (itemToUse == NULL) {
        cout << "Item '" << namaItem << "' tidak ditemukan dalam inventory!" << endl;
        return;
    }
    
    ubahNilai(&itemToUse->jumlah, -1);
    
    cout << "Item '" << namaItem << "' digunakan! Jumlah tersisa: " << itemToUse->jumlah << endl;
    
    if (itemToUse->jumlah == 0) {
        cout << "Item '" << namaItem << "' habis! Menghapus dari inventory..." << endl;
        hapusItemDariList(header, namaItem);
    }
}

int main() {
    Node* header = NULL;
    int pilihan;
    
    do {
        cout << "\n=================================================" << endl;
        cout << "|         GAME INVENTORY MANAGEMENT             |" << endl;
        cout << "|         Nama: Devon Falen Pasae               |" << endl;
        cout << "|         NIM: 2409106055                       |" << endl;
        cout << "=================================================" << endl;
        cout << "| 1. Tambah Item Baru                           |" << endl;
        cout << "| 2. Sisipkan Item                              |" << endl;
        cout << "| 3. Hapus Item Terakhir                        |" << endl;
        cout << "| 4. Gunakan Item                               |" << endl;
        cout << "| 5. Tampilkan Inventory                        |" << endl;
        cout << "| 0. Keluar                                     |" << endl;
        cout << "=================================================" << endl;
        cout << "Pilih: ";
        cin >> pilihan;
        
        switch (pilihan) {
            case 1:
                cout << "\n" << string(50, '=') << endl;
                cout << "                    TAMBAH ITEM BARU" << endl;
                cout << string(50, '=') << endl;
                addFirst(header, 55); // 55 = dua digit terakhir NIM
                break;
            case 2:
                cout << "\n" << string(50, '=') << endl;
                cout << "                    SISIPKAN ITEM" << endl;
                cout << string(50, '=') << endl;
                addMiddle(header, 55, 6); // 6 = digit terakhir NIM (5) + 1
                break;
            case 3:
                cout << "\n" << string(50, '=') << endl;
                cout << "                  HAPUS ITEM TERAKHIR" << endl;
                cout << string(50, '=') << endl;
                deleteLast(header);
                break;
            case 4:
                cout << "\n" << string(50, '=') << endl;
                cout << "                      GUNAKAN ITEM" << endl;
                cout << string(50, '=') << endl;
                gunakanItem(header);
                break;
            case 5:
                display(header);
                break;
            case 0:
                cout << "Terima kasih!" << endl;
                break;
            default:
                cout << "Pilihan tidak valid!" << endl;
        }
        
    } while (pilihan != 0);
    
    return 0;
}