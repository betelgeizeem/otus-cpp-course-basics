#pragma once

template<class T>
class IContainer
{   
public:
// Проблема 1. Я хочу сделать базовый класс итератора:
    struct Iterator
    {
        T& operator*() { return *pointer(); };
        const T& operator*() const { return *pointer(); };

        // Мне надо доопределить в наследнике это:
        virtual Iterator& operator++() = 0;

        Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }

        bool operator==(const Iterator& other) { return this->pointer() == other.pointer(); }
        bool operator!=(const Iterator& other) { return this->pointer() != other.pointer(); }
    protected:
        // ... и вот это:
        virtual const T* pointer() const = 0;
        virtual T* pointer() = 0;
    };
    // Что делать в наследниках? 

    IContainer() : _size(0) {}

    virtual void pushBack(T&& value) = 0;
    virtual void pushBack(const T& value) = 0;

    virtual void insert(size_t pos, T value) = 0;
    virtual void erase(size_t pos) = 0;
    
    virtual Iterator begin() = 0;
    virtual Iterator end() = 0;

    // Проблема 2. Как мне сделать вот такое? Бесконечное инстанцирование шаблона, если функцию объявить так:
    //virtual void erase(const IContainer<size_t>& poses) = 0;
    virtual T& operator[](size_t pos) = 0;
    virtual const T& operator[](size_t pos) const = 0;

    size_t size() const { return _size; }
    
    virtual ~IContainer() = default;

protected:
    size_t _size;
};

template<class T>
std::ostream& operator<<(std::ostream& os, IContainer<T>& container)
{
    //for (int i = 0; i < container.size(); ++i)
        //os << container[i] << " ";
    for (auto iter = container.begin(); iter != container.end(); ++iter)
        std::cout << *iter << std::endl;
    return os;
}