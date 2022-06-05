
#pragma once
#include "container.hpp"

template<class T>
class Vector : public IContainer<T>
{
public:
    using IContainer<T>::_size;
    using typename IContainer<T>::Iterator;

    //T& Iterator::operator*() { return Vector::operator*(_pos); }
    //const T& Iterator::operator*() const { return Vector::operator*(_pos); }

    friend class Iterator;

    Vector() : _capacity{0}, _expanseCoef{1.5}, _region{nullptr} {}
    ~Vector () override
    {
        if (_region)
            delete [] _region;
    }

    Iterator begin() { return Iterator(&(_region[0])); }
    Iterator end() { return Iterator(&(_region[_size - 1])); }

    // ERROR: cannot define member function ‘IContainer<T>::Iterator::operator++’ within ‘Vector<T>’
    Iterator& Iterator::operator++() override {}

    // typename IContainer<T>::Iterator
    void pushBack(const T& value) override
    {
        auto copy = value;
        pushBack(std::move(copy));
    }

    // typename IContainer<T>::Iterator
    void pushBack(T&& value) override
    {
        if (_size + 1 >= _capacity)
            expand();
        
        _region[_size++] = std::move(value);
    }

    void insert(size_t pos, T value) override
    {
        if (_size + 1 >= _capacity)
            expand();
        
        for (size_t i = _size - 1; i >= pos && i != size_t(-1); --i)
            _region[i + 1] = _region[i];
        
        _region[pos] = value;

        _size++;
    }

    void erase(size_t pos) override
    {
        for (auto i = pos + 1; i < _size; ++i)
            _region[i] = _region[i + 1];

        _size--;
    }

    const T& operator[](size_t pos) const override
    {
        return _region[pos];
    }

    T& operator[](size_t pos) override
    {
        return _region[pos];
    }

    void expand()
    {
        reserve(std::max(_size, 1ul) * _expanseCoef);
    }

private:
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
    
    size_t _capacity;
    const double _expanseCoef;
    T* _region;
};