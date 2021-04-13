#pragma once

class CVector3D
{
private:
	// 3D coordiantes
	float m_x, m_y, m_z;

public:
	// Public constructor and destructor
	CVector3D(float x, float y, float z);
	~CVector3D();

	// Getters
	float getX() const;
	float getY() const;
	float getZ() const;

	// Setters
	void setX( float x );
	void setY( float y );
	void setZ( float z );
};
