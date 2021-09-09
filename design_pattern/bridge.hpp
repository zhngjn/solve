#pragma once
#include <memory>
#include <string>
#include <vector>

enum ConvertMethod {
    MyMethod,
    BoostMethod,
};

class StringConverterImpl;

class StringConverter {
public:
    StringConverter(ConvertMethod method);
    std::string ToLower(const std::string& str) const;
    std::string ToUpper(const std::string& str) const;
    std::vector<std::string> Split(const std::string& str) const;

private:
    std::shared_ptr<StringConverterImpl> impl_;
};
