#pragma once

template<class T>
class IContainer
{   
public:
    struct Iterator
    {
        // Iterator begin();
        // Iterator end();
        // virtual T& operator*() = 0;
        // virtual T get() = 0;
        virtual ~Iterator() = default;
    };

    IContainer() : _size(0) {}

    virtual void pushBack(T&& value) = 0;
    virtual void pushBack(const T& value) = 0;

    virtual void insert(size_t pos, T value) = 0;
    virtual void erase(size_t pos) = 0;
    
    // проблема тут:
    //virtual void erase(const IContainer<size_t>& poses) = 0;
    virtual T& operator[](size_t pos) = 0;
    virtual const T& operator[](size_t pos) const = 0;

    size_t size() const { return _size; }
    
    virtual ~IContainer() = default;

protected:
    size_t _size;
};

template class IContainer<size_t>;

template<class T>
std::ostream& operator<<(std::ostream& os, const IContainer<T>& container)
{
    //for (auto el = container.begin(); el != container.end(); ++el)
    for (int i = 0; i < container.size(); ++i)
        os << container[i] << " ";
    return os;
}