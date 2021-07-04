#include <cassert>
#include <iostream>
#include "name_index.h"

using namespace alg;

int main() {
    NameIndex ni;
    assert(ni.IndexByName("but") == 0);
    assert(ni.IndexByName("that") == 1);
    assert(ni.IndexByName("river") == 2);
    assert(ni.IndexByName("river") == 2);
    assert(ni.IndexByName("see") == 3);
    assert(ni.IndexByName("dog") == 4);
    assert(ni.IndexByName("that") == 1);
    assert(ni.Count() == 5);
    std::cout << "Success" << std::endl;
}
