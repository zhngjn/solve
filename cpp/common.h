
#pragma once
#include <iostream>
#include <string>
#include <typeinfo>

namespace common {

template <typename T>
std::string TypeToString() {
    return typeid(T).name();
}

} // namespace common
