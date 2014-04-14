// logcatToolDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "logcatTool.h"
#include "logcatToolDlg.h"

#define WM_MY_UPDATE WM_USER+1 // do something
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define APP_NAME "APP_NAME"
#define FILE_NAME "config.ini"
#define KEY_NAME "tag"
#define KEY_NAME_COUNT "count"
#define INI_MAX_COUNT 5
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
void WriteDataToFile(CString keyName,CString keyValue){

	///////////////��ȡ��ǰ�ļ���·��//////////////////////
	char bufferCurDir[1024];
	GetCurrentDirectory(1024,bufferCurDir);
	strcat(bufferCurDir,"\\");
	strcat(bufferCurDir,FILE_NAME);
	////////////////////////////////////////////////////////

  WritePrivateProfileString(APP_NAME,keyName,keyValue,bufferCurDir);
}
CString ReadDataFromFile(CString keyName){
	CString result = "";

	///////////////��ȡ��ǰ�ļ���·��//////////////////////
	char bufferCurDir[1024];
	GetCurrentDirectory(1024,bufferCurDir);
	strcat(bufferCurDir,"\\");
	strcat(bufferCurDir,FILE_NAME);
	///////////////////////////////////////////////////////

  char returnValue[1024];
  GetPrivateProfileString(APP_NAME,keyName,"",returnValue,1024,bufferCurDir);
  result.Append(returnValue);
  return result;
}

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// ClogcatToolDlg �Ի���




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
END_MESSAGE_MAP()


// ClogcatToolDlg ��Ϣ�������

BOOL ClogcatToolDlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	//////////////////////����style///////////////////////////////////
	CString cmd = "adb logcat -s myGLRenderer:V";
	SetDlgItemText(IDC_EDIT_CMD,cmd);

	 LONG lStyle;
      lStyle = GetWindowLong(_list1.m_hWnd, GWL_STYLE);//��ȡ��ǰ����style
      lStyle &= ~LVS_TYPEMASK; //�����ʾ��ʽλ
      lStyle |= LVS_REPORT; //����style
      SetWindowLong(_list1.m_hWnd, GWL_STYLE, lStyle);//����style
	/////////////////////////////////////////////////////////////////////

	////////////////////////////����һ��////////////////////////////////
	 _list1.InsertColumn(0,"tag",0,500);
	 
	 
	 /////////////////////////////���ļ�///////////////////////////////////
	 int n = _ttoi(ReadDataFromFile(KEY_NAME_COUNT));	 	 
	 for(int i=0;i<n;i++)
	 {
		 CString keyname = "";	
		 keyname.Format("%s%i",KEY_NAME,n-i-1);
		 CString item = ReadDataFromFile(keyname);
		 _list1.InsertItem(0,item);
	 }
    /////////////////////////////////////////////////////////////////////
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void ClogcatToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR ClogcatToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HANDLE hThread; 
DWORD dwThreadId, dwThrdParam = 1; 


DWORD WINAPI ThreadProc(LPVOID pParam)
{
	ClogcatToolDlg* dlg = (ClogcatToolDlg*)pParam;    
	dlg->_isRunning = true;

	while (dlg->_isRunning) 
	{
	  if (dlg->_command.ReadCommand(dlg->buffer,&dlg->bytesRead) == NULL)  //��ȡ�ܵ�
	   break;
  
 		char *tmp_buffer = new char[dlg->bytesRead];
		memcpy(tmp_buffer,dlg->buffer,dlg->bytesRead);

		CString tmp ;
		Util::UTF8ToGBK(tmp,tmp_buffer);	
		dlg->strOutput.Append(tmp);

		delete tmp_buffer;

		SendMessage(dlg->m_hWnd, WM_MY_UPDATE, (WPARAM) 0, (LPARAM) 0);  
		Sleep(10);    
	}  
	dlg->_command.CloseRead();
	return 0;
}
LRESULT ClogcatToolDlg::DoUpdate(WPARAM iParam1,LPARAM iParam2){	
	_strOutput.SetWindowTextA(strOutput);
	int index=_strOutput.GetLineCount();//��õ�ǰList�ؼ�һ��������
	_strOutput.LineScroll(index,0);//����ֱ���������������һ��
	UpdateWindow();
 return 0;
}
//ʵ��edit controlȫѡ
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
			Util::LOG("Ctrl + A");			
		}
		break;
		}
	}
return CDialog::PreTranslateMessage(pMsg);
}

void ClogcatToolDlg::OnBnClickedOk()
{
	///////////////////�������//////////////////////////
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

	//�������߳�
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
	_isRunning = false;
}


void ClogcatToolDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if(pNMListView->uChanged==LVIF_STATE)
	{
	if(pNMListView->uNewState & LVIS_SELECTED)
	   {
		//��������
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

	 /////////////////��һ�������ж�//////////////////
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
