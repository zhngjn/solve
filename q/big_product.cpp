#include <iostream>
#include <string>
#include <cassert>
#include <vector>

int c2i(char c) {
    return c - '0';
}

char i2c(int i) {
    return '0' + i;
}

void BigProductStep(const std::string& n, char c, int start_idx, std::vector<int>& product) {
    for (int i = n.size() - 1; i >= 0; i--) {
        std::size_t pos = n.size() - 1 - i + start_idx;
        product[pos] += c2i(n[i]) * c2i(c);
        while (product[pos] >= 10) {
            int tmp = product[pos];
            product[pos] = tmp % 10;
            product[++pos] += tmp / 10;
        }
    }
}

std::string BigProduct(const std::string& n1, const std::string& n2) {
    std::vector<int> product;
    product.resize(n1.size() + n2.size(), 0);
    for (int i = n2.size() - 1; i >= 0; i--) {
        BigProductStep(n1, n2[i], n2.size() - 1 - i, product);
    }

    int i = product.size() - 1;
    std::string ret = "";
    while (i >= 0 && product[i] == 0)
        i--;
    while (i >= 0) {
        ret += i2c(product[i]);
        i--;
    }
    if (ret.empty())
        ret = "0";
    return ret;
}

int main() {
    auto n1 = BigProduct("0", "172568");
    auto n2 = BigProduct("1863527485998562438964573829273654100127456102716840279877326591",
                         "89238964678256156732234672366123671263671764677626779898018248147");
    auto n3 = BigProduct("1836736", "0108377263287813");

    assert(n1 == "0");
    assert(n2 == "166299263499985208160780020759413714652374451720919605124255064625160643342852585011313751069951453541228852321022390315599576877");
    assert(n3 == "199060421062204498368");

    std::cout << "Success" << std::endl;
}
