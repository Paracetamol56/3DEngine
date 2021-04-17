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

CTriangle::CTriangle(CTriangle* other)
{
    for (size_t i = 0; i < 3; i++)
    {
        m_Points.at(i) = other->getPoints().at(i);
    }
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

// Normal getter
CVector3D CTriangle::getNormal() const
{
    // Point 0 to Point 1 vector
    /*CVector3D planVector1
    (
        m_Points[1].getX() - m_Points[0].getX(),
        m_Points[1].getY() - m_Points[0].getY(),
        m_Points[1].getZ() - m_Points[0].getZ()
    );*/

    // Point 0 to Point 2 vector
    /*CVector3D planVector2
    (
        m_Points[2].getX() - m_Points[0].getX(),
        m_Points[2].getY() - m_Points[0].getY(),
        m_Points[2].getZ() - m_Points[0].getZ()
    );*/
    
    // Normal vector
    CVector3D normal
    (
        (m_Points[1].getY() - m_Points[0].getY()) * (m_Points[2].getZ() - m_Points[0].getZ()) - (m_Points[1].getZ() - m_Points[0].getZ()) * (m_Points[2].getY() - m_Points[0].getY()),
        (m_Points[1].getZ() - m_Points[0].getZ()) * (m_Points[2].getX() - m_Points[0].getX()) - (m_Points[1].getX() - m_Points[0].getX()) * (m_Points[2].getZ() - m_Points[0].getZ()),
        (m_Points[1].getX() - m_Points[0].getX()) * (m_Points[2].getY() - m_Points[0].getY()) - (m_Points[1].getY() - m_Points[0].getY()) * (m_Points[2].getX() - m_Points[0].getX())
    );

    // Normalization
    float length = sqrtf(normal.getX() * normal.getX() + normal.getY() * normal.getY() + normal.getZ() * normal.getZ());

    normal.setX(normal.getX() / length);
    normal.setY(normal.getY() / length);
    normal.setZ(normal.getZ() / length);

    return normal;
}

// Points setter
void CTriangle::setPoints(std::array<CVector3D, 3> points)
{
    m_Points = points;
}
