/*
 * Created on Tue May 30 2021
 *
 * Copyright (c) 2021 - Mathéo Galuba - All Right Reserved
 *
 * Licensed under the Apache License, Version 2.0
 * Available on GitHub at https://github.com/Paracetamol56/3DWireframeEngine
 */

#pragma once

#ifndef TRIANGLE_H_INCLUDED
#define TRIANGLE_H_INCLUDED

#include "Vector3D.h"
#include <array>

class CTriangle
{
public:
	std::array<CVector3D, 3> m_Points = { CVector3D() };

public:
	// Public constructor and destructor
	CTriangle(CVector3D point1, CVector3D point2, CVector3D point3);
	CTriangle(std::array<CVector3D, 3> points);
	CTriangle(CTriangle* other);
	~CTriangle();

	// Getters
	std::array<CVector3D, 3> getPoints() const;
	CVector3D getMassCenter() const;
	CVector3D getNormal() const;

	// Setters
	void setPoints(std::array<CVector3D, 3> points);
};

#endif // TRIANGLE_H_INCLUDE