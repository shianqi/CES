// CESAdminDlg.cpp : 实现文件
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

// CCESAdminDlg 对话框

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
	, val_audio_path(_T(""))
{
	
}

CCESAdminDlg::~CCESAdminDlg()
{
}

void CCESAdminDlg::init(){
	CString percentage_accuracy_cs;
	CString percentage_speed_cs;

	UpdateData(true);
	//读取Int
	val_total_minutes = GetPrivateProfileInt("ExamInfo","total_minutes",0,".\\typist.ini");
	val_total_questions = GetPrivateProfileInt("ExamInfo" ,"total_questions", 0,".\\typist.ini");
	val_max_speed = GetPrivateProfileInt("ExamInfo" ,"max_speed", 0,".\\typist.ini");

	//读取CString
	GetPrivateProfileString("ExamInfo","percentage_accuracy","",percentage_accuracy_cs.GetBuffer(MAX_PATH),MAX_PATH,".\\typist.ini");
	GetPrivateProfileString("ExamInfo","percentage_speed","",percentage_speed_cs.GetBuffer(MAX_PATH),MAX_PATH,".\\typist.ini");

	//CString 转到 double
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
	DDX_Text(pDX, audio_path, val_audio_path);
}

BEGIN_MESSAGE_MAP(CCESAdminDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CCESAdminDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CCESAdminDlg::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CCESAdminDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON2, &CCESAdminDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CCESAdminDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CCESAdminDlg 消息处理程序

//确定
void CCESAdminDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
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

//还原默认值
void CCESAdminDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	val_total_minutes = 15;
	val_total_questions = 5;
	val_audio_format = L"mp3";
	val_max_speed = 100;
	val_percentage_accuracy = 0.7;
	val_percentage_speed = 0.3;

	UpdateData(false);
}

//当改变题目时
void CCESAdminDlg::OnCbnSelchangeCombo1()
{
	UpdateData(true);
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	cb2_question_number.GetLBText(cb2_question_number.GetCurSel(),str);
	val2_question_number = str;
	UpdateData(false);
	getAnswer(str);
}

//读取答案，并加载到对话框
void CCESAdminDlg::getAnswer(CString str){
	UpdateData(true);
	//读取音频路径
	CString audioPathCSt;
	CString str2 = "audio"+str;
	GetPrivateProfileString("Audio",str2,"-1",audioPathCSt.GetBuffer(2000),2000,".\\typist.ini");
	val_audio_path = audioPathCSt;

	//读取答案路径

	CFile file;
	CString FileName="./answer/answer"+str+".txt";
	char buf[1000];//读1K
	memset(buf,0,1000);//初始化内存，防止读出字符末尾出现乱码
	try{
		if(!file.Open(FileName,CFile::modeRead)){
			MessageBox("没有文件!");
			return;
		}
		file.Read(buf,sizeof(buf));
		file.Close();
		//m_data=buf;//给文本框赋值CString m_data
		val_right_answer = buf;
		//UpdateData(false);//在文本框显示
		//MessageBox("读出成功！");
	}catch(CFileException *e){
		CString str;
		str.Format("读取数据失败的原因是:%d",e->m_cause);
		MessageBox("str");
		file.Abort();
		e->Delete();
	}
	//GetPrivateProfileString("Answer",str1,"-1",right_answer.GetBuffer(2000),2000,".\\typist.ini");
	string s(val_right_answer.GetBuffer());
	s = uncrypt(s);
	CString cstr(s.c_str());
	val_right_answer = cstr;
	UpdateData(false);
}

//保存文本
void CCESAdminDlg::OnBnClickedButton2()
{
	//判断是否选择了试题
	CString questionStr;
	questionStr = val2_question_number;
	if(questionStr==""){
		MessageBox("请选择试题");
		return;
	}


	UpdateData(true);
	CString fileName="answer";
	CString str;
	cb2_question_number.GetLBText(cb2_question_number.GetCurSel(),str);
	fileName+=str;

	string s(val_right_answer.GetBuffer());
	s = encrypt(s);
	CString cstr(s.c_str());

	CFile file;
	CString FileName="./answer/"+fileName+".txt";
	try
	{
		file.Open(FileName,CFile::modeCreate|CFile::modeWrite);
		file.SeekToBegin();
		file.Write((unsigned char *)(cstr.GetBuffer(0)),cstr.GetLength());//CString m_data
		file.Flush();
		file.Close();
		MessageBox("保存成功！");
	}
	catch(CFileException *e)
	{
		CString str;
		str.Format("写入失败的原因是:%d",e->m_cause);
		MessageBox("str");
		file.Abort();
		e->Delete();
	}
	//WritePrivateProfileString("Answer",fileName,cstr,".\\typist.ini");
	UpdateData(false);
}

//更改路径
void CCESAdminDlg::OnBnClickedButton3()
{
	CString str;
	str = val2_question_number;
	if(str==""){
		MessageBox("请选择试题");
		return;
	}


	CString m_strFolderPath="D:\\audio";
// 判断路径是否存在 
	if (!PathIsDirectory(m_strFolderPath)){ 
		CString strMsg; 
		strMsg.Format ("指定路径\"%s\"不存在，是否创建?", m_strFolderPath); 
		if (AfxMessageBox(strMsg, MB_YESNO) == IDYES) { 
			if (!CreateDirectory(m_strFolderPath, NULL ) ) { 
				strMsg.Format ("创建路径\"%s\"失败！是否继续?", m_strFolderPath); 
				if (AfxMessageBox(strMsg, MB_YESNO) == IDYES) 
					return; 
			} 
		} 
	} 


	CFile m_file;
	CString m_filePath,m_fileName;

	CFileDialog dlg = CFileDialog(FALSE, NULL, NULL, OFN_READONLY,
		"Audio Files (*.mp3;*.WMA)|*.mp3;*.WMA|",this);
    if(dlg.DoModal() == IDCANCEL)
        return;
    
    if(m_file.m_hFile != CFile::hFileNull)
        OnClose();
 
    m_fileName = dlg.GetFileName();
 
    m_filePath = dlg.GetPathName();
    
	UpdateData();
	
	CString fpath = "D:\\audio\\audio"+str+".mp3";
	WritePrivateProfileString("Audio","audio"+str,fpath,"./typist.ini");
	::CopyFile(m_filePath,fpath,false);  
	//MessageBox(m_filePath);
	//MessageBox(fpath);
	MessageBox("保存成功");
}

//加密
string CCESAdminDlg::encrypt(string str){
	for(int i=0;i<str.length();i++){
		str[i]++;
	}
	return str;
}

//解密
string CCESAdminDlg::uncrypt(string str){
	for(int i=0;i<str.length();i++){
		str[i]--;
	}
	return str;
}