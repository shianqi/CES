// CESAdminDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CES.h"
#include "CESAdminDlg.h"
#include "afxdialogex.h"

BOOL CCESAdminDlg::OnInitDialog(){
	CDialogEx::OnInitDialog();
	init();
	return TRUE;
}

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
	, val2_question_number(_T(""))
	, val_right_answer(_T(""))
{
	
}

CCESAdminDlg::~CCESAdminDlg()
{
}

void CCESAdminDlg::init(){
	CString percentage_accuracy_cs;
	CString percentage_speed_cs;

	UpdateData(true);
	//��ȡInt
	val_total_minutes = GetPrivateProfileInt("ExamInfo","total_minutes",0,".\\typist.ini");
	val_total_questions = GetPrivateProfileInt("ExamInfo" ,"total_questions", 0,".\\typist.ini");
	val_max_speed = GetPrivateProfileInt("ExamInfo" ,"max_speed", 0,".\\typist.ini");

	//��ȡCString
	GetPrivateProfileString("ExamInfo","percentage_accuracy","",percentage_accuracy_cs.GetBuffer(MAX_PATH),MAX_PATH,".\\typist.ini");
	GetPrivateProfileString("ExamInfo","percentage_speed","",percentage_speed_cs.GetBuffer(MAX_PATH),MAX_PATH,".\\typist.ini");

	//CString ת�� double
	val_percentage_accuracy = transformPlus.toDouble(percentage_accuracy_cs);
	val_percentage_speed = transformPlus.toDouble(percentage_speed_cs);

	GetPrivateProfileString("ExamInfo","audio_format","",val_audio_format.GetBuffer(MAX_PATH),MAX_PATH,".\\typist.ini");
	

	for(int i= 1;i<=val_total_questions;i++){
		CString str = transformPlus.toCString(i);
		cb2_question_number.AddString(str);
	}
	UpdateData(false);
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
	DDX_Control(pDX, IDC_COMBO1, cb2_question_number);
	DDX_CBString(pDX, IDC_COMBO1, val2_question_number);
	DDX_Text(pDX, IDC_EDIT2, val_right_answer);
}

BEGIN_MESSAGE_MAP(CCESAdminDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CCESAdminDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CCESAdminDlg::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CCESAdminDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON2, &CCESAdminDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CCESAdminDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CCESAdminDlg ��Ϣ�������

//ȷ��
void CCESAdminDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	WritePrivateProfileString("ExamInfo","audio_format",val_audio_format,".\\typist.ini");

	WritePrivateProfileString("ExamInfo","total_minutes",transformPlus.toCString(val_total_minutes),".\\typist.ini");
	WritePrivateProfileString("ExamInfo","total_questions",transformPlus.toCString(val_total_questions),".\\typist.ini");
	WritePrivateProfileString("ExamInfo","max_speed",transformPlus.toCString(val_max_speed),".\\typist.ini");

	WritePrivateProfileString("ExamInfo","percentage_accuracy",transformPlus.toCString(val_percentage_accuracy),".\\typist.ini");
	WritePrivateProfileString("ExamInfo","percentage_speed",transformPlus.toCString(val_percentage_speed),".\\typist.ini");
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

//���ı���Ŀʱ
void CCESAdminDlg::OnCbnSelchangeCombo1()
{
	UpdateData(true);



	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString fileName="answer";
	CString str;

	cb2_question_number.GetLBText(cb2_question_number.GetCurSel(),str);

	val2_question_number = str;
	UpdateData(false);
	fileName+=str;
	getAnswer(fileName);
}

//��ȡ�𰸣������ص��Ի���
void CCESAdminDlg::getAnswer(CString str){
	UpdateData(true);
	GetPrivateProfileString("Answer",str,"-1",right_answer.GetBuffer(2000),2000,".\\typist.ini");

	string s(right_answer.GetBuffer());
	s = uncrypt(s);
	CString cstr(s.c_str());

	val_right_answer = cstr;
	UpdateData(false);
}

//�����ı�
void CCESAdminDlg::OnBnClickedButton2()
{
	UpdateData(true);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString fileName="answer";
	CString str;
	cb2_question_number.GetLBText(cb2_question_number.GetCurSel(),str);
	fileName+=str;

	string s(val_right_answer.GetBuffer());
	s = encrypt(s);
	CString cstr(s.c_str());

	WritePrivateProfileString("Answer",fileName,cstr,".\\typist.ini");
	MessageBox("����ɹ�");
	UpdateData(false);
}

//����·��
void CCESAdminDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	BROWSEINFO bi;	                   //BROWSEINFO�ṹ�кܶ��Ա���������Լ�����
	ZeroMemory(&bi,sizeof(BROWSEINFO));     //����&biΪ��ʼ��ַ����СΪsizeof(BROWSEINFO)���ڴ�������0���
	bi.ulFlags=BIF_BROWSEINCLUDEFILES;        //���õ����ĶԻ������ԡ��˴���˼Ϊ�����ļ�������������ֵ��Ĭ�ϵ���ֻ���ļ��С�ulFlags�����Զ���ܶ�������
	//bi.ulFlags=BIF_NEWDIALOGSTYLE;            //���ڿ��Ե�����С�����½��ļ��а�ť
	//bi.lpszTitle=L"ָ��Ҫ������ļ���";       //�ڴ�������ʾ��ʾ�û������
	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);   //Displays a dialog box enabling the user to select a Shell folder.
	TCHAR * path = new TCHAR[MAX_PATH];
	if(pidl != NULL)
	{
		SHGetPathFromIDList(pidl,path);      //Converts an item identifier list to a file system path
		MessageBox(path);
	}
}

//����
string CCESAdminDlg::encrypt(string str){
	for(int i=0;i<str.length();i++){
		str[i]++;
	}
	return str;
}

//����
string CCESAdminDlg::uncrypt(string str){
	for(int i=0;i<str.length();i++){
		str[i]--;
	}
	return str;
}