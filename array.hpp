#ifndef __ARRAY_HPP__
#define __ARRAY_HPP__

#include <algorithm>
#include <initializer_list>
#include <stdexcept>
#include <utility>

namespace uti {

template<class T>
class Array
{
private:
    size_t size_ = 0;
    size_t capacity_ = 10;
    T* data_ = new T[capacity_];

public:
    Array()
    {
    }
    Array(size_t sz)
        : size_(sz)
        , capacity_(size_ * 2)
        , data_(new T[capacity_])
    {
    }
    Array(const Array& other) : Array(other.size_)
    {
        std::copy(other.data_, other.data_ + other.size_, data_);
    }
    Array(Array&& other) noexcept
        : size_(other.size_)
        , data_(other.data_)
    {
        other.size_ = 0;
        other.data_ = nullptr;
    }
    Array(std::initializer_list<T> il) : Array(il.size())
    {
        std::copy(il.begin(), il.end(), data_);
    }
    Array& operator=(Array other)
    {
        std::swap(size_, other.size_);
        std::swap(data_, other.data_);
        return *this;
    }
    ~Array() noexcept
    {
        delete[] data_;
    }

    T& operator[](size_t i)
    {
        if (i >= size_)
            throw std::out_of_range("index out of range.");
        return data_[i];
    }
    size_t size() const
    {
        return size_;
    }
    size_t capacity() const
    {
        return capacity_;
    }
    void push_back(const T& val)
    {
        if (size_ == capacity_)
            return;
        data_[size_] = val;
        ++size_;
    }

    class iterator
    {
        T* elem = nullptr;
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        iterator(pointer e)
            : elem(e)
        {
        }
        iterator& operator++()
        {
            elem++;
            return *this;
        }
        iterator operator++(int)
        {
            iterator rval = *this;
            ++(*this);
            return rval;
        }
        bool operator==(iterator other) const
        {
            return elem == other.elem;
        }
        bool operator!=(iterator other) const
        {
            return !(*this == other);
        }
        reference operator*() const
        {
            return *elem;
        }
        reference operator->() const
        {
            return *elem;
        }
    };
    iterator begin()
    {
        return iterator(data_);
    }
    iterator end()
    {
        return iterator(data_ + size_);
    }
};

}

#endif /* __ARRAY_HPP__ */
