#pragma once

#include <iostream>
#include <algorithm>

template<class T>
class Vector
{
public:
    Vector() : _capacity{0}, _expanseCoef{1.5}, _region{nullptr}, _size{0} {}

    Vector(const Vector& other)
    {
        *this = other;
        std::cout << "(copy ctr)" << std::endl;
    }

    Vector(Vector&& other) noexcept
    {
        *this = std::move(other);
        std::cout << "(move ctr)" << std::endl;
    }

    Vector& operator=(const Vector& other)
    {
        const auto size = other.size();
        reserve(size);

        for (auto i = 0; i < size; ++i)
            _region[i] = other[i];

        _size = size;

        std::cout << "(copy assgn)" << std::endl;
        
        return *this;
    }

    Vector& operator=(Vector&& other) noexcept
    {
        std::swap(_region, other._region);
        _capacity = other._capacity;
        _size = other._size;

        std::cout << "(move assgn)" << std::endl;

        return *this;
    }

    ~Vector ()
    {
        if (_region)
            delete [] _region;
    }

    void pushBack(const T& value)
    {
        auto copy = value;
        pushBack(std::move(copy));
    }

    void pushBack(T&& value) 
    {
        if (_size + 1 >= _capacity)
            expand();
        
        _region[_size++] = std::move(value);
    }

    void insert(size_t pos, T value)
    {
        if (_size + 1 >= _capacity)
            expand();
        
        for (size_t i = _size - 1; i >= pos && i != size_t(-1); --i)
            _region[i + 1] = _region[i];
        
        _region[pos] = value;

        _size++;
    }

    void erase(size_t pos)
    {
        for (auto i = pos + 1; i < _size; ++i)
            _region[i] = _region[i + 1];

        _size--;
    }

    void erase(std::vector<size_t> poses)
    {
        std::sort(poses.begin(), poses.end(), std::greater<size_t>());
        for (auto p : poses)
            erase(p);
    }

    size_t size() const { return _size; }

    const T& operator[](size_t pos) const 
    {
        return _region[pos];
    }

    T& operator[](size_t pos)
    {
        return _region[pos];
    }

    void expand()
    {
        reserve(size_t(std::max(_capacity, size_t(1)) * _expanseCoef + 1));
    }

    void reserve(size_t n)
    {
        if (n <=_capacity)
            return;
        
        T* newRegion = new T[n];

        if (_region)
        {
            for (size_t i = 0; i < _size; ++i) 
                newRegion[i] = _region[i]; 
            
            delete[] _region;
        }
        _region = newRegion;
        _capacity = n;
    }

    void shrink()
    {
        T* newRegion = new T[_size];

        if (_region)
        {
            for (size_t i = 0; i < _size; ++i) 
                newRegion[i] = _region[i]; 
            
            delete [] _region; 
        }
        
        _capacity = _size;
    }

    class Iterator
    {
    public:
        Iterator(T* item) : item(item) {};
        
        T& operator*() { return *item; };
        const T& operator*() const { return *item; };

        Iterator& operator++() { item++; return this; }
        Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }

        Iterator& operator--() { item--; return this; }
        Iterator operator--(int) { Iterator tmp = *this; --(*this); return tmp; }

        bool operator==(const Iterator& other) { return this->item == other.item; }
        bool operator!=(const Iterator& other) { return this->item != other.item; }

    private:
        T* item;
    };

    class ConstIterator
    {
    public:
        ConstIterator(const T* item) : item(item) {};
        
        const T& operator*() const { return *item; };

        ConstIterator& operator++() { item++; return *this; }
        ConstIterator operator++(int) { ConstIterator tmp = *this; ++(*this); return tmp; }

        ConstIterator& operator--() { item--; return *this; }
        ConstIterator operator--(int) { ConstIterator tmp = *this; --(*this); return tmp; }

        bool operator==(const ConstIterator& other) { return this->item == other.item; }
        bool operator!=(const ConstIterator& other) { return this->item != other.item; }

    private:
        const T* item;
    };

    Iterator begin() { return Iterator(&(_region[0])); }
    Iterator end() { return Iterator(&(_region[_size])); }

    ConstIterator cbegin() const { return ConstIterator(&(_region[0])); }
    ConstIterator cend() const { return ConstIterator(&(_region[_size])); }

    friend class Iterator;
private:
    
    size_t _capacity;
    size_t _size;
    T* _region;
    const double _expanseCoef;
};

template <class T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& vector)
{
    for (auto iter = vector.cbegin(); iter != vector.cend(); ++iter)
        std::cout << *iter << " ";
    std::cout << std::endl;

    return os;
}