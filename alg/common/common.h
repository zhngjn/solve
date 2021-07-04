#pragma once
#include <stack>
#include <queue>
#include <chrono>
#include <random>
#include <sstream>

namespace alg {

template <typename T>
void Qpush2(std::queue<T>& q, const T& l, const T& r) {
    q.push(l);
    q.push(r);
}

template <typename T>
void STpush2(std::stack<T>& st, const T& l, const T& r) {
    st.push(r);
    st.push(l);
}

template <typename T>
T Qpop(std::queue<T>& q) {
    T v = q.front();
    q.pop();
    return v;
}

template <typename T>
T STpop(std::stack<T>& st) {
    T v = st.top();
    st.pop();
    return v;
}

template <typename T>
void Compswap(T& a, T& b) {
    if (a > b) {
        std::swap(a, b);
    }
}

int RandInt(int min, int max);

template <typename Cont>
std::string Cont2Str(const Cont& c) {
    std::stringstream ss;
    for (const auto& v : c) {
        ss << v << ", ";
    }
    return ss.str();
}

} // namespace alg
