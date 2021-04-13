#pragma once

class CVector3D
{
private:
	float m_x, m_y, m_z;

public:
	// Public constructor and destructor
	CVector3D(float x, float y, float z);
	~CVector3D();

	// Getters
	float getX();
	float getY();
	float getZ();

	// Setters
	void setX( float x );
	void setY( float y );
	void setZ( float z );
};

