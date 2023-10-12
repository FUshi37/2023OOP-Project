
// ApplicationView.h: CApplicationView 类的接口
//

#pragma once
#include "Camera.h"
#include "ColorSet.h"
#include "BasicGeometry.h"
#include "ModelTest.h"
#include "ThreeDLine.h"

class CApplicationView : public CView
{
protected: // 仅从序列化创建
	CApplicationView() noexcept;
	DECLARE_DYNCREATE(CApplicationView)

// 特性
public:
	CApplicationDoc* GetDocument() const;

// 操作
protected:
	C3DPoint pt;
	Cube acube;
	C3DLine m_Line;
	CCamera m_Camera;
	Color m_Color;
	BOOL m_bDrawing;
	CDC* m_pDC;
	HGLRC m_hRC;
	GLMmodel* m_object;
	BOOL m_objectshow;
	void DrawScene();
	BOOL SetupPixelFormat(PIXELFORMATDESCRIPTOR* pPFD = 0);
	GLMmodel* LoadModelsFromFiles(CString FilePath);
	BOOL InitializeOpenGL(CDC* pDC);
	void SetBackGroundColor();
	void SetupLighting();
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CApplicationView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//afx_msg void OnFileOpen();
	afx_msg void OnClickButton();
};

#ifndef _DEBUG  // ApplicationView.cpp 中的调试版本
inline CApplicationDoc* CApplicationView::GetDocument() const
   { return reinterpret_cast<CApplicationDoc*>(m_pDocument); }
#endif

