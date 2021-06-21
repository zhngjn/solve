#include <iostream>

#include "type_list.h"

using namespace common;
using namespace type_list;

int main() {
    {
        using TestType = TypeList<int, char, double, float>;
        std::cout << TypeToString<Front<TestType>>() << std::endl;

        std::cout << TypeListString<PushFront<TestType, std::string>>::ToString() << std::endl;
        std::cout << TypeListString<PopFront<TestType>>::ToString() << std::endl;
    }

    return 0;
}
