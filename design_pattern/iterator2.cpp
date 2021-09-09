#include <cstddef>
#include <iostream>
#include <algorithm>

template <typename T>
class IList {
public:
    virtual ~IList() {}

    virtual void PushBack(const T& value) = 0;
    virtual void PopBack() = 0;
    virtual std::size_t Size() const = 0;
    virtual bool IsEmpty() const = 0;
};

template <typename T>
class ArrayList : public IList<T> {
public:
    class ArrayListRIterator;
    class ArrayListIterator {
        friend class ArrayListRIterator;
    public:
        ArrayListIterator(ArrayList<T>* l, std::size_t pos)
            : list_(l), pos_(pos) {}
        ArrayListIterator(const ArrayListIterator& it)
            : list_(it.list_), pos_(it.pos_) {}

        T* operator->() { return &list_->data_[pos_]; }
        const T* operator->() const { return &list_->data_[pos_]; }
        T& operator*() { return list_->data_[pos_]; }
        const T& operator*() const { return list_->data_[pos_]; }

        ArrayListIterator& operator++() {
            pos_++;
            return *this;
        }
        ArrayListIterator operator++(int) {
            ArrayListIterator it(*this);
            ++*this;
            return it;
        }
        ArrayListIterator& operator--() {
            pos_--;
            return *this;
        }
        ArrayListIterator operator--(int) {
            ArrayListIterator it(*this);
            --*this;
            return it;
        }

        bool operator==(const ArrayListIterator& other) {
            return list_ == other.list_ && pos_ == other.pos_;
        }
        bool operator!=(const ArrayListIterator& other) {
            return !operator==(other);
        }

    private:
        ArrayList<T>* list_;
        std::size_t pos_;
    };

    class ArrayListRIterator {
    public:
        ArrayListRIterator(ArrayList<T>* l, std::size_t pos)
            : list_(l), pos_(pos) {}
        ArrayListRIterator(const ArrayListRIterator& it)
            : list_(it.list_), pos_(it.pos_) {}

        ArrayListRIterator(const ArrayListIterator& it)
            : list_(it.list_), pos_(it.pos_) {}

        T* operator->() { return &list_->data_[pos_ - 1]; }
        const T* operator->() const { return &list_->data_[pos_ - 1]; }
        T& operator*() { return list_->data_[pos_ - 1]; }
        const T& operator*() const { return list_->data_[pos_ - 1]; }

        ArrayListRIterator& operator++() {
            pos_--;
            return *this;
        }
        ArrayListRIterator operator++(int) {
            ArrayListRIterator it(*this);
            ++*this;
            return it;
        }
        ArrayListRIterator& operator--() {
            pos_++;
            return *this;
        }
        ArrayListRIterator operator--(int) {
            ArrayListRIterator it(*this);
            --*this;
            return it;
        }

        bool operator==(const ArrayListRIterator& other) {
            return list_ == other.list_ && pos_ == other.pos_;
        }
        bool operator!=(const ArrayListRIterator& other) {
            return !operator==(other);
        }

    private:
        ArrayList<T>* list_;
        std::size_t pos_;
    };
    using Iterator = ArrayListIterator;
    using RIterator = ArrayListRIterator;

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

    Iterator Begin() {
        return ArrayListIterator(this, 0);
    }
    Iterator End() {
        return ArrayListIterator(this, size_);
    }
    RIterator Rbegin() {
        return ArrayListRIterator(this, size_);
    }
    RIterator Rend() {
        return ArrayListRIterator(this, 0);
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

template <typename T>
class LinkList : public IList<T> {
public:
    struct Node {
        T value;
        Node *prev, *next;
    };

public:
    class LinkListRIterator;
    class LinkListIterator {
        friend class LinkListRIterator;
    public:
        LinkListIterator(LinkList<T>* l, typename LinkList<T>::Node* c)
            : list_(l), cur_(c) {}
        LinkListIterator(const LinkListIterator& it)
            : list_(it.list_), cur_(it.cur_) {}

        T* operator->() { return &cur_->value; }
        const T* operator->() const { return &cur_->value; }
        T& operator*() { return cur_->value; }
        const T& operator*() const { return cur_->value; }

        LinkListIterator& operator++() {
            cur_ = cur_->next;
            return *this;
        }
        LinkListIterator operator++(int) {
            LinkListIterator it(*this);
            ++*this;
            return it;
        }
        LinkListIterator& operator--() {
            cur_ = cur_->prev;
            return *this;
        }
        LinkListIterator operator--(int) {
            LinkListIterator it(*this);
            --*this;
            return it;
        }

        bool operator==(const LinkListIterator& other) {
            return list_ == other.list_ && cur_ == other.cur_;
        }
        bool operator!=(const LinkListIterator& other) {
            return !operator==(other);
        }

    private:
        LinkList<T>* list_;
        typename LinkList<T>::Node* cur_;
    };

    class LinkListRIterator {
    public:
        LinkListRIterator(LinkList<T>* l, typename LinkList<T>::Node* c)
            : list_(l), cur_(c) {}
        LinkListRIterator(const LinkListRIterator& it)
            : list_(it.list_), cur_(it.cur_) {}

        LinkListRIterator(const LinkListIterator& it)
            : list_(it.list_), cur_(it.cur_) {}

        T* operator->() { return &cur_->prev->value; }
        const T* operator->() const { return &cur_->prev->value; }
        T& operator*() { return cur_->prev->value; }
        const T& operator*() const { return cur_->prev->value; }

        LinkListRIterator& operator++() {
            cur_ = cur_->prev;
            return *this;
        }
        LinkListRIterator operator++(int) {
            LinkListRIterator it(*this);
            ++*this;
            return it;
        }
        LinkListRIterator& operator--() {
            cur_ = cur_->next;
            return *this;
        }
        LinkListRIterator operator--(int) {
            LinkListRIterator it(*this);
            --*this;
            return it;
        }

        bool operator==(const LinkListRIterator& other) {
            return list_ == other.list_ && cur_ == other.cur_;
        }
        bool operator!=(const LinkListRIterator& other) {
            return !operator==(other);
        }

    private:
        LinkList<T>* list_;
        typename LinkList<T>::Node* cur_;
    };
    using Iterator = LinkListIterator;
    using RIterator = LinkListRIterator;

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

    Iterator Begin() {
        return LinkListIterator(this, head_->next);
    }
    Iterator End() {
        return LinkListIterator(this, head_);
    }
    RIterator Rbegin() {
        return LinkListRIterator(this, head_);
    }
    RIterator Rend() {
        return LinkListRIterator(this, head_->next);
    }

private:
    Node* head_ = nullptr;
    std::size_t size_ = 0;
};

template <typename List>
void IterateList(List& l) {
    std::cout << "---- iterate ----" << std::endl;
    std::for_each(l.Begin(), l.End(), [](int v){
        std::cout << v << ",";
    });
    std::cout << std::endl;

    std::for_each(l.Rbegin(), l.Rend(), [](int v){
        std::cout << v << ",";
    });
    std::cout << std::endl;
}

template <typename List>
void IterateList_2(List& l) {
    std::cout << "---- iterate 2 ----" << std::endl;
    {
        auto it = l.Begin();
        auto it_end = l.End();
        while (it != it_end) {
            std::cout << *it << ",";
            ++it;
        }
        std::cout << std::endl;
    }
    {
        if (!l.IsEmpty())
        {
            auto it = l.End();
            it--;
            auto it_begin = l.Begin();
            while (it != it_begin) {
                std::cout << *it << ",";
                --it;
            }
            std::cout << *it << ",";
            std::cout << std::endl;
        }
    }
    {
        typename List::RIterator rit(l.End());
        typename List::RIterator rit_end(l.Begin());
        while (rit != rit_end) {
            std::cout << *rit << ",";
            ++rit;
        }
        std::cout << std::endl;
    }
    {
        if (!l.IsEmpty())
        {
            typename List::RIterator rit(l.Begin());
            rit--;
            typename List::RIterator rit_begin(l.End());
            while (rit != rit_begin) {
                std::cout << *rit << ",";
                --rit;
            }
            std::cout << *rit << ",";
            std::cout << std::endl;
        }
    }
}

template <typename List>
void ScaleList(List& l, int factor) {
    for (auto it = l.Begin(); it != l.End(); ++it) {
        *it *= factor;
    }
}

template <typename List>
void TestIterator() {
    List l;
    IterateList<List>(l);
    IterateList_2<List>(l);
    for (int i = 0; i < 10; i++) {
        l.PushBack(i);
        IterateList<List>(l);
        IterateList_2<List>(l);
    }
    ScaleList<List>(l, 2);
    while (!l.IsEmpty()) {
        l.PopBack();
        IterateList<List>(l);
        IterateList_2<List>(l);
    }
}

int main() {
    TestIterator<ArrayList<int>>();
    TestIterator<LinkList<int>>();
}
