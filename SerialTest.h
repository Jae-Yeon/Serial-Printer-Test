// SerialTest.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error PCH���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����Ͻʽÿ�.
#endif

#include "resource.h"		// �� ��ȣ


// CSerialTestApp:
// �� Ŭ������ ������ ���ؼ��� SerialTest.cpp�� �����Ͻʽÿ�.
//

class CSerialTestApp : public CWinApp
{
public:
	CSerialTestApp();

// ������
	public:
	virtual BOOL InitInstance();

// ����

	DECLARE_MESSAGE_MAP()
};

extern CSerialTestApp theApp;
