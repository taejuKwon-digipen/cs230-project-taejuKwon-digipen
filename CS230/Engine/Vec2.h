/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Vec2.h
Author: Taeju Kwon
Creation date: 2021.03.15
-----------------------------------------------------------------*/
#pragma once

#include <cmath>
#include <limits>
#include <iostream>

using namespace std;

namespace math
{
    [[nodiscard]] constexpr double abs(double d) noexcept { return (d < 0.0) ? -d : d; }

    [[nodiscard]] constexpr bool is_equal(double d1, double d2) noexcept
    {
        return abs(d1 - d2) <= std::numeric_limits<double>::epsilon() * abs(d1 + d2);
    }

    [[nodiscard]] constexpr bool is_equal(int i1, int i2) noexcept { return i1 == i2; }

    struct [[nodiscard]] vec2
    {
        double x, y;
    	

        constexpr vec2() noexcept : vec2(0, 0) {};
        constexpr vec2(double _x, double _y) noexcept : x(_x), y(_y) {};
        constexpr vec2(double val) noexcept : vec2(val, val) {};
        constexpr vec2(const vec2& v) = default;

        constexpr vec2& operator += (const vec2& rhs) noexcept;
        constexpr vec2& operator -= (const vec2& rhs) noexcept;
        constexpr vec2& operator *= (double scale) noexcept;
        constexpr vec2& operator /= (double scale) noexcept;
        constexpr vec2 operator*(double rhs) noexcept;
        constexpr vec2 operator/ (double rhs) noexcept;


        constexpr double LengthSquared() noexcept;
        vec2 Normalize() noexcept;

    };
    constexpr vec2 operator+(const vec2& lhs, const vec2& rhs) noexcept;
    constexpr vec2 operator-(const vec2& lhs, const vec2& rhs) noexcept;
    constexpr vec2 operator-(const vec2& rhs) noexcept;
    constexpr vec2 operator*(double lhs, const vec2& rhs) noexcept;
    constexpr bool operator==(const vec2& lhs, const vec2& rhs) noexcept;
    constexpr bool operator!=(const vec2& lhs, const vec2& rhs) noexcept;


    struct ivec2
    {
        int x, y;
    	
        constexpr ivec2() noexcept : ivec2(0, 0) {};
        constexpr ivec2(int _x, int _y) noexcept : x(_x), y(_y) {};
        constexpr ivec2(int val) noexcept : ivec2(val, val) {};
        constexpr ivec2(const ivec2& v) = default;

        constexpr ivec2& operator +=(const ivec2 rhs) noexcept;
        constexpr ivec2& operator -=(const ivec2 rhs) noexcept;
        constexpr ivec2& operator *=(const ivec2 rhs) noexcept;
        constexpr ivec2& operator /=(const ivec2 rhs) noexcept;
        constexpr ivec2 operator *(int rhs) noexcept;
        constexpr vec2 operator*(double rhs) noexcept;
        constexpr ivec2 operator/(int rhs) noexcept;
        constexpr vec2 operator/(double rhs) noexcept;

        constexpr operator vec2()
        {
            return vec2{ static_cast<double>(this->x), static_cast<double>(this->y) };
        }

    };

    constexpr ivec2 operator+ (const ivec2& lhs, const ivec2& rhs) noexcept;
    constexpr ivec2 operator- (const ivec2& lhs, const ivec2& rhs) noexcept;
    constexpr ivec2 operator- (const ivec2& rhs) noexcept;
    constexpr ivec2 operator* (int lhs, const ivec2 rhs) noexcept;
    constexpr vec2 operator* (double lhs, const ivec2& rhs) noexcept;
    constexpr bool operator == (const ivec2& lhs, const ivec2& rhs) noexcept;
    constexpr bool operator != (const ivec2& lhs, const ivec2& rhs) noexcept;
	
}
	

#include "Vec2.inl"

