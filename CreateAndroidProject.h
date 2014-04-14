#pragma once


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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
