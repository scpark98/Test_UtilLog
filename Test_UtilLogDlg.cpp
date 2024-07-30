
// Test_UtilLogDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Test_UtilLog.h"
#include "Test_UtilLogDlg.h"
#include "afxdialogex.h"

#include <imm.h>

#include <thread>
#include "../../Common/Functions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTestUtilLogDlg 대화 상자



CTestUtilLogDlg::CTestUtilLogDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TEST_UTILLOG_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestUtilLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestUtilLogDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CTestUtilLogDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTestUtilLogDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CTestUtilLogDlg 메시지 처리기

BOOL CTestUtilLogDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	/*
	[멀티바이트 환경]
	* - 유니코드로 만들어진 현재 날짜의 로그파일(UTF-8)이 이미 있다면
	    이를 지우고 프로그램을 실행해야 EUC-KR 인코딩의 로그파일이 새로 생성되고 정상적으로 저장된다.
	*   (그 반대인 경우도 마찬가지임)
	* - char 타입의 문자열을 logWrite, TRACE해도 정상이며 다만 logWrite의 리턴문자열은 VS의 변수값 표시창에서는 깨져서 표시되나
	*   CString에 리턴값을 받아보면 정상적으로 처리된다. CString str = CString(cstr); 로 정상 동작함.
	* 
	[유니코드 환경]
	* - char 타입의 문자열을 logWrite, TRACE로 그냥 출력하면 비정상 동작하나
	    CString(cstr)로 캐스팅하여 처리하면 모두 정상 동작함.
	  - 단, 메모리 상황에 따라 cstr의 뒷부분에 어떤 garbage가 존재할 지 장담할 수 없으므로
	    반드시 실제 데이터만 가지도록 \0을 추가해줘야 한다.

	[결론]
	  - char* 문자열을 사용할 경우 그 데이터의 끝에 '\0'이 있을 경우는 CString(cstr)로 사용하지만
	    끝문자가 없을 경우는 장담할 수 없으므로 char2CString(cstr, len)으로 길이까지 명확히 줘야한다.
	*/

	/*
	CString log;
	CString str;
	//char* cstr = "동해물과 백두산이";
	//char* cstr = "동해물과 백두산이\0";
	//char cstr[200000];
	char* cstr = new char[200];
	ZeroMemory(cstr, sizeof(char) * 200);

	strcpy(cstr, "동해물과 백두산이");

	TRACE(_T("CString(cstr) = %s\n"), CString(cstr));			//ok
	log = logWrite(_T("cstr = %s"), cstr);						//fail. 한글깨짐

	//유니코드에서 에러
	str = char2CString(cstr);
	log = logWrite(_T("char2CString(cstr) : %s"), str);			//fail "동해물과"까지만 출력

	str = CString(cstr);
	log = logWrite(_T("CString(cstr) : %s"), str);				//ok

	TRACE(_T("%s\n"), CString(cstr));

	delete[] cstr;
	*/

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CTestUtilLogDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CTestUtilLogDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

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
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CTestUtilLogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTestUtilLogDlg::OnBnClickedOk()
{
	//0 ~ 999까지 반복되는 thread_function()을 호출한다.
	SetWindowText(i2S(m_thread_index));

	int max_loop = 1000;

	//각 thread는 0 ~ 999, 1000 ~ 1999, ..., 9000 ~ 9999까지 반복된다.
	std::thread th(&CTestUtilLogDlg::thread_function, this, m_thread_index, m_thread_index * max_loop, m_thread_index * max_loop + max_loop);
	th.detach();

	m_thread_index++;
}


void CTestUtilLogDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}

void CTestUtilLogDlg::thread_function(int thread_index, int start, int end)
{
	for (int i = start; i < end; i++)
	{
		logWrite(_T("thread_index = %d, loop = %d"), thread_index, i);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	logWrite(_T("thread %d terminated."), thread_index);
}