// LeftWindow.cpp: 实现文件
//

#include "pch.h"
#include "Application.h"
#include "LeftWindow.h"
#include "ApplicationDoc.h"


// LeftWindow

IMPLEMENT_DYNCREATE(LeftWindow, CFormView)

LeftWindow::LeftWindow()
	: CFormView(IDD_DIALOG1)
	, m_example_flag(FALSE)
{

}

LeftWindow::~LeftWindow()
{
}

void LeftWindow::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, m_BackgroundColor_R);
	DDX_Control(pDX, IDC_SLIDER3, m_BackgroundColor_G);
	DDX_Control(pDX, IDC_SLIDER2, m_BackgroundColor_B);
	DDX_Control(pDX, IDC_SLIDER4, m_FrameColor_R);
	DDX_Control(pDX, IDC_SLIDER5, m_FrameColor_G);
	DDX_Control(pDX, IDC_SLIDER6, m_FrameColor_B);
	DDX_Control(pDX, IDC_SLIDER7, m_ObjColor_R);
	DDX_Control(pDX, IDC_SLIDER8, m_ObjColor_G);
	DDX_Control(pDX, IDC_SLIDER9, m_ObjColor_B);
}

BEGIN_MESSAGE_MAP(LeftWindow, CFormView)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &LeftWindow::OnNMCustomdrawSlider1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER3, &LeftWindow::OnNMCustomdrawSlider3)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER2, &LeftWindow::OnNMCustomdrawSlider2)
	ON_BN_CLICKED(EXAMPLE, &LeftWindow::OnBnClickedExample)
	ON_BN_CLICKED(IDC_SETBACKCOLOR_CHECK, &LeftWindow::OnBnClickedSetbackcolorCheck)
	ON_BN_CLICKED(IDC_LIGHTING_CHECK, &LeftWindow::OnBnClickedLightingCheck)
	ON_BN_CLICKED(IDC_FRAMELINE, &LeftWindow::OnBnClickedFrameline)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER4, &LeftWindow::OnNMCustomdrawSlider4)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER5, &LeftWindow::OnNMCustomdrawSlider5)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER6, &LeftWindow::OnNMCustomdrawSlider6)
	ON_BN_CLICKED(IDC_CHANGEOBJ_COLOR, &LeftWindow::OnBnClickedChangeobjColor)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER7, &LeftWindow::OnNMCustomdrawSlider7)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER8, &LeftWindow::OnNMCustomdrawSlider8)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER9, &LeftWindow::OnNMCustomdrawSlider9)
END_MESSAGE_MAP()


// LeftWindow 诊断

#ifdef _DEBUG
void LeftWindow::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void LeftWindow::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// LeftWindow 消息处理程序



void LeftWindow::OnNMCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CApplicationDoc* pDoc = (CApplicationDoc*)GetDocument();

	int pos = m_BackgroundColor_R.GetPos();
	pDoc->m_RGB.red = (GLclampf)pos / 100;
	//CString cstr;
	////转换为字符串
	//cstr.Format(_T("%d"), pos);
	////设置静态文本框显示的内容
	//SetDlgItemText(IDC_STATIC, cstr);


	*pResult = 0;
}


void LeftWindow::OnNMCustomdrawSlider3(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CApplicationDoc* pDoc = (CApplicationDoc*)GetDocument();

	int pos = m_BackgroundColor_G.GetPos();
	pDoc->m_RGB.green = (GLclampf)pos / 100;
	*pResult = 0;
}


void LeftWindow::OnNMCustomdrawSlider2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CApplicationDoc* pDoc = (CApplicationDoc*)GetDocument();

	int pos = m_BackgroundColor_B.GetPos();
	pDoc->m_RGB.blue = (GLclampf)pos / 100;
	*pResult = 0;
}




void LeftWindow::OnBnClickedExample()
{
	// TODO: 在此添加控件通知处理程序代码
	CApplicationDoc* pDoc = (CApplicationDoc*)GetDocument();// 获取文档
	m_example_flag = !m_example_flag;
	if (m_example_flag == TRUE)
		pDoc->m_Cube_example = TRUE;
	else if (m_example_flag == FALSE)
		pDoc->m_Cube_example = FALSE;

	pDoc->UpdateAllViews(NULL);// 更新数据
}


void LeftWindow::OnBnClickedSetbackcolorCheck()
{
	// TODO: 在此添加控件通知处理程序代码
	CApplicationDoc* pDoc = (CApplicationDoc*)GetDocument();// 获取文档

	m_setbackground_color_flag = !m_setbackground_color_flag;
	if (m_setbackground_color_flag == TRUE)
		pDoc->m_SetBackGroundColor = TRUE;
	else if (m_setbackground_color_flag == FALSE)
		pDoc->m_SetBackGroundColor = FALSE;

	pDoc->UpdateAllViews(NULL);// 更新数据
}


void LeftWindow::OnBnClickedLightingCheck()
{
	// TODO: 在此添加控件通知处理程序代码
	CApplicationDoc* pDoc = (CApplicationDoc*)GetDocument();// 获取文档

	m_lighting_flag = !m_lighting_flag;
	if (m_lighting_flag == TRUE)
		pDoc->m_Light = TRUE;
	else if (m_lighting_flag == FALSE)
		pDoc->m_Light = FALSE;

	pDoc->UpdateAllViews(NULL);// 更新数据
}


void LeftWindow::OnBnClickedFrameline()
{
	// TODO: 在此添加控件通知处理程序代码
	CApplicationDoc* pDoc = (CApplicationDoc*)GetDocument();// 获取文档

	m_frameline_flag = !m_frameline_flag;
	if (m_frameline_flag == TRUE)
		pDoc->m_frameline = TRUE;
	else if (m_frameline_flag == FALSE)
	{
		pDoc->m_frameline = FALSE;
		pDoc->m_FrameColor = FALSE;
	}

	pDoc->UpdateAllViews(NULL);// 更新数据
}


void LeftWindow::OnNMCustomdrawSlider4(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CApplicationDoc* pDoc = (CApplicationDoc*)GetDocument();
	
	if(pDoc->m_frameline == TRUE)
		pDoc->m_FrameColor = TRUE;
	int pos = m_FrameColor_R.GetPos();
	pDoc->m_Frame_RGB.red = (GLclampf)pos / 100;
	*pResult = 0;
}


void LeftWindow::OnNMCustomdrawSlider5(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CApplicationDoc* pDoc = (CApplicationDoc*)GetDocument();

	if (pDoc->m_frameline == TRUE)
		pDoc->m_FrameColor = TRUE;
	int pos = m_FrameColor_G.GetPos();
	pDoc->m_Frame_RGB.green = (GLclampf)pos / 100;
	*pResult = 0;
}


void LeftWindow::OnNMCustomdrawSlider6(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CApplicationDoc* pDoc = (CApplicationDoc*)GetDocument();

	if (pDoc->m_frameline == TRUE)
		pDoc->m_FrameColor = TRUE;
	int pos = m_FrameColor_B.GetPos();
	pDoc->m_Frame_RGB.blue = (GLclampf)pos / 100;
	*pResult = 0;
}


void LeftWindow::OnBnClickedChangeobjColor()
{
	// TODO: 在此添加控件通知处理程序代码
	CApplicationDoc* pDoc = (CApplicationDoc*)GetDocument();// 获取文档

	m_objcolor_falg = !m_objcolor_falg;
	if (m_objcolor_falg == TRUE)
		pDoc->m_ObjColor = TRUE;
	else if (m_objcolor_falg == FALSE)
		pDoc->m_ObjColor = FALSE;

	pDoc->UpdateAllViews(NULL);// 更新数据
}


void LeftWindow::OnNMCustomdrawSlider7(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CApplicationDoc* pDoc = (CApplicationDoc*)GetDocument();

	int pos = m_ObjColor_R.GetPos();
	pDoc->m_Object_RGB.red = (GLclampf)pos / 100;
	*pResult = 0;
}


void LeftWindow::OnNMCustomdrawSlider8(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CApplicationDoc* pDoc = (CApplicationDoc*)GetDocument();

	int pos = m_ObjColor_G.GetPos();
	pDoc->m_Object_RGB.green = (GLclampf)pos / 100;
	*pResult = 0;
}


void LeftWindow::OnNMCustomdrawSlider9(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CApplicationDoc* pDoc = (CApplicationDoc*)GetDocument();

	int pos = m_ObjColor_B.GetPos();
	pDoc->m_Object_RGB.blue = (GLclampf)pos / 100;
	*pResult = 0;
}
