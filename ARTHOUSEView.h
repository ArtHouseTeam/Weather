
// ARTHOUSEView.h : CARTHOUSEView 클래스의 인터페이스
//

#pragma once
#include "PictureEx.h"
#include "afxwin.h"

struct ThreadArg
{
	CWnd *pWnd;	// 출력할 대상 윈도우 객체의 주소다.
	int pos;	// 1이면 위쪽에, 2면 아래쪽에 출력한다.
};

class CARTHOUSEView : public CFormView
{
protected: // serialization에서만 만들어집니다.
	CARTHOUSEView();
	DECLARE_DYNCREATE(CARTHOUSEView)

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ARTHOUSE_FORM };
#endif

	// 특성입니다.
public:
	CARTHOUSEDoc* GetDocument() const;
	CWinThread *p2; //스레드 객체주소
	CWinThread *pThread1, *pThread2;
	ThreadArg arg1, arg2;
	static UINT Weather_Renewal(LPVOID arg);


	// 작업입니다.
public:

	// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.
									// 구현입니다.

									// 구현입니다.
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

	// 생성된 메시지 맵 함수
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

#ifndef _DEBUG  // ARTHOUSEView.cpp의 디버그 버전
inline CARTHOUSEDoc* CARTHOUSEView::GetDocument() const
{
	return reinterpret_cast<CARTHOUSEDoc*>(m_pDocument);
}
#endif

