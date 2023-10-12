#include "pch.h"
#include "ColorSet.h"
#include "Application.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

Color::Color()
{
	red = 0.0f;
	green = 0.0f;
	blue = 0.0f;
	timeValue = 0.1f;
}

Color::~Color()
{

}

void Color::SineColorChange() 
{
	//float timeValue = glfwGetTime();
	timeValue += 0.1f;
	red = sin(timeValue) / 2.0f + 0.5;
	green = sin(timeValue+3.14/2) / 2.0f + 0.5;
	blue = sin(timeValue + 3.14) / 2.0f + 0.5;
}

void Color::SetBackGroundColor()
{

}