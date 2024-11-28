#include <iostream>
/// Custom Container Class

template<typename  U>
struct Node{
    U _value;
    Node<U> *_next;
    Node(const U &newVal):_next(nullptr), _value(newVal) {}
};

template<class T>
class Iterator {
Node<T> *m_Node;

public:
    Iterator(Node<T>* Node) : m_Node(Node) {};

    bool operator==(const Iterator& other)
    {
        return this == &other || m_Node == other.m_Node;
    }

    bool operator!=(const Iterator& other)
    {
        return !operator==(other);
    }
    T operator*()
    {
    if (m_Node)
        {
            return m_Node->_value;
        }
        return T();
    }

    Iterator operator++()
    {
        Iterator i = *this;
        if (m_Node)
        {
            m_Node = m_Node->_next;
        }
        return i;
    }
};

template<class T, class Allocator = std::allocator<T>>
class Container{

using node_alloc_t = typename std::allocator_traits<Allocator>::
    template rebind_alloc<Node<T>>;

node_alloc_t node_alloc;

public:
    Container<T, Allocator>():_size(0){}

    Iterator<T> begin() const
    {
        return Iterator<T>(_first);
    }
    Iterator<T> end() const
    {
        return Iterator<T>(nullptr);
    }

    Node<T>* _first = nullptr;
    Node<T>* _last = nullptr;

    Iterator<T> push_back(const T&object)
    {
        return Add(object);
    }

    Iterator<T> Add(const T&object)
    {
        _size++;

        Node<T>* newNode = node_alloc.allocate(1);
        node_alloc.construct(newNode, Node<T>(object));

        if(!_first)
            _first = newNode;
        
        newNode->_next = nullptr;
        newNode->_value = object;
        if(_last)
        {
            _last->_next = newNode;
        }
        _last = newNode;
        return Iterator<T>(_last);
    }        
    void remove(size_t index)
    {

    }
    bool empty()
    {
        return !!_size;
    }
    size_t size()
    {
        return _size;
    }
    void clear()
    {
        Node<T> *first = _first;
		Node<T> *next;

		while (first) {
			next = first->_next;
			node_alloc.destroy(first);
			first = next;
		}
        node_alloc.deallocate(_first, _size);
		
        _first = nullptr;
		_last = nullptr;		

		_size = 0;
    }

private:
    size_t _size;
    Allocator _alloc;
};