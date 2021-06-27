#include <utility>
#include <vector>
#include <algorithm>

#include "radix_sort.h"

// max digits10 for [0, 2147483647]
constexpr int kMaxDigits10 = 10;
// max digits2 for [0, 2147483647]
constexpr int kMaxDigits2 = 31;

constexpr int kRadix10 = 10;

namespace alg {
namespace {
int digit10(int n, int d) {
    for (int i = 0; i < kMaxDigits10 - 1 - d; i++) {
        if (n == 0) {
            return 0;
        }
        n /= 10;
    }
    return n % 10;
}

int digit2(int n, int d) {
    return (n >> (kMaxDigits2 - 1 - d)) & 0x1u;
}
} // namespace

void QuickRadixSort(int *a, int l, int r, int d) {
    if (l >= r || d >= kMaxDigits2)
        return;

    int i = l, j = r;
    while (i < j) {
        while (digit2(a[i], d) == 0 && (i < j)) i++;
        while (digit2(a[j], d) == 1 && (i < j)) j--;
        std::swap(a[i], a[j]);
    }

    if (digit2(a[i], d) == 0)
        i++;
    QuickRadixSort(a, l, i - 1, d + 1);
    QuickRadixSort(a, i, r, d + 1);
}

void QuickRadixSort(int* a, int l, int r) {
    QuickRadixSort(a, l, r, 0);
}

void MSDRadixSort(int* a, int l, int r, int d) {
    if (l >= r || d >= kMaxDigits10)
        return;

    std::vector<int> count(kRadix10 + 1, 0);
    for (int i = l; i <= r; i++) {
        count[digit10(a[i], d) + 1]++;
    }
    for (int i = 1; i <= kRadix10; i++) {
        count[i] += count[i - 1];
    }

    std::vector<int> aux(r - l + 1);
    for (int i = l; i <= r; i++) {
        aux[count[digit10(a[i], d)]++] = a[i];
    }
    for (int i = l; i <= r; i++)  {
        a[i] = aux[i - l];
    }

    MSDRadixSort(a, l, l + count[0] - 1, d + 1);
    for (int i = 1; i < kRadix10; i++) {
        MSDRadixSort(a, l + count[i - 1], l + count[i] - 1, d + 1);
    }
}

void MSDRadixSort(int* a, int l, int r) {
    MSDRadixSort(a, l, r, 0);
}

void LSDRadixSort(int* a, int l, int r) {
    if (l >= r)
        return;

    std::vector<int> count(kRadix10 + 1);
    std::vector<int> aux(r - l + 1);
    for (int d = kRadix10 - 1; d >= 0; d--) {
        std::fill(count.begin(), count.end(), 0);

        for (int i = l; i <= r; i++) {
            count[digit10(a[i], d) + 1]++;
        }
        for (int i = 1; i <= kRadix10; i++) {
            count[i] += count[i - 1];
        }

        for (int i = l; i <= r; i++) {
            aux[count[digit10(a[i], d)]++] = a[i];
        }
        for (int i = l; i <= r; i++) {
            a[i] = aux[i - l];
        }
    }
}

} // namespace alg
