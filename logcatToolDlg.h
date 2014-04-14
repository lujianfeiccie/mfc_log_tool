// logcatToolDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "Command.h"

// ClogcatToolDlg 对话框
class ClogcatToolDlg : public CDialog
{
// 构造
public:
	Command _command;
	DWORD bytesRead;
	char buffer[MAX_SIZE];
	CString strOutput;
	LRESULT DoUpdate(WPARAM iParam1,LPARAM iParam2);
	bool _isRunning;
	ClogcatToolDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_LOGCATTOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedEnd();

	//实现Ctrl+A全选
	afx_msg BOOL PreTranslateMessage(MSG* pMsg);
public:
	CListCtrl _list1;
public:
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
public:
	CEdit _strInput;
	CEdit _strOutput;
	void InsertItem(CString item);
};
