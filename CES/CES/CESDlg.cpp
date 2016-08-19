
// CESDlg.cpp : ʵ���ļ�
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
	readIni();
	
	
	if(!check_ticket_number(val_tecket_number)){
		return;
	}

	if(!check_id_number(val_id_number)){
		return;
	}
	
	if(!readAnswer(val_question_number)){
		return;
	}

	bt_begin_test.EnableWindow(FALSE);//�ð�ť�޷����
	ed_ticket_number.EnableWindow(FALSE);
	ed_id_number.EnableWindow(FALSE);
	cb_question_number.EnableWindow(FALSE);
	ed_answer_sheet.EnableWindow(TRUE);//���ı����������
	bt_submit_button.EnableWindow(TRUE);
	SetTimer(1,1000,NULL);

	playMusic();
	Invalidate();
}

void CCESDlg::readIni(){
	CString percentage_accuracy_cs;
	CString percentage_speed_cs;

	//��ȡInt
	total_minutes = GetPrivateProfileInt(L"ExamInfo",L"total_minutes",0,L".\\typist.ini");
	total_questions = GetPrivateProfileInt(L"ExamInfo" ,L"total_questions", 0,L".\\typist.ini");
	max_spee = GetPrivateProfileInt(L"ExamInfo" ,L"max_speed", 0,L".\\typist.ini");

	//��ȡCString
	GetPrivateProfileString(L"ExamInfo",L"percentage_accuracy",L"",percentage_accuracy_cs.GetBuffer(MAX_PATH),MAX_PATH,L".\\typist.ini");
	GetPrivateProfileString(L"ExamInfo",L"percentage_speed",L"",percentage_speed_cs.GetBuffer(MAX_PATH),MAX_PATH,L".\\typist.ini");

	//CString ת�� double
	percentage_accuracy = _wtof(percentage_accuracy_cs);
	percentage_speed = _wtof(percentage_speed_cs);

	GetPrivateProfileString(L"ExamInfo",L"audio_format",L"",audio_format.GetBuffer(MAX_PATH),MAX_PATH,L".\\typist.ini");


	CString t;
	t.Format(L"%f",percentage_accuracy);
	//MessageBox(t);
}

//��ȡ��ȷ��
bool CCESDlg::readAnswer(CString str){
	if(str==""){
		MessageBox(_T("��ѡ��������"));
		return false;
	}

	CFile file;
	CString FileName1=L"data";
	CString FileName2=L".txt";
	CString FileName = FileName1+str+FileName2;
	char buf[10000];//��1K
	memset(buf,0,10000);//��ʼ���ڴ棬��ֹ�����ַ�ĩβ��������
	try
	{
		if(!file.Open(FileName,CFile::modeRead))
		{
			MessageBox(L"no file!");
			return false;
		}
		file.Read(buf,sizeof(buf));
		file.Close();
		CString t;
		t.Format(L"%s",buf);
		//m_data=buf;//���ı���ֵCString m_data
		//UpdateData(false);//���ı�����ʾ
		//MessageBox(t);
		right_answer = t;
		return true;
	}catch(int e){
		MessageBox(_T("ERROR"));
		return false;
	}
}


/**
 * ����
 */
string CCESDlg::encrypt(string str){
	for(int i=0;i<str.length();i++){
		str[i]+=1;
	}
	return str;
}

/**
 * ����
 */
string CCESDlg::uncrypt(string str){
	for(int i=0;i<str.length();i++){
		str[i]-=1;
	}
	return str;
}

MCI_OPEN_PARMS op;
void CCESDlg::playMusic(){
	DWORD cdlen;//��Ƶ�ļ�����
	op.dwCallback=NULL; 
	op.lpstrAlias=NULL; 
	op.lpstrDeviceType=audio_format;  //�豸���ͣ�������ļ������������� 
	op.lpstrElementName=_T(".\\music.mp3"); //�ļ�·�� 
	op.wDeviceID=NULL;      //���豸�ɹ��Ժ󱣴�����豸�ű��� 
	UINT rs;        //���ܺ������ؽ�� 
	//����������豸���ɹ�����0�����򷵻ش���ţ������������������MCI_OPEN_ELEMENT  
	rs=mciSendCommand(NULL,MCI_OPEN,MCI_OPEN_ELEMENT,(DWORD)&op);
	mciSendCommand(NULL,MCI_SET,MCI_SET_DOOR_OPEN,NULL);
	cdlen = getInfo(op.wDeviceID,MCI_STATUS_LENGTH);//��ȡ��Ƶ�ļ�����
	
	if(rs==0)        //�豸�򿪳ɹ��Ͳ����ļ� 
	{ 
		MCI_PLAY_PARMS pp; 
		pp.dwCallback=NULL; 
		pp.dwFrom=0;      //��ʼ���ŵ�λ�� 
		mciSendCommand(op.wDeviceID,MCI_PLAY,MCI_NOTIFY,(DWORD)&pp);
		//�����ļ������������������ΪMCI_WAIT����򴰿ڻᱻ������Ϊ�˱����������������ΪMCI_NOTIFY 
	}
	//Sleep(cdlen);//�����ļ����ȵȴ�����MCI_WAITЧ��һ����cdlen�������Կ��Ʋ���ʱ��
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
	//��WM_CLOSE��Ϣ��������з���MCI_CLOSE����ر��豸
	MCI_GENERIC_PARMS gp; 
	gp.dwCallback=NULL; 
	mciSendCommand(op.wDeviceID,MCI_CLOSE,MCI_WAIT,(DWORD)&gp);  
}


void CCESDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	UpdateData(TRUE);
	idc_time_left = getOverplus_time(++overplus_time);
	if(overplus_time>=total_minutes*60){
		submit();
	}
    UpdateData(FALSE);
	CDialogEx::OnTimer(nIDEvent);
}


CString CCESDlg::getOverplus_time(int time_left)
{
	int sum = total_minutes*60 - time_left;
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
	INT_PTR nRes; 
	nRes = MessageBox(_T("�ύ֮�����ı��ο��Խ���������ȷ���ύ��"), _T("��ʾ"), MB_OKCANCEL | MB_ICONQUESTION); 
	if (IDCANCEL == nRes)   
        return;
	
	submit();
}

void CCESDlg::submit(){
	last_score = getScore();
	UpdateData(TRUE);
	CString t;
	t.Format(L"�����εĳɼ�Ϊ��\n ׼ȷ�ʣ�%.2f %% \n �ٶȣ�%.2f��/���� \n �ɼ���%.2f",last_accuracy*100, last_speed, last_score);
	idc_time_left = t;
	KillTimer(1);
	UpdateData(FALSE);
	
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	bt_submit_button.EnableWindow(FALSE);
	bt_print_button.EnableWindow(TRUE);
	ed_answer_sheet.EnableWindow(FALSE);
	//ֹͣ����
	stopMusic();
}


//��ӡ�ɼ���
void CCESDlg::OnBnClickedPrintButton()
{
	if(create_pdf(val_tecket_number, val_id_number, last_accuracy,last_speed,last_score,val_answer_sheet)){
		MessageBox(_T("��ӡ�ɹ������ڳ����Ŀ¼�鿴�ļ���grade.pdf��"));
	}
}

/**
 * ��ȡ���ճɼ�
 */
double CCESDlg::getScore(){
	USES_CONVERSION;
	string str1 = T2A(( val_answer_sheet.GetBuffer()));
	string str2 = T2A(( right_answer.GetBuffer()));

	double accuracy = getAccuracy(str1,str2);
	//CString t;
	//t.Format(L"%f %f %f %f",percentage_accuracy,accuracy ,percentage_speed ,getSpeed());
	//MessageBox(t);
	return percentage_accuracy * accuracy + percentage_speed * getSpeed();
}

/**
 * ��ȡ׼ȷ��
 */
double CCESDlg::getAccuracy(string str1, string str2){
	//���������ַ����ĳ��ȡ� 
	int len1 = str1.length(); 
	str2 = str2.substr(1,str2.length());
	int len2 = str2.length(); 

	str2 = uncrypt(str2);
	//CString t;
	//t = uncrypt(str2).c_str();
	//MessageBox(t);

	//�������飬���ַ����ȴ�һ���ռ� 
	int **dif;
	dif = new int*[len1 + 1];
	for(int j=0;j<len1 + 1;j++){
		dif[j] = new int[len2 + 1];        
		//���ָ�������ÿ��ָ��Ԫ����ָ��һ�����顣
	}

	//����ֵ������B�� 
	for (int a = 0; a <= len1; a++) {
		dif[a][0] = a; 
	} 
	for (int a = 0; a <= len2; a++) { 
		dif[0][a] = a;
	} 
	//���������ַ��Ƿ�һ�����������ϵ�ֵ 
	int temp; 
	for (int i = 1; i <= len1; i++) {
		for (int j = 1; j <= len2; j++) {
			if (str1[i - 1] == str2[j - 1]) {
				temp = 0; 
			} else { 
				temp = 1; 
			} 
			//ȡ����ֵ����С�� 
			dif[i][j] = getMin(dif[i - 1][j - 1] + temp, dif[i][j - 1] + 1, dif[i - 1][j] + 1); 
		} 
	}
	double maxNumber = 1 - (float) dif[len1][len2] / 
		(str1.length() > str2.length()? str1.length():str2.length());
	for (int i=0;i<len1 + 1;i++){
		delete[] dif[i]; //�ȳ���ָ��Ԫ����ָ�������
	}                     
	delete[] dif; 
	last_accuracy = maxNumber;
	return maxNumber*100.0;
}  

//�õ���Сֵ 
int CCESDlg::getMin(int a, int b,int c) { 
	int min = 99999999; 
	if(a<min){
		min = a;
	}
	if(b<min){
		min = b;
	}
	if(c<min){
		min = c;
	}
	return min;
}

/**
 * ��ȡ�����ٶ�
 * �����ٶȺ�����ٶ��и����
 */
double CCESDlg::getSpeed(){
	int answer_sheet_length = val_answer_sheet.GetLength();
	double overplus_time_min = ((double)overplus_time)/60;
	CString t;
	//t.Format(L"%f",overplus_time_min);
	//MessageBox(t);
	double speedNow = answer_sheet_length / overplus_time_min;
	double max_speed = (double)max_spee;
	last_speed = speedNow;
	//t.Format(L"%f %f",speedNow ,max_speed);
	//MessageBox(t);

	if( speedNow <= max_speed){
		return speedNow;
	}else{
		return max_speed;
	}
}

/**
 * ����pdf
 */
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
		cs.Format(L"�����ֵ���ȷ����%.2f%%���ٶ���%.2f��/���ӣ����ο��Եĳɼ���%.2f��",accuracy_rate*100,typing_speed,grade);
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
