#pragma once

class CVector3D
{
private:
	// 3D coordinates
	float m_x = 0.0f;
	float m_y = 0.0f;
	float m_z = 0.0f;

public:
	// Public constructor and destructor
	CVector3D();
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
