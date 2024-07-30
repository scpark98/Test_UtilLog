
// Test_UtilLogDlg.h: 헤더 파일
//

#pragma once


// CTestUtilLogDlg 대화 상자
class CTestUtilLogDlg : public CDialogEx
{
// 생성입니다.
public:
	CTestUtilLogDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEST_UTILLOG_DIALOG };
#endif

protected:
	enum ENUM_LIST
	{
		enum_test = 0,
		enum_test1,
	};

	int		m_thread_index = 0;
	void	thread_function(int thread_index, int start, int end);

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
