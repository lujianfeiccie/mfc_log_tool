// ShowCmd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "logcatTool.h"
#include "ShowCmdDlg.h"
#include "afxdialogex.h"


// CShowCmdDlg �Ի���

IMPLEMENT_DYNAMIC(CShowCmdDlg, CDialog)

CShowCmdDlg::CShowCmdDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShowCmdDlg::IDD, pParent)
{

}

CShowCmdDlg::~CShowCmdDlg()
{
}

void CShowCmdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, _editOutput);
}


BEGIN_MESSAGE_MAP(CShowCmdDlg, CDialog)		
END_MESSAGE_MAP()

// CShowCmdDlg ��Ϣ�������
