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
    size_t len = 0;
    size_t size = 10;
    T* data = new T[size];

public:
    Array()
    {
    }
    Array(size_t l)
        : len(l)
        , size(l)
        , data(new T[l])
    {
    }
    Array(const Array& other) : Array(other.size)
    {
        std::copy(other.data, other.data + other.size, data);
    }
    Array(Array&& other) noexcept
        : len(other.len)
        , size(other.size)
        , data(other.data)
    {
        other.len = 0;
        other.size = 0;
        other.data = nullptr;
    }
    Array(std::initializer_list<T> il) : Array(il.size())
    {
        std::copy(il.begin(), il.end(), data);
    }
    Array& operator=(Array other)
    {
        std::swap(len, other.len);
        std::swap(size, other.size);
        std::swap(data, other.data);
        return *this;
    }
    ~Array() noexcept
    {
        delete[] data;
    }

    T& operator[](size_t i)
    {
        if (i >= len)
            throw std::out_of_range("index out of range.");
        return data[i];
    }
    size_t Size() const
    {
        return size;
    }
    size_t Length() const
    {
        return len;
    }
};

}

#endif /* __ARRAY_HPP__ */
