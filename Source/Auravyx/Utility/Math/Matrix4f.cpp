#include "MSVC/pch.h"
#include "Auravyx/Utility/Math/Matrix4f.h"
#include <cmath>
Matrix4f::Matrix4f()
{
	setIdentity();
}


Matrix4f::~Matrix4f()
{
	
}

Matrix4f::Matrix4f(const float m00, const float m10, const float m20, const float m30,
	const float m01, const float m11, const float m21, const float m31,
	const float m02, const float m12, const float m22, const float m32,
	const float m03, const float m13, const float m23, const float m33)
{
	this->m00 = m00;
	this->m01 = m01;
	this->m02 = m02;
	this->m03 = m03;

	this->m10 = m10;
	this->m11 = m11;
	this->m12 = m12;
	this->m13 = m13;

	this->m20 = m20;
	this->m21 = m21;
	this->m22 = m22;
	this->m23 = m23;

	this->m30 = m30;
	this->m31 = m31;
	this->m32 = m32;
	this->m33 = m33;
}

Matrix4f& Matrix4f::operator*=(const Matrix4f b)
{
	m00 = m00 * b.m00 + m10 * b.m01 + m20 * b.m02 + m30 * b.m03;
	m10 = m00 * b.m10 + m10 * b.m11 + m20 * b.m12 + m30 * b.m13;
	m20 = m00 * b.m20 + m10 * b.m21 + m20 * b.m22 + m30 * b.m23;
	m30 = m00 * b.m30 + m10 * b.m31 + m20 * b.m32 + m30 * b.m33;

	m01 = m01 * b.m00 + m11 * b.m01 + m21 * b.m02 + m31 * b.m03;
	m11 = m01 * b.m10 + m11 * b.m11 + m21 * b.m12 + m31 * b.m13;
	m21 = m01 * b.m20 + m11 * b.m21 + m21 * b.m22 + m31 * b.m23;
	m31 = m01 * b.m30 + m11 * b.m31 + m21 * b.m32 + m31 * b.m33;

	m02 = m02 * b.m00 + m12 * b.m01 + m22 * b.m02 + m32 * b.m03;
	m12 = m02 * b.m10 + m12 * b.m11 + m22 * b.m12 + m32 * b.m13;
	m22 = m02 * b.m20 + m12 * b.m21 + m22 * b.m22 + m32 * b.m23;
	m32 = m02 * b.m30 + m12 * b.m31 + m22 * b.m32 + m32 * b.m33;

	m03 = m03 * b.m00 + m13 * b.m01 + m23 * b.m02 + m33 * b.m03;
	m13 = m03 * b.m10 + m13 * b.m11 + m23 * b.m12 + m33 * b.m13;
	m23 = m03 * b.m20 + m13 * b.m21 + m23 * b.m22 + m33 * b.m23;
	m33 = m03 * b.m30 + m13 * b.m31 + m23 * b.m32 + m33 * b.m33;
	return *this;
}

void Matrix4f::setIdentity()
{
	m00 = 1;
	m01 = 0;
	m02 = 0;
	m03 = 0;

	m10 = 0;
	m11 = 1;
	m12 = 0;
	m13 = 0;

	m20 = 0;
	m21 = 0;
	m22 = 1;
	m23 = 0;

	m30 = 0;
	m31 = 0;
	m32 = 0;
	m33 = 1;

	x = 0;
	y = 0;
	z = 0;
	w = 1;
}

void Matrix4f::scale(const float xS, const float yS, const float zS)
{
	m00 *= xS;
	m01 *= xS;
	m02 *= xS;
	m03 *= xS;

	m10 *= yS;
	m11 *= yS;
	m12 *= yS;
	m13 *= yS;

	m20 *= zS;
	m21 *= zS;
	m22 *= zS;
	m23 *= zS;
}

void Matrix4f::rotate(const float angle, const float x, const float y, const float z)
{
	float s = sin(toRadians(angle));
	float c = cos(toRadians(angle));
	float oc = 1.0 - c;

	m00 = oc * x * x + c;
	m01 = oc * x * y - z * s;
	m02 = oc * z * x + y * s;
	m03 = 0.0;

	m10 = oc * x * y + z * s;
	m11 = oc * y * y + c;
	m12 = oc * y * z - x * s;
	m13 = 0.0;

	m20 = oc * z * x - y * s;
	m21 = oc * y * z + x * s;
	m22 = oc * z * z + c;
	m23 = 0.0;

	m30 = 0.0;
	m31 = 0.0;
	m32 = 0.0;
	m33 = 1.0;
}

void Matrix4f::translate(const float x, const float y, const float z)
{
	m30 += x;
	m31 += y;
	m32 += z;
}

void Matrix4f::set(const Matrix4f& mat)
{
	m00 = mat.m00;
	m01 = mat.m01;
	m02 = mat.m02;
	m03 = mat.m03;

	m10 = mat.m10;
	m11 = mat.m11;
	m12 = mat.m12;
	m13 = mat.m13;

	m20 = mat.m20;
	m21 = mat.m21;
	m22 = mat.m22;
	m23 = mat.m23;

	m30 = mat.m30;
	m31 = mat.m31;
	m32 = mat.m32;
	m33 = mat.m33;
}

void Matrix4f::set(const float m00, const float m10, const float m20,
	const float m01, const float m11, const float m21,
	const float m02, const float m12, const float m22)
{
	this->m00 = m00;
	this->m01 = m01;
	this->m02 = m02;

	this->m10 = m10;
	this->m11 = m11;
	this->m12 = m12;

	this->m20 = m20;
	this->m21 = m21;
	this->m22 = m22;

	this->m30 = m30;
	this->m31 = m31;
	this->m32 = m32;
}

float Matrix4f::toRadians(const float angle)
{
	return angle / 180 * 3.14159265;
}

void Matrix4f::createProjectionMatrix(const float screenWidth, const float screenHeight, const float farPlane, const float nearPlane, const float FOV)
{
	float aspectRatio = (float)screenWidth / (float)screenHeight;
	float y_scale = (float)((float)1 / tan(toRadians(FOV / (float)2)));
	float x_scale = y_scale / aspectRatio;
	float frustum_length = farPlane - nearPlane;

	m00 = x_scale;
	m11 = y_scale;
	m22 = -((farPlane + nearPlane) / frustum_length);
	m23 = -1;
	m32 = -((2 * nearPlane * farPlane) / frustum_length);
	m33 = 0;
}

void Matrix4f::createViewMatrix(const float x, const float y, const float z, const float xRot, const float yRot, const float zRot)
{
	Matrix4f translation;
	translation.translate(-x, -y, -z);

	Matrix4f xRotation;
	xRotation.rotate(xRot, 1, 0, 0);

	Matrix4f yRotation;
	yRotation.rotate(yRot, 0, 1, 0);

	Matrix4f zRotation;
	zRotation.rotate(zRot, 0, 0, 1);

	multiply(xRotation);
	multiply(yRotation);
	multiply(zRotation);
	multiply(translation);
}

void Matrix4f::createOrthographicMatrix(const float left, const float right, const float top, const float bottom, const float nearPlane, const float farPlane)
{
	m00 = 2.0f / (right - left);
	m11 = 2.0f / (top - bottom);
	m22 = -2.0f / (farPlane - nearPlane);

	m33 = 1.0f;
}

Matrix4f Matrix4f::multiply(const Matrix4f& mat)
{
	Matrix4f ret;

	ret.m00 = m00 * mat.m00 + m10 * mat.m01 + m20 * mat.m02 + m30 * mat.m03;
	ret.m10 = m00 * mat.m10 + m10 * mat.m11 + m20 * mat.m12 + m30 * mat.m13;
	ret.m20 = m00 * mat.m20 + m10 * mat.m21 + m20 * mat.m22 + m30 * mat.m23;
	ret.m30 = m00 * mat.m30 + m10 * mat.m31 + m20 * mat.m32 + m30 * mat.m33;

	ret.m01 = m01 * mat.m00 + m11 * mat.m01 + m21 * mat.m02 + m31 * mat.m03;
	ret.m11 = m01 * mat.m10 + m11 * mat.m11 + m21 * mat.m12 + m31 * mat.m13;
	ret.m21 = m01 * mat.m20 + m11 * mat.m21 + m21 * mat.m22 + m31 * mat.m23;
	ret.m31 = m01 * mat.m30 + m11 * mat.m31 + m21 * mat.m32 + m31 * mat.m33;

	ret.m02 = m02 * mat.m00 + m12 * mat.m01 + m22 * mat.m02 + m32 * mat.m03;
	ret.m12 = m02 * mat.m10 + m12 * mat.m11 + m22 * mat.m12 + m32 * mat.m13;
	ret.m22 = m02 * mat.m20 + m12 * mat.m21 + m22 * mat.m22 + m32 * mat.m23;
	ret.m32 = m02 * mat.m30 + m12 * mat.m31 + m22 * mat.m32 + m32 * mat.m33;

	ret.m03 = m03 * mat.m00 + m13 * mat.m01 + m23 * mat.m02 + m33 * mat.m03;
	ret.m13 = m03 * mat.m10 + m13 * mat.m11 + m23 * mat.m12 + m33 * mat.m13;
	ret.m23 = m03 * mat.m20 + m13 * mat.m21 + m23 * mat.m22 + m33 * mat.m23;
	ret.m33 = m03 * mat.m30 + m13 * mat.m31 + m23 * mat.m32 + m33 * mat.m33;

	set(ret);

	return ret;
}
/*void Matrix4f::set(const Mat3& rhs)
{
	this->set(rhs.m00, rhs.m01, rhs.m02, rhs.m10, rhs.m11, rhs.m12, rhs.m20,
		rhs.m21, rhs.m22);
}*/

/*void Matrix4f::setSymmetric(const SMat3& rhs)
{
	this->setSymmetric(rhs.m00, rhs.m01, rhs.m02, rhs.m11, rhs.m12, rhs.m22);
}
*/
void Matrix4f::setSymmetric(const float a00, const float a01, const float a02,
	const float a11, const float a12, const float a22)
{
	/*this->set(a00, a01, a02,
		a01, a11, a12, 
		a02, a12, a22);*/
	this->m00 = a00;
	this->m01 = a01;
	this->m02 = a02;

	this->m10 = a01;
	this->m11 = a11;
	this->m12 = a12;


	this->m20 = a02;
	this->m21 = a12;
	this->m22 = a22;
}

void Matrix4f::setSymmetric(const Matrix4f& m)
{
	this->setSymmetric(m.m00, m.m01, m.m02, m.m11, m.m12, m.m22);
}

void Matrix4f::set(const float x, const float y, const float z)
{
	m00 = x;
	m10 = x;
	m20 = x;

	m01 = y;
	m11 = y;
	m21 = y;

	m02 = z;
	m12 = z;
	m22 = z;
}

void Matrix4f::vMulSymmetric(Vec3f& out, const Matrix4f& a, const Vec3f& v)
{
	out.x = (a.m00 * v.x) + (a.m01 * v.y) + (a.m02 * v.z);
	out.y = (a.m01 * v.x) + (a.m11 * v.y) + (a.m12 * v.z);
	out.z = (a.m02 * v.x) + (a.m12 * v.y) + (a.m22 * v.z);
}

Matrix4f& operator*(const Matrix4f a, const Matrix4f b)
{
	Matrix4f m = a;
	m *= b;
	return m;
}
