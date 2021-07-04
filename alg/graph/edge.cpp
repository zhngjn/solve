#include <unordered_map>

#include "edge.h"

namespace alg {

std::ostream& operator<<(std::ostream& strm, LinkType l) {
    static std::unordered_map<LinkType, std::string> lt_2_str = {
        {kTreeLink, "t"},
        {kParentLink, "p"},
        {kBackLink, "b"},
        {kDownLink, "d"},
    };
    return strm << lt_2_str[l];
}

std::ostream& operator<<(std::ostream& strm, const LinkEdge& e) {
    strm << "[" << e.e.u << " :";
    strm << e.l;
    strm << " " << e.e.v << "]";
    return strm;
}

} // namespace alg
