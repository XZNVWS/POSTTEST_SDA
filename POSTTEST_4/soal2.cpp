#include <iostream>
#include <string>

using namespace std;

// Struktur Node 
struct Node
{
    char data;
    Node *next;
};

// Fungsi untuk menambahkan elemen ke atas (top) dari stack
void push(Node *&top, char data)
{
    Node *newNode = new Node{data, top};
    top = newNode;
}

// Fungsi untuk menghapus dan mengembalikan elemen dari atas (top) stack
char pop(Node *&top)
{
    if (top == nullptr)
        return '\0';
    Node *temp = top;
    char poppedValue = temp->data;
    top = top->next;
    delete temp;
    return poppedValue;
}

bool areBracketsBalanced(string expr)
{
    Node *stackTop = nullptr;

    // 1. Loop setiap karakter dalam `expr`.
    for (char c : expr)
    {

        // 2. Jika karakter adalah kurung buka, push ke stack.
        if (c == '(' || c == '{' || c == '[')
        {
            push(stackTop, c);
        }
        // 3. Jika karakter adalah kurung tutup.
        else if (c == ')' || c == '}' || c == ']')
        {
            // a. Cek apakah stack kosong. Jika ya, berarti ada kurung tutup
            //    tanpa pasangan buka.
            if (stackTop == nullptr)
            {
                return false;
            }

            // b. Pop stack, lalu cek apakah pasangannya cocok.
            char topChar = pop(stackTop);
            if ((c == ')' && topChar != '(') ||
                (c == '}' && topChar != '{') ||
                (c == ']' && topChar != '['))
            {
                return false; // Pasangan tidak cocok
            }
        }
    }

    // 4. Setelah loop selesai, jika stack kosong, return true. Jika tidak, return false.
    if (stackTop == nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    string expr1 = "{[()]}";
    cout << expr1 << " -> " << (areBracketsBalanced(expr1) ? "Seimbang" : "Tidak Seimbang") << endl;

    string expr2 = "{[(])}";
    cout << expr2 << " -> " << (areBracketsBalanced(expr2) ? "Seimbang" : "Tidak Seimbang") << endl;

    string expr3 = "((()))";
    cout << expr3 << " -> " << (areBracketsBalanced(expr3) ? "Seimbang" : "Tidak Seimbang") << endl;

    string expr4 = "{[}";
    cout << expr4 << " -> " << (areBracketsBalanced(expr4) ? "Seimbang" : "Tidak Seimbang") << endl;

    string expr5 = "([]";
    cout << expr5 << " -> " << (areBracketsBalanced(expr5) ? "Seimbang" : "Tidak Seimbang") << endl;

    return 0;
}