
// CESDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CES.h"
#include "CESDlg.h"
#include "afxdialogex.h"
#include "cCheckIdCard.h"
#include "pdflib.h"
#include <MMSystem.h>
#include <string>
#include <stdio.h>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "PDFLib.lib")

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
	, val_question_number(_T(""))
	, val_answer_sheet(_T(""))
	, total_minutes(0)
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
	DDX_CBString(pDX, IDC_QUESTION_NUMBER, val_question_number);
	DDX_Text(pDX, IDC_ANSWER_SHEET, val_answer_sheet);
	DDX_Control(pDX, IDC_ANSWER_SHEET, ed_answer_sheet);
	DDX_Control(pDX, IDC_TICKET_NUMBER, ed_ticket_number);
	DDX_Control(pDX, IDC_ID_NUMBER, ed_id_number);
	DDX_Control(pDX, IDC_QUESTION_NUMBER, cb_question_number);
	DDX_Control(pDX, IDC_SUBMIT_BUTTON, bt_submit_button);
	DDX_Control(pDX, IDC_PRINT_BUTTON, bt_print_button);
}

BEGIN_MESSAGE_MAP(CCESDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_BN_CLICKED(IDC_BUTTON3, &CCESDlg::OnBnClickedButton3)
ON_BN_CLICKED(IDC_BEGIN_TEST, &CCESDlg::OnBnClickedBeginTest)
ON_WM_TIMER()
ON_BN_CLICKED(IDC_SUBMIT_BUTTON, &CCESDlg::OnBnClickedSubmitButton)
ON_BN_CLICKED(IDC_PRINT_BUTTON, &CCESDlg::OnBnClickedPrintButton)
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
	readIni();
	
	if(!check_ticket_number(val_tecket_number)){
		return;
	}

	if(!check_id_number(val_id_number)){
		return;
	}

	if(val_question_number==""){
		MessageBox(_T("请选择试题编号"));
		return;
	}

	bt_begin_test.EnableWindow(FALSE);//让按钮无法点击
	ed_ticket_number.EnableWindow(FALSE);
	ed_id_number.EnableWindow(FALSE);
	cb_question_number.EnableWindow(FALSE);
	ed_answer_sheet.EnableWindow(TRUE);//让文本框可以输入
	bt_submit_button.EnableWindow(TRUE);
	SetTimer(1,1000,NULL);

	playMusic();
	Invalidate();
}

void CCESDlg::readIni(){
	CString percentage_accuracy_cs;
	CString percentage_speed_cs;

	//读取Int
	total_minutes = GetPrivateProfileInt(L"ExamInfo",L"total_minutes",0,L".\\typist.ini");
	total_questions = GetPrivateProfileInt(L"ExamInfo" ,L"total_questions", 0,L".\\typist.ini");
	max_spee = GetPrivateProfileInt(L"ExamInfo" ,L"max_spee", 0,L".\\typist.ini");

	//读取CString
	GetPrivateProfileString(L"ExamInfo",L"percentage_accuracy",L"",percentage_accuracy_cs.GetBuffer(MAX_PATH),MAX_PATH,L".\\typist.ini");
	GetPrivateProfileString(L"ExamInfo",L"percentage_speed",L"",percentage_speed_cs.GetBuffer(MAX_PATH),MAX_PATH,L".\\typist.ini");

	//CString 转到 double
	percentage_accuracy = _wtof(percentage_accuracy_cs);
	percentage_speed = _wtof(percentage_speed_cs);

	GetPrivateProfileString(L"ExamInfo",L"audio_format",L"",audio_format.GetBuffer(MAX_PATH),MAX_PATH,L".\\typist.ini");


	CString t;
	t.Format(L"%f",percentage_accuracy);
	//MessageBox(t);
}

MCI_OPEN_PARMS op;
void CCESDlg::playMusic(){
	DWORD cdlen;//音频文件长度
	op.dwCallback=NULL; 
	op.lpstrAlias=NULL; 
	op.lpstrDeviceType=audio_format;  //设备类型，大多数文件可以这样设置 
	op.lpstrElementName=_T(".\\music.mp3"); //文件路径 
	op.wDeviceID=NULL;      //打开设备成功以后保存这个设备号备用 
	UINT rs;        //接受函数返回结果 
	//发送命令打开设备，成功返回0，否则返回错误号，第三个参数这里必须MCI_OPEN_ELEMENT  
	rs=mciSendCommand(NULL,MCI_OPEN,MCI_OPEN_ELEMENT,(DWORD)&op);
	mciSendCommand(NULL,MCI_SET,MCI_SET_DOOR_OPEN,NULL);
	cdlen = getInfo(op.wDeviceID,MCI_STATUS_LENGTH);//获取音频文件长度
	
	if(rs==0)        //设备打开成功就播放文件 
	{ 
		MCI_PLAY_PARMS pp; 
		pp.dwCallback=NULL; 
		pp.dwFrom=0;      //开始播放的位置 
		mciSendCommand(op.wDeviceID,MCI_PLAY,MCI_NOTIFY,(DWORD)&pp);
		//播放文件，如果第三个参数设为MCI_WAIT则程序窗口会被阻塞，为了避免这种情况可以设为MCI_NOTIFY 
	}
	//Sleep(cdlen);//根据文件长度等待，与MCI_WAIT效果一样，cdlen参数可以控制播放时间
	//stopMusic();
}

DWORD CCESDlg::getInfo(UINT wDeviceID,DWORD item){
	MCI_STATUS_PARMS mcistatusparms;
	mcistatusparms.dwCallback=(DWORD)GetSafeHwnd();
	mcistatusparms.dwItem=item;
	mcistatusparms.dwReturn=0;
	mciSendCommand(wDeviceID,MCI_STATUS,MCI_STATUS_ITEM,(DWORD)&mcistatusparms);
	return mcistatusparms.dwReturn;
}

void CCESDlg::stopMusic(){
	//在WM_CLOSE消息处理过程中发送MCI_CLOSE命令关闭设备
	MCI_GENERIC_PARMS gp; 
	gp.dwCallback=NULL; 
	mciSendCommand(op.wDeviceID,MCI_CLOSE,MCI_WAIT,(DWORD)&gp);  
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

//提交成绩
void CCESDlg::OnBnClickedSubmitButton()
{
	// TODO: 在此添加控件通知处理程序代码
	bt_submit_button.EnableWindow(FALSE);
	bt_print_button.EnableWindow(TRUE);
	ed_answer_sheet.EnableWindow(FALSE);
	//停止音乐
	stopMusic();
}


//打印成绩单
void CCESDlg::OnBnClickedPrintButton()
{
	if(create_pdf(val_tecket_number, val_id_number, 4,2,3,val_answer_sheet)){
		MessageBox(_T("打印成功，请在程序根目录查看文件“grade.pdf”"));
	}
	// TODO: 在此添加控件通知处理程序代码
}


bool CCESDlg::create_pdf(CString val_ticket_number, CString val_id_number, 
	double accuracy_rate, double typing_speed, double grade, CString text)
{
	remove("Grade.pdf");

    PDF *p;

    if ((p = PDF_new()) == (PDF *) 0){
        printf("Couldn't create PDFlib object (out of memory)!/n");
        return false;
    }

    PDF_TRY(p) {
        /* This means we must check return values of load_font() etc. */
        //PDF_set_parameter(p, "errorpolicy", "return");

        if (PDF_begin_document(p, "./Grade.pdf", 0, "") == -1) {
            printf("Error: %s/n", PDF_get_errmsg(p));
            return false;
        }

        /* This line is required to avoid problems on Japanese systems */
        PDF_set_parameter(p, "hypertextencoding", "host");
        //PDF_set_parameter(p, "fakebold", "true");



        PDF_set_info(p, "Creator", "hello.c");
        PDF_set_info(p, "Author", "Thomas Merz");
        PDF_set_info(p, "Title", "Hello, world (C)!");

        PDF_begin_page_ext(p, a4_width, a4_height, "");

        int font_song = PDF_findfont(p,"STSong-Light", "GB-EUC-H", 0);
        PDF_setfont(p,font_song, 12);
        PDF_set_text_pos(p,50, a4_height - 50);



        USES_CONVERSION;
        string s = T2A(( val_ticket_number.GetBuffer()));
        s = "准考证号：" + s;
        PDF_show(p,s.c_str());

        PDF_set_text_pos(p,50, a4_height - 65);
        s = T2A(( val_id_number.GetBuffer()));
        s = "身份证号：" + s;
        PDF_show(p,s.c_str());

        PDF_setfont(p,font_song, 8);
        PDF_set_text_pos(p,50, a4_height - 85);
        CString cs;
		cs.Format(L"您打字的正确率是%f，速度是%f字/分钟，本次考试的成绩是%f分",accuracy_rate,typing_speed,grade);
        s = T2A(cs.GetBuffer());
        PDF_show(p,s.c_str());

        PDF_setfont(p,font_song, 8);
        PDF_set_text_pos(p,50, a4_height - 100);
        s="以下是您本次考试录入的内容:";
        PDF_show(p,s.c_str());

        PDF_set_text_pos(p,50, a4_height - 130);
        s = T2A(text.GetBuffer());
        PDF_show(p,s.c_str());
        //PDF_setcolor(p, "fill", "cmyk", 1, 0,0,0);
        //PDF_rect(p, 250,250, 250, 250);




        //PDF_fill(p);

        PDF_end_page_ext(p, "");
        PDF_end_document(p, "");
    }

    PDF_CATCH(p) {
        printf("PDFlib exception occurred in sample:/n");
        printf("[%d] %s: %s/n",
            PDF_get_errnum(p), PDF_get_apiname(p), PDF_get_errmsg(p));
        CString cs;
        cs.Format(L"[%d] %s: %s/n",
            PDF_get_errnum(p), PDF_get_apiname(p), PDF_get_errmsg(p));
        PDF_delete(p);

        return false;
    }

    PDF_delete(p);
    return true;
}
