#include "alg/data/array.h"
#include "radix_sort.h"

using namespace alg;

int main() {
    for (int i = 0; i < 100; i++) {
        Array<int> a(1000, 0, 1000000);
        QuickRadixSort(&a.data[0], 0, a.data.size() - 1);
        assert(a.IsSorted());
    }

    for (int i = 0; i < 100; i++) {
        Array<int> a(1000, 0, 1000000);
        MSDRadixSort(&a.data[0], 0, a.data.size() - 1);
        assert(a.IsSorted());
    }

    for (int i = 0; i < 100; i++) {
        Array<int> a(1000, 0, 1000000);
        LSDRadixSort(&a.data[0], 0, a.data.size() - 1);
        assert(a.IsSorted());
    }
}
