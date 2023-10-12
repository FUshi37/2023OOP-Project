#include "pch.h"
#include "Camera.h"
#include "Application.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCamera::CCamera()
{
	//m_xAngle = 0;
	//m_yAngle = 0;
	//m_zPos = -5.0;
	//m_ptMouseDown.x = 0;
	//m_ptMouseDown.y = 0;
	m_xPos = 0.0f;
	m_yPos = 0.0f;
	m_zPos = -5.0f;
	m_xAngle = 0.0f;
	m_yAngle = 0.0f;
	m_zAngle = 0.0f;
	m_Scale = 1.0f;
	SpinFactor = 1.0f;
}

CCamera::~CCamera()
{
}

void CCamera::ResetCamera()
{
	//Reset members to initial value
	m_xAngle = 0;
	m_yAngle = 0;
	m_zPos = -5.0;
	m_ptMouseDown.x = 0;
	m_ptMouseDown.y = 0;

	//Update the view
	UpdateView();
}

void CCamera::UpdateView(int n)
{
	/*
	CString Info;
	Info.Format("x Angle = %f, y Angle = %f, z Pos = %f", m_xAngle, m_yAngle, m_zPos);
	CWnd *pWnd = AfxGetMainWnd();
	pWnd->SetWindowText(Info.GetBuffer(0));
	*/

	//Update view
	if (n != 0)
	{
		glTranslatef(0.0f, 0.0f, m_zPos);
	}
	else
		glTranslatef(0.0f, 0.0f, -5.0f);
	glRotatef(m_xAngle, 1.0f, 0.0f, 0.0f);
	glRotatef(m_yAngle, 0.0f, 1.0f, 0.0f);

}

void CCamera::SetMouseDownPoint(const CPoint& ptMouseDown)
{
	//Save point
	m_ptMouseDown = ptMouseDown;
}

void CCamera::UpdateAngle(const CPoint& MousePoint)
{
	//Calculate rotate angle
	m_xAngle += (MousePoint.y - m_ptMouseDown.y) / 3.6;
	m_yAngle += (MousePoint.x - m_ptMouseDown.x) / 3.6;
	m_ptMouseDown = MousePoint;
}

void CCamera::UpdateDistance(const short& zDelta)
{
	//Calculate zoom in & zoom out
	m_zPos += zDelta / WHEEL_DELTA;
}

void CCamera::UpdateScale(const short& zDelta)
{
	if (m_Scale >= 0)
	{
		m_Scale += 0.05 * zDelta / WHEEL_DELTA;
	}
	else
	{
		if (zDelta > 0)
		{
			m_Scale += 0.05 * zDelta / WHEEL_DELTA;
		}
	}
}

void CCamera::UpdatePosition(const unsigned int nChar)
{
	switch (nChar)
	{
	case VK_UP:        m_yPos = m_yPos + 0.1f;
		break;
	case VK_DOWN:    m_yPos = m_yPos - 0.1f;
		break;
	case VK_LEFT:    m_xPos = m_xPos - 0.1f;
		break;
	case VK_RIGHT:  m_xPos = m_xPos + 0.1f;
		break;
	default:        //AfxMessageBox(_T("Press the arrow keys only"));
		break;
	}
}

void CCamera::CoordinateTransform()
{
	glTranslatef(m_xPos, m_yPos, m_zPos);
	glRotatef(m_xAngle, 1.0f, 0.0f, 0.0f);
	glRotatef(m_yAngle, 0.0f, 1.0f, 0.0f);
	glScalef(m_Scale, m_Scale, m_Scale);
}

//镜头绕固定轴旋转，线性旋转
void CCamera::CameraSpin(GLfloat speedfactor, GLfloat X, GLfloat Y, GLfloat Z)
{
	//GLfloat angle = 0;
	//angle += SpinFactor * speedfactor;
	//glRotatef(angle, X, Y, Z);
	SpinFactor += speedfactor;
	//SpinFactor++;
}