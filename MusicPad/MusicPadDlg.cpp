
// MusicPadDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MusicPad.h"
#include "MusicPadDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMusicPadDlg 对话框



CMusicPadDlg::CMusicPadDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_MUSICPAD_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMusicPadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_NOTE_LIST, m_note_list_ctrl);
}

BEGIN_MESSAGE_MAP(CMusicPadDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_PLAY_BUTTON, &CMusicPadDlg::OnBnClickedPlayButton)
END_MESSAGE_MAP()


// CMusicPadDlg 消息处理程序

void CMusicPadDlg::ShowNoteList()
{
	m_note_list_ctrl.DeleteAllItems();
	int index = 0;
	for (const auto& note : m_music_source.GetNoteList())
	{
		m_note_list_ctrl.InsertItem(index, CCommon::IntToString(note.note));
		m_note_list_ctrl.SetItemText(index, 1, CCommon::IntToString(note.octave));
		m_note_list_ctrl.SetItemText(index, 2, CCommon::IntToString(note.type));
		m_note_list_ctrl.SetItemText(index, 3, CCommon::IntToString(note.extend_half));
		m_note_list_ctrl.SetItemText(index, 4, CCommon::IntToString(note.signature));
		index++;
	}
}

BOOL CMusicPadDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	//初始化音符列表控件
	m_note_list_ctrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	int width0;
	width0 = theApp.DPI(50);
	//CRect rect;
	//GetWindowRect(rect);
	//width1 = rect.Width() - width0 - width2 - DPI(21);
	m_note_list_ctrl.InsertColumn(0, _T("音符"), LVCFMT_LEFT, width0);		//插入第1列
	m_note_list_ctrl.InsertColumn(1, _T("八度"), LVCFMT_LEFT, width0);		//插入第2列
	m_note_list_ctrl.InsertColumn(2, _T("类型"), LVCFMT_LEFT, width0);		//插入第3列
	m_note_list_ctrl.InsertColumn(3, _T("时值延长"), LVCFMT_LEFT, width0);		//插入第2列
	m_note_list_ctrl.InsertColumn(4, _T("升降调"), LVCFMT_LEFT, width0);		//插入第3列

	m_music_source.AddNote(3, 0, 4);
	m_music_source.AddNote(3, 0, 4);
	m_music_source.AddNote(4, 0, 4);
	m_music_source.AddNote(5, 0, 4);

	m_music_source.AddNote(5, 0, 4);
	m_music_source.AddNote(4, 0, 4);
	m_music_source.AddNote(3, 0, 4);
	m_music_source.AddNote(2, 0, 4);
	ShowNoteList();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMusicPadDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMusicPadDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
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

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMusicPadDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMusicPadDlg::OnBnClickedPlayButton()
{
	// TODO: 在此添加控件通知处理程序代码
	m_music_note.PlayMusicSource(m_music_source.GetNoteList());
}
