#pragma once
#include "afxwin.h"


// CCreateAndroidProject 对话框

class CCreateAndroidProject : public CDialog
{
	DECLARE_DYNAMIC(CCreateAndroidProject)

public:
	CCreateAndroidProject(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCreateAndroidProject();

// 对话框数据
	enum { IDD = IDD_CREATEANDROIDPROJECT };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnBnClickedBtnBrowser();
	CEdit _editProjectName;
	CEdit _editTargetID;
	CEdit _editOutputPath;
	CEdit _editPackageName;
	CEdit _editActivityName;
	CEdit _editSdkPath;
	afx_msg void OnBnClickedOk();
};
