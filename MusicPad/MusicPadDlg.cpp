
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
	ON_BN_CLICKED(IDC_ADD_NOTE_BUTTON, &CMusicPadDlg::OnBnClickedAddNoteButton)
	ON_BN_CLICKED(IDC_DELETE_BACK_BUTTON, &CMusicPadDlg::OnBnClickedDeleteBackButton)
	ON_COMMAND(ID_FILE_OPEN, &CMusicPadDlg::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, &CMusicPadDlg::OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, &CMusicPadDlg::OnFileSaveAs)
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

bool CMusicPadDlg::SaveInquiry(LPCTSTR info)
{
	if (m_modified)
	{
		CString text;
		if (info == NULL)
		{
			if (m_file_path.IsEmpty())
				text = _T("无标题 中的内容已更改，是否保存？");
			else
				text.Format(_T("“%s”文件中的内容已更改，是否保存？"), m_file_path);
		}
		else
		{
			text = info;
		}

		int rtn = MessageBox(text, NULL, MB_YESNOCANCEL | MB_ICONWARNING);
		switch (rtn)
		{
		case IDYES: return _OnFileSave();
		case IDNO: m_modified = false; break;
		default: return false;
		}
	}
	return true;
}

void CMusicPadDlg::SetTitle()
{
	CString title;
	if (!m_file_path.IsEmpty())
		title = m_file_path + _T(" - MusicPad");
	else
		title = _T("无标题 - MusicPad");
	if (m_modified)
		title = _T('*') + title;
	SetWindowText(title);
}

bool CMusicPadDlg::_OnFileSave()
{
	if (m_modified)		//只有在已更改过之后才保存
	{
		//已经打开过一个文件时就直接保存，还没有打开一个文件就弹出“另存为”对话框
		if (!m_file_path.IsEmpty())
		{
			if (m_music_source.SaveToFile(m_file_path))
			{
				m_modified = false;
				SetTitle();
				return true;
			}
			else
			{
				return _OnFileSaveAs();		//文件无法保存时弹出“另存为”对话框
			}
		}
		else
		{
			return _OnFileSaveAs();
		}
	}
	return false;
}

bool CMusicPadDlg::_OnFileSaveAs()
{
	//设置过滤器
	const wchar_t* szFilter = _T("MusicPad文件(*.mcs)|*.mcs|所有文件(*.*)|*.*||");
	//设置另存为时的默认文件名
	wstring file_name;
	if (!m_file_path.IsEmpty())
	{
		wstring file_path(m_file_path);
		size_t index = file_path.find_last_of(L'\\');
		file_name = file_path.substr(index + 1);
	}
	else
	{
		file_name = L"无标题";
	}
	//构造保存文件对话框
	CFileDialog fileDlg(FALSE, _T("mcs"), file_name.c_str(), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	//显示保存文件对话框
	if (IDOK == fileDlg.DoModal())
	{
		if (m_music_source.SaveToFile(fileDlg.GetPathName().GetString()))
		{
			m_file_path = fileDlg.GetPathName();	//另存为后，当前文件名为保存的文件名
			m_modified = false;
			SetTitle();					//用新的文件名设置标题
			return true;
		}
	}
	return false;
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
	m_note_list_ctrl.InsertColumn(3, _T("延长"), LVCFMT_LEFT, width0);		//插入第2列
	m_note_list_ctrl.InsertColumn(4, _T("升降调"), LVCFMT_LEFT, width0);		//插入第3列

	//m_music_source.AddNote(3, 0, 4);
	//m_music_source.AddNote(3, 0, 4);
	//m_music_source.AddNote(4, 0, 4);
	//m_music_source.AddNote(5, 0, 4);

	//m_music_source.AddNote(5, 0, 4);
	//m_music_source.AddNote(4, 0, 4);
	//m_music_source.AddNote(3, 0, 4);
	//m_music_source.AddNote(2, 0, 4);
	ShowNoteList();

	SetTitle();

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


void CMusicPadDlg::OnBnClickedAddNoteButton()
{
	// TODO: 在此添加控件通知处理程序代码
	CAddNoteDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		m_music_source.AddNote(dlg.GetNote());

		int index = m_music_source.GetNoteList().size() - 1;
		m_note_list_ctrl.InsertItem(index, CCommon::IntToString(dlg.GetNote().note));
		m_note_list_ctrl.SetItemText(index, 1, CCommon::IntToString(dlg.GetNote().octave));
		m_note_list_ctrl.SetItemText(index, 2, CCommon::IntToString(dlg.GetNote().type));
		m_note_list_ctrl.SetItemText(index, 3, CCommon::IntToString(dlg.GetNote().extend_half));
		m_note_list_ctrl.SetItemText(index, 4, CCommon::IntToString(dlg.GetNote().signature));

		m_modified = true;
		SetTitle();
	}
}


void CMusicPadDlg::OnBnClickedDeleteBackButton()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_music_source.GetNoteList().size() > 0)
	{
		m_music_source.GetNoteList().pop_back();
		m_note_list_ctrl.DeleteItem(m_music_source.GetNoteList().size());

		m_modified = true;
		SetTitle();
	}
}


void CMusicPadDlg::OnFileOpen()
{
	// TODO: 在此添加命令处理程序代码
	//打开新文件前询问用户是否保存
	if (!SaveInquiry())
		return;
	//设置过滤器
	LPCTSTR szFilter = _T("MusicPad文件(*.mcs)|*.mcs|所有文件(*.*)|*.*||");
	//构造打开文件对话框
	CFileDialog fileDlg(TRUE, _T("mcs"), NULL, 0, szFilter, this);
	//显示打开文件对话框
	if (IDOK == fileDlg.DoModal())
	{
		m_file_path = fileDlg.GetPathName();	//获取打开的文件路径
		m_music_source.LoadFromFile(m_file_path);					//打开文件
		SetTitle();								//设置窗口标题
		ShowNoteList();
	}
}


void CMusicPadDlg::OnFileSave()
{
	// TODO: 在此添加命令处理程序代码
	_OnFileSave();
}


void CMusicPadDlg::OnFileSaveAs()
{
	// TODO: 在此添加命令处理程序代码
	_OnFileSaveAs();
}
