#include <vector>
#include <queue>

#include "merge_sort.h"

namespace alg {
using node = Slist<int>;
using link = Slist<int>*;

namespace {

void MergeAB(int* c, int* a, int M, int* b, int N) {
    int i = 0, j = 0, k = 0;
    while (i < M && j < N) {
        c[k++] = (a[i] <= b[j] ? a[i++] : b[j++]);
    }
    while (i < M)
        c[k++] = a[i++];
    while (j < N)
        c[k++] = b[j++];
}

// Merge [l, m] & [m+1, r]
void MergeBitonic(int* a, int l, int m, int r) {
    if (l >= r || m < l || m >= r)
        return;

    std::vector<int> aux(r - l + 1);
    for (int i = l; i <= m; i++) {
        aux[i - l] = a[i];
    }
    for (int i = m + 1; i <= r; i++) {
        aux[r - l - (i - m - 1)] = a[i];
    }

    int i = l, j = r;
    for (int k = l; k <= r; k++) {
        if (aux[i - l] <= aux[j - l]) {
            a[k] = aux[i - l];
            i++;
        }
        else {
            a[k] = aux[j - l];
            j--;
        }
    }
}

link MergeAB(link a, link b) {
    // use dummy head
    node head;
    link c = &head;
    while (a && b) {
        if (a->data <= b->data) {
            c->next = a;
            c = a;
            a = a->next;
        } else {
            c->next = b;
            c = b;
            b = b->next;
        }
    }
    c->next = a ? a : b;
    return head.next;
}

} // namespace

void MergeSortBitonic(int* a, int l, int r) {
    if (l >= r)
        return;

    int m = (l + r) / 2;
    MergeSortBitonic(a, l, m);
    MergeSortBitonic(a, m + 1, r);

    MergeBitonic(a, l, m, r);
}

void MergeSortAB(int *a, int* aux, int l, int r) {
    if (l >= r)
        return;

    int m = (l + r) / 2;
    MergeSortAB(aux, a, l, m);
    MergeSortAB(aux, a, m + 1, r);

    MergeAB(a + l, aux + l, m - l + 1, aux + m + 1, r - m);
}

void MergeSortAB(int* a, int l, int r) {
    if (l >= r)
        return;

    // to improve
    std::vector<int> aux(r + 1);
    for (int i = l; i <= r; i++)
        aux[i] = a[i];

    MergeSortAB(a, &aux[0], l, r);
}

void MergeSortBU(int* a, int l, int r) {
    if (l >= r)
        return;

    for (int s = 1; s <= r - l; s *= 2) {
        for (int i = l; i <= r - s; i += 2 * s) {
            MergeBitonic(a, i, i + s - 1, std::min(i + 2 * s - 1, r));
        }
    }
}

link MergeSortAB(link c) {
    if (c == nullptr || c->next == nullptr)
        return c;

    link a = c, b = c->next;
    while (b && b->next) {
        c = c->next;
        b = b->next->next;
    }
    b = c->next;
    c->next = nullptr;

    return MergeAB(MergeSortAB(a), MergeSortAB(b));
}

link MergeSortQ(link c) {
    if (c == nullptr)
        return c;

    std::queue<link> q;
    link n;
    while (c) {
        n = c->next;
        c->next = nullptr;
        q.push(c);
        c = n;
    }
    link t = q.front();
    q.pop();
    while (!q.empty()) {
        q.push(t);
        link a = q.front();
        q.pop();
        link b = q.front();
        q.pop();
        t = MergeAB(a, b);
    }
    return t;
}

} // namespace alg
