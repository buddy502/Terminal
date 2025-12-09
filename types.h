#pragma once

template <typename T>
struct Vec3 {
    T x{}, y{}, z{};

    Vec3() = default;
    Vec3(T x_, T y_, T z_) : x(x_), y(y_), z(z_) {}
};
