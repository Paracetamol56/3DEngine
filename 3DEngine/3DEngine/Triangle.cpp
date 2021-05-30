/*
 * Created on Tue May 30 2021
 *
 * Copyright (c) 2021 - Mathéo Galuba - All Right Reserved
 *
 * Licensed under the Apache License, Version 2.0
 * Available on GitHub at https://github.com/Paracetamol56/3DWireframeEngine
 */

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

CVector3D CTriangle::getMassCenter() const
{
    // Center point
    CVector3D massCenter
    (
        (m_Points[0].m_x + m_Points[1].m_x + m_Points[2].m_x) / 3,
        (m_Points[0].m_y + m_Points[1].m_y + m_Points[2].m_y) / 3,
        (m_Points[0].m_z + m_Points[1].m_z + m_Points[2].m_z) / 3
    );

    return massCenter;
}

// Normal getter
CVector3D CTriangle::getNormal() const
{
    // Normal vector
    CVector3D normal
    (
        (m_Points[1].m_y - m_Points[0].m_y) * (m_Points[2].m_z - m_Points[0].m_z) - (m_Points[1].m_z - m_Points[0].m_z) * (m_Points[2].m_y - m_Points[0].m_y),
        (m_Points[1].m_z - m_Points[0].m_z) * (m_Points[2].m_x - m_Points[0].m_x) - (m_Points[1].m_x - m_Points[0].m_x) * (m_Points[2].m_z - m_Points[0].m_z),
        (m_Points[1].m_x - m_Points[0].m_x) * (m_Points[2].m_y - m_Points[0].m_y) - (m_Points[1].m_y - m_Points[0].m_y) * (m_Points[2].m_x - m_Points[0].m_x)
    );

    // Normalization
    float length = sqrtf(normal.m_x * normal.m_x + normal.m_y * normal.m_y + normal.m_z * normal.m_z);

    normal.m_x /= length;
    normal.m_y /= length;
    normal.m_z /= length;

    return normal;
}

// Points setter
void CTriangle::setPoints(std::array<CVector3D, 3> points)
{
    m_Points = points;
}
