#include <iostream>
#include <vector>
#include <numeric>
#include <limits>
#include <algorithm>

struct Point {
    Point(double x = 0.0, double y = 0.0)
        : x_(x), y_(y) {}
    Point& operator+=(const Point& other) {
        x_ += other.x_;
        y_ += other.y_;
        return *this;
    }

    double x_, y_;
};
Point operator+(const Point& p1, const Point& p2) {
    Point p(p1);
    p += p2;
    return p;
}
std::ostream& operator<<(std::ostream& strm, const Point& p) {
    return strm << "(" << p.x_ << "," << p.y_ << ")";
}

struct BoundingBox {
    BoundingBox(const Point& c, double w, double h)
        : center_(c), width_(w), height_(h) {}

    Point center_;
    double width_, height_;
};
std::ostream& operator<<(std::ostream& strm, const BoundingBox& bb) {
    return strm << "{" << bb.center_ << "," << bb.width_ << "," << bb.height_ << ")";
}

class IShape {
public:
    virtual Point Center() const = 0;
    virtual BoundingBox GetBoundingBox() const = 0;
    virtual std::string Type() const = 0;
};

class Circle : public IShape {
public:
    Circle(const Point& c, double r)
        : center_(c), radius_(r) {}

    Point Center() const {
        return center_;
    }

    BoundingBox GetBoundingBox() const {
        return BoundingBox(center_, 2 * radius_, 2 * radius_);
    }

    std::string Type() const { return "Circle"; }

private:
    Point center_;
    double radius_;
};

class Triangle : public IShape {
public:
    Triangle(const Point& p1, const Point& p2, const Point& p3)
        : p1_(p1), p2_(p2), p3_(p3) {}

    Point Center() const {
        return Point((p1_.x_ + p2_.x_ + p3_.x_) / 3,
                     (p1_.y_ + p2_.y_ + p3_.y_) / 3);
    }

    BoundingBox GetBoundingBox() const {
        double min_x = std::min(p1_.x_, p2_.x_);
        double max_x = std::max(p1_.x_, p2_.x_);
        double min_y = std::min(p1_.y_, p2_.y_);
        double max_y = std::max(p1_.y_, p2_.y_);
        min_x = std::min(min_x, p3_.x_);
        max_x = std::max(max_x, p3_.x_);
        min_y = std::min(min_y, p3_.y_);
        max_y = std::max(max_y, p3_.y_);
        return BoundingBox(Point((min_x + max_x) / 2, (min_y + max_y) / 2),
                           max_x - min_x,
                           max_y - min_y);
    }

    std::string Type() const { return "Triangle"; }

private:
    Point p1_, p2_, p3_;
};

class Character {
public:
    Character(int c, bool cap)
        : code_(c), capital_(cap) {}

    std::vector<Point> Polygon() const {
        return {Point(0, 0), Point(1, 0), Point(0.2, 0.2), Point(0, 1), Point(0, 0)};
    }

    int Code() const { return code_; }
    bool Capital() const { return capital_; }

private:
    int code_;
    bool capital_;
};

namespace impl1
{
class CharacterShape : public IShape, private Character {
public:
    CharacterShape(const Point& lb, int code, bool cap)
        : Character(code, cap),
          left_bottom_(lb) {}

    Point Center() const {
        const auto polygon = Polygon();
        const auto p = std::accumulate(polygon.begin(), polygon.end(), Point(), [](const auto& p1, const auto& p2){
            return p1 + p2;
        });
        return Point(p.x_ / polygon.size(), p.y_ / polygon.size());
    }

    BoundingBox GetBoundingBox() const {
        const auto polygon = Polygon();
        double min_x = (*std::min_element(polygon.begin(), polygon.end(), [](const auto& p1, const auto& p2){
            return p1.x_ < p2.x_;
        })).x_;
        double max_x = (*std::max_element(polygon.begin(), polygon.end(), [](const auto& p1, const auto& p2){
            return p1.x_ < p2.x_;
        })).x_;
        double min_y = (*std::min_element(polygon.begin(), polygon.end(), [](const auto& p1, const auto& p2){
            return p1.y_ < p2.y_;
        })).y_;
        double max_y = (*std::max_element(polygon.begin(), polygon.end(), [](const auto& p1, const auto& p2){
            return p1.y_ < p2.y_;
        })).y_;
        Point c((min_x + max_x) / 2, (min_y + max_y) / 2);
        return BoundingBox(c, max_x - min_x, max_y - min_y);
    }

    std::string Type() const { return "CharacterShape"; }

    std::vector<Point> Polygon() const {
        auto polygon = Character::Polygon();
        for (auto& p : polygon) {
            p += left_bottom_;
        }
        return polygon;
    }

    int Code() const { return Character::Code(); }
    bool Capital() const { return Character::Capital(); }

private:
    Point left_bottom_;
};
} // namespace impl1

namespace impl2
{
class CharacterShape : public IShape {
public:
    CharacterShape(const Point& lb, const Character& ch)
        : left_bottom_(lb), ch_(ch) {}

    Point Center() const {
        const auto polygon = Polygon();
        const auto p = std::accumulate(polygon.begin(), polygon.end(), Point(), [](const auto& p1, const auto& p2){
            return p1 + p2;
        });
        return Point(p.x_ / polygon.size(), p.y_ / polygon.size());
    }

    BoundingBox GetBoundingBox() const {
        const auto polygon = Polygon();
        double min_x = (*std::min_element(polygon.begin(), polygon.end(), [](const auto& p1, const auto& p2){
            return p1.x_ < p2.x_;
        })).x_;
        double max_x = (*std::max_element(polygon.begin(), polygon.end(), [](const auto& p1, const auto& p2){
            return p1.x_ < p2.x_;
        })).x_;
        double min_y = (*std::min_element(polygon.begin(), polygon.end(), [](const auto& p1, const auto& p2){
            return p1.y_ < p2.y_;
        })).y_;
        double max_y = (*std::max_element(polygon.begin(), polygon.end(), [](const auto& p1, const auto& p2){
            return p1.y_ < p2.y_;
        })).y_;
        Point c((min_x + max_x) / 2, (min_y + max_y) / 2);
        return BoundingBox(c, max_x - min_x, max_y - min_y);
    }

    std::string Type() const { return "CharacterShape"; }

    std::vector<Point> Polygon() const {
        auto polygon = ch_.Polygon();
        for (auto& p : polygon) {
            p += left_bottom_;
        }
        return polygon;
    }

    int Code() const { return ch_.Code(); }
    bool Capital() const { return ch_.Capital(); }

private:
    Point left_bottom_;
    Character ch_;
};
} // namespace impl2

template <typename Shape>
void ShowShape(const Shape& shape)
{
    std::cout << shape.Type() << std::endl;
    std::cout << "  Center:" << shape.Center() << std::endl;
    std::cout << "  BoundingBox:" << shape.GetBoundingBox() << std::endl;
}

int main() {
    std::cout << "### Test 1" << std::endl;
    {
        using namespace impl1;
        Circle circle(Point(2, 0), 1);
        Triangle triangle(Point(-1, 0), Point(1, 0), Point(0, 2));
        CharacterShape ch(Point(5, 2), 'A', true);
        ShowShape(circle);
        ShowShape(triangle);
        ShowShape(ch);
    }
    std::cout << "### Test 2" << std::endl;
    {
        using namespace impl2;
        Circle circle(Point(2, 0), 1);
        Triangle triangle(Point(-1, 0), Point(1, 0), Point(0, 2));
        CharacterShape ch(Point(5, 2), Character('A', true));
        ShowShape(circle);
        ShowShape(triangle);
        ShowShape(ch);
    }
}
