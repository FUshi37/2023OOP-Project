#ifndef COLORSET_H_
#define COLORSET_H_

#include "pch.h"

class Color
{
private:
public:
	GLfloat red;
	GLfloat green;
	GLfloat blue;
	GLfloat timeValue;
	Color();
	virtual ~Color();
	void SineColorChange();
	void SetBackGroundColor();
};


#endif // !COLORSET_H_
