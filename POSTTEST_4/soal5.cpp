#include <iostream>
using namespace std;

// Struktur Node
struct Node
{
    int data;
    Node *next;
    Node *prev;
};

/*
 * Fungsi ini menerima referensi ke pointer head.
 * Pointer head akan di-update setelah penukaran.
 */

void exchangeHeadAndTail(Node *&head_ref)
{
    // Hanya berjalan jika ada 2 node atau lebih.
    // Jika list kosong atau hanya punya 1 node, tidak ada yang perlu ditukar.
    if (head_ref == nullptr || head_ref->next == head_ref)
    {
        return;
    }

    // Kasus khusus untuk list dengan tepat 2 node.
    // Cukup geser pointer head ke node berikutnya.
    if (head_ref->next == head_ref->prev)
    {
        head_ref = head_ref->next;
        return;
    }

    // --- Implementasi untuk 3 node atau lebih ---

    // 1. Simpan semua node penting
    Node *old_head = head_ref;
    Node *old_tail = head_ref->prev;
    Node *head_neighbor = old_head->next; // Tetangga setelah head
    Node *tail_neighbor = old_tail->prev; // Tetangga sebelum tail

    // 2. Sambungkan old_tail (head baru) dengan tetangga head lama
    old_tail->next = head_neighbor;
    head_neighbor->prev = old_tail;

    // 3. Sambungkan old_head (tail baru) dengan tetangga tail lama
    old_head->prev = tail_neighbor;
    tail_neighbor->next = old_head;

    // 4. Tutup lingkaran dengan menyambungkan head dan tail baru
    old_head->next = old_tail; // next dari tail baru adalah head baru
    old_tail->prev = old_head; // prev dari head baru adalah tail baru

    // 5. Update pointer head utama untuk menunjuk ke head yang baru (yaitu old_tail)
    head_ref = old_tail;
}

// --- Fungsi Bantuan (Tidak Perlu Diubah) ---

void printList(Node *head_ref)
{
    if (head_ref == nullptr)
    {
        cout << "List kosong" << endl;
        return;
    }

    Node *current = head_ref;
    do
    {
        cout << current->data << " ";
        current = current->next;
    } while (current != head_ref);
    cout << endl;
}

void insertEnd(Node *&head_ref, int data)
{
    Node *newNode = new Node{data, nullptr, nullptr};

    if (head_ref == nullptr)
    {
        newNode->next = newNode;
        newNode->prev = newNode;
        head_ref = newNode;
        return;
    }

    Node *tail = head_ref->prev;
    newNode->next = head_ref;
    newNode->prev = tail;
    head_ref->prev = newNode;
    tail->next = newNode;
}

int main()
{
    Node *head = nullptr;

    // Buat list: 1 <-> 2 <-> 3 <-> 4 <-> 5
    insertEnd(head, 1);
    insertEnd(head, 2);
    insertEnd(head, 3);
    insertEnd(head, 4);
    insertEnd(head, 5);

    cout << "List sebelum exchange: ";
    printList(head);

    exchangeHeadAndTail(head);

    cout << "List setelah exchange head dan tail: ";
    // Expected output: 5 2 3 4 1
    printList(head);

    // Test case dengan 2 node
    Node *head2 = nullptr;
    insertEnd(head2, 10);
    insertEnd(head2, 20);
    cout << "\nTest case 2 node, sebelum: ";
    printList(head2);
    exchangeHeadAndTail(head2);
    cout << "Test case 2 node, setelah: ";
    printList(head2); // Expected: 20 10

    return 0;
}