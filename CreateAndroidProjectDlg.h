#pragma once
#include "afxwin.h"
#include "ShowCmdDlg.h"

// CCreateAndroidProject �Ի���

class CCreateAndroidProjectDlg : public CDialog
{
	DECLARE_DYNAMIC(CCreateAndroidProjectDlg)

public:
	CCreateAndroidProjectDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCreateAndroidProjectDlg();

// �Ի�������
	enum { IDD = IDD_CREATEANDROIDPROJECT };

protected:
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	static DWORD WINAPI ThreadProc(LPVOID pParam);
	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnBnClickedBtnBrowser();
	CEdit _editProjectName;
	CEdit _editTargetID;
	CEdit _editOutputPath;
	CEdit _editPackageName;
	CEdit _editActivityName;
	CEdit _editSdkPath;
	//About the thread
	HANDLE hThread;
	DWORD dwThreadId;	
	bool _isRunning;
	//About the msg dlg
	CShowCmdDlg _msgDlg;
	//About the command
	Command _command;
	DWORD bytesRead;
	char buffer[MAX_SIZE];
	CString _strOutput;


	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnBrowserOutput();
	afx_msg void OnBnClickedCancel();
};
