
// ARTHOUSE.h : ARTHOUSE ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CARTHOUSEApp:
// �� Ŭ������ ������ ���ؼ��� ARTHOUSE.cpp�� �����Ͻʽÿ�.
//

class CARTHOUSEApp : public CWinApp
{
public:
	CARTHOUSEApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CARTHOUSEApp theApp;
