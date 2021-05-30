/*
 * Created on Tue May 30 2021
 *
 * Copyright (c) 2021 - Mathéo Galuba - All Right Reserved
 *
 * Licensed under the Apache License, Version 2.0
 * Available on GitHub at https://github.com/Paracetamol56/3DWireframeEngine
 */

#pragma once

#ifndef MATRIX4_H_INCLUDED
#define MATRIX4_H_INCLUDED

#include <array>

class CMatrix4
{
private:
	std::array<std::array<float, 4>, 4> m_matrix = { 0.0f };

public:
	// Public constructor and destructor
	CMatrix4();
	~CMatrix4();

public:
	// Getters
	std::array<std::array<float, 4>, 4> getMatrix();
	float getMatrixAt (size_t i, size_t j) const;

	// Setters
	void setMatrixAt (size_t i, size_t j, float value);

public:
	// Operator
	CMatrix4& operator*=(const CMatrix4 other) const;
	CMatrix4& operator*(const CMatrix4 other) const;

public:
	// Initialize the matrix to 0
	CMatrix4& setZeros();
	// Initialize the matrix to the unit matrix
	CMatrix4& setIdentity();
};

#endif // MATRIX4_H_INCLUDED