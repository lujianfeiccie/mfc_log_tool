#pragma once
#include "afxwin.h"


// CShowCmdDlg �Ի���

class CShowCmdDlg : public CDialog
{
	DECLARE_DYNAMIC(CShowCmdDlg)

public:
	CShowCmdDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CShowCmdDlg();
	 
// �Ի�������
	enum { IDD = IDD_SHOWCMD };
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit _editOutput;
};
