#include "Matrix4.h"

std::array<std::array<float, 4>, 4> CMatrix4::getMatrix()
{
	return m_matrix;
}

float CMatrix4::getMatrixAt(int i, int j) const
{
	if (i <= 4 && j <= 4)
	{
		return m_matrix[i][j];
	}
	return 0.0f;
}

void CMatrix4::setMatrixAt(size_t i, size_t j, float value)
{
	if (i <= 4 && j <= 4)
	{
		m_matrix[i][j] = value;
	}
}
