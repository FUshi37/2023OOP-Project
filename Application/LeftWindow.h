#pragma once



// LeftWindow 窗体视图

class LeftWindow : public CFormView
{
	DECLARE_DYNCREATE(LeftWindow)

protected:
	LeftWindow();           // 动态创建所使用的受保护的构造函数
	virtual ~LeftWindow();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMCustomdrawSlider3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMCustomdrawSlider2(NMHDR* pNMHDR, LRESULT* pResult);
	CSliderCtrl m_BackgroundColor_R;
	CSliderCtrl m_BackgroundColor_G;
	CSliderCtrl m_BackgroundColor_B;
	afx_msg void OnBnClickedExample();
	BOOL m_example_flag;
	BOOL m_setbackground_color_flag;
	BOOL m_lighting_flag;
	BOOL m_frameline_flag;
	BOOL m_objcolor_falg;
	afx_msg void OnBnClickedSetbackcolorCheck();
	afx_msg void OnBnClickedLightingCheck();
	afx_msg void OnBnClickedFrameline();
	afx_msg void OnNMCustomdrawSlider4(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMCustomdrawSlider5(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMCustomdrawSlider6(NMHDR* pNMHDR, LRESULT* pResult);
	CSliderCtrl m_FrameColor_R;
	CSliderCtrl m_FrameColor_G;
	CSliderCtrl m_FrameColor_B;
	afx_msg void OnBnClickedChangeobjColor();
	afx_msg void OnNMCustomdrawSlider7(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMCustomdrawSlider8(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMCustomdrawSlider9(NMHDR* pNMHDR, LRESULT* pResult);
	CSliderCtrl m_ObjColor_R;
	CSliderCtrl m_ObjColor_G;
	CSliderCtrl m_ObjColor_B;
};


