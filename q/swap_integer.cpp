#include <iostream>

void Swap1(int& a, int& b) {
    a = a + b;
    b = a - b; // (a + b) - b = a
    a = a - b; // (a + b) - a = b
}

void Swap2(int& a, int& b) {
    a = a ^ b;
    b = a ^ b; // (a ^ b) ^ b = a ^ 0 = a
    a = a ^ b; // (a ^ b) ^ a = (a ^ a) ^ b = b
}

int main() {
    {
        int a = 789, b = 1234;
        Swap1(a, b);
        std::cout << "a=" << a << ", b=" << b << std::endl;
    }
    {
        int a = 789, b = 1234;
        Swap2(a, b);
        std::cout << "a=" << a << ", b=" << b << std::endl;
    }
}
