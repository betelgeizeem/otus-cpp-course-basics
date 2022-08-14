#pragma once

#include <vector>
#include <iostream>
#include <algorithm>

template<class T>
class BidirectionalList
{
public:
    BidirectionalList() : _first{nullptr}, _last{nullptr}, _size{0} {}

    BidirectionalList(const BidirectionalList& other)
    {
        *this = other;

        std::cout << "(copy ctr)" << std::endl;
    }

    BidirectionalList(BidirectionalList&& other) noexcept
    {
        *this = std::move(other);

        std::cout << "(move ctr)" << std::endl;
    }

    BidirectionalList& operator=(const BidirectionalList& other)
    {
        clear(); 

        for (const auto& item : other)
            pushBack(item);

        std::cout << "(copy assgn)" << std::endl;
    }

    BidirectionalList& operator=(BidirectionalList&& other) noexcept
    {
        std::swap(_first, other._first); 
        std::swap(_last, other._last);
        _size = other._size;

        std::cout << "(move assgn)" << std::endl;

        return *this;
    }

    ~BidirectionalList()
    {
        for (auto node = _first; node != nullptr; )
        {
            auto nodeToRemove = node;
            node = node->next;
            delete nodeToRemove;
        }
    }

    void pushBack(const T& value) 
    {
        auto copy = value;
        pushBack(std::move(copy));
    }

    void pushBack(T&& value) 
    {
        auto node = addNode(_size);
        node->_data = std::move(value);
    }

    void insert(size_t pos, T value) 
    {
        auto node = addNode(pos);
        if (node)
            node->_data = value;
    }

    void erase(size_t pos) 
    {
        auto node = getNode(pos);
        if (!node)
            return;
        
        erase(node);
    }

    void erase(std::vector<size_t> poses)
    {
        std::sort(poses.begin(), poses.end(), std::greater<size_t>());
        for (auto p : poses)
            erase(p);
    }

    size_t size() const { return _size; }

    T& operator[](size_t pos)
    {
        return getNode(pos)->_data;
    }

    const T& operator[](size_t pos) const
    {
        return getNode(pos)->data();
    }

    void clear()
    {
        for (auto node = _first; node != nullptr; )
        {
            auto nodeToRemove = node;
            node = node->next;
            delete nodeToRemove;
            _size--;
        }

        _first = nullptr;
        _last = nullptr;
    }

    class Iterator
    {
    public:
        Iterator(typename BidirectionalList::Node* node) : node(node) {};
        
        T& operator*() { return node->_data; };
        const T& operator*() const { return node->data(); };

        Iterator& operator++() { node = node->next; return this; }
        Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }

        Iterator& operator--() { node = node->prev; return this; }
        Iterator operator--(int) { Iterator tmp = *this; --(*this); return tmp; }

        bool operator==(const Iterator& other) { return this->node == other.node; }
        bool operator!=(const Iterator& other) { return this->node != other.node; }

    private:
        typename BidirectionalList::Node* node;
    };

    class ConstIterator
    {
    public:
        ConstIterator(const typename BidirectionalList::Node* node) : node(node) {};
        
        const T& operator*() const { return node->_data; };

        ConstIterator& operator++() { node = node->next; return *this; }
        ConstIterator operator++(int) { ConstIterator tmp = *this; ++(*this); return tmp; }

        ConstIterator& operator--() { node = node->prev; return *this; }
        ConstIterator operator--(int) { ConstIterator tmp = *this; --(*this); return tmp; }

        bool operator==(const ConstIterator& other) { return this->node == other.node; }
        bool operator!=(const ConstIterator& other) { return this->node != other.node; }

    private:
        const typename BidirectionalList::Node* node;
    };

    Iterator begin() { return Iterator(_first); }
    Iterator end() { return Iterator(_last->next); }

    ConstIterator cbegin() const { return ConstIterator(_first); }
    ConstIterator cend() const { return ConstIterator(_last->next); }

    friend class Iterator;
private:
    struct Node 
    {
        Node* next; 
        Node* prev; 
        T _data; 
        const T& data() const { return _data; };
    };

    Node* getNode(size_t pos) const
    {
        if (pos >= _size)
            return nullptr;

        auto node = _first;
        for (auto i = 0; i < pos; ++i)
            node = node->next;
        return node;
    }

    void link(Node* node1, Node* node2)
    {
        if (node1)
            node1->next = node2;
        if (node2)
            node2->prev = node1;
    }

    Node* addNode(size_t pos)
    {
        if (pos > _size)
            return nullptr;

        auto node = newNode();

        if (pos == 0)
        {
            link(nullptr, node);
            link(node, _first);
            _first = node;
        }
        
        if (pos == _size)
        {
            link(_last, node);
            link(node, nullptr);
            _last = node;    
        } 
        
        if (0 < pos && pos < _size)
        {
            auto oldNodeThis = getNode(pos);
            auto oldNodePrev = oldNodeThis->prev;
            
            link(oldNodePrev, node);
            link(node, oldNodeThis);
        }

        _size++;
      
        return node;
    }

    Node* newNode()
    {
        return new Node{};
    }

    void erase(Node* node)
    {
        if (!node)
            return;
        
        auto next = node->next;
        auto prev = node->prev;

        if (node == _first)
            _first = next;
        else if (node == _last)
            _last = prev;

        delete node; 
        _size--;

        link(prev, next);
    }

    Node* _first;
    Node* _last;

    size_t _size;
};

template <class T>
std::ostream& operator<<(std::ostream& os, const BidirectionalList<T>& list)
{
    for (auto iter = list.cbegin(); iter != list.cend(); ++iter)
        std::cout << *iter << " ";
    std::cout << std::endl;

    return os;
}