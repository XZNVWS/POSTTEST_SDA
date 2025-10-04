#include <iostream>
#include <string>

using namespace std;

// Struktur Node
struct Node
{
    char data;
    Node *next;
};

// Fungsi untuk menambahkan elemen top pada stack
void push(Node *&top, char data)
{
    Node *newNode = new Node{data, top};
    top = newNode;
}

// Fungsi untuk menghapus dan mengembalikan elemen dari top stack
char pop(Node *&top)
{
    if (top == nullptr)
        return '\0'; // Mengembalikan karakter null jika stack kosong
    Node *temp = top;
    char poppedValue = temp->data;
    top = top->next;
    delete temp;
    return poppedValue;
}

// Fungsi untuk membalikkan string menggunakan stack

string reverseString(string s)
{
    Node *stackTop = nullptr;
    string reversed = "";

    // 1. Push setiap karakter dari string s ke dalam stack.
    for (char c : s)
    {
        push(stackTop, c);
    }

    // 2. Pop setiap karakter dari stack dan tambahkan ke string `reversed`.
    while (stackTop != nullptr)
    {
        reversed += pop(stackTop);
    }

    return reversed;
}

int main()
{
    string text = "Struktur Data";
    cout << "Teks asli: " << text << endl;
    cout << "Teks terbalik: " << reverseString(text) << endl; // Output yang diharapkan: ataD rukurts

    string text2 = "Hello World!";
    cout << "Teks asli: " << text2 << endl;
    cout << "Teks terbalik: " << reverseString(text2) << endl; // Output yang diharapkan: !dlroW olleH

    return 0;
}