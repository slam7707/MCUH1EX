
// MCUH1EXDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MCUH1EX.h"
#include "MCUH1EXDlg.h"
#include "afxdialogex.h"
#include "MCU1Common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Implementation
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

CMCUH1EXDlg::CMCUH1EXDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MCUH1EX_DIALOG, pParent)
	, m_sz_status(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_b_thd_flag = FALSE;
}

void CMCUH1EXDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT4, m_sz_status);
}

UINT CMCUH1EXDlg::ThreadMain(LPVOID param)
{
	CMCUH1EXDlg* pDlg = (CMCUH1EXDlg*)param;
	BOOL *bCon = &pDlg->m_b_thd_flag;

	int nPos = 0, nVelo = 0;
	CString szPara;

	while (*bCon) {
		if (mcu1_connect_check() == OK) {
			pDlg->m_sz_status = _T("Connect");

			if (mcu1_read_current_position(nPos) == OK && mcu1_read_velocity(nVelo) == OK){		// mcuh1 현재 위치, 현재 속도 
				szPara.Format(_T("%0.3lf"), (double)nPos / 1000);								// 마이크로 단위 변경
				pDlg->SetDlgItemText(IDC_EDIT5, szPara);

				szPara.Format(_T("%d"), nVelo);
				pDlg->SetDlgItemText(IDC_EDIT6, szPara);

			}

		}else{
			*bCon = FALSE;
			mcu1_terminate();

			pDlg->m_sz_status = _T("Connection Fail");
		}
		pDlg->SetDlgItemText(IDC_EDIT4, pDlg->m_sz_status);
		Sleep(100);
	}

	return 0;
}

BEGIN_MESSAGE_MAP(CMCUH1EXDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON1, &CMCUH1EXDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CMCUH1EXDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &CMCUH1EXDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CMCUH1EXDlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// CMCUH1EXDlg message handlers

BOOL CMCUH1EXDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(1);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMCUH1EXDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMCUH1EXDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMCUH1EXDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int CMCUH1EXDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

void CMCUH1EXDlg::OnBnClickedButton1()
{
	int nPortNum = GetDlgItemInt(IDC_EDIT1);
	int nResult = 0;

	if (nPortNum != 0) {
		if (mcu1_initialization() == OK && mcu1_serial_connect(nPortNum) == OK) {		// mcuh1 dll 초기화, 시리얼 포트 접속 성공시
			m_sz_status = _T("Connect");												// 상태 메세지

			m_b_thd_flag = TRUE;														// mcuh1 접속 플래그
			m_thd_main = ::AfxBeginThread(ThreadMain, this);
		}
		else {																			// 접속 실패시 
			m_sz_status = _T("Connect Fail");
			mcu1_terminate();															//mcuh1 dll 해제
		}
	}
	else m_sz_status = _T("Port Num Empty");

	SetDlgItemText(IDC_EDIT4, m_sz_status);
}

void CMCUH1EXDlg::OnBnClickedButton3()
{
	if (m_b_thd_flag && mcu1_set_org_mode() == OK) {									// mcuh1 접속상태 정상, mcuh1 원점 모드로 변경
		mcu1_jog_origin_move(1, 1);														// 원점 실행
	}
}

void CMCUH1EXDlg::OnBnClickedButton5()
{
	if (m_b_thd_flag && mcu1_reset() == OK) {											// mcuh1 접속상태 정상, mcuh1 리셋 실행 

	}
}

BOOL CMCUH1EXDlg::PreTranslateMessage(MSG* pMsg)
{
	if (m_b_thd_flag) {																	// mcuh1 접속상태 정상
		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON2)->m_hWnd) {
			if (pMsg->message == WM_LBUTTONDOWN) {
				if (mcu1_set_jog_mode() == OK) mcu1_jog_origin_move(0, 1);				// 조그모드로 변경, 조그 + 실행
			}
			if (pMsg->message == WM_LBUTTONUP) {
				mcu1_jog_origin_move(0, 0);												// 조그 중지	
			}
		}

		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON4)->m_hWnd) {
			if (pMsg->message == WM_LBUTTONDOWN) {
				if (mcu1_set_jog_mode() == OK) mcu1_jog_origin_move(1, 1);				// 조그모드로 변경, 조그 - 실행
			}
			if (pMsg->message == WM_LBUTTONUP) {
				mcu1_jog_origin_move(0, 0);												// 조그 중지	
			}
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CMCUH1EXDlg::OnBnClickedButton6()
{
	if (m_b_thd_flag && mcu1_set_step_mode() == OK) {									// mcuh1 접속상태 정상, 스텝모드로 변경
		CString szPara;

		BOOL bSel = FALSE;
		int nPos = 0, nVelo = 0;

		GetDlgItemText(IDC_EDIT2, szPara);												// 스텝옵션 위치 파라미터 입력
		nPos = _ttof(szPara) * 1000;													

		GetDlgItemText(IDC_EDIT3, szPara);												// 스텝옵션 속도 파라미터	입력
		nVelo = _ttof(szPara);
		if (nVelo == 0) nVelo = 500;

        bSel = ((CButton*)GetDlgItem(IDC_RADIO2))->GetCheck();							// 스텝옵션 절대위치 or 증분위치 운전선택


		if (mcu1_step_option(nPos, nVelo, bSel) == OK) {								// 스텝옵션 실행

		}
	}
}
