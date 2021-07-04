#include <utility>
#include <stack>
#include <queue>
#include <limits>

#include "alg/common/common.h"
#include "quick_sort.h"

namespace alg {

int Partition(int* a, int l, int r) {
    // needed ?
    if (l >= r)
        return l;

    int i = l, j = r - 1;
    int v = a[r];
    while (true) {
        while (a[i] < v) i++;
        while (a[j] > v) {
            if (j == l)
                break;
            j--;
        }
        if (i >= j)
            break;
        std::swap(a[i], a[j]);
    }
    std::swap(a[i], a[r]);
    return i;
}

void QuickSort(int* a, int l, int r) {
    if (l >= r)
        return;

    int m = Partition(a, l, r);
    QuickSort(a, l, m - 1);
    QuickSort(a, m + 1, r);
}

void QuickSortQ(int* a, int l, int r) {
    if (l >= r)
        return;

    std::queue<int> q;
    Qpush2(q, l, r);
    while (!q.empty()) {
        l = Qpop(q);
        r = Qpop(q);
        if (l >= r)
            continue;

        int m = Partition(a, l, r);
        // minimize queue size
        if (m - l > r - m) {
            Qpush2(q, l, m - 1);
            Qpush2(q, m + 1, r);
        } else {
            Qpush2(q, m + 1, r);
            Qpush2(q, l, m - 1);
        }
    }
}

void QuickSortST(int* a, int l, int r) {
    if (l >= r)
        return;

    std::stack<int> st;
    STpush2(st, l, r);
    while (!st.empty()) {
        l = STpop(st);
        r = STpop(st);
        if (l >= r)
            continue;

        int m = Partition(a, l, r);
        // minimize stack size
        if (m - l > r - m) {
            STpush2(st, l, m - 1);
            STpush2(st, m + 1, r);
        } else {
            STpush2(st, m + 1, r);
            STpush2(st, l, m - 1);
        }
    }
}

void QuickSortMedian(int* a, int l, int r) {
    if (l >= r)
        return;
    if (r - l == 1) {
        Compswap(a[l], a[r]);
        return;
    }

    int m = (l + r) / 2;
    std::swap(a[m], a[r - 1]);
    Compswap(a[l], a[r - 1]);
    Compswap(a[l], a[r]);
    Compswap(a[r - 1], a[r]);

    m = Partition(a, l + 1, r - 1);
    QuickSortMedian(a, l, m - 1);
    QuickSortMedian(a, m + 1, r);
}

void QuickSort3(int* a, int l, int r) {
    if (l >= r)
        return;

    int i = l - 1, j = r;
    int p = l - 1, q = r;
    int v = a[r];
    while (true) {
        while (a[++i] < v);
        while (a[--j] > v) {
            if (j == l)
                break;
        }
        if (i >= j)
            break;
        std::swap(a[i], a[j]);

        if (a[i] == v)
            std::swap(a[++p], a[i]);
        if (a[j] == v)
            std::swap(a[--q], a[j]);
    }
    std::swap(a[i], a[r]);

    j = i + 1;
    i = i - 1;
    for (int k = l; k <= p; k++, i--)
        std::swap(a[k], a[i]);
    for (int k = r - 1; k >= q; k--, j++)
        std::swap(a[k], a[j]);

    QuickSort3(a, l, i);
    QuickSort3(a, j, r);
}

int SelectKthR(int* a, int l, int r, int k) {
    if (l > r || k < l || k > r)
        return std::numeric_limits<int>::min();

    int m = Partition(a, l, r);
    if (k < m)
        return SelectKthR(a, l, m - 1, k);
    else if (k > m)
        return SelectKthR(a, m + 1, r, k);
    else
        return a[m];
}

int SelectKthI(int* a, int l, int r, int k) {
    if (l > r || k < l || k > r)
        return std::numeric_limits<int>::min();

    while (l <= r) {
        int m = Partition(a, l, r);
        if (k < m)
            r = m - 1;
        else if (k > m)
            l = m + 1;
        else
            return a[m];
    }
    // reachable?
    return std::numeric_limits<int>::min();
}

} // namespace alg
