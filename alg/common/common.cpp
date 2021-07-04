#include "common.h"

namespace alg {

int RandInt(int min, int max) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}

} // namespace alg
