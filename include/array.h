#pragma once
#include <iostream>
#include <concepts>
#include <memory>
#include <assert.h>

template <class T>
concept Arrayable = std::is_default_constructible<T>::value;

template <Arrayable T>
class Array
{
private:
    size_t size;
    size_t capacity;
    std::shared_ptr<T[]> data;

    void resize(){
        capacity *= 2;

        std::shared_ptr<T[]> new_data(new T[capacity]);

        for(size_t i = 0; i < size; ++i){
            new_data[i] = std::move(data[i]);
        }

        data = std::move(new_data);
    }

public:
    Array(){
        size = 0;
        capacity = 10;
        data = std::shared_ptr<T[]>(new T[capacity]);
    }

    Array(size_t capacity_){
        size = 0;
        capacity = capacity_;
        data = std::shared_ptr<T[]>(new T[capacity]);
    }

    Array(const std::initializer_list<T>& initialValues){
        size = 0;
        capacity = initialValues.size();
        data = std::shared_ptr<T[]>(new T[capacity]);

        for(auto&& elem: initialValues){
            data[size++] = std::move(elem);
        }
    }

    Array(const Array& other){
        this->size = other.size;
        this->capacity = other.capacity;
        this->data = std::shared_ptr<T[]>(new T[this->capacity]);

        for(size_t i = 0; i < other.size; ++i){
            this->data[i] = other.data[i];
        }
    }


    Array(Array&& other) noexcept{
        this->size = other.size;
        this->capacity = other.capacity;
        this->data = std::move(other.data);

        other.size = 0;
        other.capacity = 0;
    }

    void push_back(T&& elem){
        if(size >= capacity){
            resize();
        }
        data[size++] = std::move(elem);
    }

    void push_back(const T& value) {
        if (size >= capacity) {
            resize();
        }
        data[size++] = value;
    }

    void remove(size_t index){
        if(index >= size){
            throw std::out_of_range("Index out of range");
        }

        for(size_t i = index + 1; i < size; ++i){
            data[i-1] = std::move(data[i]);
        }
        --size;
    }

    T& operator[](size_t index) {
        if (index >= size){
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    size_t getsize() const {return size;}
};