// CreateAndroidProject.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "logcatTool.h"
#include "CreateAndroidProjectDlg.h"
#include "afxdialogex.h"



void ReadFromFile(CString &projectName,
	CString &targetID,
	CString &outputPath,
	CString &packageName,
	CString &activityName,
	CString &sdkPath)
{
	Config::ReadConfig("projectName",projectName.GetBuffer(1024));
	projectName.ReleaseBuffer();
	Config::ReadConfig("targetID",targetID.GetBuffer(1024));
	targetID.ReleaseBuffer();
	Config::ReadConfig("outputPath",outputPath.GetBuffer(1024));
	outputPath.ReleaseBuffer();
	Config::ReadConfig("packageName",packageName.GetBuffer(1024));
	packageName.ReleaseBuffer();
	Config::ReadConfig("activityName",activityName.GetBuffer(1024));
	activityName.ReleaseBuffer();
	Config::ReadConfig("sdkPath",sdkPath.GetBuffer(1024));
	sdkPath.ReleaseBuffer();
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
// CCreateAndroidProject �Ի���

IMPLEMENT_DYNAMIC(CCreateAndroidProjectDlg, CDialog)


CCreateAndroidProjectDlg::CCreateAndroidProjectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCreateAndroidProjectDlg::IDD, pParent)
{
	
}
BOOL CCreateAndroidProjectDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
 CString projectName = "";
	CString targetID = "";
	CString outputPath = "";
	CString packageName = "";
	CString activityName = "";
	CString sdkPath = "";

	ReadFromFile(projectName,targetID,outputPath,packageName,activityName,sdkPath);

	_editProjectName.SetWindowText(projectName);
	_editTargetID.SetWindowText(targetID);
	_editOutputPath.SetWindowText(outputPath);
	_editPackageName.SetWindowText(packageName);
	_editActivityName.SetWindowText(activityName);
	_editSdkPath.SetWindowText(sdkPath);
    /////////////////////////////////////////////////////////////////////
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}
CCreateAndroidProjectDlg::~CCreateAndroidProjectDlg()
{
}

void CCreateAndroidProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, _editProjectName);
	DDX_Control(pDX, IDC_EDIT2, _editTargetID);
	DDX_Control(pDX, IDC_EDIT3, _editOutputPath);
	DDX_Control(pDX, IDC_EDIT4, _editPackageName);
	DDX_Control(pDX, IDC_EDIT5, _editActivityName);
	DDX_Control(pDX, IDC_EDIT6, _editSdkPath);
}


BEGIN_MESSAGE_MAP(CCreateAndroidProjectDlg, CDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_BROWSER, &CCreateAndroidProjectDlg::OnBnClickedBtnBrowser)
	ON_BN_CLICKED(IDOK, &CCreateAndroidProjectDlg::OnBnClickedOk)	
	ON_BN_CLICKED(IDC_BTN_BROWSER_OUTPUT, &CCreateAndroidProjectDlg::OnBnClickedBtnBrowserOutput)
	ON_BN_CLICKED(IDCANCEL, &CCreateAndroidProjectDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CCreateAndroidProject ��Ϣ�������


void CCreateAndroidProjectDlg::OnBnClickedBtnBrowser()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ��ȡ�ض��ļ��е�LPITEMIDLIST�����Խ�֮���ΪHANDLE
	// ��ν���ض��ļ���,�������CSIDL_XXX������֮��
	LPITEMIDLIST rootLoation;
	SHGetSpecialFolderLocation( NULL, CSIDL_DESKTOP, &rootLoation );
	if ( rootLoation == NULL ) {
	   // unkown error
	   // return
	}
	// ���öԻ���
	BROWSEINFO bi;
	ZeroMemory( &bi, sizeof( bi ) );
	bi.pidlRoot = rootLoation; // �ļ��жԻ���֮��Ŀ¼����ָ���Ļ���Ϊ�ҵĵ���
	bi.lpszTitle = _T( "�Ի���̧ͷ" ); // ���Բ�ָ��
	// bi.ulFlags = BIF_EDITBOX | BIF_RETURNONLYFSDIRS;

	// �򿪶Ի���, �е���DoModal
	LPITEMIDLIST targetLocation = SHBrowseForFolder( &bi );
	if ( targetLocation != NULL ) {
	   TCHAR targetPath[ MAX_PATH ];
	   SHGetPathFromIDList( targetLocation, targetPath );
	   _editSdkPath.SetWindowText(targetPath);
	   // MessageBox( targetPath );
	 //  Util::LOG(L"Browser clicked %s",targetPath);
	}
	
}
DWORD WINAPI CCreateAndroidProjectDlg::ThreadProc(LPVOID pParam)
{
	CCreateAndroidProjectDlg* dlg = (CCreateAndroidProjectDlg*)pParam;    
	dlg->_isRunning = true;
	while(dlg->_isRunning){
		Sleep(10);		
		//Util::LOG("i=%d",i);
		/*CString tmp = "";
		tmp.Format("i=%d",i);
		dlg->_msgDlg._editOutput.SetWindowText(tmp);*/
		 if (dlg->_command.ReadCommand(dlg->buffer,&dlg->bytesRead) == NULL)  //��ȡ�ܵ�
		break;

		char *tmp_buffer = new char[dlg->bytesRead];
		memcpy(tmp_buffer,dlg->buffer,dlg->bytesRead);

		CString tmp ;
		//Util::UTF8ToGBK(tmp,tmp_buffer);	
		dlg->_strOutput.Append(tmp_buffer);

		dlg->_msgDlg._editOutput.SetWindowText(dlg->_strOutput);
		delete tmp_buffer;
	}
	
	return 0;
}


void CCreateAndroidProjectDlg::OnBnClickedOk()
{	
	_strOutput = "";
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


	
	CString tmp="";
	tmp.Format("%s\\tools\\android.bat create project -n %s -t %s -p %s -k %s -a %s",
		sdkPath,projectName,targetID,outputPath,packageName,activityName);
	Util::LOG(tmp);
	_command.WriteCommand(tmp);
	//�������߳�
	hThread = CreateThread(NULL, // default security attributes 
                            0, // use default stack size 
                           ThreadProc, // thread function 
                            this, // argument to thread function 
                            0, // use default creation flags 
                            &dwThreadId);  
		
	_msgDlg.DoModal();	
}


void CCreateAndroidProjectDlg::OnBnClickedBtnBrowserOutput()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	LPITEMIDLIST rootLoation;
	SHGetSpecialFolderLocation( NULL, CSIDL_DESKTOP, &rootLoation );
	if ( rootLoation == NULL ) {
	   // unkown error
	   // return
	}
	// ���öԻ���
	BROWSEINFO bi;
	ZeroMemory( &bi, sizeof( bi ) );
	bi.pidlRoot = rootLoation; // �ļ��жԻ���֮��Ŀ¼����ָ���Ļ���Ϊ�ҵĵ���
	bi.lpszTitle = _T( "�Ի���̧ͷ" ); // ���Բ�ָ��
	// bi.ulFlags = BIF_EDITBOX | BIF_RETURNONLYFSDIRS;

	// �򿪶Ի���, �е���DoModal
	LPITEMIDLIST targetLocation = SHBrowseForFolder( &bi );
	if ( targetLocation != NULL ) {
	   TCHAR targetPath[ MAX_PATH ];
	   SHGetPathFromIDList( targetLocation, targetPath );
	   _editOutputPath.SetWindowText(targetPath);
	   // MessageBox( targetPath );
	 //  Util::LOG(L"Browser clicked %s",targetPath);
	}
}


void CCreateAndroidProjectDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	_isRunning = false;
	CDialog::OnCancel();
}

void CCreateAndroidProjectDlg::OnClose()
{
	CDialog::OnClose();
	_isRunning = false;
}
