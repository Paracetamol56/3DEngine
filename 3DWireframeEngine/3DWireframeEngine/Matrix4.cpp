#include "Matrix4.h"

// Constructor
CMatrix4::CMatrix4()
{
}

// Destructor
CMatrix4::~CMatrix4()
{
}

// Matrix getter
std::array<std::array<float, 4>, 4> CMatrix4::getMatrix()
{
	return m_matrix;
}

// Matrix getter at a specific position
float CMatrix4::getMatrixAt(size_t i, size_t j) const
{
	if (i <= 4 && j <= 4)
	{
		return m_matrix[i][j];
	}
	return 0.0f;
}

// Matrix setter at a specific position
void CMatrix4::setMatrixAt(size_t i, size_t j, float value)
{
	if (i <= 4 && j <= 4)
	{
		m_matrix[i][j] = value;
	}
}

// * operator (with an other matrix)
CMatrix4& CMatrix4::operator*(const CMatrix4 other) const
{
	// New matrix
	CMatrix4 mat;

	for (size_t i = 0; i < 4; ++i) {
		for (size_t j = 0; j < 4; ++j)
		{
			for (size_t k = 0; k < 4; ++k)
			{
				mat.setMatrixAt(i, j, mat.getMatrixAt(i, j) + (mat.getMatrixAt(i, k) * other.getMatrixAt(k, j)));
			}
		}
	}
	return mat;
}

// Initialize the matrix to 0
CMatrix4& CMatrix4::setZeros()
{
	m_matrix = { 0 };
	return *this;
}

// Initialize the matrix to the unit matrix
CMatrix4& CMatrix4::setIdentity()
{
	setZeros();
	for (size_t i = 0; i < 4; ++i) {
		for (size_t j = 0; j < 4; ++j) {
			if (i == j) {
				m_matrix[i][j] = 1;
			}
		}
	}
	return *this;
}
