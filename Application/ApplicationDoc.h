
// ApplicationDoc.h: CApplicationDoc 类的接口
//


#pragma once
#include "ModelTest.h"
#include "ColorSet.h"

class CApplicationDoc : public CDocument
{
protected: // 仅从序列化创建
	CApplicationDoc() noexcept;
	DECLARE_DYNCREATE(CApplicationDoc)

// 特性
public:
	BOOL m_SetBackGroundColor; // 自定义背景色表示
	BOOL m_Cube_example;       // 彩色旋转立方体例程
	BOOL m_Light;              // 设置光源
	BOOL m_frameline;          // 线框模式
	BOOL m_FrameColor;		   // 设置线框颜色
	BOOL m_ObjColor;           // 设置物体颜色
	GLMmodel*	m_GeomObject;
	GLMmodel* m_GeomModelObject;
	//GeomModel* m_GeomObject;
	//GeomModel* m_GeomModelObject;
	GLuint		m_ObjectList;
	//	GLuint		m_ObjectList_;

// 操作
public:
	CPoint p1, p2;
	Color m_RGB;
	Color m_Object_RGB;
	Color m_Frame_RGB;
// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	GLMmodel* LoadModelsFromFiles(CString FilePath);
	void WriteModelsToFiles(CString FilePath);
	BOOL m_bShowObject;
	BOOL m_bShowUserEdge;

	virtual ~CApplicationDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	//virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
};
