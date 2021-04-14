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

// Operator *= a 4x4 matrix
CVector3D& CVector3D::operator*=(CMatrix4 mat)
{
	m_x = m_x * mat.getMatrixAt(0, 0) + m_y * mat.getMatrixAt(1, 0) + m_z * mat.getMatrixAt(2, 0) + mat.getMatrixAt(3, 0);
	m_y = m_x * mat.getMatrixAt(0, 1) + m_y * mat.getMatrixAt(1, 1) + m_z * mat.getMatrixAt(2, 1) + mat.getMatrixAt(3, 1);
	m_z = m_x * mat.getMatrixAt(0, 2) + m_y * mat.getMatrixAt(1, 2) + m_z * mat.getMatrixAt(2, 2) + mat.getMatrixAt(3, 2);
	float w = m_x * mat.getMatrixAt(0, 3) + m_y * mat.getMatrixAt(1, 3) + m_z * mat.getMatrixAt(2, 3) + mat.getMatrixAt(3, 3);

	if (w != 0.0f)
	{
		m_x /= w; m_y /= w; m_z /= w;
	}
	return *this;
}

// Operator * a 4x4 matrix
CVector3D CVector3D::operator*(CMatrix4 mat) const
{
	CVector3D out = *this;
	out *= mat;
	return out;
}
