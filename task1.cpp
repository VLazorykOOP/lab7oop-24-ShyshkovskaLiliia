#include <iostream>
#include <cstring> 

using namespace std;

template <typename T>
void swapValues(T &a, T &b) {
    T temp = a;
    a = b;
    b = temp;
}

// Специфікація шаблону для типу char*
template <>
void swapValues<char*>(char* &a, char* &b) {
    // Знаходимо довжину кожного рядка
    size_t lenA = strlen(a);
    size_t lenB = strlen(b);
    
    // Створюємо тимчасові копії
    char* temp = new char[lenA + 1];
    strcpy(temp, a);
    
    // Перевиділяємо пам'ять для a та копіюємо b в a
    delete[] a;
    a = new char[lenB + 1];
    strcpy(a, b);
    
    // Перевиділяємо пам'ять для b та копіюємо temp (оригінальний a) в b
    delete[] b;
    b = new char[lenA + 1];
    strcpy(b, temp);
    
    // Звільняємо тимчасову пам'ять
    delete[] temp;
}

int main() {
    // Тестування шаблонної функції для int
    int x = 5, y = 10;
    cout << "Before swap (int): " << x << " " << y << endl;
    swapValues(x, y);
    cout << "After swap (int): " << x << " " << y << endl << endl;
    
    // Тестування шаблонної функції для double
    double a = 3.14, b = 2.71;
    cout << "Before swap (double): " << a << " " << b << endl;
    swapValues(a, b);
    cout << "After swap (double): " << a << " " << b << endl << endl;
    
    // Тестування специфікації для char*
    char* str1 = new char[50];
    char* str2 = new char[50];
    strcpy(str1, "Hello");
    strcpy(str2, "World");
    
    cout << "Before swap (char*): " << str1 << " " << str2 << endl;
    swapValues(str1, str2);
    cout << "After swap (char*): " << str1 << " " << str2 << endl;
    
    // Звільняємо пам'ять
    delete[] str1;
    delete[] str2;
    
    return 0;
}
