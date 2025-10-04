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
 * Fungsi ini menerima referensi ke pointer head dan data yang akan disisipkan.
 * Pointer head bisa berubah jika data baru menjadi elemen terkecil.
 */

void sortedInsert(Node *&head_ref, int data)
{
    Node *newNode = new Node{data, nullptr, nullptr};

    // Kasus 1: List masih kosong
    if (head_ref == nullptr)
    {
        newNode->next = newNode;
        newNode->prev = newNode;
        head_ref = newNode;
        return;
    }
    // Kasus 2: Data baru lebih kecil dari head (akan menjadi head baru)
    if (data < head_ref->data)
    {
        // Node terakhir adalah node sebelum head
        Node *last = head_ref->prev;

        // Sambungkan newNode dengan head lama dan node terakhir
        newNode->next = head_ref;
        head_ref->prev = newNode;
        newNode->prev = last;
        last->next = newNode;

        // Update head_ref untuk menunjuk ke newNode
        head_ref = newNode;
        return;
    }

    // Kasus 3: Cari posisi yang tepat (di tengah atau di akhir)
    Node *current = head_ref;

    // Loop untuk mencari node yang datanya lebih kecil dari data baru.
    // Loop berhenti ketika 'current' adalah node sebelum posisi sisip yang benar.
    while (current->next != head_ref && current->next->data < data)
    {
        current = current->next;
    }

    // Sisipkan newNode di antara 'current' dan 'current->next'
    newNode->next = current->next;
    current->next->prev = newNode;
    current->next = newNode;
    newNode->prev = current;
}

// Fungsi untuk mencetak list
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

int main()
{
    Node *head = nullptr;

    // Test sorted insert
    cout << "Menyisipkan 30..." << endl;
    sortedInsert(head, 30);
    printList(head); // Output: 30

    cout << "Menyisipkan 10..." << endl;
    sortedInsert(head, 10);
    printList(head); // Output: 10 30

    cout << "Menyisipkan 40..." << endl;
    sortedInsert(head, 40);
    printList(head); // Output: 10 30 40

    cout << "Menyisipkan 20..." << endl;
    sortedInsert(head, 20);
    printList(head); // Output: 10 20 30 40

    cout << "\nHasil akhir Circular Doubly Linked List (sorted): ";
    printList(head);

    return 0;
}