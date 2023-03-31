// SerialTestDlg.h : 헤더 파일
//
//1234
#pragma once
#include "afxcmn.h"
#include "PYH_Comm.h"

// CSerialTestDlg 대화 상자
class CSerialTestDlg : public CDialog
{
// 생성
public:
	CPYH_Comm* m_Comm;
	LRESULT	OnThreadClosed(WPARAM length, LPARAM lpara);
	LRESULT	OnReceive(WPARAM length, LPARAM lpara);
	CSerialTestDlg(CWnd* pParent = NULL);	// 표준 생성자

// 대화 상자 데이터
	enum { IDD = IDD_SERIALTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원


// 구현
protected:
	HICON m_hIcon;

	// 메시지 맵 함수를 생성했습니다.
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
