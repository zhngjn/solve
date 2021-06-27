#include "array.h"

namespace alg {

std::ostream& operator<<(std::ostream& os, const Array<int>& array) {
    for (std::size_t i = 0; i < array.data.size(); i++) {
        os << array.data[i] << ", ";
    }
    return os;
}

}  //  namespace alg
