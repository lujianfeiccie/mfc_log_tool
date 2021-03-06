// logcatToolDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "logcatTool.h"
#include "logcatToolDlg.h"
#include "CreateAndroidProjectDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define KEY_NAME "tag"
#define KEY_NAME_UTF8_TO_GBK "utf8_to_gbk"
#define KEY_NAME_COUNT "count"
#define INI_MAX_COUNT 5
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
void WriteDataToFile(CString keyName,CString keyValue){
  Config::WriteConfig(keyName,keyValue);
}
CString ReadDataFromFile(CString keyName){
	CString result = "";
	Config::ReadConfig(keyName,result.GetBuffer(1024));	
	result.ReleaseBuffer();
  return result;
}

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// ClogcatToolDlg 对话框




ClogcatToolDlg::ClogcatToolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ClogcatToolDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void ClogcatToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_OUTPUT, _strOutput);
	DDX_Control(pDX, IDC_LIST1, _list1);
	DDX_Control(pDX, IDC_EDIT_CMD, _strInput);
	DDX_Control(pDX, IDC_CHECK1, _cbxFromUtf8ToGBK);
}

BEGIN_MESSAGE_MAP(ClogcatToolDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_MY_UPDATE,DoUpdate)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDOK, &ClogcatToolDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_END, &ClogcatToolDlg::OnBnClickedEnd)	
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &ClogcatToolDlg::OnLvnItemchangedList1)
	ON_COMMAND(ID_ANDROID32771, &ClogcatToolDlg::OnMenuCreateAndroidProj)
END_MESSAGE_MAP()


// ClogcatToolDlg 消息处理程序

BOOL ClogcatToolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	//////////////////////设置style///////////////////////////////////	
	_strInput.SetWindowText("dir");

	 LONG lStyle;
      lStyle = GetWindowLong(_list1.m_hWnd, GWL_STYLE);//获取当前窗口style
      lStyle &= ~LVS_TYPEMASK; //清除显示方式位
      lStyle |= LVS_REPORT; //设置style
      SetWindowLong(_list1.m_hWnd, GWL_STYLE, lStyle);//设置style
	/////////////////////////////////////////////////////////////////////

	////////////////////////////放入一列////////////////////////////////
	 _list1.InsertColumn(0,"tag",0,500);
	 
	 
	 /////////////////////////////读文件///////////////////////////////////
	 int n = _ttoi(ReadDataFromFile(KEY_NAME_COUNT));	 	 
	 for(int i=0;i<n;i++)
	 {
		 CString keyname = "";	
		 keyname.Format("%s%i",KEY_NAME,n-i-1);
		 CString item = ReadDataFromFile(keyname);
		 _list1.InsertItem(0,item);
	 }
	 CString utf8_to_gbk = ReadDataFromFile(KEY_NAME_UTF8_TO_GBK);
	 if("1"==utf8_to_gbk)
	 {
		 _cbxFromUtf8ToGBK.SetCheck(1);
	 }
	 else
	 {
		 _cbxFromUtf8ToGBK.SetCheck(0);
	 }
	 
    /////////////////////////////////////////////////////////////////////
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void ClogcatToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void ClogcatToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR ClogcatToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HANDLE hThread; 
DWORD dwThreadId, dwThrdParam = 1; 


DWORD WINAPI ClogcatToolDlg::ThreadProc(LPVOID pParam)
{
	ClogcatToolDlg* dlg = (ClogcatToolDlg*)pParam;    
	dlg->_isRunning = true;

	while (dlg->_isRunning) 
	{
	  if (dlg->_command.ReadCommand(dlg->buffer,&dlg->bytesRead) == NULL)  //读取管道
	   break;
  
 		char *tmp_buffer = new char[dlg->bytesRead];
		memcpy(tmp_buffer,dlg->buffer,dlg->bytesRead);

		if(1==dlg->_cbxFromUtf8ToGBK.GetCheck()) //判断是否需要转码
		{
			CString tmp ;
			Util::UTF8ToGBK(tmp,tmp_buffer);	
			dlg->strOutput.Append(tmp);
		}
		else
		{
			dlg->strOutput.Append(tmp_buffer);
		}
		delete tmp_buffer;

		SendMessageW(dlg->m_hWnd, WM_MY_UPDATE, (WPARAM) 0, (LPARAM) 0);  
		Sleep(10);    
	}  
	dlg->_command.CloseRead();
	return 0;
}
LRESULT ClogcatToolDlg::DoUpdate(WPARAM iParam1,LPARAM iParam2){	
	_strOutput.SetWindowText(strOutput);
	int index=_strOutput.GetLineCount();//获得当前List控件一共多少行
	_strOutput.LineScroll(index,0);//将垂直滚动条滚动到最后一行
	UpdateWindow();
 return 0;
}
//实现edit control全选
BOOL ClogcatToolDlg::PreTranslateMessage(MSG* pMsg)
{
// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message==WM_KEYDOWN)
	{
	BOOL bCtrl=::GetKeyState(VK_CONTROL)&0x8000;
	BOOL bShift=::GetKeyState(VK_SHIFT)&0x8000;

	// only gets here if CTRL key is pressed
	BOOL bAlt=::GetKeyState(VK_MENU)&0x8000;
	
	Util::LOG("Ctrl=%d Shift=%d Alt=%d Keycode=%d",bCtrl,bShift,bAlt,pMsg->wParam);
	switch( pMsg->wParam )
	{
		
		case 'A':
		if (bCtrl){
			_strInput.SetSel(0,-1);
			_strOutput.SetSel(0,-1);
			Util::LOG("Ctrl + A");			
		}
		break;
		}
	}
return CDialog::PreTranslateMessage(pMsg);
}

void ClogcatToolDlg::OnBnClickedOk()
{
	///////////////////添加数据//////////////////////////
	CString cmd;
	_strInput.GetWindowTextA(cmd);
	InsertItem(cmd);
	UpdateWindow();
	/////////////////////////////////////////////////////
	strOutput = "";
	_strOutput.SetWindowTextA("");

	_command.WriteCommand(cmd);
	_command.CloseWrite();


	memset(buffer,0,MAX_SIZE);
 
	_isRunning = false;

	//开启读线程
	hThread = CreateThread(NULL, // default security attributes 
                            0, // use default stack size 
                           ThreadProc, // thread function 
                            this, // argument to thread function 
                            0, // use default creation flags 
                            &dwThreadId);  
	
}
void ClogcatToolDlg::OnBnClickedEnd()
{
	system("adb logcat -c");
	_isRunning = false;
	Util::LOG("END");
}
void ClogcatToolDlg::OnClose()
{
CDialog::OnClose();
_isRunning = false;

//MessageBox("onClose");
 int n=_list1.GetItemCount();
 if(n>INI_MAX_COUNT){
	 n = INI_MAX_COUNT;
 }
 CString strN = "";
 strN.Format("%d",n);
 WriteDataToFile(KEY_NAME_COUNT,strN);
 for(int i=0;i<n;i++)
 {
	 CString keyname = "";	
	 keyname.Format("%s%i",KEY_NAME,i);
	 WriteDataToFile(keyname,_list1.GetItemText(i,0));
 }

 int utf8_to_gbk = _cbxFromUtf8ToGBK.GetCheck();
 strN.Format("%d",utf8_to_gbk);
 WriteDataToFile(KEY_NAME_UTF8_TO_GBK,strN);
	
}


void ClogcatToolDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if(pNMListView->uChanged==LVIF_STATE)
	{
	if(pNMListView->uNewState & LVIS_SELECTED)
	   {
		//处理内容
		int nItem=pNMListView->iItem;
		CString value =_list1.GetItemText(nItem,0);
		_strInput.SetWindowTextA(value);
		Util::LOG(value);
		 
	   }
	}

	*pResult = 0;
}
void ClogcatToolDlg::InsertItem(CString item){
	 int n = _list1.GetItemCount();

	 /////////////////做一个存在判断//////////////////
	 bool isExist = false;
	 for(int i=0;i<n;i++){
		 CString temp = _list1.GetItemText(i,0);
		 if(temp == item){
			 isExist = true;
			break;
		 }
	 }

	 if(!isExist){
		 if(n >= INI_MAX_COUNT){
			 _list1.DeleteItem(n-1);
		 }
		_list1.InsertItem(0,item);
	 }
}


void ClogcatToolDlg::OnMenuCreateAndroidProj()
{
	// TODO: 在此添加命令处理程序代码
	CCreateAndroidProjectDlg dlg;
	dlg.DoModal();

	Util::LOG("OnMenuCreateAndroidProj");
}
