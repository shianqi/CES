
// CESDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CCESDlg �Ի���
class CCESDlg : public CDialogEx
{
// ����
public:
	CCESDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CES_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
};
