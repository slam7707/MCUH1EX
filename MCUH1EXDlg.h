
// MCUH1EXDlg.h : header file
//

#pragma once


// CMCUH1EXDlg dialog
class CMCUH1EXDlg : public CDialogEx
{
// Construction
public:
	CMCUH1EXDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MCUH1EX_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

private:
	CWinThread* m_thd_main;			// mcuh1 정보 스레드
	static UINT ThreadMain(LPVOID param);

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBnClickedButton1();

	CString m_sz_status;			// mcuh1 접속 상태 메세지 변수
	BOOL m_b_thd_flag;				// mcuh1 접속 플래그

	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton5();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButton6();
};
