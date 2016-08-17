
// CESDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CES.h"
#include "CESDlg.h"
#include "afxdialogex.h"
#include "cCheckIdCard.h"
#include "pdflib.h"
#include <string>
#include <stdio.h>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(lib, "PDFLib.lib")

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CCESDlg �Ի���




CCESDlg::CCESDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCESDlg::IDD, pParent)
	, overplus_time(0)
	, idc_time_left(_T(""))
	, val_tecket_number(_T(""))
	, val_id_number(_T(""))
	, val_question_number(_T(""))
	, val_answer_sheet(_T(""))
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


// CCESDlg ��Ϣ�������

BOOL CCESDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCESDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();

		int port = 0;
		port = GetPrivateProfileInt(L"ExamInfo",L"total_questions",0,L".\\typist.ini");
		
		CString t;
		t.Format(L"%d",port);
		MessageBox(t);
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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

	if(val_question_number==""){
		MessageBox(_T("��ѡ��������"));
		return;
	}

	bt_begin_test.EnableWindow(FALSE);//�ð�ť�޷����
	ed_ticket_number.EnableWindow(FALSE);
	ed_id_number.EnableWindow(FALSE);
	cb_question_number.EnableWindow(FALSE);
	ed_answer_sheet.EnableWindow(TRUE);//���ı����������
	bt_submit_button.EnableWindow(TRUE);
	SetTimer(1,1000,NULL);
}


void CCESDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
    t.Format(L"�࿼�Խ������У�%d��%d��",minute,second);
    return t;
}

/**
 * ���׼��֤���Ƿ�Ϸ�
 */
bool CCESDlg::check_ticket_number(CString ticketNumber)
{
	if(ticketNumber.GetLength()!=11){
		MessageBox(_T("׼��֤����Ϊ11λ����"));
		return false;
	}
	return true;
}

/**
 * ������֤���Ƿ�Ϸ�
 */
bool CCESDlg::check_id_number(CString idNumber)
{
	if(idNumber.GetLength()!=18){
		MessageBox(_T("���֤��Ϣ����Ϊ18λ"));
		return false;
	}
	cCheckIdCard tempID;
	USES_CONVERSION; 
	string str(W2A(idNumber));
	bool b = tempID.CheckIDCard(str);
	if(b){
		return true;
	}else{
		MessageBox(_T("���֤��Ϣ���Ϸ���"));
	}
	return false;
}

//�ύ�ɼ�
void CCESDlg::OnBnClickedSubmitButton()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	bt_submit_button.EnableWindow(FALSE);
	bt_print_button.EnableWindow(TRUE);
}


//��ӡ�ɼ���
void CCESDlg::OnBnClickedPrintButton()
{
	if(create_pdf(val_tecket_number, val_id_number, 4,2,3,val_answer_sheet)){
		MessageBox(_T("��ӡ�ɹ������ڳ����Ŀ¼�鿴�ļ���grade.pdf��"));
	}
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
        s = "׼��֤�ţ�" + s;
        PDF_show(p,s.c_str());

        PDF_set_text_pos(p,50, a4_height - 65);
        s = T2A(( val_id_number.GetBuffer()));
        s = "���֤�ţ�" + s;
        PDF_show(p,s.c_str());

        PDF_setfont(p,font_song, 8);
        PDF_set_text_pos(p,50, a4_height - 85);
        CString cs;
		cs.Format(L"�����ֵ���ȷ����%f���ٶ���%f��/���ӣ����ο��Եĳɼ���%f��",accuracy_rate,typing_speed,grade);
        s = T2A(cs.GetBuffer());
        PDF_show(p,s.c_str());

        PDF_setfont(p,font_song, 8);
        PDF_set_text_pos(p,50, a4_height - 100);
        s="�����������ο���¼�������:";
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
