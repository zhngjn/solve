#include "alg/data/array.h"
#include "alg/data/list.h"
#include "merge_sort.h"

using namespace alg;

int main() {
    for (int i = 0; i < 100; i++) {
        Array<int> a(1000, 0, 1000000);
        MergeSortBitonic(&a.data[0], 0, a.data.size() - 1);
        assert(a.IsSorted());
    }

    for (int i = 0; i < 100; i++) {
        Array<int> a(1000, 0, 1000000);
        MergeSortAB(&a.data[0], 0, a.data.size() - 1);
        assert(a.IsSorted());
    }

    for (int i = 0; i < 100; i++) {
        Array<int> a(1000, 0, 1000000);
        MergeSortBU(&a.data[0], 0, a.data.size() - 1);
        assert(a.IsSorted());
    }

    for (int i = 0; i < 100; i++) {
        Array<int> a(1000, 0, 1000000);
        Slist<int>* list = MakeSlist(a);
        Slist<int>* list2 = MergeSortAB(list);
        assert(IsSlistSorted(list2));
        DeleteSlist(list2);
    }

    for (int i = 0; i < 100; i++) {
        Array<int> a(1000, 0, 1000000);
        Slist<int>* list = MakeSlist(a);
        Slist<int>* list2 = MergeSortQ(list);
        assert(IsSlistSorted(list2));
        DeleteSlist(list2);
    }
}
