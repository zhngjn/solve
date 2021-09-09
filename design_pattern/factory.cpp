#include <string>
#include <memory>
#include <iostream>

enum CustomerId {
    kHuman,
    kDog,
    kCat,
};

class IMeal {
public:
    virtual std::string Food() const = 0;
};

class HumanMeal : public IMeal {
public:
    std::string Food() const {
        return "{Rice, Beef, Cabbage, Coffee, Orange}";
    }
};

class DogMeal : public IMeal {
public:
    std::string Food() const {
        return "{Beef, Pork, Chicken, Sausage, Milk}";
    }
};

class CatMeal : public IMeal {
public:
    std::string Food() const {
        return "{Bread, Chicken, Fish, Banana, Milk}";
    }
};

class FreeMeal : public IMeal {
public:
    std::string Food() const {
        return "{Water}";
    }
};

class Restaurant {
public:
    std::shared_ptr<IMeal> MakeMeal(CustomerId customer_id) {
        switch (customer_id) {
        case kHuman:
            return std::make_shared<HumanMeal>();
        case kDog:
            return std::make_shared<DogMeal>();
        case kCat:
            return std::make_shared<CatMeal>();
        default:
            return std::make_shared<FreeMeal>();
        }
    }
};

class IRestaurant {
public:
    virtual std::shared_ptr<IMeal> MakeMeal() = 0;
};

class HumanRestaurant : public IRestaurant {
public:
    std::shared_ptr<IMeal> MakeMeal() {
        return std::make_shared<HumanMeal>();
    }
};

class DogRestaurant : public IRestaurant {
public:
    std::shared_ptr<IMeal> MakeMeal() {
        return std::make_shared<DogMeal>();
    }
};

class CatRestaurant : public IRestaurant {
public:
    std::shared_ptr<IMeal> MakeMeal() {
        return std::make_shared<CatMeal>();
    }
};

class ILife {
public:
    void CreateLife() {
        CreateRestaurant();
    }

    std::shared_ptr<IRestaurant> GotoRestaurant() {
        return restaurant_;
    }

private:
    virtual void CreateRestaurant() = 0;

protected:
    std::shared_ptr<IRestaurant> restaurant_;
};

class HumanLife : public ILife {
private:
    void CreateRestaurant() {
        restaurant_ = std::make_shared<HumanRestaurant>();
    }
};

class DogLife : public ILife {
private:
    void CreateRestaurant() {
        restaurant_ = std::make_shared<DogRestaurant>();
    }
};

class CatLife : public ILife {
private:
    void CreateRestaurant() {
        restaurant_ = std::make_shared<CatRestaurant>();
    }
};

int main() {
    Restaurant restaurant;
    auto human_meal = restaurant.MakeMeal(kHuman);
    auto dog_meal = restaurant.MakeMeal(kDog);
    auto cat_meal = restaurant.MakeMeal(kCat);
    std::cout << human_meal->Food() << std::endl;
    std::cout << dog_meal->Food() << std::endl;
    std::cout << cat_meal->Food() << std::endl;

    HumanLife human_life;
    DogLife dog_life;
    CatLife cat_life;
    human_life.CreateLife();
    dog_life.CreateLife();
    cat_life.CreateLife();
    std::cout << human_life.GotoRestaurant()->MakeMeal()->Food() << std::endl;
    std::cout << dog_life.GotoRestaurant()->MakeMeal()->Food() << std::endl;
    std::cout << cat_life.GotoRestaurant()->MakeMeal()->Food() << std::endl;
}
