#pragma once
#include "container.hpp"

template<class T>
class BidirectionalList : public IContainer<T>
{
public:
    using IContainer<T>::_size;
    using typename IContainer<T>::Iterator;

    BidirectionalList() : _first{nullptr}, _last{nullptr} {}
    ~BidirectionalList() override
    {
        for (auto node = _first; node != nullptr; )
        {
            auto nodeToRemove = node;
            node = node->next;
            delete nodeToRemove;
        }
    }

    Iterator begin() { return Iterator(&(getNode(0)->_data)); }
    Iterator end() { return Iterator(&(getNode(_size-1)->_data)); }

    // ERROR: cannot define member function ‘IContainer<T>::Iterator::operator++’ within ‘BidirectionalList<T>’
    Iterator& Iterator::operator++() override {}

    void pushBack(const T& value) override
    {
        auto copy = value;
        pushBack(std::move(copy));
    }

    void pushBack(T&& value) override
    {
        auto node = addNode(_size);
        node->_data = std::move(value);
    }

    void insert(size_t pos, T value) override
    {
        auto node = addNode(pos);
        if (node)
            node->_data = value;
    }

    void erase(size_t pos) override
    {
        auto node = getNode(pos);
        if (!node)
            return;
        
        erase(node);
    }

    // void erase(const IContainer<size_t>& poses) override
    // {
    //     List<Node*> nodes;

    //     for (auto i = 0; i < poses.size(); ++i)
    //     {
    //         nodes.pushBack(getNode(poses[i]));
    //     }
        
    //     for (auto i = 0; i < poses.size(); ++i)
    //     {
    //         erase(nodes[i]);
    //     }
    // }

    T& operator[](size_t pos) override
    {
        return getNode(pos)->_data;
    }

    const T& operator[](size_t pos) const override
    {
        return getNode(pos)->data();
    }

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
};