
// ApplicationDoc.cpp: CApplicationDoc 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Application.h"
#endif

#include "ApplicationDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CApplicationDoc

IMPLEMENT_DYNCREATE(CApplicationDoc, CDocument)

BEGIN_MESSAGE_MAP(CApplicationDoc, CDocument)
	ON_COMMAND(ID_FILE_OPEN, &CApplicationDoc::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, &CApplicationDoc::OnFileSave)
END_MESSAGE_MAP()


// CApplicationDoc 构造/析构

CApplicationDoc::CApplicationDoc() noexcept
{
	// TODO: 在此添加一次性构造代码
	m_GeomObject  = NULL;
}

CApplicationDoc::~CApplicationDoc()
{
}

BOOL CApplicationDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CApplicationDoc 序列化

void CApplicationDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CApplicationDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CApplicationDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CApplicationDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CApplicationDoc 诊断

#ifdef _DEBUG
void CApplicationDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CApplicationDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

GLMmodel* CApplicationDoc::LoadModelsFromFiles(CString FilePath)
{
	//LPTSTR cpath = (LPTSTR)(LPCTSTR)FilePath;
	LPTSTR cpath = new TCHAR[FilePath.GetLength() + 1];
	_tcscpy(cpath, FilePath);

	GLfloat center[3] = { 0 };
	GLfloat scalefactor = 0.0;
	//Load Computer from file
	GLMmodel* object1;
	object1 = glmReadOBJ(FilePath.GetBuffer(0));
	if (!scalefactor)
	{
		scalefactor = glmUnitize(object1,center);
	}
	else
	{
		glmScale(object1, scalefactor);
	}
	glmScale(object1, 8);

	return object1;
}

void CApplicationDoc::OnFileOpen()
{
	 //TODO: 在此添加命令处理程序代码
	CFileDialog* fDlg = new CFileDialog(TRUE, NULL, NULL, OFN_OVERWRITEPROMPT,
		"Obj Files (*.Obj)|*.obj||All Files (*.*)|*.*||");

	if (fDlg->DoModal() == IDOK)
	{
		CString FilePath = fDlg->GetPathName();
		m_GeomObject = LoadModelsFromFiles(FilePath);
		UpdateAllViews(NULL);

		//InvalidateRect(NULL, FALSE);
	}
	m_bShowObject = TRUE;
}


void CApplicationDoc::OnFileSave()
{
	// TODO: 在此添加命令处理程序代码
	CFileDialog* fDlg = new CFileDialog(TRUE, NULL, NULL, OFN_OVERWRITEPROMPT,
		"Obj Files (*.Obj)|*.obj||All Files (*.*)|*.*||");

	if (fDlg->DoModal() == IDCANCEL)
	{
		CString FilePath = fDlg->GetPathName();
		
	}
}

void CApplicationDoc::WriteModelsToFiles(CString FilePath)
{
	LPTSTR cpath = new TCHAR[FilePath.GetLength() + 1];
	_tcscpy(cpath, FilePath);

	//m_GeomObject;

	//glmWriteOBJ(m_GeomObject, FilePath.GetBuffer(0), GLM_NONE);

}
