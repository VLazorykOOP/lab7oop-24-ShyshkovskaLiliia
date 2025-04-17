#include <iostream>

template <typename T>
class TreeNode {
public:
    T data;           
    TreeNode* left;  
    TreeNode* right;  

    TreeNode(T val) : data(val), left(nullptr), right(nullptr) {} 
};

// Шаблонний клас ітератора для бінарного дерева
template <typename T>
class BinaryTreeIterator {
private:
    // Власна структура для стеку
    struct StackNode {
        TreeNode<T>* node;     // Вузол дерева
        StackNode* next;       // Наступний елемент стеку
        StackNode(TreeNode<T>* n) : node(n), next(nullptr) {} 
    };

    StackNode* stack;    // Вказівник на стек
    TreeNode<T>* current; // Поточний вузол

    // Додавання вузла до стеку
    void push(TreeNode<T>* node) {
        StackNode* newNode = new StackNode(node);
        newNode->next = stack;
        stack = newNode;
    }

    // Видалення вузла зі стеку
    TreeNode<T>* pop() {
        if (!stack) return nullptr;
        StackNode* temp = stack;
        TreeNode<T>* node = temp->node;
        stack = temp->next;
        delete temp;
        return node;
    }

    // Очищення стеку
    void clearStack() {
        while (stack) {
            StackNode* temp = stack;
            stack = stack->next;
            delete temp;
        }
    }

    // Допоміжна функція для заповнення стеку лівими вузлами
    void pushLeft(TreeNode<T>* node) {
        while (node) {
            push(node);
            node = node->left;
        }
    }

public:
    BinaryTreeIterator(TreeNode<T>* root) : stack(nullptr), current(nullptr) {
        pushLeft(root); // Ініціалізація стеку лівими вузлами
        if (stack) {
            current = stack->node; // Поточний вузол — верхній у стеку
        }
    }

    ~BinaryTreeIterator() {
        clearStack(); // Очищення стеку при знищенні
    }

    // Оператор розіменування
    T& operator*() {
        return current->data;
    }

    // Оператор префіксного інкременту
    BinaryTreeIterator& operator++() {
        if (current) {
            current = pop(); // Видалити поточний вузол зі стеку
            pushLeft(current ? current->right : nullptr); // Додати праве піддерево
            current = stack ? stack->node : nullptr; // Оновити поточний вузол
        }
        return *this;
    }

    // Оператор порівняння на нерівність
    bool operator!=(const BinaryTreeIterator& other) const {
        return current != other.current;
    }

    // Оператор порівняння на рівність
    bool operator==(const BinaryTreeIterator& other) const {
        return current == other.current;
    }
};

// Шаблонний клас бінарного дерева
template <typename T>
class BinaryTree {
private:
    TreeNode<T>* root; // Корінь дерева

    // Допоміжна функція для додавання елемента
    void insertHelper(TreeNode<T>*& node, T val) {
        if (node == nullptr) {
            node = new TreeNode<T>(val); // Створити новий вузол
        } else if (val < node->data) {
            insertHelper(node->left, val); // Вставити в ліве піддерево
        } else {
            insertHelper(node->right, val); // Вставити в праве піддерево
        }
    }

    // Допоміжна функція для видалення дерева
    void clearHelper(TreeNode<T>* node) {
        if (node != nullptr) {
            clearHelper(node->left);  // Видалити ліве піддерево
            clearHelper(node->right); // Видалити праве піддерево
            delete node;              // Видалити поточний вузол
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

    // Метод для отримання початкового ітератора
    BinaryTreeIterator<T> begin() {
        return BinaryTreeIterator<T>(root);
    }

    // Метод для отримання кінцевого ітератора
    BinaryTreeIterator<T> end() {
        return BinaryTreeIterator<T>(nullptr);
    }
};


int main() {
    BinaryTree<int> tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(20);
    tree.insert(40);
    tree.insert(70);
    tree.insert(60);
    tree.insert(80);

    // Обхід дерева за допомогою ітератора
    std::cout << "Симетричний обхід бінарного дерева: ";
    for (BinaryTreeIterator<int> it = tree.begin(); it != tree.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}
