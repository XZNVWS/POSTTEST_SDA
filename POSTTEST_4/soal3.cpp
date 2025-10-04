#include <iostream>
#include <string>

using namespace std;

// Struktur Node
struct Node
{
    string document;
    Node *next;
};

// Fungsi untuk menambahkan dokumen ke akhir antrian (queue)
void enqueue(Node *&front, Node *&rear, string document)
{
    Node *newNode = new Node{document, nullptr};

    // 1. Jika queue kosong, front dan rear menunjuk ke node baru
    if (rear == nullptr)
    {
        front = newNode;
        rear = newNode;
        return;
    }

    // 2. Jika tidak kosong, sambungkan node terakhir ke node baru, lalu update rear
    rear->next = newNode;
    rear = newNode;
}

// Fungsi untuk menghapus dan mengembalikan dokumen dari depan antrian
string dequeue(Node *&front, Node *&rear)
{
    if (front == nullptr)
    {
        return "Error: Antrian kosong"; 
    }

    // 1. Simpan node depan dan datanya
    Node *temp = front;
    string documentData = temp->document;

    // 2. Geser front ke node berikutnya
    front = front->next;

    // 3. Jika setelah digeser front menjadi null, berarti antrian kosong,
    if (front == nullptr)
    {
        rear = nullptr;
    }

    // 4. Hapus node lama dan kembalikan datanya
    delete temp;
    return documentData;
}

// Fungsi untuk memproses semua dokumen dalam antrian
void processAllDocuments(Node *&front, Node *&rear)
{

    // Loop hingga queue kosong (ditandai oleh front == nullptr)
    while (front != nullptr)
    {
        // Ambil dokumen dari depan, lalu cetak
        string docToProcess = dequeue(front, rear);
        cout << "Memproses: " << docToProcess << endl;
    }
}

int main()
{
    Node *front = nullptr;
    Node *rear = nullptr;

    enqueue(front, rear, "Document1.pdf");
    enqueue(front, rear, "Report.docx");
    enqueue(front, rear, "Presentation.pptx");

    cout << "Memulai pemrosesan antrian printer:" << endl;
    processAllDocuments(front, rear);

    // Membuktikan bahwa antrian sudah kosong
    cout << "\nStatus antrian setelah pemrosesan: ";
    if (front == nullptr && rear == nullptr)
    {
        cout << "Kosong." << endl;
    }
    else
    {
        cout << "Masih ada isi." << endl;
    }

    return 0;
}