
// ApplicationView.cpp: CApplicationView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Application.h"
#endif

#include "ApplicationDoc.h"
#include "ApplicationView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CApplicationView

IMPLEMENT_DYNCREATE(CApplicationView, CView)

BEGIN_MESSAGE_MAP(CApplicationView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
//	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
//ON_COMMAND(ID_FILE_OPEN, &CApplicationView::OnFileOpen)
//ON_COMMAND(ID_FILE_OPEN, &CApplicationView::OnFileOpen)
	ON_BN_CLICKED(130, OnClickButton)
END_MESSAGE_MAP()

// CApplicationView 构造/析构

CApplicationView::CApplicationView() noexcept
{
	// TODO: 在此处添加构造代码
	
}

CApplicationView::~CApplicationView()
{
}

BOOL CApplicationView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	return CView::PreCreateWindow(cs);
}

// CApplicationView 绘图

void CApplicationView::OnDraw(CDC* /*pDC*/)
{
	CApplicationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码

	DrawScene();
}


// CApplicationView 打印

BOOL CApplicationView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CApplicationView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CApplicationView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CApplicationView 诊断

#ifdef _DEBUG
void CApplicationView::AssertValid() const
{
	CView::AssertValid();
}

void CApplicationView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CApplicationDoc* CApplicationView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CApplicationDoc)));
	return (CApplicationDoc*)m_pDocument;
}
#endif //_DEBUG


// CApplicationView 消息处理程序


int CApplicationView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	m_pDC = new CClientDC(this);	// get device context
	InitializeOpenGL(m_pDC);

	return 0;
}


void CApplicationView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	if (wglMakeCurrent(0, 0) == FALSE)
		::AfxMessageBox(_T("wglMakeCurrent failed"));
	if (m_hRC && (wglDeleteContext(m_hRC) == FALSE))
		::AfxMessageBox(_T("sglDeleteContext failed"));
	if (m_pDC)
		delete m_pDC;

	KillTimer(1);
}


BOOL CApplicationView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	// return CView::OnEraseBkgnd(pDC);
	return TRUE;
}


void CApplicationView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	if (m_hRC)
		wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);
	else
		return;
	// TODO: 在此处添加消息处理程序代码
	GLdouble aspect_ratio;

	if (cx <= 0 || cy <= 0)
	{
		return;
	}

	//Select the full client area
	::glViewport(0, 0, cx, cy);

	//Compute the aspect ratio
	aspect_ratio = (GLdouble)cx / (GLdouble)cy;

	//Select the projection matrix and clear it
	::glMatrixMode(GL_PROJECTION);
	::glLoadIdentity();

	//Select the viewing volume
	::gluPerspective(45.0f, aspect_ratio, 0.01f, 200.0f);

	//Switch back to the modelview matrix and clear it
	//::glMatrixMode(GL_MODELVIEW);
	//::glLoadIdentity();

	//glViewport(0, 0, cx, cy);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	////gluOrtho2D(0, 500, 0, 500);
	if (cx < cy)
		glOrtho(-10.0, 100.0, -10.0 * (GLfloat)cy / (GLfloat)cx, 10.0 * (GLfloat)cy / (GLfloat)cx, -100.0, 100.0);
	else
		glOrtho(-10.0 * (GLfloat)cx / (GLfloat)cy, 10.0 * (GLfloat)cx / (GLfloat)cy, -10.0, 10.0, -100.0, 100.0);
	//// switch back to the modelview matrix and clear it  
	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();
}


BOOL CApplicationView::SetupPixelFormat(PIXELFORMATDESCRIPTOR* pPFD)
{
	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL,
		PFD_TYPE_RGBA,
		24,
		0, 0, 0, 0, 0, 0,
		0, 0, 0,
		0, 0, 0, 0,
		16,
		0, 0,
		PFD_MAIN_PLANE,
		0, 0, 0, 0 };

	int pixelformat;

	PIXELFORMATDESCRIPTOR* pPFDtoUse;

	pPFDtoUse = (0 == pPFD) ? &pfd : pPFD;

	if (0 == (pixelformat = ::ChoosePixelFormat(m_pDC->GetSafeHdc(), pPFDtoUse)))
	{
		::AfxMessageBox(_T("ChoosePixelFormat failed"));
		return FALSE;
	}

	if (FALSE == ::SetPixelFormat(m_pDC->GetSafeHdc(), pixelformat, pPFDtoUse))
	{
		::AfxMessageBox(_T("SetPixelFormat failed"));
		return FALSE;
	}

	return TRUE;
}

void CApplicationView::DrawScene()
{
	CApplicationDoc* pDoc = GetDocument();
	if (m_hRC)
		wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);
	else
		return;
	RECT rect;
	GetClientRect(&rect);

	//Calculate window's height and width
	int window_width = rect.right - rect.left;
	int window_height = rect.bottom - rect.top;
	// 设置背景色控件
	SetBackGroundColor();

	// 设置背景光照
	SetupLighting();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glScalef(1.0f, 1.0f, 1.0f);


	// 初始化相机
	m_Camera.CoordinateTransform();
	glRotatef(m_Camera.SpinFactor, 1, 1, 1);

	// 旋转彩色立方体例程
	if (pDoc->m_Cube_example == TRUE)
	{
		glColor3f(m_Color.red, m_Color.green, m_Color.blue);
		acube.Display();
		acube.DisplayFrame();
	}
	// 改变物体颜色
	if (pDoc->m_ObjColor == TRUE)
	{
		glColor3f(pDoc->m_Object_RGB.red, pDoc->m_Object_RGB.green, pDoc->m_Object_RGB.blue);
	}
	// 读取物体显示
	if (pDoc->m_bShowObject)
	{
		if(pDoc->m_GeomObject != NULL)
		{
			SetupLighting();
			glmDraw(pDoc->m_GeomObject, GLM_TEXTURE | GLM_COLOR | GLM_MATERIAL);
		}
		// 线框模式
		if (pDoc->m_frameline == TRUE)
		{
			if (pDoc->m_FrameColor == TRUE)
			{
				m_Line.DrawFrames(pDoc->m_GeomObject, pDoc->m_Frame_RGB);
			}
			else
			{
				Color normal;
				normal.red = 0; normal.green = 0; normal.blue = 0;
				m_Line.DrawFrames(pDoc->m_GeomObject, normal);
			}
		}
	}

	::SwapBuffers(m_pDC->GetSafeHdc());

	glFlush();
}


void CApplicationView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_Camera.SetMouseDownPoint(point);
	SetCapture();

	CView::OnLButtonDown(nFlags, point);
}


void CApplicationView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_Camera.SetMouseDownPoint(CPoint(0, 0));
	ReleaseCapture();

	CView::OnLButtonUp(nFlags, point);
}


BOOL CApplicationView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_Camera.UpdateScale(zDelta);
	InvalidateRect(NULL, FALSE);

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}


void CApplicationView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_bDrawing)
	{
		InvalidateRect(NULL, FALSE);
	}

	//Update Camera Anlge
	if (GetCapture() == this)
	{
		m_Camera.UpdateAngle(point);
		InvalidateRect(NULL, FALSE);
	}

	CView::OnMouseMove(nFlags, point);
}


void CApplicationView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_Camera.UpdatePosition(nChar);

	InvalidateRect(NULL, FALSE);
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CApplicationView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent) 
	{
	case 1:
		CApplicationDoc * pDoc = GetDocument();
		if (pDoc->m_Cube_example == TRUE)
		{
			m_Color.SineColorChange();
			m_Camera.CameraSpin(1, 1, 1, 1);
		}
		OnDraw(m_pDC);
		break;
	}

	CView::OnTimer(nIDEvent);
}


BOOL CApplicationView::InitializeOpenGL(CDC* m_pDC)
{
	GetDocument()->m_bShowObject = FALSE;
	GetDocument()->m_bShowUserEdge = FALSE;
	GetDocument()->m_SetBackGroundColor = FALSE;
	GetDocument()->m_Cube_example = FALSE;
	GetDocument()->m_Light = FALSE;
	GetDocument()->m_frameline = FALSE;
	GetDocument()->m_FrameColor = FALSE;
	GetDocument()->m_ObjColor = FALSE;

	m_objectshow = FALSE;

	if (m_pDC == NULL)
	{
		::AfxMessageBox(_T("fail to get device context"));
		return FALSE;
	}

	if (!SetupPixelFormat())	// setup pixel format
	{
		::AfxMessageBox(_T("SetupPixelFormat failed"));
		return FALSE;
	}

	// get rendering context
	if ((m_hRC = wglCreateContext(m_pDC->GetSafeHdc())) == 0)
	{
		::AfxMessageBox(_T("wglCreateContext failed"));
		return FALSE;
	}

	// make current rendering context
	if (wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC) == FALSE)
	{
		::AfxMessageBox(_T("wglMakeCurrent failed"));
		return FALSE;
	}
	//Specify Black as the clear color
	::glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//Specify the back of the buffer as clear depth
	::glClearDepth(1.0f);

	//Enable depth testing
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);

	int argc = 1;
	char* argv[] = { "MFC_GLUT" };
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);


	SetTimer(1, 10, NULL);

	return TRUE;
}





void CApplicationView::OnClickButton()
{
	//MessageBox("hello", "helloworld", MB_OK);
}


void CApplicationView::SetBackGroundColor()
{
	CApplicationDoc* pDoc = GetDocument();

	if (pDoc->m_SetBackGroundColor == FALSE)
		glClearColor(0, 0, 0, 0);
	if (pDoc->m_SetBackGroundColor == TRUE)
		glClearColor(pDoc->m_RGB.red, pDoc->m_RGB.green, pDoc->m_RGB.blue, 1);
}


void CApplicationView::SetupLighting()
{
	CApplicationDoc* pDoc = GetDocument();
	float ambientlight0Color[] = { 0.0f,0.0f,0.0f,1.0f };
	float diffuselight0Color[] = { 1.0f,1.0f,1.0f,1.0f };
	float specularlight0Color[] = { 1.0f,1.0f,1.0f,1.0f };
	float light0Position[] = { -2.0,2.0f,2.0f,1.0f };
	float ambientM[] = { 0.11f,0.06f,0.11f,1.0f };
	float ambientD[] = { 0.43f,0.47f,0.54f,1.0f };
	float ambientS[] = { 0.33f,0.33f,0.52f,1.0f };
	float ambientE[] = { 0.0f,0.0f,0.0f,0.0f };
	float ambientSE = 10;

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientlight0Color);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuselight0Color);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularlight0Color);
	glLightfv(GL_LIGHT0, GL_POSITION, light0Position);
	//----------设置材质
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambientM);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, ambientD);
	glMaterialfv(GL_FRONT, GL_SPECULAR, ambientS);
	glMaterialfv(GL_FRONT, GL_EMISSION, ambientE);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0f);
	//控制镜面反射光斑的大小 0---120
	//-----------启动光照
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	if (pDoc->m_Light == TRUE)
	{
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHTING);
		//glEnable(GL_LIGHTING);
		//glEnable(GL_COLOR_MATERIAL);
		//glLightModeli(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	}
	if (pDoc->m_Light == FALSE)
	{
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
	}
}