#pragma once
#include "afxwin.h"


// CShowCmdDlg 对话框

class CShowCmdDlg : public CDialog
{
	DECLARE_DYNAMIC(CShowCmdDlg)

public:
	CShowCmdDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CShowCmdDlg();
	 
// 对话框数据
	enum { IDD = IDD_SHOWCMD };
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit _editOutput;
};
