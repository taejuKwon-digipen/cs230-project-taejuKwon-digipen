/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Vec2.inl
Author: Taeju Kwon
Creation date: 2021.03.15
-----------------------------------------------------------------*/
namespace math
{

    constexpr vec2& vec2::operator += (const vec2& rhs) noexcept
   {
		this->x += rhs.x;
		this->y += rhs.y;
		return *this;
   }
	
   constexpr vec2& vec2::operator -= (const vec2& rhs) noexcept
   {
	   this->x -= rhs.x;
	   this->y-= rhs.y;
	   return *this;
   }

   [[nodiscard]] constexpr vec2& vec2::operator *= (double scale) noexcept
   {
	   this->x *= scale;
	   this->y *= scale;
	   return *this;
   }
	
   [[nodiscard]] constexpr vec2& vec2::operator /= (double scale) noexcept
   {
	   this->x /= scale;
	   this->y /= scale;
	   return *this;
   }
	
   constexpr vec2 vec2::operator*(double rhs) noexcept
   {
	   this->x *= rhs;
	   this->y *= rhs;
	   return *this;
   }
	
   [[nodiscard]] constexpr vec2 vec2::operator/ (double rhs) noexcept
   {
	   this->x /= rhs;
	   this->y /= rhs;
	   return *this;
   }

   [[nodiscard]] constexpr vec2 operator+(const vec2& lhs, const vec2& rhs) noexcept
   {
	   return vec2(lhs.x + rhs.x, lhs.y + rhs.y);
   }

   [[nodiscard]] constexpr vec2 operator-(const vec2& lhs, const vec2& rhs) noexcept
   {
	   return vec2(lhs.x - rhs.x, lhs.y - rhs.y);
   }

   [[nodiscard]] constexpr vec2 operator-(const vec2& rhs) noexcept
   {
	   return vec2(-rhs.x, -rhs.y);
   }

   [[nodiscard]] constexpr vec2 operator*(double lhs, const vec2& rhs) noexcept
   {
	   return vec2(lhs * rhs.x, lhs * rhs.y);
   }

   [[nodiscard]] constexpr bool operator==(const vec2& lhs, const vec2& rhs) noexcept
   {
	   return is_equal(lhs.x, rhs.x) && is_equal(lhs.y, rhs.y);
   }

   [[nodiscard]] constexpr bool operator!=(const vec2& lhs, const vec2& rhs) noexcept
   {
	   return !(lhs == rhs);
   }

   [[nodiscard]] inline vec2 vec2::Normalize() noexcept
   {
	   x = x / sqrt(LengthSquared());
	   y = y / sqrt(LengthSquared());
	   return vec2(x, y);
   }

   [[nodiscard]] constexpr double vec2::LengthSquared() noexcept
   {
	   x = x * x;
	   y = y * y;
	   return (x + y );
   }

   [[nodiscard]] constexpr ivec2& ivec2::operator +=(const ivec2 rhs) noexcept
   {
	   this->x += rhs.x;
	   this->y += rhs.y;
	   return *this;
   }
	
   [[nodiscard]] constexpr ivec2& ivec2::operator -=(const ivec2 rhs) noexcept
   {
	   this->x -= rhs.x;
	   this->y -= rhs.y;
	   return *this;
   }
	
   [[nodiscard]] constexpr ivec2& ivec2::operator *=(const ivec2 rhs) noexcept
   {
	   this->x *= rhs.x;
	   this->y *= rhs.y;
	   return *this;
   }
	
   [[nodiscard]] constexpr ivec2& ivec2::operator /=(const ivec2 rhs) noexcept
   {
	   this->x /= rhs.x;
	   this->y /= rhs.y;
	   return *this;
   }
	
   [[nodiscard]] constexpr ivec2 ivec2::operator *(int rhs) noexcept
   {
	   this->x*= rhs;
	   this->y*= rhs;
	   return *this;
   }
	
   [[nodiscard]] constexpr ivec2 ivec2::operator/(int rhs) noexcept
   {
	   this->x /= rhs;
	   this->y /= rhs;
	   return *this;
   }

   [[nodiscard]] constexpr ivec2 operator+ (const ivec2& lhs, const ivec2& rhs) noexcept
   {
	   return ivec2(lhs.x + rhs.x, lhs.y + rhs.y);
   }
	
   [[nodiscard]] constexpr ivec2 operator- (const ivec2& lhs, const ivec2& rhs) noexcept
   {
	   return ivec2(lhs.x - rhs.x, lhs.y - rhs.y);
   }
	
   [[nodiscard]] constexpr ivec2 operator- (const ivec2& rhs) noexcept
   {
	   return ivec2(-rhs.x,-rhs.y);
   }
	
   [[nodiscard]] constexpr ivec2 operator* (int lhs, const ivec2 rhs) noexcept
   {
	   return ivec2(lhs * rhs.x, lhs * rhs.y);
   }
	
   constexpr vec2 operator* (double lhs, const ivec2& rhs) noexcept
   {
	   return vec2(lhs * rhs.x, lhs * rhs.y);
   }
	
   [[nodiscard]] constexpr bool operator == (const ivec2& lhs, const ivec2& rhs) noexcept
   {
	   return is_equal(lhs.x, rhs.x) && is_equal(lhs.y, rhs.y);
   }
	
   [[nodiscard]] constexpr bool operator != (const ivec2& lhs, const ivec2& rhs) noexcept
   {
	   return !(lhs == rhs);
   }
}
