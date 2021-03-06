#pragma once
#include "TransformPlus.h"
#include "afxwin.h"

// CCESAdminDlg 对话框

class CCESAdminDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCESAdminDlg)

public:
	CCESAdminDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCESAdminDlg();
	virtual BOOL OnInitDialog();

// 对话框数据
	enum { IDD = IDD_CESADMINDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	void init();

	TransformPlus transformPlus;

	//配置信息
	int total_minutes;
	int total_questions;
	int max_spee;
	double percentage_accuracy;
	double percentage_speed;
	CString audio_format;

	CString right_answer;

	int val_total_minutes;
	int val_total_questions;
	CString val_audio_format;
	int val_max_speed;
	double val_percentage_accuracy;
	double val_percentage_speed;
	CComboBox cb2_question_number;
	CString val2_question_number;
	afx_msg void OnCbnSelchangeCombo1();
	CString val_right_answer;
	void getAnswer(CString str);
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	string encrypt(string str);
	string uncrypt(string str);
	CString val_audio_path;
};
