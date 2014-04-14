// CreateAndroidProject.cpp : 实现文件
//

#include "stdafx.h"
#include "logcatTool.h"
#include "CreateAndroidProject.h"
#include "afxdialogex.h"
#include "Config.h"
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
	DDX_Control(pDX, IDC_EDIT1, _editProjectName);
	DDX_Control(pDX, IDC_EDIT2, _editTargetID);
	DDX_Control(pDX, IDC_EDIT3, _editOutputPath);
	DDX_Control(pDX, IDC_EDIT4, _editPackageName);
	DDX_Control(pDX, IDC_EDIT5, _editActivityName);
	DDX_Control(pDX, IDC_EDIT6, _editSdkPath);
}


BEGIN_MESSAGE_MAP(CCreateAndroidProject, CDialog)	
	ON_BN_CLICKED(IDC_BTN_BROWSER, &CCreateAndroidProject::OnBnClickedBtnBrowser)
	ON_BN_CLICKED(IDOK, &CCreateAndroidProject::OnBnClickedOk)
END_MESSAGE_MAP()


// CCreateAndroidProject 消息处理程序


void CCreateAndroidProject::OnBnClickedBtnBrowser()
{
	// TODO: 在此添加控件通知处理程序代码
	Util::LOG("Browser clicked");
}
void WriteToFile(CString projectName,
	CString targetID,
	CString outputPath,
	CString packageName,
	CString activityName,
	CString sdkPath)
{
	Config::WriteConfig("projectName",projectName);
	Config::WriteConfig("targetID",targetID);
	Config::WriteConfig("outputPath",outputPath);
	Config::WriteConfig("packageName",packageName);
	Config::WriteConfig("activityName",activityName);
	Config::WriteConfig("sdkPath",sdkPath);
}
void CCreateAndroidProject::OnBnClickedOk()
{	
	CString projectName = "";
	CString targetID = "";
	CString outputPath = "";
	CString packageName = "";
	CString activityName = "";
	CString sdkPath = "";
	_editProjectName.GetWindowTextA(projectName);
	_editTargetID.GetWindowTextA(targetID);
	_editOutputPath.GetWindowTextA(outputPath);
	_editPackageName.GetWindowTextA(packageName);
	_editActivityName.GetWindowTextA(activityName);
	_editSdkPath.GetWindowTextA(sdkPath);

	WriteToFile(projectName,targetID,outputPath,packageName,activityName,sdkPath);
	Util::LOG("projectName=%s targetID=%s outputPath=%s packageName=%s activityName=%s sdkPath=%s",
		projectName,targetID,outputPath,packageName,activityName,sdkPath);
}
