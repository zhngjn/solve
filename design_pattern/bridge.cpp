#include <cctype>
#include <cassert>
#include <iostream>
#include <iterator>
#include <algorithm>

#include "boost/algorithm/string/case_conv.hpp"
#include "boost/algorithm/string/split.hpp"

#include "bridge.hpp"

class StringConverterImpl {
public:
    virtual std::string ToLower(const std::string& str) const = 0;
    virtual std::string ToUpper(const std::string& str) const = 0;
    virtual std::vector<std::string> Split(const std::string& str) const = 0;
};

class MyStringConverterImpl : public StringConverterImpl {
public:
    std::string ToLower(const std::string& str) const {
        std::string s = str;
        for (auto& c : s) {
            c = std::tolower(c);
        }
        return s;
    }

    std::string ToUpper(const std::string& str) const {
        std::string s = str;
        for (auto& c : s) {
            c = std::toupper(c);
        }
        return s;
    }

    std::vector<std::string> Split(const std::string& str) const {
        std::vector<std::string> str_list{};
        std::size_t p = 0, q;
        while (p < str.size()) {
            while (p < str.size() && std::isspace(str[p]))
                p++;
            if (p >= str.size())
                break;

            q = p;
            q++;
            while (q < str.size() && !std::isspace(str[q]))
                q++;
            str_list.push_back(str.substr(p, q - p));

            p = q;
        }
        return str_list;
    }
};

class BoostStringConverterImpl : public StringConverterImpl {
public:
    std::string ToLower(const std::string& str) const {
        std::string s;
        boost::algorithm::to_lower_copy(std::back_inserter(s), str);
        return s;
    }

    std::string ToUpper(const std::string& str) const {
        std::string s;
        boost::algorithm::to_upper_copy(std::back_inserter(s), str);
        return s;
    }

    std::vector<std::string> Split(const std::string& str) const {
        const auto IsSpacePred = [](char c) -> bool {
            return std::isspace(c);
        };
        std::vector<std::string> strings;
        boost::algorithm::split(strings, str, IsSpacePred, boost::algorithm::token_compress_on);
        strings.erase(std::remove_if(strings.begin(), strings.end(), [](const auto& s){
            return s.empty();
        }), strings.end());
        return strings;
    }
};

StringConverter::StringConverter(ConvertMethod method) {
    if (method == MyMethod) {
        impl_ = std::make_shared<MyStringConverterImpl>();
    }
    else if (method == BoostMethod) {
        impl_ = std::make_shared<BoostStringConverterImpl>();
    }
    else {
        assert(false);
    }
}

std::string StringConverter::ToLower(const std::string& str) const {
    return impl_->ToLower(str);
}

std::string StringConverter::ToUpper(const std::string& str) const {
    return impl_->ToUpper(str);
}

std::vector<std::string> StringConverter::Split(const std::string& str) const {
    return impl_->Split(str);
}

int main() {
    std::vector<std::string> texts = {
        "",
        "  ",
        "This",
        " TODAY ",
        "Circumambulate the CITY of a dreamy Sabbath afternoon.",
        " But look! here come more crowds, pacing straight for the water, and seemingly bound for a dive.",
        "ONCE MORE.  ",
        " And there is   all the difference in the world   between PAYING and BEING PAID.  "
    };

    const auto vec_2_str = [](const std::vector<std::string>& strings) -> std::string {
        std::stringstream ss;
        ss << "[";
        for (const auto& str : strings) {
            ss << str << ",";
        }
        ss << "]";
        return ss.str();
    };

    const auto test_converter = [&](const StringConverter& converter){
        int i = 0;
        for (const auto& str : texts) {
            std::cout << ("#s" + std::to_string(++i) + ":") << std::endl;
            std::cout << " " << converter.ToLower(str) << std::endl;
            std::cout << " " << converter.ToUpper(str) << std::endl;
            std::cout << " " << vec_2_str(converter.Split(str)) << std::endl;
        }
    };

    const auto compare_converter = [&](
            const StringConverter& conv1,
            const StringConverter& conv2){
        for (const auto& str : texts) {
            assert(conv1.ToLower(str) == conv2.ToLower(str));
            assert(conv1.ToUpper(str) == conv2.ToUpper(str));
            assert(conv1.Split(str) == conv2.Split(str));
        }
    };

    std::cout << "MyMethod=====" << std::endl;
    StringConverter my_converter(MyMethod);
    test_converter(my_converter);

    std::cout << "BoostMethod=====" << std::endl;
    StringConverter boost_converter(BoostMethod);
    test_converter(boost_converter);

    compare_converter(my_converter, boost_converter);
}
