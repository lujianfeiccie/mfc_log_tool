// logcatToolDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "Command.h"

// ClogcatToolDlg �Ի���
class ClogcatToolDlg : public CDialog
{
// ����
public:
	Command _command;
	DWORD bytesRead;
	char buffer[MAX_SIZE];
	CString strOutput;
	LRESULT DoUpdate(WPARAM iParam1,LPARAM iParam2);
	bool _isRunning;
	ClogcatToolDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_LOGCATTOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedEnd();

	//ʵ��Ctrl+Aȫѡ
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
