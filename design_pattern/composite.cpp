#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <algorithm>
#include <exception>
#include <cassert>

class IllegalLeafOperation : public std::exception {
public:
    const char* what() const noexcept {
        return "Illegal operation for Leaf Component.";
    }
};

class Component {
public:
    enum Type {
        kEntity,
        kContainer
    };

    Component(const std::string& name)
        : name_(name) {}
    virtual ~Component() {}

    std::string Name() const { return name_; }

    virtual void AddChild(std::shared_ptr<Component> c) = 0;
    virtual bool DeleteChild(const std::string& name) = 0;
    virtual bool HasChild(const std::string& name) const = 0;
    virtual std::shared_ptr<Component> GetChild(const std::string& name) const = 0;
    virtual std::size_t ChildrenNumber() const = 0;

    virtual Type GetType() const = 0;
    virtual void Draw(int level = 0) const = 0;

protected:
    std::string name_;
};

class Container : public Component {
public:
    Container(const std::string& name)
        : Component(name) {}

    void AddChild(std::shared_ptr<Component> c) {
        if (!HasChild(c->Name())) {
            children_.push_back(c);
        }
    }
    bool DeleteChild(const std::string& name) {
        auto it = std::find_if(children_.begin(), children_.end(), [&](const auto& c){
            return c->Name() == name;
        });
        if (it != children_.end()) {
            children_.erase(it);
            return true;
        }
        else
            return false;
    }
    bool HasChild(const std::string& name) const {
        return std::find_if(children_.begin(), children_.end(), [&](const auto& c){
            return c->Name() == name;
        }) != children_.end();
    }
    std::shared_ptr<Component> GetChild(const std::string& name) const {
        auto it = std::find_if(children_.begin(), children_.end(), [&](const auto& c){
            return c->Name() == name;
        });
        return (it != children_.end()) ? *it : std::shared_ptr<Component>();
    }
    std::size_t ChildrenNumber() const {
        return children_.size();
    }

    Type GetType() const {
        return kContainer;
    }
    void Draw(int level = 0) const {
        std::cout << std::string(level * 4, '.')
                  << "Container " << name_ << std::endl;
        for (const auto& c : children_) {
            c->Draw(level + 1);
        }
    }

private:
    std::vector<std::shared_ptr<Component>> children_;
};

class Text : public Component {
public:
    Text(const std::string& name)
        : Component(name) {}

    void AddChild(std::shared_ptr<Component> c) {
        throw IllegalLeafOperation();
    }
    bool DeleteChild(const std::string& name) {
        throw IllegalLeafOperation();
    }
    bool HasChild(const std::string& name) const {
        throw IllegalLeafOperation();
    }
    std::shared_ptr<Component> GetChild(const std::string& name) const {
        throw IllegalLeafOperation();
    }
    std::size_t ChildrenNumber() const {
        return 0;
    }

    Type GetType() const {
        return kEntity;
    }
    void Draw(int level = 0) const {
        std::cout << std::string(level * 4, '.')
                  << "Text " << name_ << std::endl;
    }
};

class Image : public Component {
public:
    Image(const std::string& name)
        : Component(name) {}

    void AddChild(std::shared_ptr<Component> c) {
        throw IllegalLeafOperation();
    }
    bool DeleteChild(const std::string& name) {
        throw IllegalLeafOperation();
    }
    bool HasChild(const std::string& name) const {
        throw IllegalLeafOperation();
    }
    std::shared_ptr<Component> GetChild(const std::string& name) const {
        throw IllegalLeafOperation();
    }
    std::size_t ChildrenNumber() const {
        return 0;
    }

    Type GetType() const {
        return kEntity;
    }
    void Draw(int level = 0) const {
        std::cout << std::string(level * 4, '.')
                  << "Image " << name_ << std::endl;
    }
};

class Button : public Component {
public:
    Button(const std::string& name)
        : Component(name) {}

    void AddChild(std::shared_ptr<Component> c) {
        throw IllegalLeafOperation();
    }
    bool DeleteChild(const std::string& name) {
        throw IllegalLeafOperation();
    }
    bool HasChild(const std::string& name) const {
        throw IllegalLeafOperation();
    }
    std::shared_ptr<Component> GetChild(const std::string& name) const {
        throw IllegalLeafOperation();
    }
    std::size_t ChildrenNumber() const {
        return 0;
    }

    Type GetType() const {
        return kEntity;
    }
    void Draw(int level = 0) const {
        std::cout << std::string(level * 4, '.')
                  << "Button " << name_ << std::endl;
    }
};

int main() {
    auto container1 = std::make_shared<Container>("container1");
    container1->AddChild(std::make_shared<Text>("text1"));
    container1->AddChild(std::make_shared<Button>("button1"));

    auto container2 = std::make_shared<Container>("container2");
    container2->AddChild(std::make_shared<Image>("image1"));
    container2->AddChild(std::make_shared<Button>("button2"));

    auto container3 = std::make_shared<Container>("container3");
    container3->AddChild(container1);
    container3->AddChild(container2);

    auto container4 = std::make_shared<Container>("container4");
    container4->AddChild(std::make_shared<Text>("text2"));
    container4->AddChild(std::make_shared<Image>("image2"));

    auto container5 = std::make_shared<Container>("container5");
    container5->AddChild(container3);
    container5->AddChild(container4);
    container5->AddChild(std::make_shared<Button>("button3"));

    try {
        container5->GetChild("container3")->GetChild("container1")->GetChild("text1")->DeleteChild("not-exist");
    }
    catch (const IllegalLeafOperation& e) {
        std::cerr << e.what() << std::endl;
    }

    assert(container5->ChildrenNumber() == 3);
    assert(container5->HasChild("container4"));
    container5->GetChild("button3")->Draw();

    container5->Draw();
    container5->GetChild("container3")->DeleteChild("container2");
    container5->GetChild("container4")->DeleteChild("image2");
    assert(!container3->HasChild("container2"));
    container5->Draw();
}
