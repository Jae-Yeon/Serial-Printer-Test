// SerialTestDlg.h : ��� ����
//
//1234
#pragma once
#include "afxcmn.h"
#include "PYH_Comm.h"

// CSerialTestDlg ��ȭ ����
class CSerialTestDlg : public CDialog
{
// ����
public:
	CPYH_Comm* m_Comm;
	LRESULT	OnThreadClosed(WPARAM length, LPARAM lpara);
	LRESULT	OnReceive(WPARAM length, LPARAM lpara);
	CSerialTestDlg(CWnd* pParent = NULL);	// ǥ�� ������

// ��ȭ ���� ������
	enum { IDD = IDD_SERIALTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ����


// ����
protected:
	HICON m_hIcon;

	// �޽��� �� �Լ��� �����߽��ϴ�.
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_SendData;
	CRichEditCtrl m_RcvData;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();

	static CString excuteCurl(CString jsonObj,CString jsonUrl);
	static bool boxPickUpsStatus(CString AreaCode,int setTemp, int latestTemp, bool tempStatus, bool sensorStatus, bool ambientStatus);

	void InitRichEdit(void);
	afx_msg void OnBnClickedButton4();
};
