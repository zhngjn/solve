#include <cstddef>
#include <stdexcept>
#include <random>
#include <chrono>
#include <iostream>
#include <functional>

template <typename T>
class IList {
public:
    virtual ~IList() {}

    virtual void PushBack(const T& value) = 0;
    virtual void PopBack() = 0;
    virtual std::size_t Size() const = 0;
    virtual bool IsEmpty() const = 0;
};

template <typename> class ArrayListIterator;
template <typename> class SkipArrayListIterator;
template <typename> class FilterArrayListIterator;
template <typename> class RandomArrayListIterator;
template <typename T>
class ArrayList : public IList<T> {
    friend class ArrayListIterator<T>;
    friend class SkipArrayListIterator<T>;
    friend class FilterArrayListIterator<T>;
    friend class RandomArrayListIterator<T>;
public:
    ~ArrayList() {
        if (data_) {
            delete[] data_;
        }
    }

    void PushBack(const T& value) {
        if (size_ + 1 > cap_) {
            ReallocMem((size_ + 1) * 2);
        }
        data_[size_++] = value;
    }

    void PopBack() {
        if (size_ == 0) {
            throw std::runtime_error("Empty ArrayList");
        }
        --size_;
        if (size_ < cap_ / 2) {
            ReallocMem(cap_ / 2);
        }
    }

    std::size_t Size() const {
        return size_;
    }

    bool IsEmpty() const {
        return size_ == 0;
    }

private:
    void ReallocMem(std::size_t new_size) {
        T* new_data = new T[new_size];
        for (std::size_t i = 0; i < size_; i++) {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
        cap_ = new_size;
    }

private:
    T* data_ = nullptr;
    std::size_t size_ = 0;
    std::size_t cap_ = 0;
};

template <typename> class LinkListIterator;
template <typename T>
class LinkList : public IList<T> {
    friend class LinkListIterator<T>;
public:
    struct Node {
        T value;
        Node *prev, *next;
    };

public:
    LinkList() {
        head_ = new Node();
        head_->next = head_;
        head_->prev = head_;
    }

    ~LinkList() {
        Node* tmp = head_->next;
        while (tmp != head_) {
            Node* n = tmp->next;
            delete tmp;
            tmp = n;
        }
        delete head_;
    }

    void PushBack(const T& value) {
        Node* new_node = new Node();
        new_node->value = value;
        Node* prev = head_->prev;
        prev->next = new_node;
        new_node->prev = prev;
        new_node->next = head_;
        head_->prev = new_node;

        ++size_;
    }

    void PopBack() {
        if (size_ == 0) {
            throw std::runtime_error("Empty LinkList");
        }
        Node* tmp = head_->prev;
        Node* prev = tmp->prev;
        prev->next = head_;
        head_->prev = prev;
        delete tmp;

        --size_;
    }

    std::size_t Size() const {
        return size_;
    }

    bool IsEmpty() const {
        return size_ == 0;
    }

private:
    Node* head_ = nullptr;
    std::size_t size_ = 0;
};

template <typename T>
class IListIterator {
public:
    virtual bool HasNext() const = 0;
    virtual T& Next() = 0;

    virtual bool HasPrevious() const = 0;
    virtual T& Previous() = 0;
};

template <typename T>
class ArrayListIterator : public IListIterator<T> {
public:
    ArrayListIterator(ArrayList<T>* l)
        : list_(l), pos_(0) {}

    bool HasNext() const {
        return pos_ >= 0 && pos_ < list_->size_;
    }
    T& Next() {
        return list_->data_[pos_++];
    }

    bool HasPrevious() const {
        return pos_ > 0 && pos_ <= list_->size_;
    }
    T& Previous() {
        return list_->data_[--pos_];
    }

protected:
    ArrayList<T>* list_;
    std::size_t pos_;
};

template <typename T>
class LinkListIterator : public IListIterator<T> {
public:
    LinkListIterator(LinkList<T>* l)
        : list_(l) {
        cur_ = list_->head_->next;
    }

    bool HasNext() const {
        return cur_ != list_->head_;
    }
    T& Next() {
        T& v = cur_->value;
        cur_ = cur_->next;
        return v;
    }

    bool HasPrevious() const {
        return cur_->prev != list_->head_;
    }
    T& Previous() {
        cur_ = cur_->prev;
        return cur_->value;
    }

private:
    LinkList<T>* list_;
    typename LinkList<T>::Node* cur_;
};

template <typename T>
class SkipArrayListIterator : public ArrayListIterator<T> {
    using ArrayListIterator<T>::list_;
    using ArrayListIterator<T>::pos_;
public:
    SkipArrayListIterator(ArrayList<T>* l, std::size_t step, std::size_t init_pos = 0)
        : ArrayListIterator<T>(l), step_(step) {
        pos_ = std::min(init_pos, list_->Size());
    }

    bool HasNext() const {
        return pos_ >= 0 && pos_ < list_->size_;
    }
    T& Next() {
        T& v = list_->data_[pos_];
        pos_ = std::min(pos_ + step_, list_->Size());
        return v;
    }

    bool HasPrevious() const {
        return pos_ > 0 && pos_ <= list_->size_;
    }
    T& Previous() {
        T& v = list_->data_[pos_ - 1];
        pos_ = std::max<std::size_t>(1, pos_ - step_);
        return v;
    }

private:
    std::size_t step_;
};

template <typename T>
class FilterArrayListIterator : public ArrayListIterator<T> {
public:
    using ArrayListIterator<T>::list_;
    using ArrayListIterator<T>::pos_;
public:
    FilterArrayListIterator(ArrayList<T>* l, const std::function<bool(const T&)>& pred)
        : ArrayListIterator<T>(l), pred_(pred) {
        for (; pos_ < list_->size_ && !pred_(list_->data_[pos_]); pos_++);
    }

    bool HasNext() const {
        return pos_ >= 0 && pos_ < list_->size_;
    }
    T& Next() {
        T& v = list_->data_[pos_];
        for (pos_++; pos_ < list_->size_ && !pred_(list_->data_[pos_]); pos_++);
        return v;
    }

    bool HasPrevious() const {
        std::size_t pos = pos_;
        if (pos == list_->size_)
            for (; pos > 0 && !pred_(list_->data_[pos - 1]); pos--);
        return pos > 0;
    }
    T& Previous() {
        if (pos_ == list_->size_)
            for (; pos_ > 0 && !pred_(list_->data_[pos_ - 1]); pos_--);
        T& v = list_->data_[pos_ - 1];
        for (pos_--; pos_ > 0 && !pred_(list_->data_[pos_ - 1]); pos_--);
        return v;
    }

private:
    std::function<bool(const T&)> pred_;
};

template <typename T>
class RandomArrayListIterator : public ArrayListIterator<T> {
    using ArrayListIterator<T>::list_;
    using ArrayListIterator<T>::pos_;
public:
    RandomArrayListIterator(ArrayList<T>* l)
        : ArrayListIterator<T>(l) {}

    bool HasNext() const {
        return pos_ >= 0 && pos_ < list_->size_;
    }
    T& Next() {
        std::size_t rand_pos = RandomPos(pos_, list_->Size() - 1);
        T& v = list_->data_[rand_pos];
        pos_ = rand_pos + 1;
        return v;
    }

    bool HasPrevious() const {
        return pos_ > 0 && pos_ <= list_->size_;
    }
    T& Previous() {
        std::size_t rand_pos = RandomPos(1, pos_);
        T& v = list_->data_[rand_pos - 1];
        pos_ = rand_pos - 1;
        return v;
    }

private:
    std::size_t RandomPos(std::size_t min, std::size_t max) const {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine generator(seed);
        std::uniform_int_distribution<std::size_t> distribution(min, max);
        return distribution(generator);
    }
};

template <typename List, typename Iterator>
void IterateList(List& l) {
    std::cout << "---- iterate ----" << std::endl;
    Iterator it(&l);
    while (it.HasNext()) {
        std::cout << it.Next() << ",";
    }
    std::cout << std::endl;

    while (it.HasPrevious()) {
        std::cout << it.Previous() << ",";
    }
    std::cout << std::endl;

    while (it.HasNext()) {
        std::cout << it.Next() << ",";
    }
    std::cout << std::endl;
}

template <typename List, typename Iterator>
void ScaleList(List& l, int factor) {
    Iterator it(&l);
    while (it.HasNext()) {
        it.Next() *= factor;
    }
}

void SkipIterate(ArrayList<int>& l, std::size_t step, std::size_t init_pos = 0) {
    std::cout << "---- skip iterate ----" << std::endl;
    SkipArrayListIterator<int> it(&l, step, init_pos);
    while (it.HasNext()) {
        std::cout << it.Next() << ",";
    }
    std::cout << std::endl;

    while (it.HasPrevious()) {
        std::cout << it.Previous() << ",";
    }
    std::cout << std::endl;
}

void FilterIterate(ArrayList<int>& l, const std::function<bool(const int&)>& pred) {
    std::cout << "---- filter iterate ----" << std::endl;
    FilterArrayListIterator<int> it(&l, pred);
    while (it.HasNext()) {
        std::cout << it.Next() << ",";
    }
    std::cout << std::endl;

    while (it.HasPrevious()) {
        std::cout << it.Previous() << ",";
    }
    std::cout << std::endl;
}

void RandomIterate(ArrayList<int>& l) {
    std::cout << "---- random iterate ----" << std::endl;
    RandomArrayListIterator<int> it(&l);
    while (it.HasNext()) {
        std::cout << it.Next() << ",";
    }
    std::cout << std::endl;

    while (it.HasPrevious()) {
        std::cout << it.Previous() << ",";
    }
    std::cout << std::endl;
}

template <typename List, typename Iterator>
void TestIterator() {
    List l;
    IterateList<List, Iterator>(l);
    for (int i = 0; i < 10; i++) {
        l.PushBack(i);
        IterateList<List, Iterator>(l);
    }
    ScaleList<List, Iterator>(l, 2);
    while (!l.IsEmpty()) {
        l.PopBack();
        IterateList<List, Iterator>(l);
    }
}

void TestSpecialIterator() {
    ArrayList<int> l;
    SkipIterate(l, 2, 1);
    FilterIterate(l, [](const auto v){ return v % 3; });
    RandomIterate(l);
    for (int i = 0; i < 10; i++) {
        l.PushBack(i);
        SkipIterate(l, 2, 1);
        FilterIterate(l, [](const auto v){ return v % 3; });
        RandomIterate(l);
    }
    while (!l.IsEmpty()) {
        l.PopBack();
        SkipIterate(l, 2, 1);
        FilterIterate(l, [](const auto v){ return v % 3; });
        RandomIterate(l);
    }
}

int main() {
    TestIterator<ArrayList<int>, ArrayListIterator<int>>();
    TestIterator<LinkList<int>, LinkListIterator<int>>();
    TestSpecialIterator();
}
