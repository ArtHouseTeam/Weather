
// ARTHOUSEView.h : CARTHOUSEView Ŭ������ �������̽�
//

#pragma once
#include "PictureEx.h"
#include "afxwin.h"

struct ThreadArg
{
	CWnd *pWnd;	// ����� ��� ������ ��ü�� �ּҴ�.
	int pos;	// 1�̸� ���ʿ�, 2�� �Ʒ��ʿ� ����Ѵ�.
};

class CARTHOUSEView : public CFormView
{
protected: // serialization������ ��������ϴ�.
	CARTHOUSEView();
	DECLARE_DYNCREATE(CARTHOUSEView)

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ARTHOUSE_FORM };
#endif

	// Ư���Դϴ�.
public:
	CARTHOUSEDoc* GetDocument() const;
	CWinThread *p2; //������ ��ü�ּ�
	CWinThread *pThread1, *pThread2;
	ThreadArg arg1, arg2;
	static UINT Weather_Renewal(LPVOID arg);


	// �۾��Դϴ�.
public:

	// �������Դϴ�.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual void OnInitialUpdate(); // ���� �� ó�� ȣ��Ǿ����ϴ�.
									// �����Դϴ�.

									// �����Դϴ�.
public:
	virtual ~CARTHOUSEView();
	CPoint mpos1;
	void draw_flag(CPoint locate, bool color = FALSE, int size = 0);
	void PttoRg(int pt[], CPoint mpos, CString str[], int xy[]);
	void displaying_junggi(int x, int y, int region);
	void region_disp(int x, int y, int region, CString region_name);
	
	void city_cloud_disp();
	void map_disp(int mode);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	CPictureEx gif_bs;
	CPictureEx gif_cb;
	CPictureEx gif_cn;
	CPictureEx gif_dg;
	CPictureEx gif_dj;
	CPictureEx gif_gb;
	CPictureEx gif_gj;
	CPictureEx gif_gn;
	CPictureEx gif_gw;
	CPictureEx gif_ic;
	CPictureEx gif_jb;
	CPictureEx gif_jj;
	CPictureEx gif_jn;
	CPictureEx gif_su;
	CPictureEx gif_us;
	CPictureEx gif_gg;
	CPictureEx gif_city;
//	afx_msg void OnSize(UINT nType, int cx, int cy);
//	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // ARTHOUSEView.cpp�� ����� ����
inline CARTHOUSEDoc* CARTHOUSEView::GetDocument() const
{
	return reinterpret_cast<CARTHOUSEDoc*>(m_pDocument);
}
#endif

