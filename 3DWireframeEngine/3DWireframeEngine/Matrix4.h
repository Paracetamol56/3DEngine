#pragma once

#include <array>

class CMatrix4
{
private:
	std::array<std::array<float, 4>, 4> m_matrix = { 0.0f };

public:
	// Getters
	std::array<std::array<float, 4>, 4> getMatrix();
	float getMatrixAt (int i, int j) const;

	// Setters
	void setMatrixAt (size_t i, size_t j, float value);
};

