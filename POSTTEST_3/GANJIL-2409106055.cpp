
#include <iostream>
#include <string>
#include <limits>
using namespace std;

struct Node
{
    string nama;
    int jumlah;
    Node *next;
    Node *prev;
};

int ubahNilai(int *nilai, int perubahan)
{
    *nilai = *nilai + perubahan;
    return *nilai;
}

bool isEmpty(Node *header)
{
    return header == NULL;
}

void display(Node *header)
{
    if (header == NULL)
    {
        cout << ">> LinkedList kosong <<" << endl;
        return;
    }

    cout << "Isi Inventory (Urutan Normal): ";
    Node *temp = header;
    while (temp != NULL)
    {
        cout << "[" << temp->nama << ":" << temp->jumlah << "] <=> ";
        temp = temp->next;
    }
    cout << "NULL" << endl;

    cout << "\n=================================================" << endl;
    cout << "|                 INVENTORY ANDA                |" << endl;
    cout << "=================================================" << endl;
    cout << "| No | Nama Item                     | Jumlah   |" << endl;
    cout << "=================================================" << endl;

    Node *saat = header;
    int nomor = 1;
    while (saat != NULL)
    {
        cout << "| " << nomor << "  | " << saat->nama;
        for (int i = saat->nama.length(); i < 25; i++)
        {
            cout << " ";
        }
        cout << " | " << saat->jumlah;
        for (int i = to_string(saat->jumlah).length(); i < 8; i++)
        {
            cout << " ";
        }
        cout << " |" << endl;
        saat = saat->next;
        nomor++;
    }
    cout << "+===============================================+" << endl;
}

void transversalMundur(Node *header)
{
    if (isEmpty(header))
    {
        cout << ">> LinkedList kosong <<" << endl;
        return;
    }

    Node *tail = header;
    while (tail->next != NULL)
    {
        tail = tail->next;
    }

    cout << "\n=================================================" << endl;
    cout << "|         INVENTORY ANDA (DARI BELAKANG)        |" << endl;
    cout << "=================================================" << endl;
    cout << "| No | Nama Item                     | Jumlah   |" << endl;
    cout << "=================================================" << endl;

    Node *saat = tail;
    int nomor = 1;
    while (saat != NULL)
    {
        cout << "| " << nomor << "  | " << saat->nama;
        for (int i = saat->nama.length(); i < 25; i++)
        {
            cout << " ";
        }
        cout << " | " << saat->jumlah;
        for (int i = to_string(saat->jumlah).length(); i < 8; i++)
        {
            cout << " ";
        }
        cout << " |" << endl;
        saat = saat->prev;
        nomor++;
    }
    cout << "+===============================================+" << endl;
}

void addFirst(Node *&header, int dataBaru)
{
    string namaItem;
    cout << "Nama item: ";
    cin.ignore();
    getline(cin, namaItem);

    Node *nodeBaru = new Node;
    nodeBaru->nama = namaItem;
    nodeBaru->jumlah = dataBaru;
    nodeBaru->next = header;
    nodeBaru->prev = NULL;

    if (header != NULL)
    {
        header->prev = nodeBaru;
    }
    header = nodeBaru;

    cout << "Item '" << namaItem << "' ditambahkan dengan jumlah " << dataBaru << "!" << endl;
}

void addMiddle(Node *&header, int dataBaru, int posisi)
{
    if (posisi <= 1)
    {
        addFirst(header, dataBaru);
        return;
    }

    string namaItem;
    cout << "Nama item: ";
    cin.ignore();
    getline(cin, namaItem);

    Node *temp = header;
    int hitung = 1;
    while (temp != NULL && hitung < posisi - 1)
    {
        temp = temp->next;
        hitung++;
    }

    if (temp == NULL)
    {
        cout << "Posisi melebihi panjang list!" << endl;
        return;
    }

    Node *nodeBaru = new Node;
    nodeBaru->nama = namaItem;
    nodeBaru->jumlah = dataBaru;

    nodeBaru->next = temp->next;
    nodeBaru->prev = temp;

    if (temp->next != NULL)
    {
        temp->next->prev = nodeBaru;
    }
    temp->next = nodeBaru;

    cout << "Item '" << namaItem << "' disisipkan di posisi " << posisi << "!" << endl;
}

void deleteFirst(Node *&header)
{
    if (isEmpty(header))
    {
        cout << "Inventory kosong!" << endl;
        return;
    }

    Node *temp = header;
    cout << "Item '" << header->nama << "' dihapus!" << endl;
    header = header->next;
    if (header != NULL)
    {
        header->prev = NULL;
    }
    delete temp;
}

void deleteLast(Node *&header)
{
    if (isEmpty(header))
    {
        cout << "Inventory kosong!" << endl;
        return;
    }

    if (header->next == NULL)
    {
        deleteFirst(header);
    }
    else
    {
        Node *saat = header;
        while (saat->next != NULL)
        {
            saat = saat->next;
        }
        cout << "Item '" << saat->nama << "' dihapus!" << endl;
        saat->prev->next = NULL;
        delete saat;
    }
}

Node *cariItem(Node *header, string nama)
{
    Node *saat = header;
    while (saat != NULL)
    {
        if (saat->nama == nama)
        {
            return saat;
        }
        saat = saat->next;
    }
    return NULL;
}

void hapusItemDariList(Node *&header, string nama)
{
    if (isEmpty(header))
        return;

    Node *itemToDelete = cariItem(header, nama);
    if (itemToDelete == NULL)
        return;

    if (itemToDelete == header)
    {
        deleteFirst(header);
    }
    else
    {
        itemToDelete->prev->next = itemToDelete->next;
        if (itemToDelete->next != NULL)
        {
            itemToDelete->next->prev = itemToDelete->prev;
        }
        delete itemToDelete;
    }
}

void gunakanItem(Node *&header)
{
    if (isEmpty(header))
    {
        cout << "Inventory kosong! Tidak ada item untuk digunakan." << endl;
        return;
    }

    string namaItem;
    cout << "Masukkan nama item yang ingin digunakan: ";
    cin.ignore();
    getline(cin, namaItem);

    Node *itemToUse = cariItem(header, namaItem);
    if (itemToUse == NULL)
    {
        cout << "Item '" << namaItem << "' tidak ditemukan dalam inventory!" << endl;
        return;
    }

    itemToUse->jumlah--;

    cout << "Item '" << namaItem << "' digunakan! Jumlah tersisa: " << itemToUse->jumlah << endl;

    if (itemToUse->jumlah == 0)
    {
        cout << "Item '" << namaItem << "' habis! Menghapus dari inventory..." << endl;
        hapusItemDariList(header, namaItem);
    }
}

void tampilkanDetail(Node *header)
{
    if (isEmpty(header))
    {
        cout << "Inventory kosong! Tidak ada item untuk dicari." << endl;
        return;
    }

    string namaItem;
    cout << "Masukkan nama item yang ingin dicari detailnya: ";
    cin.ignore();
    getline(cin, namaItem);

    Node *itemDitemukan = cariItem(header, namaItem);

    if (itemDitemukan != NULL)
    {
        cout << "\n================ DETAIL ITEM ================" << endl;
        cout << " Nama   : " << itemDitemukan->nama << endl;
        cout << " Jumlah : " << itemDitemukan->jumlah << endl;
        cout << " Item Sebelumnya : " << (itemDitemukan->prev ? itemDitemukan->prev->nama : "Tidak ada (Ini item pertama)") << endl;
        cout << " Item Selanjutnya: " << (itemDitemukan->next ? itemDitemukan->next->nama : "Tidak ada (Ini item terakhir)") << endl;
        cout << "===========================================" << endl;
    }
    else
    {
        cout << "Item '" << namaItem << "' tidak ditemukan dalam inventory!" << endl;
    }
}

int main()
{
    Node *header = NULL;
    int pilihan;

    do
    {
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

        if (cin.fail())
        {
            cout << "Input tidak valid! Harap masukkan angka." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (pilihan)
        {
        case 1:
            cout << "\n"
                 << string(50, '=') << endl;
            cout << "                    TAMBAH ITEM BARU" << endl;
            cout << string(50, '=') << endl;
            addFirst(header, 55);
            break;
        case 2:
            cout << "\n"
                 << string(50, '=') << endl;
            cout << "                      SISIPKAN ITEM" << endl;
            cout << string(50, '=') << endl;
            addMiddle(header, 55, 6);
            break;
        case 3:
            cout << "\n"
                 << string(50, '=') << endl;
            cout << "                   HAPUS ITEM TERAKHIR" << endl;
            cout << string(50, '=') << endl;
            deleteLast(header);
            break;
        case 4:
            cout << "\n"
                 << string(50, '=') << endl;
            cout << "                      GUNAKAN ITEM" << endl;
            cout << string(50, '=') << endl;
            gunakanItem(header);
            break;
        case 5:
            display(header);
            break;
        case 6:
            transversalMundur(header);
            break;
        case 7:
            tampilkanDetail(header);
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