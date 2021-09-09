#include <iostream>
#include <memory>
#include <vector>

struct Point {
    Point(double x, double y) :
        x_(x), y_(y) {}
    Point() : Point(0.0, 0.0) {}

    void Translate(double x, double y) {
        x_ += x;
        y_ += y;
    }

    double x_, y_;
};

std::ostream& operator<<(std::ostream& strm, const Point& p) {
    return strm << "(" << p.x_ << "," << p.y_ << ")";
}

class IShape {
public:
    virtual void Draw() const = 0;
    virtual std::shared_ptr<IShape> Clone() const = 0;
    virtual void Translate(double x, double y) = 0;
};

class Circle : public IShape {
public:
    Circle(const Point& c, double r) :
        center_(c),
        radius_(r) {}

    void Draw() const {
        std::cout << "{Circle, center=" << center_ << ", "
                  << "radius=" << radius_ << "}"
                  << std::endl;
    }

    std::shared_ptr<IShape> Clone() const {
        return std::make_shared<Circle>(center_, radius_);
    }

    void Translate(double x, double y) {
        center_.Translate(x, y);
    }

private:
    Point center_;
    double radius_;
};

class Rectangle : public IShape {
public:
    Rectangle(const Point& lb, double w, double h) :
        left_bottom_(lb),
        width_(w),
        height_(h) {}

    void Draw() const {
        std::cout << "{Rectangle, left bottom=" << left_bottom_ << ", "
                  << "width=" << width_ << ", "
                  << "height=" << height_ << "}"
                  << std::endl;
    }

    std::shared_ptr<IShape> Clone() const {
        return std::make_shared<Rectangle>(left_bottom_, width_, height_);
    }

    void Translate(double x, double y) {
        left_bottom_.Translate(x, y);
    }

private:
    Point left_bottom_;
    double width_;
    double height_;
};

class Triangle : public IShape {
public:
    Triangle(const Point& v1,
             const Point& v2,
             const Point& v3) :
        vertex1_(v1),
        vertex2_(v2),
        vertex3_(v3) {}

    void Draw() const {
        std::cout << "{Triangle, vertex1=" << vertex1_ << ", "
                  << "vertex2=" << vertex2_ << ", "
                  << "vertex3=" << vertex3_ << "}"
                  << std::endl;
    }

    std::shared_ptr<IShape> Clone() const {
        return std::make_shared<Triangle>(vertex1_, vertex2_, vertex3_);
    }

    void Translate(double x, double y) {
        vertex1_.Translate(x, y);
        vertex2_.Translate(x, y);
        vertex3_.Translate(x, y);
    }

private:
    // first vertex is the most left-bottom one, in anti-clockwise order
    Point vertex1_;
    Point vertex2_;
    Point vertex3_;
};

class View : public std::enable_shared_from_this<View> {
public:
    void AppendShape(std::shared_ptr<IShape> shape) {
        shapes_.push_back(shape);
    }

    void Draw() const {
        for (auto s : shapes_) {
            s->Draw();
        }
    }

    std::shared_ptr<View> ShallowClone() {
        return shared_from_this();
    }

    std::shared_ptr<View> Clone() const {
        auto view = std::make_shared<View>();
        for (auto s : shapes_) {
            view->AppendShape(s->Clone());
        }
        return view;
    }

    void Translate(double x, double y) {
        for (auto s : shapes_) {
            s->Translate(x, y);
        }
    }

private:
    std::vector<std::shared_ptr<IShape>> shapes_;
};

int main() {
    std::cout << "shallow copy 1" << std::endl;
    {
        View view1;
        view1.AppendShape(std::make_shared<Circle>(Point(1, 1), 2));
        view1.AppendShape(std::make_shared<Rectangle>(Point(2, 4), 2, 5));
        view1.AppendShape(std::make_shared<Triangle>(Point(0, 0), Point(4, -3), Point(1, 5)));
        auto view2 = view1;

        view1.Draw();
        view2.Draw();

        view1.Translate(10, 10);
        view1.Draw();
        view2.Draw();
    }
    std::cout << std::endl;

    std::cout << "shallow copy 2" << std::endl;
    {
        auto view1 = std::make_shared<View>();
        view1->AppendShape(std::make_shared<Circle>(Point(1, 1), 2));
        view1->AppendShape(std::make_shared<Rectangle>(Point(2, 4), 2, 5));
        view1->AppendShape(std::make_shared<Triangle>(Point(0, 0), Point(4, -3), Point(1, 5)));
        auto view2 = view1->ShallowClone();

        view1->Draw();
        view2->Draw();

        view1->Translate(10, 10);
        view1->Draw();
        view2->Draw();
    }
    std::cout << std::endl;

    std::cout << "deep copy" << std::endl;
    {
        auto view1 = std::make_shared<View>();
        view1->AppendShape(std::make_shared<Circle>(Point(1, 1), 2));
        view1->AppendShape(std::make_shared<Rectangle>(Point(2, 4), 2, 5));
        view1->AppendShape(std::make_shared<Triangle>(Point(0, 0), Point(4, -3), Point(1, 5)));
        auto view2 = view1->Clone();

        view1->Draw();
        view2->Draw();

        view1->Translate(10, 10);
        view1->Draw();
        view2->Draw();
    }
    std::cout << std::endl;
}
