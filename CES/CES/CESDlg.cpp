
// CESDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CES.h"
#include "CESDlg.h"
#include "afxdialogex.h"
#include "cCheckIdCard.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCESDlg 对话框




CCESDlg::CCESDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCESDlg::IDD, pParent)
	, overplus_time(0)
	, idc_time_left(_T(""))
	, val_tecket_number(_T(""))
	, val_id_number(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCESDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BEGIN_TEST, bt_begin_test);
	DDX_Text(pDX, IDC_TIME_LEFT, idc_time_left);
	DDX_Text(pDX, IDC_TICKET_NUMBER, val_tecket_number);
	DDV_MaxChars(pDX, val_tecket_number, 11);
	DDX_Text(pDX, IDC_ID_NUMBER, val_id_number);
	DDV_MaxChars(pDX, val_id_number, 18);
}

BEGIN_MESSAGE_MAP(CCESDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_BN_CLICKED(IDC_BUTTON3, &CCESDlg::OnBnClickedButton3)
ON_BN_CLICKED(IDC_BEGIN_TEST, &CCESDlg::OnBnClickedBeginTest)
ON_WM_TIMER()
END_MESSAGE_MAP()


// CCESDlg 消息处理程序

BOOL CCESDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCESDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCESDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCESDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





void CCESDlg::OnBnClickedBeginTest()
{
	UpdateData(TRUE);	

	if(!check_ticket_number(val_tecket_number)){
		return;
	}
	if(!check_id_number(val_id_number)){
		return;
	}

	bt_begin_test.EnableWindow(FALSE);//让按钮无法点击
	SetTimer(1,1000,NULL);
}


void CCESDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	UpdateData(TRUE);
	idc_time_left = getOverplus_time(++overplus_time);
    UpdateData(FALSE);
	CDialogEx::OnTimer(nIDEvent);
}


CString CCESDlg::getOverplus_time(int time_left)
{
	int sum = 15*60 - time_left;
    int second = sum % 60;
    int minute = sum / 60;
    CString t;
    t.Format(L"距考试结束还有：%d分%d秒",minute,second);
    return t;
}

/**
 * 检查准考证号是否合法
 */
bool CCESDlg::check_ticket_number(CString ticketNumber)
{
	if(ticketNumber.GetLength()!=11){
		MessageBox(_T("准考证必须为11位数字"));
		return false;
	}
	return true;
}

/**
 * 检查身份证号是否合法
 */
bool CCESDlg::check_id_number(CString idNumber)
{
	if(idNumber.GetLength()!=18){
		MessageBox(_T("身份证信息长度为18位"));
		return false;
	}
	cCheckIdCard tempID;
	USES_CONVERSION; 
	string str(W2A(idNumber));
	bool b = tempID.CheckIDCard(str);
	if(b){
		return true;
	}else{
		MessageBox(_T("身份证信息不合法！"));
	}
	return false;
}
