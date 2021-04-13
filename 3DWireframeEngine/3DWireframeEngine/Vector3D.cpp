#include "Vector3D.h"

// Defalt constructor
CVector3D::CVector3D()
{
}

// Constructor
CVector3D::CVector3D(float x, float y, float z)
{
	m_x = x;
	m_y = y;
	m_z = z;
}

// Destructor
CVector3D::~CVector3D()
{
}

// X getter
float CVector3D::getX() const
{
	return m_x;
}

// Y getter
float CVector3D::getY() const
{
	return m_y;
}

// Z getter
float CVector3D::getZ() const
{
	return m_z;
}

// X setter
void CVector3D::setX( float x )
{
	m_x = x;
}

// Y setter
void CVector3D::setY( float y )
{
	m_z = y;
}

// Z setter
void CVector3D::setZ( float z )
{
	m_z = z;
}

// Operator -
CVector3D CVector3D::operator-() const
{
	return CVector3D( -m_x, -m_y, -m_z);
}

// Operator +
CVector3D CVector3D::operator+() const
{
	return *this;
}

// Operator +=
CVector3D& CVector3D::operator+=(CVector3D& other)
{
	m_x += other.getX();
	m_y += other.getY();
	m_z += other.getZ();
	return *this;
}

// Operator -=
CVector3D& CVector3D::operator-=(CVector3D& other)
{
	m_x -= other.getX();
	m_y -= other.getY();
	m_z -= other.getZ();
	return *this;
}

// Operator *=
CVector3D& CVector3D::operator*=(float factor)
{
	m_x *= factor;
	m_y *= factor;
	m_z *= factor;
	return *this;
}

// Operator /=
CVector3D& CVector3D::operator/=(float factor)
{
	m_x /= factor;
	m_y /= factor;
	m_z /= factor;
	return *this;
}

// Operator +
CVector3D& CVector3D::operator+(CVector3D& other) const
{
	CVector3D out = *this;
	out += other;
	return out;
}

// Operator -
CVector3D& CVector3D::operator-(CVector3D& other) const
{
	CVector3D out = *this;
	out -= other;
	return out;
}

// Operator *
CVector3D& CVector3D::operator*(float factor) const
{
	CVector3D out = *this;
	out *= factor;
	return out;
}

// Operator /
CVector3D& CVector3D::operator/(float factor) const
{
	CVector3D out = *this;
	out /= factor;
	return out;
}
