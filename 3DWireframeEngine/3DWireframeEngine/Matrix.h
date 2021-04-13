#pragma once

#include <array>

template<int S>
class CMatrix
{
private:
	std::array<std::array<float, S>, S> m_matrix;

public:
	// Getters
	std::array<std::array<float, S>, S> getMatrix();
	float getMatrixAt (int i, int j) const;

	// Setters
	void setMatrixAt (size_t i, size_t j, float value);
};

template<int S>
inline std::array<std::array<float, S>, S> CMatrix<S>::getMatrix()
{
	return m_matrix;
}

template<int S>
inline float CMatrix<S>::getMatrixAt(int i, int j) const
{
	if ( i <= S && j <= S )
	{
		return m_matrix[i][j];
	}
	return 0.0f;
}

template<int S>
inline void CMatrix<S>::setMatrixAt(size_t i, size_t j, float value)
{
	if (i <= S && j <= S)
	{
		m_matrix[i][j] = value;
	}
}
