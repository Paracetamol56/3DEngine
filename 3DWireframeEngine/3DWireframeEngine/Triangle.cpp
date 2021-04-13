#include "Triangle.h"

// Constructors
CTriangle::CTriangle(CVector3D point1, CVector3D point2, CVector3D point3)
{
    m_Points[0] = point1;
    m_Points[1] = point2;
    m_Points[2] = point3;
}

CTriangle::CTriangle(std::array<CVector3D, 3> points)
{
    m_Points = points;
}

// Destructor
CTriangle::~CTriangle()
{
}

// Points getter
std::array<CVector3D, 3> CTriangle::getPoints() const
{
    return m_Points;
}

// Points setter
void CTriangle::setPoints(std::array<CVector3D, 3> points)
{
    m_Points = points;
}
