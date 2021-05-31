/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Vec2.inl
Project: CS230
Author: Rudy Castan
Creation date:
-----------------------------------------------------------------*/

namespace math
{
    constexpr bool vec2::operator==(const vec2& v) const noexcept { return is_equal(x, v.x) && is_equal(y, v.y); }
    constexpr bool vec2::operator!=(const vec2& v) const noexcept { return !operator==(v); }

    constexpr vec2 vec2::operator+(const vec2& v) const noexcept { return { x + v.x, y + v.y }; }
    constexpr vec2& vec2::operator+=(const vec2& v) noexcept
    {
        x += v.x;
        y += v.y;
        return *this;
    }

    constexpr vec2 vec2::operator-(const vec2& v) const noexcept { return { x - v.x, y - v.y }; }
    constexpr vec2& vec2::operator-=(const vec2& v) noexcept
    {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    constexpr vec2 vec2::operator-() const noexcept { return { -x, -y }; }

    constexpr vec2 vec2::operator*(double scale) const noexcept { return { x * scale, y * scale }; }
    constexpr vec2 vec2::operator/(double divisor) const noexcept { return { x / divisor, y / divisor }; }
    constexpr vec2& vec2::operator*=(double scale) noexcept
    {
        x *= scale, y *= scale;
        return *this;
    }
    constexpr vec2& vec2::operator/=(double divisor) noexcept
    {
        x /= divisor, y /= divisor;
        return *this;
    }
    constexpr vec2 operator*(double scale, const vec2& v) noexcept { return v * scale; }

    [[nodiscard]] inline vec2 vec2::Normalize() noexcept
    {
        x = x / sqrt(x * x);
        y = y / sqrt(y * y);
        return vec2(x, y);
    }
	
    constexpr bool ivec2::operator==(const ivec2& v) const noexcept { return is_equal(x, v.x) && is_equal(y, v.y); }
    constexpr bool ivec2::operator!=(const ivec2& v) const noexcept { return !operator==(v); }

    constexpr ivec2 ivec2::operator+(const ivec2& v) const noexcept { return { x + v.x, y + v.y }; }
    constexpr ivec2& ivec2::operator+=(const ivec2& v) noexcept {
        x += v.x;
        y += v.y;
        return *this;
    }

    constexpr ivec2 ivec2::operator-(const ivec2& v) const noexcept { return { x - v.x, y - v.y }; }
    constexpr ivec2& ivec2::operator-=(const ivec2& v) noexcept {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    constexpr ivec2 ivec2::operator-() const noexcept { return { -x, -y }; }

    constexpr ivec2 ivec2::operator*(int scale) const noexcept { return { x * scale, y * scale }; }
    constexpr ivec2 ivec2::operator/(int divisor) const noexcept { return { x / divisor, y / divisor }; }
    constexpr ivec2& ivec2::operator*=(int scale) noexcept {
        x *= scale, y *= scale;
        return *this;
    }
    constexpr ivec2& ivec2::operator/=(int divisor) noexcept {
        x /= divisor, y /= divisor;
        return *this;
    }

    constexpr vec2 ivec2::operator*(double scale) const noexcept { return { x * scale, y * scale }; }
    constexpr vec2 ivec2::operator/(double divisor) const noexcept { return { x / divisor, y / divisor }; }
    constexpr ivec2 operator*(int scale, const ivec2& v) noexcept { return v * scale; }


}