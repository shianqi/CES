// CESAdminDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CES.h"
#include "CESAdminDlg.h"
#include "afxdialogex.h"


// CCESAdminDlg �Ի���

IMPLEMENT_DYNAMIC(CCESAdminDlg, CDialogEx)

CCESAdminDlg::CCESAdminDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCESAdminDlg::IDD, pParent)
	, val_total_minutes(0)
	, val_total_questions(0)
	, val_audio_format(_T(""))
	, val_max_speed(0)
	, val_percentage_accuracy(0)
	, val_percentage_speed(0)
{
	init();
}

CCESAdminDlg::~CCESAdminDlg()
{
}

void CCESAdminDlg::init(){
	CString percentage_accuracy_cs;
	CString percentage_speed_cs;


	//��ȡInt
	val_total_minutes = GetPrivateProfileInt(L"ExamInfo",L"total_minutes",0,L".\\typist.ini");
	val_total_questions = GetPrivateProfileInt(L"ExamInfo" ,L"total_questions", 0,L".\\typist.ini");
	val_max_speed = GetPrivateProfileInt(L"ExamInfo" ,L"max_speed", 0,L".\\typist.ini");

	//��ȡCString
	GetPrivateProfileString(L"ExamInfo",L"percentage_accuracy",L"",percentage_accuracy_cs.GetBuffer(MAX_PATH),MAX_PATH,L".\\typist.ini");
	GetPrivateProfileString(L"ExamInfo",L"percentage_speed",L"",percentage_speed_cs.GetBuffer(MAX_PATH),MAX_PATH,L".\\typist.ini");

	//CString ת�� double
	val_percentage_accuracy = transformPlus.toDouble(percentage_accuracy_cs);
	val_percentage_speed = transformPlus.toDouble(percentage_speed_cs);

	GetPrivateProfileString(L"ExamInfo",L"audio_format",L"",val_audio_format.GetBuffer(MAX_PATH),MAX_PATH,L".\\typist.ini");
	//UpdateData(false);
}

void CCESAdminDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, val_total_minutes);
	DDV_MinMaxInt(pDX, val_total_minutes, 0, 180);
	DDX_Text(pDX, IDC_EDIT4, val_total_questions);
	DDV_MinMaxInt(pDX, val_total_questions, 0, 20);
	DDX_Text(pDX, IDC_EDIT5, val_audio_format);
	DDV_MaxChars(pDX, val_audio_format, 10);
	DDX_Text(pDX, IDC_EDIT6, val_max_speed);
	DDX_Text(pDX, IDC_EDIT7, val_percentage_accuracy);
	DDV_MinMaxDouble(pDX, val_percentage_accuracy, 0, 1);
	DDX_Text(pDX, IDC_EDIT8, val_percentage_speed);
	DDV_MinMaxDouble(pDX, val_percentage_speed, 0, 1);
}


BEGIN_MESSAGE_MAP(CCESAdminDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CCESAdminDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CCESAdminDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CCESAdminDlg ��Ϣ�������

//ȷ��
void CCESAdminDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	WritePrivateProfileString(L"ExamInfo",L"audio_format",val_audio_format,L".\\typist.ini"); 
	UpdateData(false);
	CDialogEx::OnOK();
}

//��ԭĬ��ֵ
void CCESAdminDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	val_total_minutes = 15;
	val_total_questions = 5;
	val_audio_format = L"mp3";
	val_max_speed = 100;
	val_percentage_accuracy = 0.7;
	val_percentage_speed = 0.3;

	UpdateData(false);
}
