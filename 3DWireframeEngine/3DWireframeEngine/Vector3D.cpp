#include "Vector3D.h"

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
