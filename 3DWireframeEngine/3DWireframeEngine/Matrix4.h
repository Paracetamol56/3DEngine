#pragma once

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

