#pragma once

namespace alg {

template <typename T>
struct TypeTraits {
    static constexpr T Invalid = T{};
};

template <>
struct TypeTraits<int> {
    static constexpr int Invalid = -1;
};

} // namespace alg
