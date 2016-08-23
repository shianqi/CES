
// CESDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include <string>
#include "TransformPlus.h"
#include "CESAdminDlg.h"
using namespace std;


// CCESDlg 对话框
class CCESDlg : public CDialogEx
{
// 构造
public:
	CCESDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CES_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CButton bt_begin_test;
	afx_msg void OnBnClickedBeginTest();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int overplus_time;
	CString getOverplus_time(int time_left);
	CString idc_time_left;
	CString val_tecket_number;
	CString val_id_number;
	void readIni();
	bool check_ticket_number(CString ticketNumber);
	bool check_id_number(CString idNumber);
	CString val_question_number;
	CString val_answer_sheet;
	CEdit ed_answer_sheet;
	CEdit ed_ticket_number;
	CEdit ed_id_number;
	CComboBox cb_question_number;
	CButton bt_submit_button;
	CButton bt_print_button;
	afx_msg void OnBnClickedSubmitButton();
	void submit();
	afx_msg void OnBnClickedPrintButton();

	//音乐模块
	void playMusic();
	DWORD getInfo(UINT wDeviceID,DWORD item);
	void stopMusic();

	//计算成绩模块
	double getScore(); 
	double getSpeed();
	int getMin(int a, int b,int c);
	double getAccuracy(string str1, string str2);

	double last_score;
	double last_speed;
	double last_accuracy;

	//答案读模块
	bool readAnswer(CString str);
	CString right_answer;

	//答案加密模块
	string encrypt(string str);
	string uncrypt(string str);

	//pdf模块
	bool create_pdf(CString val_ticket_number, CString val_id_number, double accuracy_rate, double typing_speed, double grade, CString text);
	
	//类型转换模块
	TransformPlus transformPlus;

	//读取配置文件模块
	int total_minutes;
	int total_questions;
	int max_spee;
	double percentage_accuracy;
	double percentage_speed;
	CString audio_format;

//	afx_msg void OnChangeTicketNumber();
	afx_msg void OnBnClickedButtonAdmin();
};
