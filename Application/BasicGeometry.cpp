#include "pch.h"
#include "BasicGeometry.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//Geometry类定义
Geometry::Geometry()
{
	centroid.X = 0;
	centroid.Y = 0;
	centroid.Z = 0;
}
Geometry::Geometry(C3DPoint &pt)
{
	centroid = pt;
};
Geometry::~Geometry()
{

};
void Geometry::Display()
{
	glVertex3f(centroid.X, centroid.Y, centroid.Z);
}

//Cube类定义
Cube::Cube()
{
	centroid.X = 0;
	centroid.Y = 0;
	centroid.Z = 0;
	width = 10;
	length = 10;
	height = 10;
}
Cube::Cube(C3DPoint &pt, GLfloat side)
{
	centroid = pt;
	width = side;
	length = side;
	height = side;
}
Cube::~Cube()
{
}
void Cube::Display()
{
	glBegin(GL_QUADS);
	//顶面
	glVertex3f(centroid.X + length / 2, centroid.Y + width / 2, centroid.Z - height / 2);     //右上顶点
	glVertex3f(centroid.X - length / 2, centroid.Y + width / 2, centroid.Z - height / 2);    //左上顶点
	glVertex3f(centroid.X - length / 2, centroid.Y + width / 2, centroid.Z + height / 2);     //左下顶点
	glVertex3f(centroid.X + length / 2, centroid.Y + width / 2, centroid.Z + height / 2);      //右下顶点

	//底面
	glVertex3f(centroid.X + length / 2, centroid.Y - width / 2, centroid.Z + height / 2);     //右上顶点
	glVertex3f(centroid.X - length / 2, centroid.Y - width / 2, centroid.Z + height / 2);    //左上顶点
	glVertex3f(centroid.X - length / 2, centroid.Y - width / 2, centroid.Z - height / 2);   //左下顶点
	glVertex3f(centroid.X + length / 2, centroid.Y - width / 2, centroid.Z - height / 2);    //右下顶点

	//前面
	glVertex3f(centroid.X + length / 2, centroid.Y + width / 2, centroid.Z + height / 2);      //右上顶点
	glVertex3f(centroid.X - length / 2, centroid.Y + width / 2, centroid.Z + height / 2);     //左上顶点
	glVertex3f(centroid.X - length / 2, centroid.Y - width / 2, centroid.Z + height / 2);    //左下顶点
	glVertex3f(centroid.X + length / 2, centroid.Y - width / 2, centroid.Z + height / 2);     //右下顶点

	//后面
	glVertex3f(centroid.X + length / 2, centroid.Y - width / 2, centroid.Z - height / 2);    //右上顶点
	glVertex3f(centroid.X - length / 2, centroid.Y - width / 2, centroid.Z - height / 2);   //左上顶点
	glVertex3f(centroid.X - length / 2, centroid.Y + width / 2, centroid.Z - height / 2);    //左下顶点
	glVertex3f(centroid.X + length / 2, centroid.Y + width / 2, centroid.Z - height / 2);     //右下顶点

	//左侧面
	glVertex3f(centroid.X - length / 2, centroid.Y + width / 2, centroid.Z + height / 2);     //右上顶点
	glVertex3f(centroid.X - length / 2, centroid.Y + width / 2, centroid.Z - height / 2);    //左上顶点
	glVertex3f(centroid.X - length / 2, centroid.Y - width / 2, centroid.Z - height / 2);   //左下顶点
	glVertex3f(centroid.X - length / 2, centroid.Y - width / 2, centroid.Z + height / 2);     //右下顶点

	//右侧面
	glVertex3f(centroid.X + length / 2, centroid.Y + width / 2, centroid.Z - height / 2);     //右上顶点
	glVertex3f(centroid.X + length / 2, centroid.Y + width / 2, centroid.Z + height / 2);      //左上顶点
	glVertex3f(centroid.X + length / 2, centroid.Y - width / 2, centroid.Z + height / 2);     //左下顶点
	glVertex3f(centroid.X + length / 2, centroid.Y - width / 2, centroid.Z - height / 2);    //右下顶点

	glEnd();
}

void Cube::DisplayFrame()
{
	glColor3f(1, 1, 1);
	glLineWidth(2);
	glBegin(GL_LINES);
	//+ + -
	glVertex3f(centroid.X + length / 2, centroid.Y + width / 2, centroid.Z - height / 2);     //右上顶点
	glVertex3f(centroid.X + length / 2, centroid.Y + width / 2, centroid.Z + height / 2);      //右下顶点

	glVertex3f(centroid.X + length / 2, centroid.Y + width / 2, centroid.Z - height / 2);
	glVertex3f(centroid.X + length / 2, centroid.Y - width / 2, centroid.Z - height / 2);

	glVertex3f(centroid.X + length / 2, centroid.Y + width / 2, centroid.Z - height / 2);
	glVertex3f(centroid.X - length / 2, centroid.Y + width / 2, centroid.Z - height / 2);

	//+ + +
	glVertex3f(centroid.X + length / 2, centroid.Y + width / 2, centroid.Z + height / 2);
	glVertex3f(centroid.X - length / 2, centroid.Y + width / 2, centroid.Z + height / 2);

	glVertex3f(centroid.X + length / 2, centroid.Y + width / 2, centroid.Z + height / 2);
	glVertex3f(centroid.X + length / 2, centroid.Y - width / 2, centroid.Z + height / 2);

	//+ - -
	glVertex3f(centroid.X + length / 2, centroid.Y - width / 2, centroid.Z - height / 2);
	glVertex3f(centroid.X + length / 2, centroid.Y - width / 2, centroid.Z + height / 2);

	glVertex3f(centroid.X + length / 2, centroid.Y - width / 2, centroid.Z - height / 2);
	glVertex3f(centroid.X - length / 2, centroid.Y - width / 2, centroid.Z - height / 2);

	//- - +
	glVertex3f(centroid.X - length / 2, centroid.Y - width / 2, centroid.Z + height / 2);
	glVertex3f(centroid.X + length / 2, centroid.Y - width / 2, centroid.Z + height / 2);

	glVertex3f(centroid.X - length / 2, centroid.Y - width / 2, centroid.Z + height / 2);
	glVertex3f(centroid.X - length / 2, centroid.Y + width / 2, centroid.Z + height / 2);

	glVertex3f(centroid.X - length / 2, centroid.Y - width / 2, centroid.Z + height / 2);
	glVertex3f(centroid.X - length / 2, centroid.Y - width / 2, centroid.Z - height / 2);

	//- + +
	glVertex3f(centroid.X - length / 2, centroid.Y + width / 2, centroid.Z + height / 2);
	glVertex3f(centroid.X - length / 2, centroid.Y + width / 2, centroid.Z - height / 2);

	glVertex3f(centroid.X - length / 2, centroid.Y - width / 2, centroid.Z - height / 2);
	glVertex3f(centroid.X - length / 2, centroid.Y + width / 2, centroid.Z - height / 2);

	glEnd();
}