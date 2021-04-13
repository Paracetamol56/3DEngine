#include "Vector3D.h"

CVector3D::CVector3D(float x, float y, float z)
{
	m_x = x;
	m_y = y;
	m_z = z;
}

CVector3D::~CVector3D()
{
}

float CVector3D::getX()
{
	return m_x;
}

float CVector3D::getY()
{
	return m_y;
}

float CVector3D::getZ()
{
	return m_z;
}

void CVector3D::setX( float x )
{
	m_x = x;
}

void CVector3D::setY( float y )
{
	m_z = y;
}

void CVector3D::setZ( float z )
{
	m_z = z;
}
