// PhoneClient.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPhoneClientApp:
// �йش����ʵ�֣������ PhoneClient.cpp
//

class CPhoneClientApp : public CWinApp
{
public:
	CPhoneClientApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CPhoneClientApp theApp;