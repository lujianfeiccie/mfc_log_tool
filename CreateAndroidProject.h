#pragma once
#include "afxwin.h"


// CCreateAndroidProject �Ի���

class CCreateAndroidProject : public CDialog
{
	DECLARE_DYNAMIC(CCreateAndroidProject)

public:
	CCreateAndroidProject(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCreateAndroidProject();

// �Ի�������
	enum { IDD = IDD_CREATEANDROIDPROJECT };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
