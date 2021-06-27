#pragma once
#include <vector>
#include <random>
#include <chrono>
#include <cassert>
#include <iostream>

namespace alg {

template <typename T>
class Array {};

template <>
class Array<int> {
public:
    Array(std::size_t size, int min, int max) {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine generator(seed);
        std::uniform_int_distribution<int> distribution(min, max);
        for (std::size_t i = 0; i < size; i++) {
            data.push_back(distribution(generator));
        }
    }

    bool IsSorted() const {
        bool ret = true;
        if (data.size() >= 2) {
            for (std::size_t i = 0; i < data.size() - 2; i++) {
                if (data[i] > data[i + 1])
                    ret = false;
            }
        }
        if (ret) {
            std::cout << "\e[0;32mArray is sorted\e[0m" << std::endl;
        } else {
            std::cout << "\e[1;31mArray is not sorted\e[0m" << std::endl;
        }
        return ret;
    }

public:
    std::vector<int> data;
};

std::ostream& operator<<(std::ostream& os, const Array<int>& array);

} // namespace alg
