#pragma once

#include "Matrix4.h"

class CVector3D
{
public:
	// 3D coordinates
	float m_x = 0.0f;
	float m_y = 0.0f;
	float m_z = 0.0f;

public:
	// Public constructor and destructor
	CVector3D();
	CVector3D(float x, float y, float z);
	~CVector3D();

public:
	// Operators
	CVector3D operator- () const;
	CVector3D operator+ () const;

	CVector3D& operator += (CVector3D& other);
	CVector3D& operator -= (CVector3D& other);
	CVector3D& operator *= (float factor);
	CVector3D& operator /= (float factor);

	CVector3D& operator + (CVector3D& other) const;
	CVector3D& operator - (CVector3D& other) const;
	CVector3D& operator * (float factor) const;
	CVector3D& operator / (float factor) const;

	CVector3D& operator *= (CMatrix4 mat);
	CVector3D operator * (CMatrix4 mat) const;
};
