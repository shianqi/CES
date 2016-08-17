
// CESDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


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
};
