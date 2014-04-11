// logcatToolDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#define MAX_SIZE 1024*10

// ClogcatToolDlg �Ի���
class ClogcatToolDlg : public CDialog
{
// ����
public:
	SECURITY_ATTRIBUTES sa;
	HANDLE hRead,hWrite; 
	char buffer[MAX_SIZE];
	DWORD bytesRead;
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
public:
	CEdit _strOutput;
public:
	CListCtrl _list1;
public:
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
public:
	CEdit _strInput;

	void InsertItem(CString item);
};
