// CreateAndroidProject.cpp : 实现文件
//

#include "stdafx.h"
#include "logcatTool.h"
#include "CreateAndroidProject.h"
#include "afxdialogex.h"


// CCreateAndroidProject 对话框

IMPLEMENT_DYNAMIC(CCreateAndroidProject, CDialog)

CCreateAndroidProject::CCreateAndroidProject(CWnd* pParent /*=NULL*/)
	: CDialog(CCreateAndroidProject::IDD, pParent)
{

}

CCreateAndroidProject::~CCreateAndroidProject()
{
}

void CCreateAndroidProject::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCreateAndroidProject, CDialog)
END_MESSAGE_MAP()


// CCreateAndroidProject 消息处理程序
