#pragma once

#include "Vector3D.h"
#include <array>

class CTriangle
{
private:
	std::array<CVector3D, 3> m_Points = { CVector3D() };

public:
	// Public constructor and destructor
	CTriangle(CVector3D, CVector3D, CVector3D);
	CTriangle(std::array<CVector3D, 3>);
	~CTriangle();

	// Getters
	std::array<CVector3D, 3> getPoints() const;

	// Setters
	void setPoints(std::array<CVector3D, 3> points);
};
