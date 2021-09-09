#include <memory>
#include <string>
#include <iostream>
#include <vector>
#include <utility>

class IPet {
public:
    IPet(std::string name) :
        name_(std::move(name)) {}

    virtual std::string Kind() const = 0;

    std::string Name() const {
        return name_;
    }

    virtual void Stream(std::ostream& strm) const = 0;

private:
    std::string name_;
};

std::ostream& operator<<(std::ostream& strm, const IPet& pet) {
    pet.Stream(strm);
    return strm;
}

class Dog : public IPet {
public:
    Dog(std::string name) :
        IPet(name) {}

    std::string Kind() const {
        return "Dog";
    }

    void Stream(std::ostream& strm) const {
        strm << "{" << Kind() << ":" << Name() << ":~wang}";
    }
};

class Cat : public IPet {
public:
    Cat(std::string name) :
        IPet(name) {}

    std::string Kind() const {
        return "Cat";
    }

    void Stream(std::ostream& strm) const {
        strm << "{" << Kind() << ":" << Name() << ":~miao}";
    }
};

class Person {
public:
    Person(std::string name) :
        name_(std::move(name)) {}

    std::string Name() const {
        return name_;
    }

private:
    std::string name_;
};

std::ostream& operator<<(std::ostream& strm, const Person& p) {
    return strm << "{Person:" << p.Name() << "}";
}

class Family {
    friend class FamilyBuilder;
public:
    void Show() const {
        if (father_) {
            std::cout << "father:" << *father_ << std::endl;
        }
        if (mother_) {
            std::cout << "mother:" << *mother_ << std::endl;
        }
        if (!children_.empty()) {
            std::cout << "children:";
            for (auto c : children_) {
                std::cout << *c << ",";
            }
            std::cout << std::endl;
        }
        if (!pets_.empty()) {
            std::cout << "pets:";
            for (auto p : pets_) {
                std::cout << *p << ",";
            }
            std::cout << std::endl;
        }
    }

private:
    std::shared_ptr<Person> father_;
    std::shared_ptr<Person> mother_;
    std::vector<std::shared_ptr<Person>> children_;
    std::vector<std::shared_ptr<IPet>> pets_;
};

class FamilyBuilder {
public:
    FamilyBuilder() {
        family_ = std::make_shared<Family>();
    }

    void BuildFather(const std::string& name) {
        family_->father_ = std::make_shared<Person>(name);
    }
    void BuildMother(const std::string& name) {
        family_->mother_ = std::make_shared<Person>(name);
    }
    void AddChild(const std::string& name) {
        family_->children_.push_back(std::make_shared<Person>(name));
    }
    void AddPet(const std::string& kind, const std::string& name) {
        if (kind == "dog")
            family_->pets_.push_back(std::make_shared<Dog>(name));
        else if (kind == "cat")
            family_->pets_.push_back(std::make_shared<Cat>(name));
    }

    std::shared_ptr<Family> GetFamily() const {
        return family_;
    }

private:
    std::shared_ptr<Family> family_;
};

class FamilyManager {
public:
    static std::shared_ptr<Family> CreateMCFamily(
            const std::string& mother,
            const std::vector<std::string>& children) {
        FamilyBuilder builder;
        builder.BuildMother(mother);
        for (const auto& c : children) {
            builder.AddChild(c);
        }
        return builder.GetFamily();
    }

    static std::shared_ptr<Family> CreateFMCFamily(
            const std::string& father,
            const std::string& mother,
            const std::vector<std::string>& children) {
        FamilyBuilder builder;
        builder.BuildFather(father);
        builder.BuildMother(mother);
        for (const auto& c : children) {
            builder.AddChild(c);
        }
        return builder.GetFamily();
    }

    static std::shared_ptr<Family> CreateFMCPFamily(
            const std::string& father,
            const std::string& mother,
            const std::vector<std::string>& children,
            const std::vector<std::pair<std::string, std::string>>& pets) {
        FamilyBuilder builder;
        builder.BuildFather(father);
        builder.BuildMother(mother);
        for (const auto& c : children) {
            builder.AddChild(c);
        }
        for (const auto& p : pets) {
            builder.AddPet(p.first, p.second);
        }
        return builder.GetFamily();
    }
};

int main() {
    FamilyManager manager;
    auto family1 = manager.CreateMCFamily("Lili", {"Tom", "Wang", "Jim"});
    auto family2 = manager.CreateFMCFamily("Tim", "Lora", {"Zhang", "Henry"});
    auto family3 = manager.CreateFMCPFamily("Nicolas", "Jean", {"Pierre"}, {{"dog", "Trump"}, {"cat", "Super"}});
    family1->Show();
    family2->Show();
    family3->Show();
}
