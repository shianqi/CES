#pragma once
#include "TransformPlus.h"

// CCESAdminDlg �Ի���

class CCESAdminDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCESAdminDlg)

public:
	CCESAdminDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCESAdminDlg();

// �Ի�������
	enum { IDD = IDD_CESADMINDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	void init();

	TransformPlus transformPlus;

	//������Ϣ
	int total_minutes;
	int total_questions;
	int max_spee;
	double percentage_accuracy;
	double percentage_speed;
	CString audio_format;

	int val_total_minutes;
	int val_total_questions;
	CString val_audio_format;
	int val_max_speed;
	double val_percentage_accuracy;
	double val_percentage_speed;
};
