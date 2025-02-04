#include "MSVC/pch.h"
#include "Auravyx/Utility/Math/Vec3f.h"
#include "Auravyx/Utility/Math/M.h"
#include <cmath>

Vec3f::Vec3f(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vec3f::~Vec3f()
{
}

float Vec3f::getX()
{
	return x;
}

float Vec3f::getY()
{
	return y;
}

float Vec3f::getZ()
{
	return z;
}

void Vec3f::add(const float xN, const float yN, const float zN)
{
	x += xN;
	y += yN;
	z += zN;
}

Vec3f Vec3f::add(Vec3f& a, const Vec3f& b)
{
	a.add(b);
	return a;
}

void Vec3f::add(const Vec3f& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
}

void Vec3f::subtract(const float x, const float y, const float z)
{
	this->x -= x;
	this->y -= y;
	this->z -= z;
}

Vec3f Vec3f::subtract(const Vec3f& sub)
{
	Vec3f n(x, y, z);
	n.x -= sub.x;
	n.y -= sub.y;
	n.z -= sub.z;
	return n;
}

Vec3f Vec3f::subtract(const Vec3f& sub, const Vec3f& a)
{
	Vec3f n(sub.x, sub.y, sub.z);
	n.x -= a.x;
	n.y -= a.y;
	n.z -= a.z;
	return n;
}

void Vec3f::normalize()
{
	Vec3f n = M::normalize(Vec3f(x, y, z));
	x = n.x;
	y = n.y;
	z = n.z;
}


void Vec3f::cross(const Vec3f& a, const Vec3f& b)
{
	x = a.y * b.z - a.z * b.y;
	y = a.x * b.z - a.z * b.x;
	z = a.x * b.y - a.y * b.x;
}

void Vec3f::divide(const float d)
{
	this->x /= d;
	this->y /= d;
	this->z /= d;
}

void Vec3f::multiply(const float m)
{
	x *= m;
	y *= m;
	z *= m;
}

Vec3f Vec3f::multiply(const Vec3f& v, const float m)
{
	return Vec3f(v.x * m, v.y * m, v.z * m);
}

Vec3f Vec3f::absolute()
{
	return Vec3f(abs(x), abs(y), abs(z));
}

Vec3f Vec3f::absolute(const Vec3f& v)
{
	return Vec3f(abs(v.x), abs(v.y), abs(v.z));
}

float Vec3f::length()
{
	return sqrt(x*x + y*y + z*z);
}

void Vec3f::set(const Vec3f& v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
}

float Vec3f::dot(const Vec3f& a, const Vec3f& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3f Vec3f::mod(const Vec3f& a, const int mod)
{
	return Vec3f((int) a.x % mod, (int) a.y % mod, (int) a.z % mod);
}

Vec3f& Vec3f::operator+=(const Vec3f b)
{
	this->x += b.x;
	this->y += b.y;
	this->z += b.z;
	return *this;
}
Vec3f& Vec3f::operator-=(const Vec3f b)
{
	this->x -= b.x;
	this->y -= b.y;
	this->z -= b.z;
	return *this;
}
Vec3f& Vec3f::operator*=(const Vec3f b)
{
	this->x *= b.x;
	this->y *= b.y;
	this->z *= b.z;
	return *this;
}
Vec3f& Vec3f::operator/=(const Vec3f b)
{
	this->x /= b.x;
	this->y /= b.y;
	this->z /= b.z;
	return *this;
}

Vec3f& Vec3f::operator+=(const float b)
{
	this->x += b;
	this->y += b;
	this->z += b;
	return *this;
}
Vec3f& Vec3f::operator-=(const float b)
{
	this->x -= b;
	this->y -= b;
	this->z -= b;
	return *this;
}
Vec3f& Vec3f::operator*=(const float b)
{
	this->x *= b;
	this->y *= b;
	this->z *= b;
	return *this;
}
Vec3f& Vec3f::operator/=(const float b)
{
	this->x /= b;
	this->y /= b;
	this->z /= b;
	return *this;
}

Vec3f operator+(const Vec3f a, const Vec3f b)
{
	return Vec3f(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vec3f operator-(const Vec3f a, const Vec3f b)
{
	return Vec3f(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vec3f operator*(const Vec3f a, const Vec3f b)
{
	return Vec3f(a.x * b.x, a.y * b.y, a.z * b.z);
}

Vec3f operator/(const Vec3f a, const Vec3f b)
{
	return Vec3f(a.x / b.x, a.y / b.y, a.z / b.z);
}

Vec3f operator+(const Vec3f a, const float b)
{
	return Vec3f(a.x + b, a.y + b, a.z + b);
}

Vec3f operator-(const Vec3f a, const float b)
{
	return Vec3f(a.x - b, a.y - b, a.z - b);
}

Vec3f operator*(const Vec3f a, const float b)
{
	return Vec3f(a.x * b, a.y * b, a.z * b);
}

Vec3f operator/(const Vec3f a, const float b)
{
	return Vec3f(a.x / b, a.y / b, a.z / b);
}
