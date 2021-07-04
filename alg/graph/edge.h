#pragma once
#include <ostream>

namespace alg {

struct Edge {
    Edge(int u_, int v_)
        : u(u_), v(v_) {}

    Edge(int u_, int v_, double w_)
        : u(u_), v(v_), w(w_) {}

    int u, v;
    double w;
};

enum LinkType {
    kTreeLink,
    kParentLink,
    kBackLink,
    kDownLink,
};

struct LinkEdge {
    LinkEdge(const Edge& edge, LinkType link_type)
        : e(edge), l(link_type) {}

    Edge e;
    LinkType l;
};

std::ostream& operator<<(std::ostream& strm, LinkType l);
std::ostream& operator<<(std::ostream& strm, const LinkEdge& e);

} // namespace alg
