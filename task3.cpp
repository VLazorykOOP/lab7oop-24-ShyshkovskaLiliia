#include <iostream>

using namespace std;

// Шаблонний клас вузла дерева
template <typename T>
class TreeNode {
public:
    T data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(T val) : data(val), left(nullptr), right(nullptr) {}
};

// Шаблонний клас бінарного дерева
template <typename T>
class BinaryTree {
private:
    TreeNode<T>* root;

    // Допоміжна функція для додавання елемента
    void insertHelper(TreeNode<T>*& node, T val) {
        if (node == nullptr) {
            node = new TreeNode<T>(val);
        } else if (val < node->data) {
            insertHelper(node->left, val);
        } else {
            insertHelper(node->right, val);
        }
    }

    // Допоміжна функція для обходу в порядку зростання (in-order)
    void inOrderHelper(TreeNode<T>* node) {
        if (node != nullptr) {
            inOrderHelper(node->left);
            cout << node->data << " ";
            inOrderHelper(node->right);
        }
    }

    // Допоміжна функція для обходу в порядку спадання (reverse in-order)
    void descendingOrderHelper(TreeNode<T>* node) {
        if (node != nullptr) {
            descendingOrderHelper(node->right);
            cout << node->data << " ";
            descendingOrderHelper(node->left);
        }
    }

    // Допоміжна функція для пошуку
    bool searchHelper(TreeNode<T>* node, T val) {
        if (node == nullptr) {
            return false;
        } else if (node->data == val) {
            return true;
        } else if (val < node->data) {
            return searchHelper(node->left, val);
        } else {
            return searchHelper(node->right, val);
        }
    }

    // Допоміжна функція для видалення дерева
    void clearHelper(TreeNode<T>* node) {
        if (node != nullptr) {
            clearHelper(node->left);
            clearHelper(node->right);
            delete node;
        }
    }

public:
    BinaryTree() : root(nullptr) {}

    ~BinaryTree() {
        clearHelper(root);
    }

    // Додати елемент у дерево
    void insert(T val) {
        insertHelper(root, val);
    }

    // Обхід у порядку зростання (в порядку in-order)
    void inOrderTraversal() {
        inOrderHelper(root);
        cout << endl;
    }

    // Обхід у порядку спадання
    void descendingOrderTraversal() {
        descendingOrderHelper(root);
        cout << endl;
    }

    // Пошук елемента у дереві
    bool search(T val) {
        return searchHelper(root, val);
    }
};

// Приклад використання
int main() {
    BinaryTree<int> tree;

    // Додаємо елементи
    tree.insert(50);
    tree.insert(30);
    tree.insert(20);
    tree.insert(40);
    tree.insert(70);
    tree.insert(60);
    tree.insert(80);

    // Обходи дерева
    cout << "In-order traversal (ascending order): ";
    tree.inOrderTraversal();

    cout << "Descending order traversal: ";
    tree.descendingOrderTraversal();

    // Пошук елементів
    cout << "Search for 40: " << (tree.search(40) ? "Found" : "Not found") << endl;
    cout << "Search for 90: " << (tree.search(90) ? "Found" : "Not found") << endl;

    return 0;
}
