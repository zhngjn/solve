#include "alg/data/array.h"
#include "alg/common/common.h"
#include "quick_sort.h"

using namespace alg;

int main() {
    for (int i = 0; i < 100; i++) {
        Array<int> a(1000, 0, 1000000);
        QuickSort(&a.data[0], 0, a.data.size() - 1);
        assert(a.IsSorted());
    }

    for (int i = 0; i < 100; i++) {
        Array<int> a(1000, 0, 1000000);
        QuickSortQ(&a.data[0], 0, a.data.size() - 1);
        assert(a.IsSorted());
    }

    for (int i = 0; i < 100; i++) {
        Array<int> a(1000, 0, 1000000);
        QuickSortST(&a.data[0], 0, a.data.size() - 1);
        assert(a.IsSorted());
    }

    for (int i = 0; i < 100; i++) {
        Array<int> a(1000, 0, 1000000);
        QuickSortMedian(&a.data[0], 0, a.data.size() - 1);
        assert(a.IsSorted());
    }

    for (int i = 0; i < 100; i++) {
        Array<int> a(1000, 0, 1000000);
        QuickSort3(&a.data[0], 0, a.data.size() - 1);
        assert(a.IsSorted());
    }

    for (int i = 0; i < 100; i++) {
        Array<int> a(1000, 0, 1000000);
        auto a2 = a;
        int k = RandInt(0, a.data.size() - 1);
        int v = SelectKthR(&a.data[0], 0, a.data.size() - 1, k);
        QuickSort(&a2.data[0], 0, a2.data.size() - 1);
        assert(a2.IsSorted());
        assert(a2.data[k] == v);
    }

    for (int i = 0; i < 100; i++) {
        Array<int> a(1000, 0, 1000000);
        auto a2 = a;
        int k = RandInt(0, a.data.size() - 1);
        int v = SelectKthI(&a.data[0], 0, a.data.size() - 1, k);
        QuickSort(&a2.data[0], 0, a2.data.size() - 1);
        assert(a2.IsSorted());
        assert(a2.data[k] == v);
    }
}
