#pragma once


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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
