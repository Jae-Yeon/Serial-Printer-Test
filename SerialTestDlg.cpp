// SerialTestDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "SerialTest.h"
#include "SerialTestDlg.h"
#include ".\serialtestdlg.h"

#include "json.h"
#include <curl/curl.h>
#pragma comment(lib,"version.lib")

// curl 구동 후 데이터를 가져오기 위한 구조체
typedef struct _MemoryStruct {
	char *memory;
	size_t size;
} MemoryStruct;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 대화 상자 데이터
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원

// 구현
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CSerialTestDlg 대화 상자



CSerialTestDlg::CSerialTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSerialTestDlg::IDD, pParent)
	, m_SendData(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_Comm = NULL;
}

void CSerialTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_SendData);
	DDX_Control(pDX, IDC_RICHEDIT21, m_RcvData);
}

BEGIN_MESSAGE_MAP(CSerialTestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnBnClickedButton3)
	ON_MESSAGE(WM_MYRECEIVE,OnReceive)
	ON_MESSAGE(WM_MYCLOSE,OnThreadClosed)
	ON_BN_CLICKED(IDC_BUTTON4, &CSerialTestDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CSerialTestDlg 메시지 처리기

BOOL CSerialTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	// 프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	GetDlgItem(IDC_BUTTON1)->EnableWindow(true);
		GetDlgItem(IDC_BUTTON2)->EnableWindow(false);
	
	return TRUE;  // 컨트롤에 대한 포커스를 설정하지 않을 경우 TRUE를 반환합니다.
}

void CSerialTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면 
// 아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
// 프레임워크에서 이 작업을 자동으로 수행합니다.

void CSerialTestDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다. 
HCURSOR CSerialTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSerialTestDlg::OnBnClickedButton1()
{
	CString str = "COM8";
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_Comm= new CPYH_Comm("\\\\.\\"+str,"115200","None","8 Bit","1 Bit");	// initial Comm port
	if(	m_Comm->Create(GetSafeHwnd()) != 0)	//통신포트를 열고 윈도우의 핸들을 넘긴다.
	{
		AfxMessageBox("Open Success");
		m_Comm->Clear();
		GetDlgItem(IDC_BUTTON1)->EnableWindow(false);
		GetDlgItem(IDC_BUTTON2)->EnableWindow(true);
	}
	else
	{
		AfxMessageBox("Open Fail");
		GetDlgItem(IDC_BUTTON1)->EnableWindow(true);
		GetDlgItem(IDC_BUTTON2)->EnableWindow(false);
	}
}

void CSerialTestDlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(m_Comm)	//컴포트가 존재하면
	{
		m_Comm->Close();
		m_Comm = NULL;
		GetDlgItem(IDC_BUTTON1)->EnableWindow(true);
		GetDlgItem(IDC_BUTTON2)->EnableWindow(false);
	}
}

void CSerialTestDlg::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	GetDlgItem(IDC_EDIT1)->GetWindowText(str);
	m_Comm->Send(str,str.GetLength());
}


void CSerialTestDlg::OnBnClickedButton4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	char szTest[2] = {0x1B, 0x6D};
	m_Comm->Send(szTest,2);
}

LRESULT CSerialTestDlg::OnThreadClosed(WPARAM length, LPARAM lpara)
{
	//overlapped i/o 핸들을 닫는다.
	((CPYH_Comm*)lpara)->HandleClose();
	delete ((CPYH_Comm*)lpara);

	return 0;
}

void CSerialTestDlg::InitRichEdit(void)
{
	m_RcvData.SetBackgroundColor(false,RGB(221,220,222));
	CHARFORMAT cf;
	m_RcvData.GetDefaultCharFormat( cf );
	cf.crTextColor = RGB(55,55,55);
	cf.dwMask |= CFM_COLOR | CFM_BOLD | CFM_ITALIC | CFM_SIZE;
	cf.dwEffects &= (~CFE_AUTOCOLOR );
	cf.yHeight = 160;
	m_RcvData.SetDefaultCharFormat(cf);
}

LRESULT CSerialTestDlg::OnReceive(WPARAM length, LPARAM lpara)
{
	CString str;
	char data[20000];
	if(m_Comm)
	{
		m_Comm->Receive(data,length);
		data[length]='\0';
		for(int i = 0;i<(int)length;i++)
		{
			str += data[i];
		}
		CString arr[3];
		int curPos = 0;
		CString strToken;
		str = "200123456|123456";
		while ((strToken  = str.Tokenize("|", curPos)) != "")
			arr[curPos] = strToken;

		str = "";
	}

	return 0;
}

// Curl perform 값 저장
// ---------------------------------------------------------------------------------------
static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
	size_t realsize = size * nmemb;
	MemoryStruct *mem = (MemoryStruct *)userp;

	mem->memory = (char*)realloc(mem->memory, mem->size + realsize + 1);

	memcpy(&(mem->memory[mem->size]), contents, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;

	return realsize;
}

std::string cstrToStr(CString cStr)
{
	CT2CA pszConvertedAnsiString (cStr);
	std::string toStr(pszConvertedAnsiString);
	return toStr;
}

std::string boolToStr(bool bTmp)
{
	std::string isTrue;
	if(bTmp == true) isTrue = "1";
	else if(bTmp == false) isTrue = "0";
	return isTrue;
}