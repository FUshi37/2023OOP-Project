#ifndef BASICGEOMETRY
#define BASICGEOMETRY

#include "pch.h"
#include "ThreeDPoint.h"

class Geometry
{
protected:
	C3DPoint centroid;
public:
	Geometry();
	Geometry (C3DPoint &pt);
	virtual ~Geometry();
	virtual void Display();
};


class Cube : public Geometry
{
	friend class CApplicationView;
private:
	GLfloat length;
	GLfloat width;
	GLfloat height;
public:
	Cube();
	Cube(C3DPoint &pt, GLfloat side);
	virtual ~Cube();
	virtual void Display();
	void DisplayFrame();
};

#endif // !BASICGEOMETRY
