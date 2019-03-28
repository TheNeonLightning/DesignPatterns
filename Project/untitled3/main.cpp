#include <iostream>

int main() {
    const int a = 5;
    const int * a_ptr = &a;
    int * b = const_cast<int*>(a_ptr);
    *b = 3;
}