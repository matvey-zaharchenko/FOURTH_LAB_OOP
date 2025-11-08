#pragma once

#include <concepts>

template <typename T>
concept Scalar = std::is_scalar_v<T>;

template <Scalar T>
class Point {
private:
    T x{}, y{};

public:
    Point() = default;
    Point(T _x, T _y) : x(_x), y(_y) {} 

    T get_x() const { return x; }
    T get_y() const { return y; }

    void set_x(T _x) {x = _x;}
    void set_y(T _y) {y = _y;}

    virtual ~Point() = default;
};