#include <iostream>
#include <string>
#include <queue>
using namespace std;

struct Node{
    int key;     // dipakai sebagai HARGA
    string name; // nama produk
    Node *left;
    Node *right;
    Node(int k, const string &n) : key(k), name(n), left(nullptr), right(nullptr) {}
};

Node *insertNode(Node *root, int key, const string &name){
    if (!root)
        return new Node(key, name);
    if (key < root->key){
        root->left = insertNode(root->left, key, name);
    }
    else if (key > root->key){
        root->right = insertNode(root->right, key, name);
    }
    else{
        root->name = name;
        cout << "Harga " << key << " sudah ada, nama produk diperbarui.\n";
    }
    return root;
}

Node *searchNode(Node *root, int key){
    if (!root)
        return nullptr;
    if (key == root->key)
        return root;
    if (key < root->key)
        return searchNode(root->left, key);
    return searchNode(root->right, key);
}

Node *findMinNode(Node *root){
    while (root && root->left)
        root = root->left;
    return root;
}

Node *deleteNode(Node *root, int key){
    if (!root)
        return nullptr;
    if (key < root->key){
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->key){
        root->right = deleteNode(root->right, key);
    }
    else{
        if (!root->left && !root->right){
            delete root;
            return nullptr;
        }
        else if (!root->left){
            Node *t = root->right;
            delete root;
            return t;
        }
        else if (!root->right){
            Node *t = root->left;
            delete root;
            return t;
        }
        else{
            Node *succ = findMinNode(root->right);
            root->key = succ->key;
            root->name = succ->name;
            root->right = deleteNode(root->right, succ->key);
        }
    }
    return root;
}

void inorder(Node *root){
    if (!root)
        return;
    inorder(root->left);
    cout << "[" << root->key << "] " << root->name << "\n";
    inorder(root->right);
}

void preorder(Node *root){
    if (!root)
        return;
    cout << "[" << root->key << "] " << root->name << "\n";
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node *root){
    if (!root)
        return;
    postorder(root->left);
    postorder(root->right);
    cout << "[" << root->key << "] " << root->name << "\n";
}

void levelOrder(Node *root){ // per tingkat (atas - bawah)
    if (!root){
        cout << "(kosong)\n";
        return;
    }
    queue<Node *> q;
    q.push(root);
    while (!q.empty()){
        Node *cur = q.front();
        q.pop();
        cout << "[" << cur->key << "] " << cur->name << "\n";
        if (cur->left)
            q.push(cur->left);
        if (cur->right)
            q.push(cur->right);
    }
}

int main(){
    Node *root = nullptr;
    int pilih;

    do{
        cout << "\n=== Katalog Produk ===\n"
             << "1. Tambah produk (berdasarkan harga)\n"
             << "2. Cari produk (masukkan harga)\n"
             << "3. Hapus produk (masukkan harga)\n"
             << "4. Cetak: termurah -> termahal\n"
             << "5. Cetak: root dulu\n"
             << "6. Cetak: root belakangan\n"
             << "7. Cetak: per tingkat (dari atas)\n"
             << "8. Selesai\n"
             << "Pilih: ";
        if (!(cin >> pilih))
            return 0;

        if (pilih == 1){
            string nama;
            int harga;
            cout << "Nama produk: ";
            getline(cin >> ws, nama); // buang whitespace tersisa, ambil nama (boleh spasi)
            cout << "Harga (unik): ";
            cin >> harga;
            root = insertNode(root, harga, nama);
        }
        else if (pilih == 2){
            int harga;
            cout << "Masukkan harga yang dicari: ";
            cin >> harga;
            if (Node *n = searchNode(root, harga))
                cout << "Ketemu: [" << n->key << "] " << n->name << "\n";
            else
                cout << "Tidak ketemu produk dengan harga itu.\n";
        }
        else if (pilih == 3){
            int harga;
            cout << "Masukkan harga yang akan dihapus: ";
            cin >> harga;
            if (searchNode(root, harga)){
                root = deleteNode(root, harga);
                cout << "Produk sudah dihapus.\n";
            }
            else{
                cout << "Tidak ada produk dengan harga tersebut.\n";
            }
        }
        else if (pilih == 4){
            cout << "-- Katalog (termurah -> termahal) --\n";
            inorder(root);
        }
        else if (pilih == 5){
            cout << "-- Cetak: root dulu --\n";
            preorder(root);
        }
        else if (pilih == 6){
            cout << "-- Cetak: root belakangan --\n";
            postorder(root);
        }
        else if (pilih == 7){
            cout << "-- Cetak per tingkat --\n";
            levelOrder(root);
        }

    } while (pilih != 8);

    cout << "Selesai. Terima kasih!\n";
    return 0;
}
