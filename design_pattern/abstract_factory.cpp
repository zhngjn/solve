#include <memory>
#include <string>
#include <iostream>

class IActor {
public:
    virtual void Act() = 0;
};

class Professor : public IActor {
public:
    void Act() {
        std::cout << "The professor is giving a lesson" << std::endl;
    }
};

class Cook : public IActor {
public:
    void Act() {
        std::cout << "The cook is doing the cooking" << std::endl;
    }
};

class IPlace {
public:
    virtual std::string Where() = 0;
};

class Classroom : public IPlace {
public:
    std::string Where() {
        return "classroom";
    }
};

class Kitchen : public IPlace {
public:
    std::string Where() {
        return "kitchen";
    }
};

class IActionFactory {
public:
    virtual std::shared_ptr<IActor> CreateActor() const = 0;
    virtual std::shared_ptr<IPlace> CreatePlace() const = 0;
};

class LectureActionFactory : public IActionFactory {
public:
    virtual std::shared_ptr<IActor> CreateActor() const {
        return std::make_shared<Professor>();
    }

    virtual std::shared_ptr<IPlace> CreatePlace() const {
        return std::make_shared<Classroom>();
    }
};

class CookingActionFactory : public IActionFactory {
public:
    virtual std::shared_ptr<IActor> CreateActor() const {
        return std::make_shared<Cook>();
    }

    virtual std::shared_ptr<IPlace> CreatePlace() const {
        return std::make_shared<Kitchen>();
    }
};

class Action {
public:
    void CreateAction(const IActionFactory& factory) {
        actor_ = factory.CreateActor();
        place_ = factory.CreatePlace();
    }

    void Act() {
        if (actor_)
            actor_->Act();
    }

    void Where() {
        if (place_)
            std::cout << "Action happened in " << place_->Where() << std::endl;
    }

private:
    std::shared_ptr<IActor> actor_;
    std::shared_ptr<IPlace> place_;
};

int main() {
    Action action1;
    action1.CreateAction(LectureActionFactory());
    action1.Where();
    action1.Act();

    Action action2;
    action2.CreateAction(CookingActionFactory());
    action2.Where();
    action2.Act();
}
