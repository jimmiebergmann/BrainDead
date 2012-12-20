#ifndef __BRAINDEAD_VECTOR_HPP__
#define __BRAINDEAD_VECTOR_HPP__

#include <DataTypes.hpp>
#include <ostream>
#include <float.h>

namespace BD
{
	template <typename T>
	class Vector2
	{

	public:

		typedef const Vector2<T> V2;

		Vector2() : x(0), y(0) { }
		Vector2(T x, T y) { this->x = (T)x; this->y = (T)y; }
		Vector2(const Vector2<BD_SINT32>& v) {this->x = v.x; this->y = v.y; }
		Vector2(const Vector2<BD_FLOAT32>& v) {this->x = v.x; this->y = v.y; }
		V2 operator- (V2& v) const { return V2(x - v.x, y - v.y); }
		V2 operator- () const { return V2(-x, -y); }
		V2 operator+ (V2& v) const { return V2(x + v.x, y + v.y); }
		V2& operator+= (V2& v) { x += v.x; y += v.y; return *this; }
		V2& operator-= (V2& v) { x -= v.x; y -= v.y; return *this; }
		V2 operator* (const T v) const { return V2(x * v, y * v); }
		V2 operator* (const V2& v) const { return V2(x * v.x, y * v.y); }
		V2 operator/ (const int v) const { return V2(x / (float)v, y / (float)v); };
		V2 operator/ (const V2& v) const { return V2(x / (float)v.x, y / (float)v.y); };
		V2& operator *= (V2& v) { x *= v.x; y *= v.y; return *this; }
		V2& operator *= (const T v) { x *= v; y *= v; return *this; }
		V2& operator /= (V2& v) { x /= (float)v.x; y /= (float)v.y; return *this; }
		V2& operator /= (const T v) { x /= (float)v; y /= (float)v; return *this; }
		bool operator == (const V2& v) { return (x == v.x) && (y == v.y); }
		bool operator != (const V2& v) { return (x != v.x) || (y != v.y); }

		float Magnitude() const { return sqrt((float)((x*x) + (y*y))); };
		float Dot(const V2& v) const {	float dot = (x * v.x) + (y * v.y); if(_isnan(dot)) { return 0.0f; } return dot; };

		V2 Normalize() const { float l = Magnitude(); return V2(x / l, y / l); };
		V2 Absolute() const { return V2((float)abs(x), (float)abs(y)); }

		T x, y;

	};

	// Make it possible to print the vector
	template<typename T>
	std::ostream& operator << (std::ostream & out, Vector2<T>& vector)
	{
		return out << "[" << (float)vector.x << " ; " << (float)vector.y << "]";
	}
	template<typename T>
	std::ostream& operator << (std::ostream & out, const Vector2<T>& vector)
	{
		return out << "[" << (float)vector.x << " ; " << (float)vector.y << "]";
	}

	// Typedef some vector classes.
	typedef Vector2<BD_SINT32> Vector2i;
	typedef Vector2<BD_FLOAT32> Vector2f;

}



#endif
