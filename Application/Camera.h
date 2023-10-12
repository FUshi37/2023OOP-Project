#ifndef CAMERA_H_
#define CAMERA_H_
#include "pch.h"
class CCamera
{
public:
	void UpdateDistance(const short& zDelta);
	void UpdateAngle(const CPoint& MousePoint);
	void SetMouseDownPoint(const CPoint& ptMouseDown);
	void UpdateView(int n = 0);
	void UpdateScale(const short& zDelta);
	void UpdatePosition(const unsigned int nChar);
	void ResetCamera();
	void CoordinateTransform();
	void CameraSpin(GLfloat speedfactor, GLfloat X, GLfloat Y, GLfloat Z);
	CCamera();
	virtual ~CCamera();

//private:
public:
	CPoint m_ptMouseDown;
	GLfloat m_yAngle;
	GLfloat m_xAngle;
	GLfloat m_zAngle;
	GLfloat m_xPos;
	GLfloat m_yPos;
	GLfloat m_zPos;
	float m_Scale;
	GLfloat SpinFactor;
};

#endif // !CAMERA_H_
