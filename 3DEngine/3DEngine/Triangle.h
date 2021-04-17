#pragma once

#include "Vector3D.h"
#include <array>

class CTriangle
{
private:
	std::array<CVector3D, 3> m_Points = { CVector3D() };

public:
	// Public constructor and destructor
	CTriangle(CVector3D point1, CVector3D point2, CVector3D point3);
	CTriangle(std::array<CVector3D, 3> points);
	CTriangle(CTriangle* other);
	~CTriangle();

	// Getters
	std::array<CVector3D, 3> getPoints() const;
	CVector3D getNormal() const;

	// Setters
	void setPoints(std::array<CVector3D, 3> points);
};
